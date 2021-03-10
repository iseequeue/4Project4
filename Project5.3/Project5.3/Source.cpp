#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv)
{
	//check usernames: alnums or _, check dots
	//check domains: alnums or . or-, check dots and -
	std::string data = "check usernames 1.1.1.1@1.1 n@1 ._1.1.1@1.12 1.1..1.@1 1.1.1@11.13.23.123456; check domains 1@1.1 1@.1.1.1234567  1@1..1 1@1.1. PP 1@1-1 1@-1.1  1@1--1 1@-1.1.-";

	std::regex pattern(R"(((\w+[.])*(\w+)@(\w+[.])*(\w{2,6})))");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});


}