#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <execution>
#include <algorithm>
#include <future>

using namespace std::chrono_literals;
typedef std::chrono::duration<double> duration;

auto now() { return std::chrono::steady_clock::now(); }

template<typename T>void print(std::vector<T>& arr, size_t start, size_t count)
{
	start > 0 ? start : start = 0;
	start < arr.size() ? start : start = 0;
	size_t end = (start + count) >= arr.size() ? arr.size() : start + count;

	for (size_t i = start; i < end; ++i)
	{
		std::cout << arr.at(i) << " ";
	}
}

std::vector<int> generateRandVector(int size)
{
	std::vector<int> vec(size);
	std::mt19937_64 gen;
	std::uniform_int_distribution<int> dist(0, size);
	std::generate(std::execution::par, vec.begin(), vec.end(), [&gen, &dist]() {
		return dist(gen);
		});
	return vec;
}

void findMinIdx(std::vector<int>& arr, size_t start, size_t end, std::promise<size_t> promise)
{
	size_t min_idx = start;

	if (end > arr.size())
	{
		end = arr.size();
	}
	for (size_t j = start + 1; j < end; ++j)
	{
		if (arr.at(j) < arr.at(min_idx))
		{
			min_idx = j;
		}
	}
	promise.set_value(min_idx);
}

void selectionSort(std::vector<int>& arr)
{
	size_t min_idx = 0;
	int tread_cnt = std::thread::hardware_concurrency(); 
	//std::cout << tread_cnt << "\n";

	size_t portion = arr.size() / tread_cnt;

	for (size_t i = 0; i < arr.size() - 1; ++i)
	{
		min_idx = i;
		size_t start = i;
		portion = (arr.size() - i) / tread_cnt;
		size_t end = start + portion;

		std::vector<std::future<void>> tread_arr;
		std::vector<std::future<size_t>> ft_rest_arr;
		std::vector<size_t> idx_results;
		for (int k = 0; k < tread_cnt; ++k)
		{
			std::promise<size_t> promise;
			ft_rest_arr.push_back(promise.get_future());

			tread_arr.push_back(std::async(findMinIdx, std::ref(arr), start, end, std::move(promise)));

			start = end;
			if ((k == tread_cnt - 2))
			{
				end = arr.size();
			}
			else {
				end += portion;
			}
		}
		for (int k = 0; k < tread_cnt; ++k)
		{
			tread_arr.at(k).wait();
			idx_results.push_back(ft_rest_arr.at(k).get());
		}
		min_idx = *idx_results.begin();

		for (const auto& id : idx_results)
		{
			if (arr.at(id) < arr.at(min_idx))
			{
				min_idx = id;
			}
		}

		if (min_idx != i)
		{
			std::swap(arr.at(i), arr.at(min_idx));
		}
	}
}

int main()
{
	int vec_size = 2000;
	std::vector<int> vec = generateRandVector(vec_size);

	print(vec, vec_size/2, 15);std::cout << std::endl;
	
	//const auto go{ now() };

	selectionSort(vec);
	//std::cout << duration(now() - go).count() << "\n";

	print(vec, vec_size / 2, 15);
}
