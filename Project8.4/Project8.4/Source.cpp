#include <exception>
#include <memory>
#include <mutex>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <condition_variable>
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/spsc_queue.hpp>
//=======================================================================

std::atomic < bool > flag = false;

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
		std::cout << name << " has started\n";
	}

	~Timer() noexcept
	{
		try
		{
			if (!is_stopped)
			{
				auto end = clock_t::now();
				m_duration += std::chrono::duration_cast<duration_t>(end - m_begin);
				std::cout <<name << " is stopped: " << m_duration.count() << std::endl;;
			}

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
//========================================================================
template < typename T >
class Threadsafe_Stack
{
public:

	Threadsafe_Stack() = default;

	Threadsafe_Stack(const Threadsafe_Stack& other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_data = other.m_data;
	}

	Threadsafe_Stack& operator=(const Threadsafe_Stack&) = delete;

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data.push(value);
	}

	std::shared_ptr < T > pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		const auto result = std::make_shared < T >(m_data.top());
		m_data.pop();

		return result;
	}

	void pop(T& value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		value = m_data.top();
		m_data.pop();
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_data.empty();
	}

	T top() const
	{
		return m_data.top();
	}

private:

	std::stack < T > m_data;

private:

	mutable std::mutex m_mutex;
};
//========================================================================
template < typename T >
class Threadsafe_Queue
{
public:

	Threadsafe_Queue() = default;

	Threadsafe_Queue(const Threadsafe_Queue& other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_queue = other.m_queue;
	}

	Threadsafe_Queue& operator=(const Threadsafe_Queue& other)
	{
		std::scoped_lock lock(m_mutex, other.m_mutex);
		m_queue = other.m_queue;
	}

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_queue.push(value);
		m_condition_variable.notify_one();
	}

	void pop(T& value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_queue.empty(); });
		value = m_queue.front();
		m_queue.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_queue.empty(); });
		auto result = std::make_shared < T >(m_queue.front());
		m_queue.pop();

		return result;
	}

	bool try_pop(T& value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_queue.empty())
		{
			return false;
		}

		value = m_queue.front();
		m_queue.pop();

		return true;
	}

	std::shared_ptr < T > try_pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_queue.empty())
		{
			return std::shared_ptr < T >();
		}

		auto result = std::make_shared < T >(m_queue.front());
		m_queue.pop();

		return result;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_queue.empty();
	}

private:

	std::queue < T >		m_queue;
	std::condition_variable m_condition_variable;

private:

	mutable std::mutex m_mutex;
};
//======================================================
template <typename T>
void produce(unsigned int M, Threadsafe_Stack<int> &stack)
{
	while (!flag)
		std::this_thread::yield();

	for (auto i = 0u; i < M; i++)
	{
		stack.push(i);

		std::this_thread::yield();
	}
}

template <typename T>
void consume(unsigned int M, T &stack)
{
	while (!flag)
		std::this_thread::yield();


	for (unsigned i = 0; i < M; ++i)
	{
		stack.pop();
		std::this_thread::yield();

	}

}
//=========================================================
template <typename T>
void boostproduce(unsigned int M, T &stack)
{
	while (!flag)
		std::this_thread::yield();

	for (auto i = 0u; i < M; i++)
	{
		stack.push(i);

		std::this_thread::yield();
	}
}

template <typename T>
void boostconsume(unsigned int M, T &stack)
{
	while (!flag)
		std::this_thread::yield();

	int value;
	for (unsigned i = 0; i < M; ++i)
	{
		stack.pop(value);
		std::this_thread::yield();

	}

}
//================================================
int main(int argc, char** argv)
{
	auto N = 150u;
	auto M = 1000u;
	{
		Threadsafe_Stack < int > stack;

		for (auto i = 0u; i < M * 10; i++)
		{
			stack.push(i);
		}

		std::vector<std::thread> consumers(N);
		for (auto i = 0u; i < consumers.size(); i++)
		{
			consumers[i] = std::thread(consume<Threadsafe_Stack<int>>, M, std::ref(stack));
		}

		std::vector<std::thread> producers(N);
		for (auto i = 0u; i < producers.size(); i++)
		{
			producers[i] = std::thread(produce<Threadsafe_Stack<int>>, M, std::ref(stack));
		}

		Timer<std::chrono::microseconds> t1("Threadsafe_stack");

		flag = true;

		std::for_each(producers.begin(), producers.end(), [](auto& thread) {thread.join(); });
		std::for_each(consumers.begin(), consumers.end(), [](auto& thread) {thread.join(); });
	}
	flag = false;
	{
		boost::lockfree::stack < int > stack(128);

		for (auto i = 0u; i < M * 10; i++)
		{
			stack.push(i);
		}

		std::vector<std::thread> consumers(N);
		for (auto i = 0u; i < consumers.size(); i++)
		{
			consumers[i] = std::thread(boostconsume<boost::lockfree::stack<int>>, M, std::ref(stack));
		}

		std::vector<std::thread> producers(N);
		for (auto i = 0u; i < producers.size(); i++)
		{
			producers[i] = std::thread(boostproduce<boost::lockfree::stack<int>>, M, std::ref(stack));
		}

		Timer<std::chrono::microseconds> t1("Lockfree_Stack");

		flag = true;

		std::for_each(producers.begin(), producers.end(), [](auto& thread) {thread.join(); });
		std::for_each(consumers.begin(), consumers.end(), [](auto& thread) {thread.join(); });

	}
	flag = false;
	{
		Threadsafe_Queue < int > queue;

		for (auto i = 0u; i < M * 10; i++)
		{
			queue.push(i);
		}

		std::vector<std::thread> consumers(N);
		for (auto i = 0u; i < consumers.size(); i++)
		{
			consumers[i] = std::thread(boostconsume<Threadsafe_Queue<int>>, M, std::ref(queue));
		}

		std::vector<std::thread> producers(N);
		for (auto i = 0u; i < producers.size(); i++)
		{
			producers[i] = std::thread(boostproduce<Threadsafe_Queue<int>>, M, std::ref(queue));
		}

		Timer<std::chrono::microseconds> t1("Threadsafe_queue");

		flag = true;

		std::for_each(producers.begin(), producers.end(), [](auto& thread) {thread.join(); });
		std::for_each(consumers.begin(), consumers.end(), [](auto& thread) {thread.join(); });
	}
	flag = false;
	{
		boost::lockfree::spsc_queue<int> queue(128);
	
		for (auto i = 0u; i < M * 10; i++)
		{

		}

		std::vector<std::thread> consumers(N);
		for (auto i = 0u; i < consumers.size(); i++)
		{
			consumers[i] = std::thread(boostconsume<boost::lockfree::spsc_queue<int>>, M, std::ref(queue));
		}

		std::vector<std::thread> producers(N);
		for (auto i = 0u; i < producers.size(); i++)
		{
			producers[i] = std::thread(boostproduce< boost::lockfree::spsc_queue<int>>, M, std::ref(queue));
		}

		Timer<std::chrono::microseconds> t1("Lockfree_Queue");

		flag = true;

		std::for_each(producers.begin(), producers.end(), [](auto& thread) {thread.join(); });
		std::for_each(consumers.begin(), consumers.end(), [](auto& thread) {thread.join(); });

	}
}
