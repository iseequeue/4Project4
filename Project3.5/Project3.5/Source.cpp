#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Person
{
	std::string name;
	std::size_t phone;
};

using people_multi_index = multi_index_container <Person, indexed_by <hashed_non_unique <member < Person, std::string, &Person::name > >,
	hashed_non_unique <	member < Person, std::size_t, &Person::phone	> >,random_access <>,	
	ordered_non_unique <member < Person, std::size_t, &Person::phone > > > >;

int main(int argc, char** argv)
{
	people_multi_index people;

	people.insert({ "K1", 11 });
	people.insert({ "K1", 12 });
	people.insert({ "K1", 10 });
	people.insert({ "K2", 22 });
	people.insert({ "K3", 33 });
	people.insert({ "K4", 44 });
	people.insert({ "K5", 55 });
	people.insert({ "K6", 66 });
	people.insert({ "K7", 10 });

	// Simple person

	std::cout << people.count("K1") << std::endl;

	auto& hashed_phone_index = people.get < 1 >();
	std::cout << hashed_phone_index.count(10) << std::endl;

	auto iterator = hashed_phone_index.find(55);
	hashed_phone_index.modify(iterator, [](Person& person) { person.name = "A6"; });

	std::cout << hashed_phone_index.find(66)->name << std::endl;

	std::cout << std::endl;


	//Typography
	const auto & ordered_phone_index = people.get < 3 > ();

	auto begin = ordered_phone_index.lower_bound(13);
	auto end   = ordered_phone_index.upper_bound(44);

	for (; begin != end; ++begin)
	{
		std::cout << begin->name << std::endl;
	}

	std::cout << std::endl;

	// Advert Agency
	const auto& random_access_index = people.get < 2 >();

	std::cout << random_access_index[1].name << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}