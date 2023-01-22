#### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?


```
#include <iostream>
 
void func(int)
{
	std::cout << "int";
}
 
void func(double)
{
	std::cout << "double";
}
 
 
int main()
{
	func(2.F);
}
```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*

[ödev cevabı](https://vimeo.com/433296786)
