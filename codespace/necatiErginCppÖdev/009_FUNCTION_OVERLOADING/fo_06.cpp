/* #### Aşağıdaki kodlardan herbirinde function overloading ("işlev yüklemesi") olup olmadığını belirtin. Her bir kod için açıklama yapın:

*/
//``` 
void func(int);

void foo()
{
	extern func(int, int);
}
//fonksiyonların bildirimleri farklı scope'ta 
//func overloading yok
//```

//```
int func(double);
double func(double);

// parametreleri ve imzaları aynı, fakat yeniden bildirimde değil bu bir sentaks hatası 
//```

//``` 
int f(double);
int f(double = 0.);
//ilave bildirim/yendien bildirim function overloading değil
//```


//```
int g(int);
int g(const int);
//imzalar arasında farklılık yok redeclaration
//```

//```
int g(int *p);
int g(int* const p);
//imzalar arası farklılık yok redeclaration
//```

//```
int f(int *p);
int f(const int *p);
//ayrı türler ve function overloading
//```

//```
//imzalar farklı function overloading
void func(int &);
void func(const int &);
//```

//```
//function overloading

void g(int);
void g(int &);
//```

//```
//sol taraf referansı ve sağ taraf referansı
//function overloading
void foo(int &);
void foo(int &&);
//```

//```
//function overloading
void f(const double &);
void f(double &&);
//```

//```
typedef int Word;
//her iki bildirimde eş redeclaration dolayısıyla sentaks hatası yok
void f(Word);
void f(int);
//```

//```
//Bunlar farklı türler enum türünün underline  türünden bağımsız türler 
// o yüzden function overloading
enum Color {gray, red, blue};
void g(Color);
void g(int);
//```

//```
#include <cstdint>
//burada function overloading türünde
//int32_t türünün nasıl tanımlandığına bağlı olarak değişir
void func(int32_t);
void func(int);
//```

//```
//function overloading
int f(bool);
int f(int);
//```

//```
//char16_t ayrı bir tür 
//char32_t anahtar sözcükler
void foo(char16_t);
void foo(int);
//```

//```
//farklı türler 
//ayrı türler function overloading
void func(char);
void func(signed char);
//```

//```
//function overloading
void f(char);
void f(unsigned char);
//```

//```
//fonksiyon pointer'ı
//fonksiyon referansı
//function overloading
void foo(int(*)(int));
void foo(int(&)(int));
//```

//```
void g(int[10]);//bu bir pointer 
//her ikiside int'e pointer ve redeclaration
void g(int *p);
//tanımlayarak anlaşılabilir. 
//```

//```
void foo(int(&)[10]);
void foo(int(&)[20]);
//üstteki fonksiyon 10 elemanlı bir diziye referansken
//alttaki 20 elemanlı bir diziye referans ve bunlar farklı türler.
//function overloading
//```
/* 
[ödev cevabı](https://vimeo.com/433290281)
 */