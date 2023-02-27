/*
#### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

```
*/
#include <iostream> 

typedef long long mylong;

void func(unsigned myllong) //unsigned int türü anlaşılır zaten eğer fonksiyonun parametresi unsigned long long 
//olsaydı sentaks hatası verirdi.
{
	std::cout << '1';
}

void func(unsigned long long) 
{
	std::cout << '2';
}

int main() 
{
	func(0ULL);//unsigned long long yollandığı için 2 değerinin yazdırıldığı fonksiyon çağrılırdır.
	func(0U); //burada ise üstteki fonksiyon çağırılıyor.
}
/*
long long türünün eşizmi
1.fonksiyonun parametresi 
[ödevin cevabı](https://www.youtube.com/watch?v=Xjl2nA5E_Os)
*/