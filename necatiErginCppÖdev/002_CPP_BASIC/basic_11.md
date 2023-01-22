#### Aşağıdaki ifadelerin her birinin değer kategorisini (value category) belirtiniz:

```
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

	// x   
	// x + 5
	// &x
	// &y
	// y
	// ++x
	// x++
	// --x
	// x--
	// (x, y)
	// x > 5 ? x : y
	// x > 5 ? x : 7
	// x > y
	// x && y
	// +x
	// -x
	// (double)x
	// f1()
	// f2()
	// f3()
	// r
	// rr
	// nec
	// nec.x
	// ptr
	// *ptr
	// &ptr
	// ptr->a
	// &ptr->a
	// ptr + 1
	// a
	// *a
	// a + 3
	// a[4]
	// nr
	// nr.a
	// int()
	// int{}
	// Nec()
	// Nec{}
}
```
