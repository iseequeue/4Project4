#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

bool is_identifier(const std::string& string)
{
	std::regex pattern(R"([_[:alpha:]]\w*)");

	return regex_match(string, pattern);
}

int main(int argc, char** argv)
{
	//DD.MM.YYYY
	std::string data = "aa 11 31.12.2021 17.06.2001 21.15.2021 32.01.2021 00.00.4454";

	std::regex pattern(R"((0?[1-9]|[12][0-9]|3[01])[.](0?[1-9]|1[012])[.]\d{4})");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});


}