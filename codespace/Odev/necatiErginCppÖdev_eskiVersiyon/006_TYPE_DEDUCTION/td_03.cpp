/* #### Aşağıdaki C++ programı hakkında yorum yapınız

+ sentaks hatası var ise, hatayı ve hatanın nedenini belirtiniz.
+ tanımsız davranış var ise nedenini belirtiniz.
+ standart çıkış akımına ne yazdırılacağını belirtiniz.

```
 */
#include <iostream>

int main()
{
	const int x = 20;
	auto y = x; // int y = x constluk düşer
	++y;

	std::cout << y << " " << x << "\n";
	// 21 20

}
/* ```

[ödevin cevabı](https://www.youtube.com/watch?v=AYVwPKvnmPI)

 */