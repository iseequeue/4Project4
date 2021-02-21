#include <iostream>
const int precision = 5;
const int slots = 128;
int hash(double d)
{
	double mant = abs(d);
	int exp = 0;
	int h = (d>0.0)?1:0;
	if (mant > 1.0)
	{
		for (exp; mant > 1.0; exp++)
		{
			mant /= 10;
		}
	}
	else
	{
		for (exp; mant < 1.0; exp--)
		{
			mant *= 10;
		}
	}
	mant *= 10;
	d--;
	for (int i = 0; i < precision; i++)
	{
		h = h * 51 + floor(mant);
		mant = (mant - floor(mant)) * 10;
	}
	return (h * 51 + exp)%slots;


	
}



int main()
{
	std::cout << "hash( " << 33.14 << " ) = " << hash(33.14) << std::endl;
	std::cout << "hash( " << -33.14 << " ) = " << hash(-33.14) << std::endl;
	std::cout << "hash( " << 3.14 << " ) = " << hash(3.14) << std::endl;
	std::cout << "hash( " << 3.139 << " ) = " << hash(3.139) << std::endl;
	std::cout << "hash( " << 3.1411 << " ) = " << hash(3.1411) << std::endl;
	std::cout << "hash( " << 3.14112 << " ) = " << hash(3.14112) << std::endl;

}