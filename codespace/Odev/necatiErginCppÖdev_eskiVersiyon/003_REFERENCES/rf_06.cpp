/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */

#include <iostream>

int main()
{
	int x{ 1 }, y{ };

	const int &r1 = x > 0 ? x : y++;//r1 => geçici nesne oluşturucak prval
	const int &r2 = x > 0 ? x : ++y;//r2 lval x'e bağlanacak
 	x = 5;
	std::cout << r1 << r2; //15
}

/* ```

[ödev cevabı](https://www.youtube.com/watch?v=C8obQMuvk6k)
 */