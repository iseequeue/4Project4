#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv)
{
	//DD.MM.YYYY
	//HH:MM:SS
	std::string data = "aa 11 31.12.2021 23.59:27 00:505:00 23:69:27 23:00:27 dffd 23:59:27 17.06.2001 21.15.2021 32.01.2021 00.00.4454 23:59:54 ";

	std::regex pattern_date(R"((0?[1-9]|[12][0-9]|3[01])[.](0?[1-9]|1[012])[.]\d{4})");
	std::regex pattern_time(R"(([01][0-9]|2[0-3])([:]([0-5][0-9])){2})");

	std::sregex_iterator begin_data(data.cbegin(), data.cend(), pattern_date);
	std::sregex_iterator begin_time(data.cbegin(), data.cend(), pattern_time);

	std::sregex_iterator end;

	std::for_each(begin_data, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});

	std::for_each(begin_time, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});

}