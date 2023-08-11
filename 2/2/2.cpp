#include <iostream>
#include <atomic>
#include <thread>
#include <windows.h>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex m;

auto now() { return std::chrono::steady_clock::now(); }

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif // _WIN32
}

void gotoXY(short column, short line)
{
    COORD coord{column, line};
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        return { 0, 0 };
    }
}

void printProgress()
{

}

class Download
{
public:
    Download(short line_num) : _line_num(line_num)
    {
        printProgress();
    }

    ~Download()
    {}

    void printProgress()
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(handle, &structCursorInfo);
        structCursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(handle, &structCursorInfo);

        const auto start{ now() };
        std::unique_lock<std::mutex> lk(m);
        gotoXY(0, _line_num);
        std::cout << _line_num << "\t" << std::this_thread::get_id() << "\t[";
        COORD progress_start_pos = GetConsoleCursorPosition(handle);
        _progress_pos = { progress_start_pos.X, _line_num };
        std::cout << "----------] ";
        COORD persent_pos = GetConsoleCursorPosition(handle);
        std::cout << 0 << "%";

        for (int i = 1; i < 101; ++i)
        {
            lk.unlock();
            std::this_thread::sleep_for(_line_num * 30ms);
            lk.lock();

            gotoXY(persent_pos.X, persent_pos.Y);
            std::cout << i << '%';

            if (i % 10 == 0)
            {
                gotoXY(_progress_pos.X, _progress_pos.Y);
                std::cout << "#";
                ++_progress_pos.X;
            }
            try
            {
                saveDataBlockToFileFake(i);
            }
            catch (const std::exception& e)
            {
                SetConsoleTextAttribute(handle, 4);
                gotoXY(persent_pos.X + 3, persent_pos.Y);
                std::cout << "\t" << e.what() << ", download aborted";
                SetConsoleTextAttribute(handle, 7);
                break;
            }
            _progress = i;
        }
        if (_progress == 100)
        {
            gotoXY(persent_pos.X + 3, persent_pos.Y);
            std::chrono::duration<double> duration(now() - start);
            std::cout << "\t" << duration.count();
        }
    }

    bool saveDataBlockToFileFake(int i)
    {
        if (_line_num == 4 && i == 59)
        {
            throw std::logic_error("data corrupted");
        }
        return true;
    }
private:
    short _line_num = 0;
    int _progress = 0;
    COORD _progress_pos = { 0,0 };
};

void download(const int coeff)
{
    Download(short(coeff + 1));
}

int main()
{
    int thrd_cnt = 5;
    std::vector<std::thread> thrds_v;

    clearScreen();
    std::cout << "#\tID\tProgress Bar\t\tTime" << std::endl;

    for (int i = 0; i < thrd_cnt; ++i)
    {
        thrds_v.push_back(std::thread(download, i));
    }
    for (int i = 0; i < thrd_cnt; ++i)
    {
        thrds_v.at(i).join();
    }
}
