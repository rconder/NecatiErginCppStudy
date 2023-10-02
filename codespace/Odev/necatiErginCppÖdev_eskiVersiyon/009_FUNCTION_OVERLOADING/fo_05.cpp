/* #### Aşağıdaki kodda yapılan işlev çağrılarının durumunu belirtin. Geçerli mi değil mi? Geçerli ise çağrılan işlev hangisidir?

``` 
*/
void func(int &);//sol taraf referansı 1
void func(int &&);//sag taraf referansı 2
void func(const int &);//const sol taraf referansı 3

int f1(); //geri dönüş değeri int
int& f2(); //geri dönüş değeri int & 

void foo()
{
	int x = 10;
	const int cx = 20;

	func(x);//sol taraf değeri dolayısıyla 2 nolu fonksiyon uygun değil
	//geriye 1 ve 3 çağırılabilir. const olmayan fonksiyonun seçilebilirliği var
	//1 çaprılır
	func(cx);
	//nesnemiz const olduğu için 3 nolu fonksiyon çağırılacak
	func(x + 5);
	//1 nolu fonksiyon uygun değil fakat 2 ve 3 uygun.
	//sağ taraf değeri ile çağrı yapıldığı için 2'nin seçilebilirliği var
	func(f1());
	//Bu ifadenin değer kategorisi PR-Val. Pr-val expr olduğu için 2 nolu fonksiyon seçilecek.
	func(f2());
	//f2 dönüşü L-Val expression 1. ve 3. fonksiyonlar uygun ve const olmayan bir nesne olduğu için
	//1 nolu fonksiyon çağırılacak.
}
/* ```


[ödev cevabı](https://vimeo.com/433286327)
 */