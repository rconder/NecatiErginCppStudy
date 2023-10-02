/* #### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?
### her bir fonksiyon çağrısı için ayrı cevap verilecek
 */
//```
#include <iostream>
 
void display(char const *ptr)
{
	std::cout << ptr;
}
 
void display(unsigned int uval)
{
	std::cout << uval;
}
 
int main()
{
	display("abc");//fonksiyon char const *ptr çağırılıcak
	display(0);//call to 'display' is ambiguous burada exact match yok 
	//2 conversion var ve ambiguity oluşuyor
	display('A');//üstteki fonksiyon vaible değil 
	//tek çağırılabilecek fonksyion alttaki
}
//x```

/* __Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*

[ödev cevabı](https://vimeo.com/433292846)
 */