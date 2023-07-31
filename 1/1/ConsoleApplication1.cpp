#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void printCount(unsigned int count)
{
	std::cout << "Count: " << count << "\n";
}

void registerClient(unsigned int& count, bool& office_open, unsigned int total_clients)
{
	for (int i = 0; i < total_clients; ++i)
	{
		std::this_thread::sleep_for(1000ms);
		++count;
		printCount(count);
	}
	office_open = !office_open;
}

void solveCase(unsigned int& count, bool& office_open)
{
	while (office_open || count > 0)
	{
		std::this_thread::sleep_for(2000ms);
		--count;
		printCount(count);
	}
}

int main()
{
	unsigned int count = 0;
	unsigned int total_clients = 10;
	bool office_open = true;
	std::thread clients_thr(registerClient, std::ref(count), std::ref(office_open), total_clients);
	std::thread operator_thr(solveCase, std::ref(count), std::ref(office_open));
	clients_thr.join();
	operator_thr.join();
}
