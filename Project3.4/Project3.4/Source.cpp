#include <iostream>
#include <vector>
#include <string>
#include<set>
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

int main()
{
    int N = 308915776;
    char s[]="aaaaaa";
    std::vector<char*> v;
    v.reserve(N);
    


    for (auto i1 = 97; i1 <= 122; i1++)
    {
        for (auto i2 = 97; i2 <= 122; i2++)
        {
            for (auto i3 = 97; i3 <= 122; i3++)
            {
                for (auto i4 = 97; i4 <= 122; i4++)

                {
                    for (auto i5 = 97; i5 <= 122; i5++)
                    {
                        for (auto i6 = 97; i6 <= 122; i6++)
                        {
                            s[0] = static_cast<char>(i1);
                            s[1] = static_cast<char>(i2);
                            s[2] = static_cast<char>(i3);
                            s[3] = static_cast<char>(i4);
                            s[4] = static_cast<char>(i5);
                            s[5] = static_cast<char>(i6);
                            v.push_back(s);
                        }


                    }

                }
            }
        }
    }
    

    size_t collisions_0 = 0;
    size_t collisions_1 = 0;
    size_t collisions_2 = 0;
    size_t collisions_3 = 0;
    size_t collisions_4 = 0;
    size_t collisions_5 = 0;
    size_t collisions_6 = 0;
    size_t collisions_7 = 0;
    size_t collisions_8 = 0;
    std::set<int> set0;
    std::set<int> set1;
    std::set<int> set2;
    std::set<int> set3;
    std::set<int> set4;
    std::set<int> set5;
    std::set<int> set6;
    std::set<int> set7;
    std::set<int> set8;
    size_t h = 0;
    N = 1000;
    for ( int i = 0; i < N; i++)
    {
        h = RSHash(v[i],6) % (N * 10);
        collisions_0 += set0.count(h);
        set0.insert(h);

        h = JSHash(v[i], 6) % (N * 10);
        collisions_1 += set1.count(h);
        set1.insert(h);

        h = PJWHash(v[i], 6) % (N * 10);
        collisions_2 += set2.count(h);
        set2.insert(h);

        h = ELFHash(v[i], 6) % (N * 10);
        collisions_3 += set3.count(h);
        set3.insert(h);

        h = BKDRHash(v[i], 6) % (N * 10);
        collisions_4 += set4.count(h);
        set4.insert(h);

        h = SDBMHash(v[i], 6) % (N * 10);
        collisions_5 += set5.count(h);
        set5.insert(h);

        h = DJBHash(v[i], 6) % (N * 10);
        collisions_6 += set6.count(h);
        set6.insert(h);

        h = DEKHash(v[i], 6) % (N * 10);
        collisions_7 += set7.count(h);
        set7.insert(h);

        h = APHash(v[i], 6) % (N * 10);
        collisions_8 += set8.count(h);
        set8.insert(h);




    }

    std::cout << "RSHash" << collisions_0 << std::endl;
    std::cout << "JSHash" << collisions_1 << std::endl;
    std::cout << "PJWHash" << collisions_2 << std::endl;
    std::cout << "ELFHash" << collisions_3 << std::endl;
    std::cout << "BKDRHash" << collisions_4 << std::endl;
    std::cout << "SDBMHash" << collisions_5 << std::endl;
    std::cout << "DJBHash" << collisions_6 << std::endl;
    std::cout << "DEKHash" << collisions_7 << std::endl;
    std::cout << "APHash" << collisions_8 << std::endl;



}