//#### Aşağıdaki kodda yapılan referans tanımlamalarından geçersiz olanları işaretleyin ve geçersizlik nedenlerini açıklayın:
/*
```
*/

int &f1(); 
int f2();
//f1 olan fonksiyonun geri dönüş değeri int ref
//f2 olan fonksiyonun geri dönüş değeri int
 
int main()
{
	int x = 10;
	int y = 35;
	const int primes[]{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	int a[]{ 1, 2, 4 };
//	int &r1; default initialize edilemezler
	int &r2(++x); //ön ek ++ ve -- ifadeler C'dilinded R val iken C++'da lval
//	int &r3{ 10 }; // Bu ifade '10' pr val expression 
//sol değer referanslarına sağ değer referanslar verilmez. !!!!
	const int &r4{ int() }; //geçici nesne oluşturma ifadeleri -> const lval referanslara sağ taraf ilk değer verilebilir
	const int &r5{ int{} }; //
//	int &r6 = +y; // lval referansına +(sign operator)y => bu değer rvalue expression 
	int &r7 = (x, y); // coma operator C'dilinde R value iken C++ ifadeler 2.operand lvalue expressionsa ifade de lvalue expressions
	int &r8 = x > 10 ? x : y; //turnary operator'un operandları lvalue ise sonuçta lvalue expression oluyor
	int &r9 = f1(); 
//	int &r10 = f2(); // ilk değer veren ifade pr val expression dolayısıyla burada yine bir sentaks hatası var
//	int &r11 = primes[5]; // bunun nedeni CONST olmayan referansa CONST değer verilmesi yüzünden oluşuyor
	int const &r12 = *primes;
	const int &r13{ x }; // CONST olmayan bir nesneye const bir referans bağlanabilir.
//	int *&r14 = a; // düzünün türü ile referansın türü arasında uyumsuzluk var 
//	int(&r15)[] = a;
	int(&r16)[3] = a; // böyle bir tanımlamadan sonra r16 array yerine geçen a için kullanılabilir
}
/*
```
[ödev cevabı](https://www.youtube.com/watch?v=vNR3lPt25GM)
*/