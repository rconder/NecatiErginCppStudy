/* #### Aşağıdaki kodlardaki (varsa) sentaks hatalarını işaretleyiniz ve nedenlerini açıklayınız:

``` */
int f1(int x)
{
	return x + 1;
}

constexpr int f2(int x)
{
	return x + 2;
}

int g = 10;

constexpr const int *f3()
{
	return &g;
}

void f4()
{
	int a = 10;
	const int b = g;
	constexpr int c = b; // b ifadesi const olmayan bir değişkene bağlandığı için const ifade olarak kullanılamaz
	constexpr int d = f1(sizeof(a)); // f1'fonksiyonu constexpr olarak kullanılamaz
	constexpr int e = f2(sizeof(a)); 
	constexpr int *f = f3();// const int * dan int * const 
	constexpr const int *g = f3();
}
/* ``` */
