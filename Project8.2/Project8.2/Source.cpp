#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <string>
#include <random>


class Threads_Guard
{
public:
	explicit Threads_Guard(std::vector < std::thread >& threads) :
		m_threads(threads)
	{}

	Threads_Guard(Threads_Guard const&) = delete;

	Threads_Guard& operator=(Threads_Guard const&) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:
	
	std::vector < std::thread >& m_threads;
};

template < typename Iterator, typename T >
struct Searcher
{
	void operator()(Iterator first, Iterator last, const T &element, std::vector<Iterator> &result, std::mutex &mutex) noexcept
	{
		try
		{
			for (; first != std::prev(last, element.size()-1); ++first)
			{
				bool b = true;
				auto first1 = first;
				for (auto i : element)
				{
					if (*first1 != i)
					{
						b = false;
						break;
					}
					first1++;
				}
				if (b)
				{
					std::lock_guard < std::mutex > lock(mutex);
					result.push_back(first);
				}
			}
		}
		catch (...)
		{}
	}
};

template < typename Iterator, typename T >
void parallel_find(Iterator first, Iterator last, const T &element, std::vector<Iterator> &result, std::mutex &mutex)
{
	const std::size_t length = std::distance(first, last); //100


	const std::size_t min_per_thread = 25; 

	const std::size_t max_threads = (length + min_per_thread - 1) / min_per_thread; //4

	const std::size_t hardware_threads = std::thread::hardware_concurrency();

	const std::size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;

	std::vector < std::thread > threads(num_threads - 1);
	std::cout << '\n' << num_threads << ' ' << block_size << std::endl;
	{
		Threads_Guard guard(threads);

		Iterator block_start = first;


		for (std::size_t i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;

			std::advance(block_end, block_size);

			threads[i] = std::thread(Searcher < Iterator, T >(),
				block_start, block_end, element, std::ref(result), std::ref(mutex));

			block_start = std::prev(block_end, element.size()-1);
		}

		Searcher < Iterator, T >()(block_start, last, element, result, std::ref(mutex));
	}

}


int main(int argc, char** argv)
{
	std::mutex mutex;

	std::uniform_int_distribution<> urd(0, 3);
	std::random_device rd;
	std::mt19937 mersenne(rd());

	std::string let = "AGTC";
	std::string s = "G";

	for (auto i = 0U; i < 160u; i++)
	{
		//s += let[urd(mersenne)];
		s += 'A';
	}
	s += 'G';
	std::cout << s << std::endl;
	std::cout << "enter fragment: ";

	std::string fragment;
	std::cin >> fragment;

	std::vector<std::string::iterator> result;
	parallel_find(s.begin(), s.end(), fragment, result, std::ref(mutex));

	for (auto i : result) // print numbers entry
	{
		std::cout << std::distance(s.begin(), i) << ' ';
	}

	//for (auto i : result) // check subconsequences that were found (== input)
	//{
	//	unsigned int l = std::distance(s.begin(), i);
	//	for (auto j = 0u; j < fragment.size(); j++)
	//	{
	//		std::cout << s[l+j];
	//	}
	//	std::cout << std::endl;
	//}
	std::cout << "\n" << result.size() << std::endl;
	return EXIT_SUCCESS;
}
