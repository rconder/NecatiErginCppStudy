/* #### Aşağıdaki kodda yapılan işlev çağrılarının durumunu belirtin. Geçerli mi değil mi? Geçerli ise çağrılan işlev hangisidir?

``` */
void func(char *p);  //1
void func(const char *p); //2
//const overloading
void foo()
{
	char str[] = "Herb Sutter"; //char dizi
	const char cstr[] = "Stephan Lavavej";//elemanları const olan char dizi
	char *const p1 = str; //const pointer
	const char *p2 = str;//pointer to const
	func(nullptr); //vaible seçilebilirlik kriteri yok ambuguity derleme hatası
	func("Bjarne Stroustrup");//const char * türüne dönüştürülücek 2 numaralı dizi çağırılır.
	func(str); //Her ikisi de vaible char * const olmayan ile çağırıldığı için 1 çağırılcak
	func(cstr);//1 nolu fonksiyon uygun değil o yüzden 2 çağırılcak
	func(p1);//1 nolu fonksiyon çağırılıcak
	func(p2);//2 nolu fonksiyon çağırılıcak
}
/* ```

[ödev cevabı](https://vimeo.com/433282922)
 */