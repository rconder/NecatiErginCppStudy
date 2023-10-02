/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */
#include<iostream>

void func(int& ra, const int& rb) //1.parametre int ref 2.parametre const int ref
{
	std::cout << rb;
	ra = 1;
	std::cout << rb;
}

int main() 
{
	int ival = 0;

	func(ival, ival);
/* 
	çıktısı: 01
*/

}


/* 
```

[ödev cevabı](https://www.youtube.com/watch?v=Yo5hIMVW7CM)
 */