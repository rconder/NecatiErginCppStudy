/* #### Aşağıdaki C++ programı hakkında yorum yapınız

+ sentaks hatası var ise, hatayı ve hatanın nedenini belirtiniz.
+ tanımsız davranış var ise nedenini belirtiniz.
+ standart çıkış akımına ne yazdırılacağını belirtiniz.


``` */

#include <iostream>

int main()
{
	int x = 10; 
	const int &cr = x; 
	auto &r = cr; // r için yapılan tür çıkarımında auto => const int olucak 

	//++r; // const bir nesneyi değiştirmeye çalıştığımız için sentaks hatası

	std::cout << "x = " << x << "\n";
}

/* ```

[ödevin cevabı](https://www.youtube.com/watch?v=AYVwPKvnmPI)
 */