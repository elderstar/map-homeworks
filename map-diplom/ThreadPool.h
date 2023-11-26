#pragma once

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

template <class T>
class SafeQueue
{
public:

	void push(T val)
	{
		std::unique_lock<std::mutex> lock(m);
		queue.push(std::move(val));
		ready = true;
		condition.notify_one();
	};

	bool pop(T& val)
	{
		std::unique_lock<std::mutex> lock(m);
		while(!ready) condition.wait(lock);

		if (queue.empty())
		{
			return false;
		}
		else {
			val = std::move(queue.front());
			queue.pop();
			return true;
		}
	};

	T front()
	{
		return queue.front();
	};
private:
	mutable std::mutex m;
	std::atomic<bool> ready{false};
	std::condition_variable condition;
	std::queue<T> queue;
};

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void work();
	void submit(std::function<void()>&& func);
private:
	std::atomic<bool> flag_done{ false };
	const int cores = std::thread::hardware_concurrency();

	std::vector<std::thread> thr_pool;
	SafeQueue<std::function<void()>> work_queue; 
};
