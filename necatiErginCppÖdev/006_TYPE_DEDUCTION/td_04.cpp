/* 
``` */
#include <iostream>

int main()
{
	int x = 10;
	int *ptr = &x;

	auto r1 = x; //int r1 = x
	auto r2 = *ptr; // int r2 = x
	auto r3 = r2; // int r3 = r2
	auto &r4 = ptr; // int * (&r4) = ptr
	auto &r5 = *ptr;// int & r5 = x

	r1 += 3; // r1 = 13
	r2 += 13; // r2 = 23
	r3 += 20; // r3 = 43
	*r4 += r2; // x = 33
	++r5; //34

	std::cout << "x = " << x << "\n";//x = 34

}
/* ```

[ödevin cevabı](https://www.youtube.com/watch?v=5Foj9k1OGTA)
 */