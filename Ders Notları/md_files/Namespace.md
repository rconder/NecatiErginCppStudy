# C++'ta Namespace Kullanımı ve Kuralları
Örnek olarak aşağıdaki namespaceleri alalım.
- İlk olarak burada foo fonksiyonları birbirinin **overload**'ı değil. Bu iki fonksiyonun scopeları farklı.
- x değişkeni özelinde sentaks hatası olmadığı gözlemlenebilir. Gene x'in scope'u birbirlerinden

~~~cpp
namespace cansin
{
    void foo(int);
}

namespace nec
{
    namespace cansin
    {
        int x = 19;
        namespace ali
        {
            double x = 10;
        }
    }
    void foo(int, int); sa
    double x = 3.4;    
}

void x()
{

}

int main()
{
    x();            
    nec::x;
    cansin::x;
    nec::cansin::x;
    cansin::foo(1);
    nec::foo(1, 2);
    nec::cansin::ali::x;
}
~~~

## ***using*** keyword'ünün kullanımı 

- using ali::x ile kullanılan nesneyi/değişkeni/ismi using bildiriminin kullanıldığı scope alanına enjekte edilmiş olmuyor. O yüzden yorum satırına alınmış statement **SENTAKS HATASI** 

- foo fonksiyonu içindeki kod ksısmı da sentaks hatası çünkü o scope içinde ve ya global alanda kullanılan bir x'değişkeni yok

~~~cpp
namespace ali
{
    int x,y,z;
}

void func()
{
    using ali::x;
    //int x = 6; 
}
void func1()
{
    using ali::x;
    x = 52;
}
void foo()
{
    //x = 2101; //Sentaks hatası 
}
~~~

- Global namespace içindeki ismin nitelenmesi
- Bir namespace alana enjekte edilen değişken başka bir scopeta da kullanılabilir.
~~~cpp
int g = 10;
namespace neco
{
    int x;
}
namespace ali
{
    using ::g;
    using nec::x;
    int y {29};
    
}

int main()
{
    ::g = 29;
    ali::g = 60;
    ali::x = 02;
    ali::y = 393;
}
~~~
- İç içe namespacelerde kullanım using bildiriminin kullanımı 

~~~cpp 
    namespace neco
    {
        namespace alii
        {
            int a, b, c;
        }
        using namespace neco::alii;
    }
    int foo()
    {
        using namespace neco;
        // neco::alii:a demek gerekirken
        a = 20;
    }
    int main()
    {
        // neco::alii:a demek gerekirken
        neco::a = 10; // diyebiliriz çünkü using bildirimi kullanıdk
    }
~~~

- Ambiguity olmamamsına dikkat etmek lazım. Aşağıdaki örnekte ambiguity oluşturulmuş oluyor çünkü hangi x'in seçileceği belli değil. 
~~~cpp
namespace neco
{
    int x, y; 
}

using namespace neco;

int x;

int main()
{
    //x = 5; 
}
~~~

- Bir başka örnek
~~~cpp 
    namespace neco
    {
        int x, y;
    }
    namespace ali
    {
        int x, y;
    }
    using namespace neco;
    using namespace ali; // bunlardan birini kaldırmak gerekiyor

    int main()
    {
        x = 10; // ambiguity
    }
~~~

- Fonksiyon olması durumunda da fark etmiyor ve gene ambiguity oluşuyor.

~~~cpp
    namespace ali
    {
        void foo();
    }

    namespace veli
    {
        int foo = 5;
    }

    using namespace ali;
    using namespace veli;

    int main()
    {
        // foo(); // SENTAKS HATASI ambiguity oluşuyor.
        ali::foo();
        veli::foo = 56;
    }
~~~~

## ADL: Argument Dependendt Lookup

Burada bir fonksiyonun parametreleri bir sınıf türünden ve bu sınıf nitelendirilmiş bir isim alanında bulunuyorsa, argüman olarak verilen nitelendirilmiş sınıf değişkenlerinin using bildirimininin olmadan kullanılması mümkün:

~~~