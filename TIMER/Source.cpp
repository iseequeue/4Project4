#include <iostream>
#include <chrono>
#include <vector>
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

private:
	time_point_t m_begin;
	duration_t m_duration;
	bool is_stopped;
	std::string name;
};

int main()
{
	std::vector <int> v;
	v.reserve(1000000);
	for (auto i = 100000; i >= 0; --i)
	{
		v.push_back(i);
	}
	{
		Timer<std::chrono::microseconds> t1("Vasya");
		Timer<std::chrono::microseconds> t2("Petya");
		std::sort(std::begin(v), std::end(v));
		t1.pause();
		std::vector <int> vv;

		vv.reserve(1000000);
		for (auto i = 100000; i >= 0; --i)
		{
			vv.push_back(i);
		}
		t1.reset();

	}

}