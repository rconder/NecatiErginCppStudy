/* ##### Aşağıdaki her bir kod hakkında yorum yapınız:

``` */
//int &func(int x) // otomatik ömürlü bir nesneyle geri dönüş değeri verilmiş 
//!!!!!!//UNDEFINED BEHAVIOR
/* {
	return x;
} */

int main()
{
	int y = 20;
	func(y) = 50; 
}
/* ```



``` */
#include <iostream>

int main()
{
	const int x = 20;
	auto y = x;//tür çıkarımında intlik düşücek int y = x olacak
	++y;

	std::cout << y << " " << x << "\n"; // 21 20

}
/* ```



``` */
#include <iostream>

int main()
{
	int x = 10;
	int &r1 = x; // r1 x'e referans
	auto r2 = x; // int r2 = x
	auto &r3 = r2; //r3 r2'ye referans

	r2 += 5; //r2=>15 &r3=>15
	r3 += 20;//r2=>35 &r3=>35
	++x; // &r1 => 11

	std::cout << r1 + r2 + r3 << "\n"; // 11 + 35 + 35
}
/* ```


``` */
int main()
{
	int x = 10;
	const int &cr = x;// cr const int ref olduğu için
	auto &r = cr; //r'de const int ref yani tanımlama const int &r 

	//++r; //const nesnenin artırılması demek sentaks hatası 
}
/* ```


```
 */
#include <iostream>

int main()
{
	int a[] = { 0, 1, 2, 3, 4, 5 };
	auto r1 = a; //int * r1 = a; 
	auto &r2 = a; //r2 auto ile birlikte kullanıldığı için => int (&r) [6] = a demek

	++r2[3];//3.indis 1 arttı
	std::cout << (r1[3] == r2[3]) << "\n"; //değerleri birbirine eşit olduğu için ekran çıktısı 1 olacak
}
/* ```


```
 */
#include <iostream>

int main()
{
	int a[] = { 10, 20, 30, 40 };
	auto p = a; //int *p = a array dikey
	auto &r = p; // int * &r = p // r'pye bağlanmış bir isim
	++r;//p dizinin 2. elemanını gösteriyor
	++p;//3. elemanını gösteriyor

	std::cout << *r << "\n"; // 30 değeri bastırılır.
}
/* ```

``` */
#include <iostream>

int &func(int &r)
{
	++r;
	return r;
}

int main()
{
	int x = 10;
	auto f = func;//f bir function pointer int &(*f)(int & ) // hata çok fazla func olduğu için 
	auto y = f(x);//ynin değeri 11 xin dğeeri 11
	auto &r = f(x);//x 12 ve r x'e referans
	r += 400;//r => x => 412
	y += 50; // y => 61

	std::cout << "x = " << x << "\n"; // 412

}
/* ```


``` */
#include <iostream>

int main()
{
	int x = 10;
	int *ptr = &x; // ptr xin adresini tutuyor

	auto r1 = x; //r1 ayrı bir değişken değeri 10
	auto r2 = *ptr; // r2 ayrı bir değişken değeri 10
	auto r3 = r2; //r3 ayrı bir değişken değeri 10
	auto &r4 = ptr;//int * &ptr' ye referans r4 demek ptr demek
	auto &r5 = *ptr;//r5 ise x'se referans

	r1 += 3;//r1 = 13
	r2 += 13; //r2 = 23
	r3 += 20; //r3 = 30
	*r4 += r2;// x = 33
	++r5; // x = 34

	std::cout << "x = " << x << "\n"; // 34 bastırmalı

}
/* ```

[ödev cevabı](https://www.youtube.com/watch?v=F9teyZ8eHi8)
 */