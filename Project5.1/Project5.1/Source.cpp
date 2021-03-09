#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>

#include <Windows.h> 

int main(int argc, char** argv)
{

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);


	std::istringstream in("123456 €");
	std::string v3;
	in.imbue(std::locale("deu_deu.UTF-8"));
	in >> std::get_money(v3, false);
	if (in)
	{
		std::ostringstream sout;
		sout.imbue(std::locale("ru_Ru.utf8"));
		sout << std::showbase << std::put_money(v3, false) << std::endl;

		sout.imbue(std::locale("sv_SE.utf8"));
		sout << std::showbase << std::put_money(v3, false) << std::endl;

		sout.imbue(std::locale("ja_JP.utf8"));
		sout << std::showbase << std::put_money(v3, false) << std::endl;

		sout.imbue(std::locale("en_US.utf8"));
		sout << std::showbase << std::put_money(v3, false) << std::endl;
		std::cout << sout.str() << std::endl;
	}
	else
	{
		std::cout << "Parse failed\n";
	}


}