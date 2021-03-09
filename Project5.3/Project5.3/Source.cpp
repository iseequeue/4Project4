#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv)
{
	//check usernames: alnums or _, check dots
	//check domains: alnums or . or-, check dots and -
	std::string data = "check usernames1.1.1.@1 n@1 ._1.1.1@1 1.1..1.@1 1.1.1.@1; check domains 1@1.1 1@.1.1  1@1..1 1@1.1. PP 1@1-1 1@-1.1  1@1--1 1@-1.1.-";

	std::regex pattern(R"((\w+[.]{1})*(\w+)@(\w+[.]{1})*(\w+))");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});


}