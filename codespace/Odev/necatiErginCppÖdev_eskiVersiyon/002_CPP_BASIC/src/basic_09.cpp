/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */
#include <iostream>

int main()
{
	int x = 10;
	int y = 20;
	int z;
	z = x, y; //expression result unused uyarısı verir, z'ye x'in değerini atar
	std::cout << z;
}
/* ``` */
