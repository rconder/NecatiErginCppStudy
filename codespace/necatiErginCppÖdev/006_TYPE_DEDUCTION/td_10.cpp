/* <!-- #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 


``` --> */
#include <iostream>

int main()
{
	int a[] = { 10, 20, 30, 40 };
	auto p = a; // int * p = a array dikey oldu ve p değişkeni a nın ilk elemanının adresini gösteriyor
	auto &r = p;//int * &r = p olucak
	++r; // a[1]
	++p;// a[2]

	std::cout << *r << "\n"; //30
	
}
/* <!-- ```

[ödevin cevabı](https://www.youtube.com/watch?v=AYVwPKvnmPI)
 --> */