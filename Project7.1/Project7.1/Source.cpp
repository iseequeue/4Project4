#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <numeric>

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
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_real_distribution<> urd(0, 1);

	std::cout << std::thread::hardware_concurrency() << std::endl; //4	

	int N = 10000000;
	{
		int M = 0;
		Timer<std::chrono::microseconds> T1("Simple");
		Monte(N, M, mersenne, urd);
		std::cout << M * 4.0 / N << std::endl;
	}
	{
		
		Timer<std::chrono::microseconds> T2("Threads");

		std::vector<std::thread> threads(std::thread::hardware_concurrency() - 1);

		std::vector<int> m(threads.size(), 0);

		for (auto i = 0u; i < threads.size(); i++)
		{
			std::random_device rd1;
			std::mt19937 mersenne1(rd1());
			threads[i] = std::thread(Monte, N , std::ref(m[i]), mersenne1, urd);
		}

		std::for_each(threads.begin(), threads.end(), [](auto& thread) {thread.join(); });
		
		std::cout << std::accumulate(m.begin(), m.end(),0) * 4.0 /( N*m.size()) << std::endl;
	}
}
