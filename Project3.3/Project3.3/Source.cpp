#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <random>
#include <algorithm>
#include <chrono>

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


auto makeRandomWords(std::size_t length, int Words = 2000000)
{
	std::uniform_int_distribution letter(97, 122);
	std::default_random_engine e(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::set<std::string> words;
	for (std::string str(length, '_'); words.size() <= Words; words.insert(str))
		for (auto& c : str)
			c = letter(e);
	return words;
}

int main(int argc, char** argv)
{
	std::set<std::string> set1 = makeRandomWords(6);
	const auto Words = 2000000u;
	const auto first = 200000u;
	const auto step = 200000u;

	for (int j = first; j <= Words; j +=step)
	{
		std::set<int> set;
		size_t h1 = 0;
		int k = 0;
		for (auto i : set1)
		{
			h1 = hash_value(k, i);
			set.insert(h1);
			k++;
			if (k == j)
				break;
		}

		std::cout << j<<' '<< j - set.size() << std::endl;

	}
	return EXIT_SUCCESS;
}