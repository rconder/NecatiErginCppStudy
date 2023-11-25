/* #### Sentaks hatası olan satırları belirtiniz:

```
 */
//uto a; // initiallize edilmemiş ilk değer vermek zorunlu,
//int &b; // aynı durum referanslar içinde gerekli
auto c = 10;
int &d = c;
const auto &e = 20; // geçici nesne oluşturuluyor const int &e olduğu için pr expression ile değer verilebilir.
int &f = ++c; 
//int &g = c + 5;//pr expression ile lval ref değer verilemez
int &&h = c % 2;//prval ref sentaks hatası yok
int func(); int &&j = func();//dönüşü pr value olduğu için sorun yok
//int &foo(); int &&m = foo();//dönüş değeri int referans olduğu için (lval expression rval ref'e ilk değer veremez) sentaks hatası
int ival = 10; int &&rval = ival + 10; int &p = rval; //rval data type int && fakat ifade olarak LVAL
/* ```


[ödev cevabı](https://vimeo.com/433277804)
 */