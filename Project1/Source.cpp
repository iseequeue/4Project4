#include <iostream>
#include <vector>
int main()
{
	std::vector<int> a;
	//for (int i = 0; i <= 100; ++i)
	//{
	//	std::cout << i<<" elements : "<< a.capacity() << " capacity;\n";
	//	a.push_back(0);
	//}

	/*a.reserve(50);
	for (int i = 0; i <= 100; ++i)
	{
		std::cout << i << " elements : " << a.capacity() << " capacity;\n";
		a.push_back(0);
	}*/
	
	try
	{
		a.reserve(1000000000000);
		for (int i = 0; i <= 100; ++i)
		{
			std::cout << i << " elements : " << a.capacity() << " capacity;\n";
			a.push_back(0);
		}
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
/*without reserve k=1.5
0 elements : 0 capacity;
1 elements : 1 capacity;
2 elements : 2 capacity;
3 elements : 3 capacity;
4 elements : 4 capacity;
5 elements : 6 capacity;
6 elements : 6 capacity;
7 elements : 9 capacity;
8 elements : 9 capacity;
9 elements : 9 capacity;
10 elements : 13 capacity;
11 elements : 13 capacity;
12 elements : 13 capacity;
13 elements : 13 capacity;
14 elements : 19 capacity;
15 elements : 19 capacity;
16 elements : 19 capacity;
17 elements : 19 capacity;
18 elements : 19 capacity;
19 elements : 19 capacity;
20 elements : 28 capacity;
21 elements : 28 capacity;
22 elements : 28 capacity;
23 elements : 28 capacity;
24 elements : 28 capacity;
25 elements : 28 capacity;
26 elements : 28 capacity;
27 elements : 28 capacity;
28 elements : 28 capacity;
29 elements : 42 capacity;
30 elements : 42 capacity;
31 elements : 42 capacity;
32 elements : 42 capacity;
33 elements : 42 capacity;
34 elements : 42 capacity;
35 elements : 42 capacity;
36 elements : 42 capacity;
37 elements : 42 capacity;
38 elements : 42 capacity;
39 elements : 42 capacity;
40 elements : 42 capacity;
41 elements : 42 capacity;
42 elements : 42 capacity;
43 elements : 63 capacity;
44 elements : 63 capacity;
45 elements : 63 capacity;
46 elements : 63 capacity;
47 elements : 63 capacity;
48 elements : 63 capacity;
49 elements : 63 capacity;
50 elements : 63 capacity;
51 elements : 63 capacity;
52 elements : 63 capacity;
53 elements : 63 capacity;
54 elements : 63 capacity;
55 elements : 63 capacity;
56 elements : 63 capacity;
57 elements : 63 capacity;
58 elements : 63 capacity;
59 elements : 63 capacity;
60 elements : 63 capacity;
61 elements : 63 capacity;
62 elements : 63 capacity;
63 elements : 63 capacity;
64 elements : 94 capacity;
65 elements : 94 capacity;
66 elements : 94 capacity;
67 elements : 94 capacity;
68 elements : 94 capacity;
69 elements : 94 capacity;
70 elements : 94 capacity;
71 elements : 94 capacity;
72 elements : 94 capacity;
73 elements : 94 capacity;
74 elements : 94 capacity;
75 elements : 94 capacity;
76 elements : 94 capacity;
77 elements : 94 capacity;
78 elements : 94 capacity;
79 elements : 94 capacity;
80 elements : 94 capacity;
81 elements : 94 capacity;
82 elements : 94 capacity;
83 elements : 94 capacity;
84 elements : 94 capacity;
85 elements : 94 capacity;
86 elements : 94 capacity;
87 elements : 94 capacity;
88 elements : 94 capacity;
89 elements : 94 capacity;
90 elements : 94 capacity;
91 elements : 94 capacity;
92 elements : 94 capacity;
93 elements : 94 capacity;
94 elements : 94 capacity;
95 elements : 141 capacity;
96 elements : 141 capacity;
97 elements : 141 capacity;
98 elements : 141 capacity;
99 elements : 141 capacity;
100 elements : 141 capacity;
================================*/

/*with reserve k = 1.5
0 elements : 50 capacity;
1 elements : 50 capacity;
2 elements : 50 capacity;
3 elements : 50 capacity;
4 elements : 50 capacity;
5 elements : 50 capacity;
6 elements : 50 capacity;
7 elements : 50 capacity;
8 elements : 50 capacity;
9 elements : 50 capacity;
10 elements : 50 capacity;
11 elements : 50 capacity;
12 elements : 50 capacity;
13 elements : 50 capacity;
14 elements : 50 capacity;
15 elements : 50 capacity;
16 elements : 50 capacity;
17 elements : 50 capacity;
18 elements : 50 capacity;
19 elements : 50 capacity;
20 elements : 50 capacity;
21 elements : 50 capacity;
22 elements : 50 capacity;
23 elements : 50 capacity;
24 elements : 50 capacity;
25 elements : 50 capacity;
26 elements : 50 capacity;
27 elements : 50 capacity;
28 elements : 50 capacity;
29 elements : 50 capacity;
30 elements : 50 capacity;
31 elements : 50 capacity;
32 elements : 50 capacity;
33 elements : 50 capacity;
34 elements : 50 capacity;
35 elements : 50 capacity;
36 elements : 50 capacity;
37 elements : 50 capacity;
38 elements : 50 capacity;
39 elements : 50 capacity;
40 elements : 50 capacity;
41 elements : 50 capacity;
42 elements : 50 capacity;
43 elements : 50 capacity;
44 elements : 50 capacity;
45 elements : 50 capacity;
46 elements : 50 capacity;
47 elements : 50 capacity;
48 elements : 50 capacity;
49 elements : 50 capacity;
50 elements : 50 capacity;
51 elements : 75 capacity;
52 elements : 75 capacity;
53 elements : 75 capacity;
54 elements : 75 capacity;
55 elements : 75 capacity;
56 elements : 75 capacity;
57 elements : 75 capacity;
58 elements : 75 capacity;
59 elements : 75 capacity;
60 elements : 75 capacity;
61 elements : 75 capacity;
62 elements : 75 capacity;
63 elements : 75 capacity;
64 elements : 75 capacity;
65 elements : 75 capacity;
66 elements : 75 capacity;
67 elements : 75 capacity;
68 elements : 75 capacity;
69 elements : 75 capacity;
70 elements : 75 capacity;
71 elements : 75 capacity;
72 elements : 75 capacity;
73 elements : 75 capacity;
74 elements : 75 capacity;
75 elements : 75 capacity;
76 elements : 112 capacity;
77 elements : 112 capacity;
78 elements : 112 capacity;
79 elements : 112 capacity;
80 elements : 112 capacity;
81 elements : 112 capacity;
82 elements : 112 capacity;
83 elements : 112 capacity;
84 elements : 112 capacity;
85 elements : 112 capacity;
86 elements : 112 capacity;
87 elements : 112 capacity;
88 elements : 112 capacity;
89 elements : 112 capacity;
90 elements : 112 capacity;
91 elements : 112 capacity;
92 elements : 112 capacity;
93 elements : 112 capacity;
94 elements : 112 capacity;
95 elements : 112 capacity;
96 elements : 112 capacity;
97 elements : 112 capacity;
98 elements : 112 capacity;
99 elements : 112 capacity;
100 elements : 112 capacity;
==============================*/

// a.reserve(1000000000) - debug error abort() has been called/// VECTOR TOO LONG
}