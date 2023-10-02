/* Aşağıdaki bildirimlerden sentaks hatası içerenleri işaretleyiniz. Sentaks hatasının nedenini açıklayınız:



``` */
void f1(int, int = 10, int);
//2.parametre için varsayılan argüman bilg  dirilmiş
//onun sağındaki tüm parametreler içinde bu bildirimin yapılması gerekirdi

void f2(const char *= "error");
//Sentaks hatası maximum munch kuralına takılıyor
// *= bir operator olarak alınıyor bu yüzden bir karakter booşluk olması lazım

int g{};
void f3(int &r = g);
//sentaks hatası yok


void f4(int x = 10, int y = x);
//daha önceki parametreler daha sonraki ifadelerde varsayılan argüman olarak kullanılamaz


void f5(int, int, int = 10);
void f5(int, int, int = 10);
//fonksiyon re-declarationda varsayılan argüman tekrar edilemez



int f6(int x = 10, int y = 20)
{
	return x * x + y - 5;
}
//Sentaks hatası yok

int f7(int, int, int);
int f7(int, int, int = 10);
int f7(int, int = 20, int);
//Sentaks hatası yok çünkü bu bildirimler kümülatif olarak ele alınacak
//int f7(int, int =20, int =10 )


int f8(int = 0);
int f9(int = f8());
int f10(int = f9());
//Sentaks hatası yok



int f11(int = 1);

int f11(int x = 1)
{
	return x + 5;
}
//Sentaks hatası var bildirimde varsayılan argüman bildirildiyse 
//fonksiyonun tanımında bildirilemez.



/* [ödevin cevabı](https://vimeo.com/551895421)



 */