#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <cstdlib>
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
	double get_time()
	{
		return duration_t.count();
	}

private:
	time_point_t m_begin;
	duration_t m_duration;
	bool is_stopped;
	std::string name;
};

int main()
{
	std::array<int,100000> array1;

	std::vector<int> vector1;
	vector1.reserve(100000);


	std::deque<int> deque1;

	std::list<int> list1;



	std::forward_list<int> forward_list1;


	for (int i = 0; i < 100000; ++i)
	{
	    array1[i] = rand();

		vector1.push_back(array1[i]);

		deque1.push_back(array1[i]);

		list1.push_back(array1[i]);

		forward_list1.push_front(array1[i]);

	}
	forward_list1.reverse();
	for (auto i = 0; i<100; ++i)
		std::cout << array1[i] << std::endl;
	std::cout << array1[0] << ' ' << vector1[0] << ' ' << deque1[0] << ' ' << list1.front() << ' ' << forward_list1.front() << std::endl;

	{
		Timer<std::chrono::microseconds> t1("ARRAY");
		std::sort(std::begin(array1), std::end(array1));
	}
	{
		Timer<std::chrono::microseconds> t1("VECTOR");
		std::sort(std::begin(vector1), std::end(vector1));
	}
	{
		Timer<std::chrono::microseconds> t1("DEQUE");
		std::sort(std::begin(deque1), std::end(deque1));
	}
	{
		Timer<std::chrono::microseconds> t1("LIST");
		list1.sort();
	}
	{
		Timer<std::chrono::microseconds> t1("FORWARD-LIST");
		forward_list1.sort();
	}

}

