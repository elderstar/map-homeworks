#include "ThreadPool.h"

ThreadPool::ThreadPool() 
{
    for (int i = 0; i < cores; ++i)
    {
        thr_pool.push_back(std::thread(&ThreadPool::work, this));
    }
};

ThreadPool::~ThreadPool() 
{
    flag_done = true;
    for (auto& el : thr_pool)
    {
        el.join();
    }
}; 

void ThreadPool::work()
{
    while (!flag_done)
    {
        std::function<void()> f;
        if (work_queue.pop(f))
        {
            f();
        }
        else {
            std::this_thread::yield();
        }
    }
};

void ThreadPool::submit(std::function<void()>&& func)
{
    work_queue.push(std::forward<std::function<void()>>(func));
};
