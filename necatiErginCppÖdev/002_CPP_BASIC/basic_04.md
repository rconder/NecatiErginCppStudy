#### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?

```
#include <iostream>
 
int main()
{
	std::cout << 2["222"] - '2';
}
```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*
