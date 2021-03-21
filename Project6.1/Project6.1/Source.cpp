#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
int main(int argc, char** argv)
{
	std::fstream fin;
	fin.open("test.txt", std::ios::in);
	

	std::string text{ std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>() };
	std::cout << text << std::endl;
	std::cout << std::endl;

	bool open = false;
	for (int i = 0; i<text.size(); i++)
	{
		if (text[i] == '"' && text[i-1]!='\ ')
			open ^= 1;
		if (!open)
		{
			if (text[i] == '/' && text[i + 1] == '/')
			{
				int j = i;
				while (text[j] != '\n')
					j++;
				text.erase(i, j - i);
				i--;
			}

			if (text[i] == '/' && text[i + 1] == '*')
			{
				int j = i;
				while (!(text[j] == '*' && text[j+1] =='/'))
					j++;
				text.erase(i, j - i + 2);
			}
		}
			
	}

	std::cout << text;
	std::ofstream out;       
	out.open("test2.txt", std::ios::out);
	if (out.is_open())
	{
		out << text << std::endl;
	}
	return EXIT_SUCCESS;

}
