#include <iostream>
#include <vector>
#include <random>
#include <execution>
#include <algorithm>
#include <future>
#include <thread>

void print(const int& el)
{
	std::cout << el << " ";
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

template<class It, class Func> void foreachPar(It start, It end, Func func)
{
	ptrdiff_t range = end - start;

	if (!range)
	{
		return;
	}

	int min_size = 10;

	if (range <= min_size)
	{
		std::for_each(start, end, func);
	}else
	{
		It mid = start + (range / 2);
		
		std::future<void> ft = std::async(std::launch::async, foreachPar<It, Func>, start, mid, func);

		try
		{
			foreachPar(mid, end, func);
		}
		catch (const std::exception& e)
		{
			throw;
		}

		ft.get();
	}
}

int main()
{
	int vec_size = 30;
	std::vector<int> vec = generateRandVector(vec_size);

	for (const auto&el:vec)
	{
		print(el);
	}
	std::cout << std::endl;
	foreachPar(vec.begin(), vec.end(), print);
}