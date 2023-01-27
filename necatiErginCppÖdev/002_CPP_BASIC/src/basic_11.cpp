/* #### Aşağıdaki ifadelerin her birinin değer kategorisini (value category) belirtiniz:

``` */
struct Nec {
	int a, b;
};

Nec   f1();
Nec&  f2();
Nec&& f3();

int main()
{
	int x = 10;
	const int y = 20;
	int &r = x;
	int &&rr = x + 5;
	Nec nec;
	Nec *ptr = &nec;
	Nec &nr{ nec };
	int a[10];

	// x   L
	// x + 5 L
 	// &x	PR
	// &y	PR
	// y	L
	// ++x	L
	// x++ PR
	// --x L
	// x-- PR
	// (x, y) L
	// x > 5 ? x : y L 
	// x > 5 ? x : 7 L
	// x > y PR
	// x && y PR
	// +x PR 
	// -x  PR
	// (double)x L
	// f1() L
	// f2() L
	// f3() L
	// r L
	// rr L
	// nec L
	// nec.x L
 	// ptr L
	// *ptr L
	// &ptr PR 
	// ptr->a L
	// &ptr->a PR
	// ptr + 1 PR 
	// a L
	// *a L
	// a + 3 L
	// a[4] L
	// nr L
	// nr.a L 
	// int() 
	// int{}
	// Nec()
	// Nec{}
}
/* ```
 */