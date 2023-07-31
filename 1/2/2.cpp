#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <execution>
#include <algorithm>

typedef std::chrono::duration<double> duration;

using namespace std::chrono_literals;

auto now() { return std::chrono::steady_clock::now(); }

std::vector<int> generateRandVector(unsigned int size)
{
	std::vector<int> vec(size);
	std::mt19937_64 gen;
	std::uniform_int_distribution<int> dist(0, size);
	std::generate(std::execution::par, vec.begin(), vec.end(), [&gen, &dist]() {
		return dist(gen);
		});
	return vec;
}

void printResults(const std::vector < std::vector<duration>> & result_table)
{
	std::cout << "\t\t1000" << "\t\t10000" << "\t\t100000" << "\t\t1000000\n";
	unsigned int tr_x = 1;
	for (const std::vector<duration>& row : result_table)
	{
		std::cout << tr_x << " потоков\t";
			for (const duration& cell: row)
			{
				std::cout << cell.count() << "s\t";
			}
		std::cout << std::endl;
		tr_x *= 2;
	}
}

void summarizeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2, size_t start, size_t end)
{
	int result = 0;
	for (size_t i = start; i < end; ++i)
	{
		result = vec1.at(i) + vec2.at(i);
	}
}

duration measureTime(const std::vector<int>& vec, int thr_count)
{
	const auto start{ now() };

	std::vector <std::thread> th_vec;
	size_t begin = 0;
	size_t portion = vec.size() / thr_count;
	size_t end = portion;
	for (int i = 0; i < thr_count; ++i)
	{
		//std::cout << "from: " << begin << " to " << end << "\n";

		th_vec.push_back(std::thread(summarizeVectors, std::ref(vec), std::ref(vec), begin, end));
		begin = end + 1;
		end += portion;
		if (i == thr_count - 2) {
			end = vec.size();
		}
	}
	for (int i = 0; i < thr_count; ++i)
	{
		th_vec.at(i).join();
	}

	return duration(now() - start);
}

int main()
{
	system("chcp 1251");
	std::vector<std::vector<duration>> result_table;

	std::vector<int> vec_1000 = generateRandVector(1000);
	std::vector<int> vec_10000 = generateRandVector(10000);
	std::vector<int> vec_100000 = generateRandVector(100000);
	std::vector<int> vec_1000000 = generateRandVector(1000000);
	
	std::thread thr1([]() {
		std::cout << "Колличество аппаратных ядер: " << std::thread::hardware_concurrency() << "\n";
	});
	thr1.join();
	std::cout << std::endl;

	result_table.push_back(std::vector<duration>{measureTime(vec_1000, 1), measureTime(vec_10000, 1), measureTime(vec_100000, 1), measureTime(vec_1000000, 1)});
	result_table.push_back(std::vector<duration>{measureTime(vec_1000, 2), measureTime(vec_10000, 2), measureTime(vec_100000, 2), measureTime(vec_1000000, 2)});
	result_table.push_back(std::vector<duration>{measureTime(vec_1000, 4), measureTime(vec_10000, 4), measureTime(vec_100000, 4), measureTime(vec_1000000, 4)});
	result_table.push_back(std::vector<duration>{measureTime(vec_1000, 8), measureTime(vec_10000, 8), measureTime(vec_100000, 8), measureTime(vec_1000000, 8)});
	result_table.push_back(std::vector<duration>{measureTime(vec_1000, 16), measureTime(vec_10000, 16), measureTime(vec_100000, 16), measureTime(vec_1000000, 16)});

	printResults(result_table);

}
