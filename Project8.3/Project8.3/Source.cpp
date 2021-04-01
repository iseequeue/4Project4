#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include<iostream>

template <  typename T,
	typename Container = std::vector<T>,
	typename Compare = std::less<typename Container::value_type>>
class Threadsafe_Priority_Queue
{
public:

	Threadsafe_Priority_Queue() = default;

	Threadsafe_Priority_Queue(const Threadsafe_Priority_Queue& other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_priority_queue = other.m_priority_queue;
	}

	Threadsafe_Priority_Queue& operator=(const Threadsafe_Priority_Queue& other)
	{
		std::scoped_lock lock(m_mutex, other.m_mutex);
		m_priority_queue = other.m_priority_queue;
	}

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_priority_queue.push(value);
		m_condition_variable.notify_one();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_priority_queue.empty(); });
		value = m_priority_queue.top();
		m_priority_queue.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_priority_queue.empty(); });
		auto result = std::make_shared < T >(m_priority_queue.top());
		m_priority_queue.pop();

		return result;
	}

	bool try_pop(T& value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_priority_queue.empty())
		{
			return false;
		}

		value = m_priority_queue.top();
		m_priority_queue.pop();

		return true;
	}

	std::shared_ptr < T > try_pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_priority_queue.empty())
		{
			return std::shared_ptr < T >();
		}

		auto result = std::make_shared < T >(m_priority_queue.top());
		m_priority_queue.pop();

		return result;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_priority_queue.empty();
	}

private:

	std::priority_queue <T,Container,Compare> m_priority_queue;
	std::condition_variable m_condition_variable;

private:

	mutable std::mutex m_mutex;
};

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
	while (!q.empty()) {
		std::cout << q.top() << ' ';
		q.pop();
	}
	std::cout << '\n';
}

int main(int argc, char** argv)
{
	const auto data = { 1,8,5,6,3,4,0,9,7,2 };
	Threadsafe_Priority_Queue < int, std::vector<int>, std::greater<int>> pq;

	pq.push(42);
	pq.push(146);

	auto ptr = pq.wait_and_pop();

	int value;

	bool result = pq.try_pop(value);


	return EXIT_SUCCESS;
}
