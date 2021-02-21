#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
	seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

class Customer
{
private:
	friend struct Customer_Hash;
	friend struct Customer_Equal;

public:
	explicit Customer(const std::string& name, const std::size_t mark) :
		m_name(name), m_mark(mark)
	{}

	~Customer() noexcept = default;

public:
	friend std::ostream& operator << (std::ostream& stream, const Customer& customer)
	{
		return (stream << customer.m_name << "," << customer.m_mark);
	}

private:
	std::string m_name;
	std::size_t m_mark;
};

struct Customer_Hash
{
	std::size_t operator() (const Customer& customer) const noexcept
	{
		return hash_value(customer.m_name, customer.m_mark);
	}
};

struct Customer_Equal
{
	bool operator() (const Customer& lhs, const Customer& rhs) const noexcept
	{
		return (lhs.m_name == rhs.m_name);
	}
};

int main(int argc, char** argv)
{
	int N = 676 * 26*26*26;
	std::string s;
	std::vector<std::string> v;
	v.reserve(N);
	size_t collisions = 0;
	std::set<int> set;


	for (auto i1 = 97; i1 <= 122; i1++)
	{
		for (auto i2 = 97; i2 <= 122; i2++)
		{
			for (auto i3 = 97; i3 <= 122; i3++)
			{
				for (auto i4 = 97; i4 <= 122; i4++)
					
					{
					for (auto i5 = 97; i5 <= 122; i5++)
						{
							s.clear();
							s.push_back(static_cast<char>(i1));
							s.push_back(static_cast<char>(i2));
							s.push_back(static_cast<char>(i3));
							s.push_back(static_cast<char>(i4));
							s.push_back(static_cast<char>(i5));
							v.push_back(s);
						}
					}
			}
		}

	}
	size_t h = 0;
	for (auto i = 0; i<N;i++)
	{
		Customer i1(v[i], i);
		h = Customer_Hash()(i1)%(N*10);
		collisions += set.count(h);
		set.insert(h);
	}
	
	std::cout << collisions << std::endl;
	

	return EXIT_SUCCESS;
}