/* #### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?


``` */
#include <iostream>
 
int main() 
{
	auto x = 0;
	decltype((x)) y = x;// decktype'ın operandı () içine alındığı için elde edilen tür bu ifadenin val kategorisi ile belirlenir
						//sol taraf olduğu için int &y = x olur
	y++; // y arttırıldığında x 1 arttırılcak x = 1 
	std::cout << x << y; // 11 yazmalı
}
/* ```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*
 */