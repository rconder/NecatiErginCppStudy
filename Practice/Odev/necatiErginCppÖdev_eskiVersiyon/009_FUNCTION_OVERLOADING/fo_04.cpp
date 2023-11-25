/* #### Aşağıdaki kodda yapılan işlev çağrılarının durumunu belirtin. Geçerli mi değil mi? Geçerli ise çağrılan işlev hangisidir?

``` */
enum Color {Blue, Green, Red};
//
void func(Color);
void func(unsigned int);

void foo()
{
	func(12);

	//
}
/* ```
Cevap:
Burada enum Color türü tanımlanmış
2 fonksiyon bildirimi var function overloading var
Int türünden color türüne dönüşüm yok 
Cpp'da aritmetik türlerden enum türlerine dönüşüm yok
Tek uygun fonksiyon alttaki func(unsigned int ) fonksiyonu olduğu için o çağırılacak.


[ödev cevabı](http s://vimeo.com/433284105)
 */