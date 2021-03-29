#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <vector>
#include <stdexcept>
#include <condition_variable>
#include <algorithm>
//#include <boost/lockfree/stack.hpp>


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

private:

	std::stack < T > m_data;

private:

	mutable std::mutex m_mutex;
};
//========================================================================

std::condition_variable cv;
std::mutex cv_m;

void produce(unsigned int M,Threadsafe_Stack<int> &stack)
{
	//std::unique_lock<std::mutex> lk(cv_m);
	//cv.wait(lk);
	for (auto i = 0u; i < M; i++)
		stack.push(i);
}

void consume(unsigned int M, Threadsafe_Stack<int>& stack)
{
	//std::unique_lock<std::mutex> lk(cv_m);
	//cv.wait(lk);
	for (auto i = 0u; i < M; i++)
		stack.pop();
}

int main(int argc, char** argv)
{
	const auto N = 10u;
	const auto M = 10u;
	
	
	
	Threadsafe_Stack < int > stack;
	for (auto i = 0u; i < 100; i++)
		stack.push(i);

	std::vector<std::thread> producers(std::thread::hardware_concurrency());
	for (auto i = 0u; i < producers.size(); i++)
	{
		producers[i] = std::thread(produce, M, stack);
	}

	std::vector<std::thread> consumers(std::thread::hardware_concurrency());
	for (auto i = 0u; i < consumers.size(); i++)
	{
		consumers[i] = std::thread(consume, M, stack);
	}

	cv.notify_all();

	std::for_each(producers.begin(), producers.end(), [](auto& thread) {thread.join(); });
	std::for_each(consumers.begin(), consumers.end(), [](auto& thread) {thread.join(); });
	
	

	return EXIT_SUCCESS;
}
