#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <random>
#include <algorithm>
#include <chrono>
unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits =
        (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }
    return hash;
}
//===============================================================================================

std::set<std::string> makeRandomWords(std::size_t length, int Words = 10000000u)
{
    std::uniform_int_distribution letter(97, 122);
    std::default_random_engine e(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::set<std::string> words;
    for (std::string str(length, '_'); words.size() <= Words; words.insert(str))
        for (auto& c : str)
            c = letter(e);
    return words;
}
int main()
{
    const int Words = 10000000u;
    std::set<std::string> set1 = makeRandomWords(16);
    const int first = 1000000u;
    const int step = 1000000u;

    for (int j = first; j <=Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = RSHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;
    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = JSHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;
    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = PJWHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;

    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = ELFHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;

    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = BKDRHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;

    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = SDBMHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;

    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = DJBHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;


    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = DEKHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;


    for (int j = first; j <= Words; j = j + step)
    {
        std::set<int> set;
        size_t h1 = 0;
        int k = 0;
        for (auto i : set1)
        {
            h1 = APHash(i.c_str(), 16);
            set.insert(h1);
            k++;
            if (k == j)
                break;
        }

        std::cout << j - set.size() << " ,";

    }
    std::cout << std::endl;


    return EXIT_SUCCESS;
}