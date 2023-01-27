/*
Aşağıdaki kaynak kod

+ C dilinin kurallarına göre derlenip çalıştırıldığında ne olur?
+ C++ dilinin kurallarına göre derlenip çalıştırıldığında ne olur?
+ **#include <stdbool.h>** Önişlemci komutu koda eklenerek C dilinin kurallarına göre derlenip çalıştırıldığında ne olur?
   
```
*/
#include <stdio.h>

int main()
{
#if true
	printf("dogru\n");
#else
	printf("yanlis\n");
#endif

}
/*
```
CPP için çalışır ve dogru string literalini ekrana basar
C için stdbool eklenirse dogru string literalini ekrana basarken eklenilmediği durumda yanlis string literalini ekrana basar

[ödev cevabı](https://www.youtube.com/watch?v=pYURmEJYnWU)
*/