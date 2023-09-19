# Type Deduction
- C++'da dilin en önemli parçası
- Run time ile bir alakası yok, tamamiyle **Compile Time** ile alakalı

## *Auto* Type Deduction

'auto' bir place holder, tür çıkarımı auto'ya karşı yapılıyor. Deklaratörlerin (*, &, const) etkisi hala var.  

<code>auto x = expr;</code>  

- Kullanıldığı değişkene ilk değer vermek zorunlu.
- Kod yazmayı kolaylaştırıyor, karmaşık türler yerine daha anlaşılır ve hata yapma riskini azaltıyor.
- Generic programlama konsepti içerisinde kullanılıyor.

---
Integral Promotion: Integerdan küçük data typeları (char, short, ... ) aritmetik işleme sokulursa integer'a promote oluyor

---

~~~cpp
int main()
{
    char c1 = '10';
    char c2 = '20';
    auto x = c1 + c2; //integral promotion oldu ve x'in türü int
}
~~~

- Auto decution sırasında const'luk ve referanslık düşebilir.
~~~cpp
const int x = 10;
auto y = x; //y'nin türü const değil int y'dir 
y = 20;
//ve 
int & r = x;
auto z = r; //z'nin türü int oluyor. int & değil.!
~~~~

### Referans deklaratörü ile Kullanımı
~~~cpp
int a[3] = {1,2,3};
auto &x = a; // x'in türü array decay değil!!!!! int[3] oluyor
~~~
- const'luğu kaybetmiyor.

## *decltype* Specifier

- Decltype içerisindeki expresion unevaluated context yani <code>decltype(++x)</code> burada x'in değeri değişmiyor.
- bir değişkenin türü olur FAKAT value category'si olmaz.
- expressionların value category'leri olur. 
- Constluk ve referanslık korunuyor.
- operand isim biçiminde olmayan expression ise decltype(ifadenin value category'si):
    - PR Val ise decltype'in çıkarımı T
    - L val ise T&
    - X val ise T&&
~~~cpp
int x = 10;
decltype(++x);//int &
int&&foo();
decltype(foo()); //int && 
~~~

## 'constexpr' Keywordü:

Bir const nesneye her zaman ilk değer vermek zorundayız fakat değeri verilen ifade *const* olmak zorunda değil.
 <code>const int y = foo();</code> 

- En büyük avantajı runtime'da yük olacak maliyet getirebilecek fonksiyonların, compile time içerisinde geri dönüş değerinin hesaplanabilmesi.
- C++ eklemeler yapıldıkça kısıtlamaları kalktı. 

**Fonksiyonlarda constexpr**
- Fonksiyonların belirli şartları sağlaması lazım.
- Fonksiyon içindekive kullanılan türevleri leteal olmalı.
<code> constexpr int func(int a, int b){return (a*a)+ (b*b);}</code> 

- Eğer fonksiyona yapılan çağrı constexpr değişkenler veya literaller ile yapılıyorsa geri dönüş değeri COMPILE TIME'da elde ediliyor. Run time içerisinde zaman harcanmamış oluyor.
- Bu tür fonksiyonlara constexpr ifadeler ile çağrı yapılması zorunlu değil.
----
One Definition rule:
> Yazılımsal varlıkların birden fazla definasyonu olmamalı eğer birden fazla olursa program ill-formed olur.  
> Header file'da function definition yapmak ODR ihlaline sebep olabilir ( inline functionlar ile kurtulunabilir.)
---
- constexpr fonksiyonlar implicit olarak inline tanımını başlık dosyasına konabilir.
- static ömürlü ifadelerin adresleri 'constexpr'


