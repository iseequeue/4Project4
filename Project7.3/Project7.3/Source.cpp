#include <algorithm>
#include <future>
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
		std::cout << name << " is started: " << typeid(duration_t).name() << std::endl;
	}

	~Timer() noexcept
	{
		try
		{
			if (!is_stopped)
			{
				auto end = clock_t::now();
				m_duration += std::chrono::duration_cast<duration_t>(end - m_begin);
				std::cout << name << " is stopped: " << m_duration.count() << std::endl;
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
		parallel_for_each(middle, last, f);
		first_half_result.get();
		
	}

}

int main(int argc, char** argv)
{
	std::vector < int > v(100);
	Timer<std::chrono::microseconds> t1("Vasya");
	std::iota(v.begin(), v.end(), 1);
	parallel_for_each(v.begin(), v.end(), [](int n) { std::cout << n << std::endl; });

	return EXIT_SUCCESS;
}