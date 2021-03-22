#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
template <typename T >
class Timer
{
public:
	using duration_t = T;
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;

	void pause()
	{
		auto end = clock_t::now();
		m_duration += std::chrono::duration_cast<duration_t>(end - m_begin);
		is_stopped = true;
		std::cout << name << " is stopped: " << m_duration.count() << std::endl;
	}

	void reset()
	{
		m_begin = clock_t::now();
		is_stopped = false;
		std::cout << name << " is reset" << std::endl;
	}


	Timer(std::string Name) : m_begin(clock_t::now()), m_duration(0), is_stopped(false), name(Name)
	{
		//std::cout << name << " is started: " << typeid(duration_t).name() << std::endl;
	}

	~Timer() noexcept
	{
		try
		{
			if (!is_stopped)
			{
				auto end = clock_t::now();
				m_duration += std::chrono::duration_cast<duration_t>(end - m_begin);
				std::cout << m_duration.count() << ',';
			}
			//std::cout << typeid(duration_t).name() << ' ' << m_duration.count() << std::endl;
		}
		catch (...)
		{
			std::abort();
		}

	}

private:
	time_point_t m_begin;
	duration_t m_duration;
	bool is_stopped;
	std::string name;
};

template < typename Iterator, typename T >
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result); // !
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int num_threads)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t min_per_thread = 25;
	//const std::size_t max_threads =	(length + min_per_thread - 1) / min_per_thread;

	//const std::size_t hardware_threads = std::thread::hardware_concurrency();

	//const std::size_t num_threads =	std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;

	std::vector < T > results(num_threads);
	std::vector < std::thread > threads(num_threads - 1);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(
			accumulate_block < Iterator, T >(),
			block_start, block_end, std::ref(results[i])); // !

		block_start = block_end;
	}

	accumulate_block < Iterator, T >()(block_start, last, results[num_threads - 1]);

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char** argv)
{
	std::vector < int > v(503000);

	std::iota(v.begin(), v.end(), 1);
	
	for (int i = 1; i<1500; i+=20)
	{
		//std::cout << i << ',';
		Timer<std::chrono::microseconds> t1("Vasya");
		parallel_accumulate(v.begin(), v.end(), 0, i);
	}
	return EXIT_SUCCESS;
}