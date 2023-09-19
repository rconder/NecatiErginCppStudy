# Giriş
----
Bu notlar 3.dersten sonrası içindir. İlk iki derste C++ hakkında genel bilgiler ve C/C++ arasındaki farklar ve ortak noktalara deyinilmiştir.

----

3. Ders içerisinde işlenen konular ve notlar

- Varsayılan argüman kullanımı 
- Derleyicinin deklarasyonları kümülatif olarak ele alması
- Function wrapper

- ***Maximal Munch Kuralı*** : Tokenizing sırasında en uzun atomik birim oluşur.
~~~cpp
int main
{
    int x = 10;
    int y = 20;
    int z = x+++y; // aslında x++ + y 
}
~~~~
**Not**: 
> Eğer bir kütüphane yazıyorsan mutlaka dökümante et!!

## Referans Semantiği

- Cdilinde genelde *pointer semantiği* kullanılmaktadır. Fakat C++ ise pointer semantiğine ek olarak ***Referans Semantiği*** eklenmiştir. 
- Referans semantiği derleme sonucunda oluşan makina kodunda herhangi bir farklılık yaratmaz. İlk olarak ortaya çıkma nedeni ise "Operator Overloading" yapılabilmesi için.

- Modern C++\'da 3 farklı referans semantiği vardır: 
    - L value referans
    - R value referans
    - Forwarding (Universal) refreans

- Bir referans hangi nesneye bağlanırsa, scope'u boyunca yalnızca o nesneye referans olabilir.

- Referansların initialize edilmesi zorunludur. L value referanslar yalnızca L value expresssion'lar ile initiliaze olabilirler. 

### Value Category

- C++ dilinde 3 adet **Primary Category** vardır:
    - L value
    - PR value
    - X value

> Value Category'lerinin konusunun incelenmesi gerekmektedir.

- Referanslar en çok call by reference ile kullanılıyor. Aşağıdaki örneğin hem referans sentaksı için hem de C'ile farkının görülmesi için inceleyelim
~~~cpp
#include <iostream>
void c_tarzi_call_by_reference(int *a)
{
     *a = 999;
}

void referans_semantigi(int &a)
{
    a = 998;
}
int main()
{
    int x = 10;
    std::cout<<x<<"\n";
    c_tarzi_call_by_reference(&x);
    std::cout<<x<<"\n";
    referans_semantigi(x);
    std::cout<<x<<"\n";
}
~~~

**Not**
> Const correctnes dil içerisinde çok önemli bir kavram genel olarak kod yazılırken eğer salt okuma amaçlı veya nesnenin durumunu değiştirmeyecek fonksiyonların const ile yazılması kodun doğruluğu için önemli ilerleyen derslerde detaylıca görebileceğiz.

### Pointerlar ve Referanslar Arasındaki Farklar:
1. Pointerlarda ilk değer vermek zorunda değiliz. Fakat tavsiye edilmiyor!!
2. pointer değişkeni, kendisi const olmadığı sürece (<code>int* const p</code>) farklı değişkenlere/nesnelere point edebilir. Fakat referans sadece bağlandığı nesneyi/değişkeni refer eder.
3. Pointerların dizisi olabilir. Fakat referansların dizisi yok.
4. Pointer to pointer var iken, referans to referans diye bir kavram yok.
5. Null pointer kavramı/değeri varken, referanslar için böyle bir gösterim yok.
----
### Scope Leakage

Bir ismin fiilen kullanıldığı kod alanın dışında da bilinir ve kullanılabilir olması durumudur. Bunu önlemek için programcının işini kolaylıştırıcak araçlar dile eklendi. 
- Scope leakage, değişken isimlerinin istenmeyen şekilde kullanılmasına ve mantıksal hataların oluşmasına sebep olabilir.
- Kaynak yönetimi konusunda ekstra maliyetler yaratıyo olabilir.

***If with initializer***
~~~cpp
if(int x = func(); x > 10)
{
    x = 10;
}
else
{
    x = 20;
}
~~~~
x değişkeninin if bloğu dışında kullanılması artık bir sentaks hatası yaratacaktır. 
* Not: C++17 ile dile eklendi. 'static' değişkenler için istisnai çünkü static değişkenler blok içnde herhangi bir yerde tanımlanabilir. *
----

### Const L Value Referanslar
~~~cpp
double dval = 10.2;

//int &r1 = 10; //Sentaks Hatası L value referansa R'value bir expression atanamaz. FAKAT
const int &r1 = 10; // const L value referansa R value bir expression atanabilir.
const int &r2 = dval;//narrowing conversion'dan dolayı derleyici uyarı mesajı verebilir.
~~~
Burada derleyici const olan kısım iiçin derleyici bir geçici nesene oluşturuyor ve bu geçici nesne üzerinden bir kod üretiliyor. Bu nesnenin ömrü bağlanmış olduğu referans'ın scope'unun sonuna kadar devam eder.  

- <code> void func(T& tr);</code> Böyle bir fonksiyon sadece ve sadece değer kategorisi L value ifadeler ile çağırılabilir. R value ifadeler ile çağırılamaz. FAKAT
- <code> void func(const T& tr);</code> Hem L hem de R value ifadeler ile çağırılabilir.

### R Value Referanslar

Dile modern C++ ile eklendi. Temel eklenme sebepleri taşınma(move) semantiğinin implemente edilmesini sağlamaktı. Move semantics ile daha verimli kodların üretilmesi kolaylaştı.
  
Ayrıca *Perfect Forwarding* yapılamıyordu.

- İlk değer vermek ve bu değerin R value ifade olması mecburi

<code> int &&r = (10+20);</code>

Not: 4.ders içersinde bahsi geçmiş
 ReferenceCollapsing  
| First| Second   |    Final | 
| ----------- | ----------- |-------- |
| T&| &| T& |
| T&| &&| T& |
| T&&| &| T& |
| T&&| &&| T&& |

~~~cpp
auto ival = 10;
auto &&x=ival;
int &x = ival;
~~~
