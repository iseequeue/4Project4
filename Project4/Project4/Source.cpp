#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

bool isPrime(int n)
{
    if (n > 1)
    {
        for (int i = 2; i < n/2; i++)
            if (n % i == 0) 
                return false;
        return true;
    }
    else
        return false;
}
int main(int argc, char** argv)
{
	std::vector < int > vector1 = { 1,2,3,4,5,6,7,8,9,10 };                                                              // #1

	std::copy(std::istream_iterator < int >(std::cin), std::istream_iterator < int >(), std::back_inserter(vector1));      // #2
	// 2 3 12 21 12 12 12 89 98 56 81 100 11 9
	std::cout << "vector1: ";
	std::for_each(std::begin(vector1), std::end(vector1), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;

	std::cout << "unique vector1:  ";
	std::sort(std::begin(vector1), std::end(vector1));                                                                              //#4
	vector1.erase(std::unique(vector1.begin(), std::end(vector1)), std::end(vector1));
	std::for_each(std::begin(vector1), std::end(vector1), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;

	std::cout << "vector1 shuffled: ";
	std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(std::begin(vector1), std::end(vector1), dre);                                                               // #3
	std::for_each(std::begin(vector1), std::end(vector1), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;

	std::cout <<"odd numbers: "<< std::count_if(std::begin(vector1), std::end(vector1), [](auto x) {return x % 2; }) << std::endl;               //#5

	auto result = std::minmax_element(std::begin(vector1), std::end(vector1));
	std::cout << "min = " << *result.first << "; max = " << *result.second << std::endl;                                                      //#6
	
	std::cout << "Prime numbers: ";
	std::for_each(std::begin(vector1), std::end(vector1), [](auto x) {if (isPrime(x)) std::cout << x << ' '; });   //#7
	std::cout << std::endl;

	std::for_each(std::begin(vector1), std::end(vector1), [](auto& x) {x *= x; });                                        //#8
	std::cout << "vector1: vector1[i]=vector1[i]^2: ";
	std::for_each(std::begin(vector1), std::end(vector1), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;

	std::vector<int> vector2(vector1.size(), 0);
	std::uniform_int_distribution<> uid(1, 2 * vector1.size());                                                          //9
	std::generate_n(std::begin(vector2), vector1.size(), [&dre, &uid]() {return uid(dre); });
	std::cout << "Random vector2: ";
	std::for_each(std::begin(vector2), std::end(vector2), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;


	auto sum = 0;
	std::for_each(std::begin(vector2), std::end(vector2), [&sum](const auto& x) {sum+=x; });                   //10
	std::cout << "sum of vector2: " << sum << std::endl;

	int ed = 3;
	std::fill_n(std::begin(vector2), ed, 1);
	std::cout << "in vector2 change first 3 by 1: ";
	std::for_each(std::begin(vector2), std::end(vector2), [](const auto& x) {std::cout << x << ' '; });        //11
	std::cout << std::endl;


	std::vector<int> vector3;
	std::transform(std::begin(vector1), std::end(vector1), std::begin(vector2),  std::back_inserter(vector3),
		[](auto a, auto b){ return a-b; });
	std::cout << "vector3 = vector1 - vector2: ";
	std::for_each(std::begin(vector3), std::end(vector3), [](const auto& x) {std::cout << x << ' '; });        //12
	std::cout << std::endl;


	std::for_each(std::begin(vector3), std::end(vector3), [](auto& x) {if (x < 0) x = 0; });
	std::cout << "in vector3 change negative by zero: ";
	std::for_each(std::begin(vector3), std::end(vector3), [](const auto& x) {std::cout << x << ' '; });        //13
	std::cout << std::endl;


	vector3.erase(std::remove_if(std::begin(vector3), std::end(vector3),[](auto x) {return (x == 0); }));
	std::cout << "in vector3 delete zeros: ";
	std::for_each(std::begin(vector3), std::end(vector3), [](const auto& x) {std::cout << x << ' '; });        //14
	std::cout << std::endl;

	std::reverse(std::begin(vector3), std::end(vector3));
	std::cout << "reversed vector3: ";
	std::for_each(std::begin(vector3), std::end(vector3), [](const auto& x) {std::cout << x << ' '; });        //15
	std::cout << std::endl;

	std::nth_element(std::begin(vector3), std::end(vector3)-3, std::end(vector3));                              //16
	std::cout << "top 3 of vector3: " << vector3[vector3.size() - 1] << ' ' << vector3[vector3.size() - 2] << ' ' << vector3[vector3.size() - 3] << std::endl;

	std::sort(std::begin(vector1), std::end(vector1));                                                     //#17  
	std::sort(std::begin(vector2), std::end(vector2));
	std::vector <int> vector4;
	std::merge(std::begin(vector1), std::end(vector1), std::begin(vector2), std::end(vector2), std::back_inserter(vector4));  //#18
	std::cout << "vector 4 merged from vector1 and vector2:\n";
	std::for_each(std::begin(vector4), std::end(vector4), [](const auto& x) {std::cout << x << ' '; });
	std::cout << std::endl;

	
	auto it1 = std::upper_bound(std::begin(vector4), std::end(vector4), 1);            //#19
	auto it0 = std::find(std::begin(vector4), std::end(vector4), 1);
	std::cout <<"diapason for 1: " << std::distance(std::begin(vector4), it0) << ' ';
	std::cout << std::distance(std::begin(vector4), it1) << std::endl;

	std::cout << "vector1: ";                                                                    //#20
	std::copy(std::cbegin(vector1), std::cend(vector1), std::ostream_iterator < int >(std::cout, " "));
	std::cout << "\n vector2: ";
	std::copy(std::cbegin(vector2), std::cend(vector2), std::ostream_iterator < int >(std::cout, " "));
	std::cout << "\n vector3: ";
	std::copy(std::cbegin(vector3), std::cend(vector3), std::ostream_iterator < int >(std::cout, " "));
	std::cout << "\n vector4: ";
	std::copy(std::cbegin(vector4), std::cend(vector4), std::ostream_iterator < int >(std::cout, " "));
	std::cout << std::endl;


	return EXIT_SUCCESS;
}