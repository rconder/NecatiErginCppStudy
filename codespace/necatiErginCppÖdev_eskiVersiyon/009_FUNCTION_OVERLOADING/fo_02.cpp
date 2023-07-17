/* #### Aşağıdaki kodda yapılan işlev çağrılarının durumunu belirtin. Geçerli mi değil mi? Geçerli ise çağrılan işlev hangisidir?

``` */
void func(void *);  //1
void func(bool); //2

void foo()
{
	double x = 1.0;

	//!!!func(0);
	//her iki fonksiyonda çağırılabilirdi.
	//0 sabitinden iki türee de dönüşüm conversion o yüzden çift anlamlılık hattası olucak
	//
	func(nullptr);
	//2.fonksiyon vaible değil nullptr void * kopyalanabilir
	func(&x);
	//Her iki fonksiyonda uygun 
	//fakat her ikisi de conversion olmasına rağmen void * olan fonksiyon çağırılacak
	func(x);
	//double'dan void * türüne dönüşüm olmadığı için 1 numaralı fonksiyon uygun değil fakat
	//double'dan bool türüne dönüşüm olduğu için 2 numaralı fonksiyon çağırılacak
}
/* ```

[ödev cevabı](https://vimeo.com/433281751)
 */