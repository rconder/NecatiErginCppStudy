/* #### Aşağıdaki C++ programı hakkında yorum yapınız

+ sentaks hatası var ise, hatayı ve hatanın nedenini belirtiniz.
+ tanımsız davranış var ise nedenini belirtiniz.
+ standart çıkış akımına ne yazdırılacağını belirtiniz.

```
 */
#include <iostream>

int &func(int &r)
{
	++r;
	return r;
}

int main()
{
	int x = 10;
	auto f = func; //int &(*f)(int & ) şeklinde tanımlanmış bir fonksiyon pointerı olucaktı
	auto y = f(x); // func fonksiyounun geri dönüş değeri int& olmasına rağmen geri dönüş değeri int olucak // y = 11 oldu x = 11 oldu
	auto &r = f(x); //int & r = f(x) olucak //x = 12 fonksiyonun geri dönüş değerini r referansına bağladık. r demek x demek
	r += 400;//x = 412 oldu
	y += 50;// y = 61 oldu

	std::cout << "x = " << x << "\n"; // x = 412
}

/* ```

[ödevin cevabı](https://youtu.be/jWztamUwSp0)
 */