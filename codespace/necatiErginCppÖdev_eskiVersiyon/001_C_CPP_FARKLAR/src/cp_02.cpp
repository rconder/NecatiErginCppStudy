//#### Aşağıdaki kod hakkında yorum yapmanız isteniyor:

#include <stdio.h>

int nec = 0;

int main()
{
	struct nec {
		char str[64];
	};
	printf("sizeof(nec) = %zu\n", sizeof(nec));
}

/*
	C'de structure tag yapının tür ismi olarak kullanılamıyor
	struct ile birlikte kullanılması gerekiyor 
	bunun için typedef bildirimi zournlu. C derleyicisi lokal alanda nec
	değişkinini bulamayacak ve int türünün sizeof değeri yazdırılıcak
	Eğer C'de 
		typedef struct nec {...} olsaydı C'de de 64 ekranda yazdırılacaktı 

	CPP'da ise typedef bildirimi olmaksızın cpp derleyicisinde ise struct nec 
	ismini bulacak ve struct nec türünün sizeof değeri yazdırılacak ve 
	64 değeri yazdırılıcak


*/

// Bu kod C dilinin kurallarına göre derlenirse ne olur? C++ dilinin kurallarına göre derlenirse ne olur? Açıklayınız.


//[ödevin cevabı](https://www.youtube.com/watch?v=gU3s3HMpQyE)
