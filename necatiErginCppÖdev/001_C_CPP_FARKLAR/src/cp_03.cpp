//#### C dili tekrarı için sorulmaktadır:</br>
//Aşağıdaki kodda C ve C++ dillerinin kurallarına göre sentaks hatası oluşturan deyimleri *(statements)* işaretleyiniz 
//ve sentaks hatalarının nedenlerini açıklayınız. Her bir gösterici *(pointer)* değişkeni niteleyen ingilizce terimleri yazınız. 
//Soruya bir derleyici, *IDE* ya da yardımcı bira araç kullanmadan yanıt veriniz.


int main()
{
	int x = 10;
	int y = 20;
	
	int * const p1 = &x; //p1 is a constant pointer to int //p1:TOP LEVEL CONST
	const int *p2 = &x;  //p2 is a pointer to constant int 
	int const *p3 = &x; //p3 is a pointer to constant int //p2-p3: LOW LEVEL CONST
	const int* const p4 = &x; //p4 is constant pointer to constant int

	*p1 = 40; //sentaks hatası yok 
	p1 = &y; //p1 constant pointer olduğu için yeni bir adres alamaz
	//neco:p1'e başka adres atılamaz hayatı boyunca aynı değeri tutucak
	*p2 = 40;//p2 pointer to constant int olduğu için salt okuma amacı ile erişmiştir 
	//neco:p2'nin gösterdiği nesnenin değerinin değiştirilmemesi
	p2 = &y;// sentaks hatası yok

	*p3 = 40;//bir önceki ile aynı
	//neco:
	p3 = &y;//sentaks hatası yok
	
	*p4 = 40;//constant int olduğu için salt okuma amacı ile erişebilir.
	//neco:
	p4 = &y;//constant pointer olduğu için yeni bir değer alamaz.
	//neco:
}

//[ödev cevabı](https://www.youtube.com/watch?v=LLP0CyEmkJ0)
