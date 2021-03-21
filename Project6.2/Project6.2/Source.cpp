#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
int main(int argc, char** argv)
{
	std::fstream fin;
	fin.open("file.txt", std::ios::in);
	std::string s;
	std::getline(fin, s);

	int n = 5;
	fin.seekg((s.size()+2)*n, std::ios::beg);
	std::getline(fin, s);
	std::cout << s << std::endl;


	return EXIT_SUCCESS;

}
