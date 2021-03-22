#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>

#include "json.hpp"

using nlohmann::json;

class Adress
{
public:
	friend std::istream& operator>> (std::istream& in, Adress& add);


	std::string city;
	std::string streetad;
	 std::string postindex;
};

std::istream& operator>> (std::istream& in, Adress& add)
{
	in >> add.city >> add.streetad >> add.postindex;
	return in;
}

class Person
{
public:
	friend std::istream& operator>> (std::istream& in, Person&p );

	std::string firstname;
	std::string lastname;
	bool happy;
	Adress add;
};
std::istream& operator>> (std::istream& in, Person& p)
{
	in >> p.firstname >> p.lastname >> p.happy>>p.add;
	return in;
}

void f(json &j, const Person& p)
{
	j["add"]["city"] = p.add.city;
	j["add"]["streetad"] = p.add.streetad;
	j["add"]["postindex"] = p.add.postindex;
	j["firstname"] = p.firstname;
	j["lastname"] = p.lastname;
	j["happy"] = p.happy;
	
}

int main(int argc, char** argv)
{
	system("chcp 65001");


	int N = 8;
	

	auto path = std::filesystem::current_path();
	std::filesystem::create_directory(path / "directory_1");
	path = path / "directory_1";

	for (int i = 0; i < N; i++)
	{
		std::string s = "output" + std::to_string(i) + ".txt";
		std::filesystem::path path_output = path/s;
		std::fstream fout(path_output.string(), std::ios::out);
		Person p;
		json j;
		std::cin >> p;
		f(j, p);
		fout << std::setw(4) << j;
	}

	
	//Ivan Ivanov 0 Moscow Balsh_89 61123
	return EXIT_SUCCESS;
}