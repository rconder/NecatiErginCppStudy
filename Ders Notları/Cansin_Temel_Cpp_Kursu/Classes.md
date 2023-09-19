# Classes

- C'deki struct yapısının çok çok çok daha kapsamlısı.
- Cpp'de de struct kullanımı var fakat class keyword'ünün bazı özellikleri farklı hali
- **Data abstraction** Bir verinin yazılımsal olarak temsili.

~~~cpp
class sinif_ismi
{
//değişken ve fonksiyon bildiirimleri
}
~~~

- **Class declaration** Derleyiciye bir sınıf olduğu bildirimi (incomplete class)
- Eğer sınıfı client code'lar kullanıcaksa definition header dosyasında olmalı.
- Sınıfın:
- - Data member: static, non static
- - Member function: static, non static
- - type member
- - Nested type'ı olabilir.

- Her class nesnesinin non-static bir memberi var
- Static veri elemanları o sınıf için tek olan elemanlar. C'deki en yakın karşılığı global değişkenler
- Bildirimi sınıf içinde yapılan isimler sınıfların elemanlarıdır ve scope kuralına tabidir. Bu kapsama class scope denir.

- Sınıflar assemble düzeyde C' ile bir farklılık oluşturmuyor fakat dilin eklediği bir katman ve çok sayıda avantajı var.

- Algısal bir anlam sağlanmış oluyor.

**Acces Control**: sınıfların elemanlarına erişimin legal olup olmadığının kontrolü.
- Public: Sınıfın eleman erişiminde kısıt olmayan kısmı
- Private: Sadece sınıfın kendi kodlarını kullanabileceği clientların eişimine açık olmayan kısım
Client kodlar public fonksiyonları kullanarak bu üyelere erişebilir.
- Protected: Inheritance'da bir sınıf içinde yeni araçlar oluşturulabilmesini sağlıyor.

Access controller'lar bir değişkeni değil bölgeyi nitelendiriyor
~~~cpp
public:
//

//Public alan

//
protected:

//protected alan
~~~

Eğer sınıf tanımlanırken *class* keyword'ü kullanılmışsa default erişim alanı private oluyor.
~~~cpp
class x 
{
    //private alan
}
~~~

Eğer *struct* keywordü kullanılırsa default alan public oluyor.

~~~cpp
struct x
{
    //public alan
}
~~~
ve access specifierlar aynı sınıf içerisinde birden fazla kullanılabilirler.


- Bir üye fonksiyonun sınıf içinde tanımlanması ile dosya içinde global olara tanımlanması farklı şeyler.
- Bir sınıfın interface'ine sınıfın *public* bölümü ve *global* fonksiyonlar dahil.
- Global fonksiyon içinde nitelendirilmeden kullanılan isim ile üye fonksiyon içinde farklı.
- Eğer aranan değişken class scope'ta bulunamazsa daha sonra global scope'ta aranıyor.
- Sınıfın üye fonksiyonlarının sınıfın private alanına erişim yetkisi var.
- Private alanına erişim o fonksiyonun çağırıldıığ nesneden bağımsız olarak erişebilir.

~~~cpp
// A class'ı tanımlanmış olsun ve m_x isimli bir private değişkeni olsun
void A::foo()
{
    A ax;
    m_x = 5;
    ax.m_x = 10; //bu şekilde sentaks hatası olmadan erişebiliyoruz.
}
~~~

**Accesser**: Sınıf nesnesini sadece okumak amaçlı parametresi olan fonksiyonlara deniyor genellikle const oluyor.
<code> void func(const Data *) const;</code> 
**Mutator**: Nesneyi değiştirme amaçlı kullanılan fonksiyonlar.

- Const üye fonksiyonları hangi nesne için çağırılmışsa o nesnenin veri elemanını değiştiremezler.

- !!!! CONST bir sınıf nesnesi için CONST OLMAYAN bir üye fonksiyonu çağırılamaz.

- const overloading: sınıfın üye fonksiyonlarının overload edilmesi.

~~~cpp
class Myclass{
void foo() const;
void foo();
}
~~~

- Sınıfın non-static fonksiyonları hangi nesne için çağırılırsa diğer fonksiyonlarda o nesne için çağırılıyor.


~~~cpp
class x
{
    void func();
    void foo() const;
}
void x::func()
{
    foo(); //  x -> const x'e dönüşüm var.
}
////
class y
{
    void func();
    void foo() const;
}
void y::foo()
{
    //func(); //Sentaks Hatası Böyle bir dönüşüm yok
}
~~~

**Const'luk olayının semantik tanımı**
Üye fonksiyonun const olup olmaması veri elemanları ile alakalı bir durum değil. Sınıf gerçek dünyada bulunan problemin bir soyutlaması, eğer fonksiyon bu problem üzerinde bir değişiklik yapıyorsa yani fonksiyon nesneyi değiştiriyorsa const olmaması gerekiyor.

- Class tasarımları genelde dışarıdan (o sınıfı kullanıcak kişiler) -> içeriye olarak yapılıyor.

> NOT: CONST OLMASI GEREKEN HER ŞEY CONST OLMALI

## This: 

Sadece ve sadece non-static üye fonksiyonları ile kullanılabilir.
Üye fonksiyona çağrı yapan nesenin adresini belli etmek için kullanılıyor.

- Bir sınıfın üye fonskiyonu içinde o fonksiyon hangi nesne için çağırıldıysa o nesnenin adresini kullanmak için yapuldı.

~~~cpp
class A
{
    void foo();
    void func(const A&a);
}

void A::fınc(const A&a)
{
    if(this == &a )
        "gelen nesne aynı nesne"
    else
        "gelen nesne farklı"
}
~~~

- this pointer'ının oluşturduğu ifade PR-VALUE fakat *this => L-value

this kullanımında:
1. Keyfe keder her yerde kullanılmamalı.
2. Sadece non-static üye fonksiyonlar için kullanılabilir.
3. This PR-value bir fonksiyona 

## Inline Functions
