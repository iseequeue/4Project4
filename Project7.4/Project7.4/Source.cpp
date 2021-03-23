#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
#include <iterator>
#include <execution>

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

		first_half_result.get();
		parallel_for_each(middle, last, f);
	}

}

void f(double &n)
{
	for (int i = 0; i < 10000; i++)
	{
		n += (n + i) * n* 1.0 / (n*n*n + 3*n);
	}
}

int main(int argc, char** argv)
{
	/*
	std::vector < double > v1(1000);
	std::iota(v1.begin(), v1.end(), 1);

	std::vector < double > v2(10000);
	std::iota(v2.begin(), v2.end(), 1);
	{
		Timer<std::chrono::microseconds> t1("Standart");
		std::for_each(v1.begin(), v1.end(), [](double& n) { f(n); });
	}// 164903

	{
		Timer<std::chrono::microseconds> t1("Parallel");
		parallel_for_each(v2.begin(), v2.end(), [](double& n) { f(n); });
	} // 1650566 */

	/*
	std::vector < double > v(10000000);
	std::iota(v.begin(), v.end(), 1);

	
	{
		std::vector <double> a(v.size());
		Timer<std::chrono::microseconds> t1("partial_sum");
		std::partial_sum(v.begin(), v.end(), a.begin());
	} // 290488

	{
		std::vector <double> a(v.size());
		Timer<std::chrono::microseconds> t1("inclusive_sum");
		std::inclusive_scan(v.begin(), v.end(), a.begin());
	} // 553926*/


	

		
	{
		std::vector < double > v(10000000);
		std::vector<int> a(v.size());
		std::iota(v.begin(), v.end(), 1);

		Timer<std::chrono::microseconds> t1("inner_product");
		
		std::inner_product(v.begin(), v.end(), a.begin(), 0);
	} //727881

	{
		std::vector < double > v(10000000);
		std::vector<int> a(v.size());
		std::iota(v.begin(), v.end(), 1);

		Timer<std::chrono::microseconds> t1("transform_reduce");

		std::transform_reduce(v.begin(), v.end(), a.begin(), 0);

	} //84770
}


