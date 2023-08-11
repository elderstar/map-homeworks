#include <iostream>
#include <thread>
#include<atomic>

using namespace std::chrono_literals;

void printCount(const std::atomic<int>& count)
{
	std::cout << "Count: " << count.load() << "\n";
}

void registerClient(std::atomic<int>& count, std::atomic<bool>& office_open, int total_clients)
{
	for (int i = 0; i < total_clients; ++i)
	{
		std::this_thread::sleep_for(1000ms);
		count.fetch_add(1, std::memory_order_relaxed);
		printCount(count);
	}
	office_open.store(!office_open.load());
}

void solveCase(std::atomic<int>& count, std::atomic<bool>& office_open)
{
	while (office_open || count.load() > 0)
	{
		std::this_thread::sleep_for(2000ms);
		count.fetch_sub(1, std::memory_order_relaxed);
		printCount(count);
	}
}

int main()
{
	std::atomic<int> count{0};
	int total_clients = 10;
	std::atomic<bool> office_open{true};

	std::thread clients_thr(registerClient, std::ref(count), std::ref(office_open), total_clients);
	std::thread operator_thr(solveCase, std::ref(count), std::ref(office_open));
	clients_thr.join();
	operator_thr.join();
}
