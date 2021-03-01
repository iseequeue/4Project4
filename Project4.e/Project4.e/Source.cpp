#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

int main(int argc, char** argv)
{
	std::vector < int > vector1(1000000);
	std::iota(std::begin(vector1), std::end(vector1), 0);
	std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(std::begin(vector1), std::end(vector1), dre);
	std::vector <int> vector2 = vector1;

	std::cout << vector1[50] << ' ' << vector2[50] << std::endl;

	unsigned int count1 = 0;
	unsigned int count2 = 0;

	std::sort(std::begin(vector1), std::end(vector1), [&count1](int a, int b) {count1++; return a > b; });
	std::cout << count1 << std::endl;

	std::nth_element(std::begin(vector2), std::prev(std::end(vector2), 2), std::end(vector2), [&count2](int a, int b) {count2++; return a > b; });
	std::cout << count2 << std::endl;



}