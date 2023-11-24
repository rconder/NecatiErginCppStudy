/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */
#include <iostream>

int main() 
{
	int ival = 1;
	const int &r = ival > 0 ? ival : 1; // koşul operatörünün değer kategorisi 2 kategoride olabilir
	//bu operatorun 2. ve 3. operatorun lval olup olmamasına bağlu
	//burada oluşan ifadenin değeride pr val
	//eğer const olmasaydı sentax hatası olurdu 
	//bu referans geçici bir nesneye referans 
	//dolayısıyla burada r=> 1
	//life extension geçerli geçici nesnenin kapsamı 
	ival = 5;
	std::cout << ival << r;
}
/* 

*/


/* ```

[ödev cevabı](https://www.youtube.com/watch?v=oFmWzkmu1cc)
 */