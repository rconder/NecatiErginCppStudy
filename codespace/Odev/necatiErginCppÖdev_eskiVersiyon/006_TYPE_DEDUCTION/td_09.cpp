/* #### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

``` */
#include <iostream>

int main() 
{
	int x = 0;
	decltype((x)) y = x; //int & y = x olucak
	decltype(x) z = x; //isim formunda olduğu için x'in bildirim türü elde edilecek int z = x olur
	++x; // x =1 
	y += 2;//x = 3
	z += 5; // z = 5

	std::cout << x << y << z; //335
}

/* ```

[ödevin cevabı](https://youtu.be/jWztamUwSp0)
 */