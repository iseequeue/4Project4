#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>

template < typename Iterator, typename T >
void parallel_for_each(Iterator first, Iterator last, T f)
{
	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25;

	if (length <= max_size)
	{
		std::for_each(first, last, f);
	}
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < void > first_half_result = std::async(parallel_for_each < Iterator, T >, first, middle, f);
		
		first_half_result.get();
		parallel_for_each(middle, last, f);
	}

}

int main(int argc, char** argv)
{
	std::vector < int > v(100);

	std::iota(v.begin(), v.end(), 1);
	parallel_for_each(v.begin(), v.end(), [](int n) { std::cout << n << std::endl; });

	return EXIT_SUCCESS;
}