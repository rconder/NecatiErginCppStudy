/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */
#include <iostream>

int main()
{
	int x = 5;
	decltype((x)) y{ x }; // operand olarak verilen ifade (x) ifadesi parantez kullanılmasaydı elde edilcek tür int olcaktı
						  // ifadenin değer kategorisine bağlı olacağı için buradaki int & y = x olur
	decltype(y *= 2) z = x; // y *= 2 ifadesi bir lval kategorsi burada bu ifade için işlem kodu üretilmeyecek 
							// ifade int & z = x olacak
	decltype(y--) t = x; 	// y-- ifadesi prval expression buradan elde edilen tür int t = x elde edilir.

	int &rx{ x }; 
	auto ax{ rx }; // int ax = rx burada referanslık düştü

	++y;// ++ x  => x = 6
	z *= 2; // X*2 => x = 12
	t *= 5; // t = 60
	ax += 10; // ax = 120 

	std::cout << "x = " << x << "\n"; // x  = 12 
}

/* ```

[ödevin cevabı](https://www.youtube.com/watch?v=Eg279cxMVZM)
 */