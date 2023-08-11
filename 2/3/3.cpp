#include <iostream>
#include <mutex>

class Data
{
public:
    std::mutex data_mutex;

    Data(int a, char b, bool c) : _a(a), _b(b), _c(c)
    {}

    ~Data() {}
    
    int getA() { return _a; };
    char getB() { return _b; };
    bool getC() { return _c; };
    void setA(const int& a) { _a = a; };
    void setB(const char& b) { _b = b; };
    void setC(const bool& c) { _c = c; };
private:
    std::atomic<int> _a = 0;
    std::atomic<char> _b = 0;
    std::atomic<bool> _c = false;
    bool locked_status = false;
};

void swap(Data& A, Data& B)
{
    A.data_mutex.lock();
    B.data_mutex.lock();

    int a = A.getA();
    char b = A.getB();
    bool c = A.getC();

    A.setA(B.getA());
    A.setB(B.getB());
    A.setC(B.getC());

    B.setA(a);
    B.setB(b);
    B.setC(c);
    A.data_mutex.unlock();
    B.data_mutex.unlock();
}

void swap_lock(Data& A, Data& B)
{
    std::lock(A.data_mutex, B.data_mutex);
    std::lock_guard la(A.data_mutex, std::adopt_lock);
    std::lock_guard lb(B.data_mutex, std::adopt_lock);

    int a = A.getA();
    char b = A.getB();
    bool c = A.getC();

    A.setA(B.getA());
    A.setB(B.getB());
    A.setC(B.getC());

    B.setA(a);
    B.setB(b);
    B.setC(c);
}

void swap_scoped_lock(Data& A, Data& B)
{
    std::lock(A.data_mutex, B.data_mutex);
    std::lock_guard la(A.data_mutex, std::adopt_lock);
    std::lock_guard lb(B.data_mutex, std::adopt_lock);

    int a = A.getA();
    char b = A.getB();
    bool c = A.getC();

    A.setA(B.getA());
    A.setB(B.getB());
    A.setC(B.getC());

    B.setA(a);
    B.setB(b);
    B.setC(c);
}

void swap_unique_lock(Data& A, Data& B)
{
    std::scoped_lock(A.data_mutex, B.data_mutex);

    int a = A.getA();
    char b = A.getB();
    bool c = A.getC();

    A.setA(B.getA());
    A.setB(B.getB());
    A.setC(B.getC());

    B.setA(a);
    B.setB(b);
    B.setC(c);
}

int main()
{
    Data A(200, 36, true);
    Data B(404, 33, false);
    std::cout << "A: " << A.getA() << " " << A.getB() << " " << A.getC() << "\n";
    std::cout << "B: " << B.getA() << " " << B.getB() << " " << B.getC() << "\n\n";
    swap(A, B);
    std::cout << "A: " << A.getA() << " " << A.getB() << " " << A.getC() << "\n";
    std::cout << "B: " << B.getA() << " " << B.getB() << " " << B.getC() << "\n\n";
    swap_lock(A, B);
    std::cout << "A: " << A.getA() << " " << A.getB() << " " << A.getC() << "\n";
    std::cout << "B: " << B.getA() << " " << B.getB() << " " << B.getC() << "\n\n";
    swap_unique_lock(A, B);
    std::cout << "A: " << A.getA() << " " << A.getB() << " " << A.getC() << "\n";
    std::cout << "B: " << B.getA() << " " << B.getB() << " " << B.getC() << "\n\n";
    swap_scoped_lock(A, B);
    std::cout << "A: " << A.getA() << " " << A.getB() << " " << A.getC() << "\n";
    std::cout << "B: " << B.getA() << " " << B.getB() << " " << B.getC() << "\n";
}
