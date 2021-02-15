#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
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
	//std::array<int,100000> array1;

	//std::vector<int> vector1;
	//vector1.reserve(100000);


	std::deque<int> deque1;

	//std::list<int> list1;



	//std::forward_list<int> forward_list1;


	for (int i = 100000; i > 0; --i)
	{
		//array1[i - 1] = 100000 - i;

		//vector1.push_back(i);

		deque1.push_back(i);

		//list1.push_back(i);

		//forward_list1.push_front(100000-i);

	}
	std::cout << deque1[0] << std::endl;

	{
		Timer<std::chrono::microseconds> t1("Timer");
		std::sort(std::begin(deque1), std::end(deque1));
		//forward_list1.sort();
		
		
		

	}

}

