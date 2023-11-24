/* #### Aşağıdaki kodlarda (varsa) sentaks hatalarını işaretleyiniz ve sentaks hatalarının nedenlerini belirtiniz:

``` */

void f1()
{
	const int x = 10;
	auto a = x; // constluk düşer  int a = x;
	auto &b = x; // const int çıkarımı yapılcak const int &b olur
	decltype(x) c = 0; // const int c olur

	++a;
	++b;//const int değiştirilemez syntax hatası
	++c;//const int değiştirilemez syntax hatası
}


void f2()
{
	int x = 10;
	int y = 20;
	const int *p = &x; //low level const x'değiştirilemez
	int *const cp = &x; //const pointer to int top level constnast

	auto a = p; // const int* a = p
	auto b = cp; // int * b = cp olur

	a = &y; 
	*a = 20; // sentaks hatası olur çünkü low level const
	b = &y; //b const değil
	*b = 56;  //b'Nin dereference ile elde edilen nesne const değil
}


void f3()
{
	int x = 10;
	int *p = &x;
	int **pp = &p;

	decltype(p) a;   //int *
	decltype(*p) b; // decltype eğer bir expresionsa burada elde edilecek ifadenin türü value category' bağlı
					// *p lvalue olduğu için lval referans elde edilir ve sentaks hatası olur
	decltype(+*p) c;//burada *p + operatorunun operandı olduğu için prval expression 
	//elde edilen türü int türü int c anlamına geliyor
	decltype(pp) d; //int **
	decltype(*pp) e;//lval  olduğu için lval ref olur ilk değer verilmediği için, hata olur 
	decltype(**pp) f;//yine lval expression olduğu için elde edilecek tür int ref
}

void f4()
{
	int arr[]{ 1, 2, 3, 4 };
	decltype(arr)a; //int a[4] bir int dizi olur 
	auto b{ arr }; // int * array dikey olur 
	auto &c{ arr }; //int (&r) [4] biçiminde yazılması gerekli

	++a;//array dikey olucak ve modifible olmadığı için hata olucak
	++b;
	++c;//bu kez c 4 elemanlı diziye referans ++ operandı olamaz
	++*a;//*a dizinin ilk elemanı 1 artırılıcak hata yok
	++*b;
	++*c;// c bir diziye referans bu durumda gene c'nin bağlandığı dizinin ilk elemanına erişilcek
}

void f5()
{
	auto x = 10; //int x = 10
	auto y = &x;// int *y = address of x
	auto z = &y;//int **z = address of y

	y = *z;//pointer to int = pointer to int
	x = **z; // int = int
	y = 0; //y bir pointer, y = nullptr yazılmış gibi TERCİH EDİLMEMELİ
	z = 0;	//Aynı şekilde
}

void f6()
{
	const int x = 10;
	const int &r = x; 
	auto a = r; // constluk düşücek bu ifadenin türü int a = r
	decltype(a) b; // int b
	++a;
	++b;//TANIMSIZ DAVRANIŞ OTOMATİK DEĞİŞKENE INDETERMINED değer ile hayatına başladı
	decltype(*&x) c; // lval expression olduğuu için decltype => lval referans 
	//o yüzden ilk değer vermek zorunlu (const int &)
}

/* ```

[ödevin cevabı](https://www.youtube.com/watch?v=teqFH0i_rok)
 */