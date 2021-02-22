#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
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
	{
		std::vector <int> v;
		int N = 1000;
		v.reserve(N);
		std::array<int, 1000> a;

		std::cout << "N = " << N << std::endl;
		

		{
			Timer<std::chrono::microseconds> t1("VECTOR");
			
			for (auto i = N; i > 0; i--)
			{
				v.push_back(i);
				//a[N - i - 1] = i;
			}
			std::sort(std::begin(v), std::end(v));

		}

		{
			Timer<std::chrono::microseconds> t1("ARRAY");
			for (auto i = N; i > 0; i--)
			{
				//v.push_back(i);
				a[N - i - 1] = i;
			}
			std::sort(std::begin(a), std::end(a));

		}

		std::set < int > set;
		{
			Timer<std::chrono::microseconds> t1("SET");
			for (auto i = N; i > 0; i--)
				set.insert(i);
		}
	}

	{
		std::vector <int> v;
		int N = 10000;
		v.reserve(N);
		std::array<int, 10000> a;

		std::cout << "N = " << N << std::endl;
		

		{
			Timer<std::chrono::microseconds> t1("VECTOR");
			for (auto i = N; i > 0; i--)
			{
				v.push_back(i);
				//a[N - i - 1] = i;
			}
			std::sort(std::begin(v), std::end(v));

		}

		{
			Timer<std::chrono::microseconds> t1("ARRAY");
			for (auto i = N; i > 0; i--)
			{
				//v.push_back(i);
				a[N - i - 1] = i;
			}
			std::sort(std::begin(a), std::end(a));

		}

		std::set < int > set;
		{
			Timer<std::chrono::microseconds> t1("SET");
			for (auto i = N; i > 0; i--)
				set.insert(i);
		}
	}


	{
		std::vector <int> v;
		int N = 100000;
		v.reserve(N);
		std::array<int, 100000> a;

		std::cout << "N = " << N << std::endl;


		{
			Timer<std::chrono::microseconds> t1("VECTOR");
			for (auto i = N; i > 0; i--)
			{
				v.push_back(i);
				//a[N - i - 1] = i;
			}
			std::sort(std::begin(v), std::end(v));

		}

		{
			Timer<std::chrono::microseconds> t1("ARRAY");
			for (auto i = N; i > 0; i--)
			{
				//v.push_back(i);
				a[N - i - 1] = i;
			}
			std::sort(std::begin(a), std::end(a));

		}

		std::set < int > set;
		{
			Timer<std::chrono::microseconds> t1("SET");
			for (auto i = N; i > 0; i--)
				set.insert(i);
		}
	}
	
}
