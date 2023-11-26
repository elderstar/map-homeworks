#include <iostream>
#include <chrono>

#include "ThreadPool.h"

using namespace std::chrono_literals;

void func1()
{
    std::this_thread::sleep_for(200ms);
    std::cout << "working: " << __FUNCTION__ << "...\n";
}

void func2()
{
    std::this_thread::sleep_for(500ms);
    std::cout << "working: " << __FUNCTION__ << "...\n";
}


int main()
{
    ThreadPool thr_pool;

    for (int i = 0; i < 10; ++i)
    {
        thr_pool.submit(func1);
        thr_pool.submit(func2);
        std::this_thread::sleep_for(1s);
    }
}
