#include <iostream>
#include <random>
#include <chrono>
#include <thread>
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

void Monte(int N, int& M, std::default_random_engine dre, std::uniform_real_distribution<> urd)
{
		double x = 0.0;
		double y = 0.0;
		for (auto i = 0U; i < N; i++)
		{
			x = urd(dre);
			y = urd(dre);
			if (x * x + y * y <= 1)
				M++;
		}

}

int main()
{
	std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<> urd(0, 1);
	

	int M1 = 0;
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;

	int N = 100000000;
	{
		Timer<std::chrono::microseconds> T1("Simple");
		Monte(N, M1, dre, urd);
		std::cout << M1 * 4.0 / N << std::endl;
	}
	{
		Timer<std::chrono::microseconds> T2("Threads");
		std::thread t1(Monte, N / 4, std::ref(m1), dre, urd);
		std::thread t2(Monte, N / 4, std::ref(m2), dre, urd);
		std::thread t3(Monte, N / 4, std::ref(m3), dre, urd);
		std::thread t4(Monte, N / 4, std::ref(m4), dre, urd);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		std::cout << (m1 + m2 + m3 + m4) * 4.0 / N << std::endl;
	}
}
