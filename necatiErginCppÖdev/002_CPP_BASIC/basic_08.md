#### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?


```
#include <iostream>
 
int main() 
{
	void * vp = &vp, **vpp = &vp;
	std::cout << bool(vp) << bool(*vpp);
}
```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*
