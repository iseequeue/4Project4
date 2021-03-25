#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
#include <iterator>

#include <math.h>

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




void f(double &x, int row = 100u)
{
	for (int i = 0; i < row; i++)
	{
		x += ((x + i) * x * 1.0 / (x * x * x * x + 3 * x) + sin(i) - sin(i * i) + sin(i * i * i) - cos(i))*pow(-1,i);
	}
}

long double binary(double x, double y,  unsigned int row = 100u)
{
	double xx = 1;
	double yy = 1;
	for (auto i = 0u; i < row; i++)
	{
		xx += ((x + i) * x * 1.0 / (x * x * x * x + 3 * x) + sin(i) - sin(i * i) + sin(i * i * i) - cos(i)) * pow(-1, i);
		yy += ((x + i) * x * 1.0 / (x * x * x * x + 3 * x) + sin(i) - sin(i * i) + sin(i * i * i) - cos(i)) * pow(-1, i);
	}
	return xx - yy;
}

int main(int argc, char** argv)
{
	const auto size = 1'000'000u;	
	
	
	/*{
		std::vector < double > v1(size);
		std::iota(v1.begin(), v1.end(), 1);

		std::vector < double > v2(size);
		std::iota(v2.begin(), v2.end(), 1);

		{
			Timer<std::chrono::microseconds> t1("Standard");
			std::for_each(v1.begin(), v1.end(), [](double& n) { f(n); });
		}// 328290289 for 10'000'000

		{
			Timer<std::chrono::microseconds> t1("Parallel");
			std::for_each(std::execution::par,v2.begin(), v2.end(), [](double& n) { f(n); });
		} // 109235421 for 10'000'000 
	} */

	//=====================================================================================
	/*{
		std::vector < double > v1(size);
		std::iota(v1.begin(), v1.end(), 1);

		std::vector < double > v2(size);
		std::iota(v2.begin(), v2.end(), 1);


		{
			std::vector <double> a(v1.size());
			Timer<std::chrono::microseconds> t1("partial_sum");
			std::partial_sum(v1.begin(), v1.end(), a.begin(), [](double x, double y) {return binary(x, y); });
		} // 69914942 for 1'000'000

		{
			std::vector <double> a(v2.size());
			Timer<std::chrono::microseconds> t1("inclusive_sum");
			std::inclusive_scan(std::execution::par, v2.begin(), v2.end(), a.begin(), [](double x, double y) {return binary(x, y); });
		} // 42982437 for 1'000'000

	}
	*/
	//========================================================================================

	{
		{
			std::vector < double > v(size);
			std::vector<double> a(v.size());
			std::iota(v.begin(), v.end(), 1);

			Timer<std::chrono::microseconds> t1("inner_product");

			std::inner_product(v.begin(), v.end(), a.begin(),0,
				[](double x, double y) {return binary(x, y); }, [](double x, double y) {return binary(x, y); });
		}//138462526 for 1'000'000

		{
			std::vector < double > v(size);
			std::vector<double> a(v.size());
			std::iota(v.begin(), v.end(), 1);

			Timer<std::chrono::microseconds> t1("transform_reduce");

			std::transform_reduce(std::execution::par,v.begin(), v.end(), a.begin(),0,
				[](double x, double y) {return binary(x, y); }, [](double x, double y) {return binary(x, y); });

		} //44144257 for 1'000'000
	}
}


