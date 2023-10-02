/* #### Aşağıdaki kodda yapılan işlev çağrılarının durumunu belirtin. Geçerli mi değil mi? Geçerli ise çağrılan işlev hangisidir?

``` */
void func(int);  	//1
void func(double); 	//2
void func(long);  	//3
void func(bool); 	//4
//hepsi overload pparametre türlerinin hepsi farklı
void foo()
{
	int x = 10;

	func('A');
	// char'dan int'e dönüşüm promotion fakat diğerleri için conversion 
	// o yüzden int parametreli çağırılır
	func(2.3F);
	//float'tan double'a dönüşüm 
	//!!!func(4u);
	//fonksiyonların hepsi için dönüşüm bu yüzden ambiguity olucak 
	//çift anlamlılık olduğu için sentaks hatası oluşmuş olacak
	func(10 > 5);
	// bu ifadenin türü c++'da bool exact match olduğu için bool ifadesi çağırılacak
	func(&x);
	//pointer türünden diğer aritmetik türlere dönüşüm yok 
	//1-2-3 o yüzden zaten geçerli değil 
	//fakat pointer türlerinden bool türüne dönüşüm var nesne adresi true değer gibi yollanmış oluyor
	//4 nolu fonksiyon çağırılıyor.
	//!!func(nullptr);
	//hiçbir fonksiyon viable değil sentaks hatası
}
/* ```

[ödev cevabı](https://vimeo.com/433280009)
 */