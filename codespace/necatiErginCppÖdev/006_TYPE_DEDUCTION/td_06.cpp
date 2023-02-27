/* #### Aşağıdaki C++ programı hakkında yorum yapınız

+ sentaks hatası var ise, hatayı ve hatanın nedenini belirtiniz.
+ tanımsız davranış var ise nedenini belirtiniz.
+ standart çıkış akımına ne yazdırılacağını belirtiniz.


``` */
#include <iostream>

int main()
{
	int a[] = { 0, 1, 2, 3, 4, 5 };
	auto r1 = a;//önce array dikey uygulanıp a dizisinin ilk elemanın adresine değişicek
				//int * r1 = a olucak refeerans declaratoru olmadığı için oluyor
	auto &r2 = a;// int  (&r2)[6] = a olucak array dikey olmuyucak

	++r2[3];// 3->4 olucak
	std::cout << (r1[3] == r2[3]) << "\n"; // buradaki ifade doğru 
}

/* ```

[ödevin cevabı](https://youtu.be/jWztamUwSp0)
 */