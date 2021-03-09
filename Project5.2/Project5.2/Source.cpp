#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <bitset>
#include <chrono>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
#include <vector>
#include <boost/locale.hpp>
#include <unordered_map>
#include <Windows.h>



std::string convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

int main(int argc, char** argv)
{
	system("chcp 1251"); 

	try
	{
		std::unordered_map<int, std::string> map;

		map.insert({ 1072, "a" });
		map.insert({ 1073, "b" });
		map.insert({ 1074, "v" });
		map.insert({ 1075, "g" });
		map.insert({ 1076, "d" });
		map.insert({ 1077, "e" });
		map.insert({ 1105, "yo" });
		map.insert({ 1078, "zh" });
		map.insert({ 1079, "z" });
		map.insert({ 1080, "i" });
		map.insert({ 1081, "y" });
		map.insert({ 1082, "k" });
		map.insert({ 1083, "l" });
		map.insert({ 1084, "m" });
		map.insert({ 1085, "n" });
		map.insert({ 1086, "o" });
		map.insert({ 1087, "p" });
		map.insert({ 1088, "r" });
		map.insert({ 1089, "s" });
		map.insert({ 1090, "t" });
		map.insert({ 1091, "u" });
		map.insert({ 1092, "f" });
		map.insert({ 1093, "h" });
		map.insert({ 1094, "c" });
		map.insert({ 1095, "ch" });
		map.insert({ 1097, "sch" });
		map.insert({ 1096, "sh" });
		map.insert({ 1099, "y" });
		map.insert({ 1100, "y" });
		map.insert({ 1101, "e" });
		map.insert({ 1102, "yu" });
		map.insert({ 1103, "ya" });
		map.insert({ 32, " " });


		
		
		
		std::cout <<"Enter word in russian" << std::endl;		
		std::string string;
		std::getline(std::cin, string);

		
		
	
		std::string u8string = convert_locale_to_utf(string);
		std::u32string u32string = boost::locale::conv::utf_to_utf < char32_t, char >(u8string);
		std::string ss;
		for (auto i : u32string)
		{
			auto it = map.find(i);
			if (it != map.end())
				ss += it->second;
		}


		string = boost::locale::conv::utf_to_utf < char, char32_t >(u32string);
		string = convert_utf_to_locale(string);
		std::cout << "original string: " << string << std::endl;
		std::cout << "transcripted: " << ss << std::endl;
	
		
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Exception: " << exception.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}