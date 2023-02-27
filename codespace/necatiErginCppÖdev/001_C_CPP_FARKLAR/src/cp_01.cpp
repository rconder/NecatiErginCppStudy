/*
#### Aşağıdaki kaynak koddaki her bir sentaks hatasını

+ C dilinin kurallarına göre
+ C++ dilinin kurallarına 

#### belirleyiniz. Her bir sentaks hatasının nedenini açıklayınız:

*/
#include <stdlib.h>

enum Color {Blue, Red, Yellow};
enum Fruit { Apple, Melon, Mango}; //Bunlarda bir hata yok;

//foo(int, int); //geri dönüş değeri yok C++'da 
//hata fakat C99'a kadar legaldi artık legal değil.

int func();//C++ kurallarına göre parametre değişkeni yok
//C kurallarına göre fonksiyonun parametrik yapısı hakkında bir bildirim yok.

//double sum(a, b) //parametre bildirimi olmalı
//double a, b; bu bildirim olmamalı
double(double a, double)
{
	return a + b;
}
//old style function definition C'nin geçmişinden geliyor
//C++'da ise hiç geçerli olmadı.

int f(int x, int)
{
	return x * x;
}
//C'nin kurallarına göre sentaks hatası parametre değişkeni olmalı
//C++'da function overloading için kullanılıyor.

int g1 = func(); //bu C'de sentaks hatası static nesnelere ilk değer veren ifadeler constant olmalı
//C++'da geçerli 

const int g2; //C'dilinde geçerli const nesnelere ilk değer vermek zorunlu değil 0 değeri ile hayata başlar
//C++'da ilk değer verilmeli 

int main()
{
	const int ci1; //ilk değer verilmemiş C'de yanlış!! ama geçerli çöp değer barındırır tanımsız davranış
    //C++ sentaks hatası    
	const int ci2 = func();
    //Hem C hemde C++'da geçerli     
	//const c3 = 123;
    //C'de geçerli C++ geçersiz (storage class specifier için tür belirtilmeli)
	char *p1 = "necati";
    //C'de geçerli önerilmiyor. C++ const char dizi kabul edildiği için array-dikeye dönüştürülcek.
    //C'de string literalleri salt-okuma için kullanılmalı.

	int i1 = 12.5; //C ve C++'da da geçerli veri kaybı oluşturur.
    //int i1(12.5); olsaydı C++'da sentaks hatası olurdu.
	int i2 = Red; // Red enum constant C'de bu dönüşüm geçerli
    //C++'da da geçerli doğrudan aritmetik dönüştürülüyor.
    //Yeni bir enum kategorisi eklendi enum class'lar.


	//enum Color color1 = 2;
    //C++'da aritmetik türlerden enum türlerine otomatik dönüşüm yok.
    //C'de geçerli fakat tavsiye edilmiyor
	//enum Color color2 = 19;
    //C++'da aritmetik türlerden enum türlerine otomatik dönüşüm yok.
    //C'de geçerli fakat tavsiye edilmiyor

	//enum Color color3 = Mango;
    //C++'da sentaks hatası.
    //C'de geçerli fakat tavsiye edilmiyor.
  
	//!!!! char str[3] = "ali";
    //C'de geçerli str ali dizisini tutar null terminator olmuyacak
    //C++'da geçerli değil burada 4 öğe olduğu için bu kod geçersiz
	enum Color color = Red;
    // Legal
	//!!!! ++color;
    //C'de int gibi bir değişkene tabi tutuluyor onun için legal
    //C++'da bunun geçerli olabilmesi için özel bir fonksiyon tanımlanmalı   
	Fruit f = Mango;
    //C++'da geçerli enum tag aynı zamanda türü betimliyor.
    //C'de sentaks hatası typedef bildirimi zorunlu
	const int cx = 10;
    //Legal
	int ival = 56;    
	//!!!! func(ival);
    // C'de legal 
    // C++'da sentaks hatası.
	//int *ptr = &cx;
    //const int türden int * türüne otomatik dönüşüm yok
    //C'de geçerli fakat legal değil.
	//!!!! char *cptr = &ival;
    // implicit type conversion C++'da yok
    // C'de yanlış olmak ile birlikte legal.
	const int *p2 = &ival;
    //int * türünden const int * türüne dönüşüm geçerli.    
	//!!!! int *p3 = malloc(10 * sizeof(int));
    // malloc'un geri dönüş değeri void * 
    //C++'da void *'dan int * türüne dönüş var
    //C'de doğru ve legal
	int *p4 = 0;
    //C'de ve C++'da da legal 0 => nullptr'ye dönüştürülüyor
    //modern C++'da nullptr kullanılması daha iyi
	int *p5 = NULL;
        //C'de ve C++'da da legal 0 => nullptr'ye dönüştürülüyor
    //modern C++'da nullptr kullanılması daha iyi
}