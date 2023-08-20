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

template<class It, class Func> constexpr Func foreachPar(It start, It end, Func func, int threads = 1)
{
	It new_end = end;
	if (threads > 1)
	{
		ptrdiff_t range = end - start;

		new_end = start + (range / threads);
		
		std::async(std::launch::async, foreachPar<It, Func>, new_end, end, func, --threads);
	}

	for (; start != new_end; ++start)
	{
		func(*start);
	}
	return func;
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
	foreachPar(vec.begin(), vec.end(), print, 3);
}