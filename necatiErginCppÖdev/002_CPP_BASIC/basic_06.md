#### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?

```
#include <iostream>
 
int main()
{
	int ival = 0;	//Doktor bu ne ??/
	ival = 1;
	std::cout << ival;	
}
```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*
