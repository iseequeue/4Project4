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

using people_multi_index = multi_index_container <
	Person,
	indexed_by <hashed_non_unique <member < Person, std::string, &Person::name > >,
	
    random_access <>,	

	ordered_non_unique <member < Person, std::string, &Person::name > > > >;
enum Commands {
	COMMAND_print,
	COMMAND_access,
	COMMAND_find,
	COMMAND_exit,
	COMMAND_number_of_commands
};

int main(int argc, char** argv)
{
	people_multi_index people;

	people.insert({ "K1", 11 });
	people.insert({ "K2", 2 });
	people.insert({ "K3", 82 });
	people.insert({ "K4", 62 });
	people.insert({ "K5", 55 });
	people.insert({ "K6", 6 });
	people.insert({ "K7", 777 });
	people.insert({ "K8", 42 });
	people.insert({ "K9", 19 });
	people.insert({ "K10", 146 });
	int x ;
	while (true)
	{
		std::cout << "You can choose:\n";
		std::cout << "0 - print directory\n";
		std::cout << "1 - random access to data\n";
		std::cout << "2 - find number by person\n";
		std::cout << "3 - exit\n";
		int x;
		std::cin >> x;
		switch (x)
		{
		case COMMAND_print:
		{
			const auto& ordered_name_index = people.get < 2 >();


			for (auto i : ordered_name_index)
			{
				std::cout << i.name << ' ' << i.phone << std::endl;
			}

			std::cout << std::endl;

			break;
		}
		case COMMAND_access:
		{
			int a = -1;
			int b = -1;
			const auto& random_access_index = people.get < 1>();

			while ((a > 0) | (a > b) | (b > random_access_index.size() - 1))
			{
				std::cout << "enter range\n left border:\n";
				std::cin >> a;
				std::cout << "enter right border\n";
				std::cin >> b;
			}
			for (int i = a; i <= b; i++)
				std::cout << random_access_index[i].name << ' ' << random_access_index[i].phone << std::endl;
			break;
		}

		case COMMAND_find:
		{
			std::cout << "Enter name\n";
			std::string s;
			std::cin >> s;

			auto& hashed_name_index = people.get < 0 >();
			std::cout << "number of " << s << " is " << hashed_name_index.find(s)->phone << std::endl;

			std::cout << std::endl;
			break;
		}
		case COMMAND_exit:
		{
			return EXIT_SUCCESS;
		}
		default:
			std::cout << "unknown command\n";
			break;
		}
	}
}