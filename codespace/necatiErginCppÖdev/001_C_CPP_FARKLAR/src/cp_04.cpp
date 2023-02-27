/*
#### C dili tekrarı için sorulmaktadır: <br>
Aşağıdaki kod hakkında yorum yapınız. Bu kodda bir sentaks hatası var mı? Yok ise, bu kod çalıştırılırsa standart çıkış akımına ne yazılır? Bir derleyici ya da IDE kullanmadan yanıt veriniz.


```
*/
#include <stdio.h>

int main()
{
	const int x = 55;
	int *ptr = (int *)&x;
	*ptr = 99;

	printf("x = %d\n", x);
}
/*
```
x const bir nesne fakat x nesnesinin adresi tür dönüştürme operatörü ile tür değiştirilerek ilk değer olarak verilmişti.
Eğer tür dönüşümü kullanılmasaydı CPP'ta hataya sebep verecekti
Const nesnelerinin değiştirilme girişimi HER ZAMAN UNDEFINED BEHAVIOR YARATIYOR. 


[Ödevin cevabı](https://www.youtube.com/watch?v=rxdCwJFRNLI)
*/