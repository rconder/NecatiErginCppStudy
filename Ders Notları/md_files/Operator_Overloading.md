# Operator overloading

Burada bazı operator detayları anlatılmamış olabilir onlar daha önceki derslerde anlatılmıştır. 

Örnek olarak Mint Sınıfı int türünü sarmalayan bir sınıf olarak kullanılmıştır.

Operatorler eklenmeden önce Mint sınıfı aşağıdadır.

~~~cpp
class Mint{
    public:
        Mint()= default;
        explicit Mint(int x): m_x{x}{}
        void set(int val)
        {
            m_x = val;
        }
    private:
        int m_x{};
};
~~~
## Aritmetik İşlemlerin Overload Edilmesi
## Postfix & Prefix Toplama ve Çıkartma Operatorlerinin Overload'u

### Postfix Toplama operatorü
burada postfix operatörü prefix toplama operatörünü de çağırıyor.
~~~cpp
   Mint operator++(int) //postfix
   {
      Mint retVal{*this}; //nesnenin değeri retVal olan değişkende tuttuk 
      ++* this;
      return retVal;
   }
~~~
### Prefix Toplama Operatörü
~~~cpp  
    Mint & operator++() //prefix
   {
      ++m_x;
      return *this;
   }
~~~
### Postfix Çıkartma Operatörü 
~~~cpp
   Mint operator--(int) //postfix
   {
      Mint retVal{*this}; 
      --* this;
      return retVal;
   }
~~~
### Prefix Çıkartma Operatörü
~~~cpp
   Mint & operator--() //prefix
   {
      --m_x;
      return *this;
   }
~~~
## İşaret operatörleri + ve -'nin Overload'u

Bu iki operatöründe nesneye bir etkisi yok o yüzden bu iki operatör const correctnes için const olmalılar.
### Operator+()
~~~cpp
   Mint operator+() const //yan etkisi yok const olmalı
   {
      return *this;
   }
~~~
### Operator-()
~~~cpp
   Mint operator-() const
   {
      return Mint{ -m_x };
      //return -m_x eğer ctor explicit ise SENTAKS HATASI olur!!!!
   }
~~~
## Operator += Overload edilmesi

Burada +='operatörünün nesneyi değiştirmesi beklendiğinden const olmamalı
~~~cpp
   Mint &   operator+=(const Mint &other)
   {
      m_x += other.m_x;
      return *this;
   }
~~~

## Giriş & Çıkış işlemleri için kullanılan Operatorlerin Overload edilmesi

- Operator<< sınıf nesnsesini set etmediğinden const olan bir sınıf nesnesi referansı almalı.
- Fakat Operator>> sınıf nesnesini set ettiğinden const olmayan bir sınıf nesne referansı almalı.

Idiomatik olarak sentaksı: 

~~~cpp
   friend std::ostream& operator<<(std::ostream&, const Mint&); 
   friend std::istream& operator>>(std::istream, Mint &); 
~~~
~~~cpp
    #inlcude <ostream> //başlık dosyası include edilmeli
   inline std::ostream& operator<<(std::ostream &os, const Mint &mint)
   {
    return os << '(' << mint.m_x << ')'; //burada os ifadesi zaten
    //ostream & döndürdüğü için direkt böyle kullanılabilir.
   }
~~~
~~~cpp 
std::istream& operator>>(std::istream &is,  Mint &mint)
{
    return is>>mint.m_x;
} 
~~~
## Logic Operatorlerin Overload Edilmesi

  Logic operatorler overload edilirken genellikle **operator<** ve **operator==** operatorlörünün overload edilmesi, diğer logic operatorlerinin overloadlarının yazılmasını kolaylaştırıyor.
  - lhs: left hand side
  - rhs: right hand side

  ~~~cpp
  friend bool operator<(const Mint &lhs, const Mint &rhs) 
  {
      return lhs.m_x< rhs.m_x;
  }
  ~~~
  ~~~cpp
  friend bool operator==(const Mint &lhs, const Mint &rhs) 
  {
      return lhs.m_x==rhs.m_x;
  }
   ~~~

   ~~~cpp
  inline bool operator!=(const Mint &lhs, const Mint &rhs) 
  {
   return !(lhs == rhs); 
  }
  ~~~
  ~~~cpp
    inline bool operator>=(const Mint &lhs, const Mint &rhs) 
  {
      return !(lhs< rhs);
  }
~~~
~~~cpp
inline bool operator>(const Mint &lhs, const Mint &rhs) 
{
      return (rhs< lhs);
}
~~~
~~~cpp
inline bool operator<=(const Mint &lhs, const Mint &rhs) 
{
     return !(rhs< lhs);
}
~~~

## 2 Sınıf Nesnesinin Toplanması ve Çıkarma Operatorunun Overload Edilmesi

- ***1.Aşama***:
Dönüş nesne oluşturuluyor ve oluşturulan nesne için operator+=() fonksiyonu çağırılıyor. Daha sonra değer dönülüyor.
- ***2.Aşama***: Geçici nesne oluşturulup bu nesne için operator+=() fonksiyonu çağırılıyor.
- ***3.Aşama***: 2.aşama'de operator+= fonksiyonun'da işlenen geçici nesne dönülüyor.

~~~cpp
inline Mint operator+(const Mint &lhs, const Mint &rhs)
{
/*
1.aşama
-------
Mint retVal {lhs};
retval += rhs;
return retval;

/*
2.aşama
--------
Mint {lhs} += rhs; //geçici nesne için += operator fonksiyonu çağırılıyor
//sonucunda çıkan Mint dönülüyor
*/

//3.aşama --->
return Mint {lhs} += rhs;
}
~~~
## Köşeli Parantez' Un overload Edilmesi 

Operator[]() overload'u için aşağıdaki sentaks yapısı baz alınabilir. 
Sabit nesnelr için de ayrı bir fonksiyon bildirimi ve implementasyonu veriyoruz.

~~~cpp
class ivector
{
   public:
   int &operator[](size_t) // const olmayan intarray nesneleri için bu
   {
      return mp[idx];
   }
   const int &operator[](size_t) const // const olan int array nesneleri için bu
   {
      return mp[idx];
   }
}
~~~
STL Örneği
~~~ cpp
#include <iostream>
#include <vector>
int main()
{
   using namespace std;
   vector<int> ivec(12);
   ivec[3] = 45;

    Nec mynec;
    mynec[5]; // mynec.operator[](5);

    string name{"cansin onder"};
    for (size_t i{}; i < name.size(); ++i)
    {
        cout << name[i] << " "; //[] overload edildiği için kullanabiliriz.
    }

    int a[10]; // kullanmak yerine bu diziyi sarmalayan bir
    // sınıf kullanabiliri. (wrapper class)
    // stl'e daha uyumlu daha kullanıcı dostu, daha güvenli
    array<int, 10> ar;
    for (int i = 0; i < 10; ++i)
    {
        ar[i] = i;
        // ar.operator[](i) = i;
    }
    
    //vector<int> ivec{1, 4, 6, 78, 2, 1};
    const vector<int> ivec {1, 4, 6, 78, 2,1};
    auto val = ivec[3];
    //ivec[4] = 999; //SENTAKS HATASI
    // const overloading var. Const bir nesneye atama yapılıyor.

}
~~~
## Ok(->) ve * Operatorunun Overload Edilmesi

Genel olarak operator overload edilirken uygulamadaki ve domaindeki karşılıklarını uyarak ve anlamlarına dikkat ederek overload işlemini implemente etmemiz gerekiyor. Yani x + y ifadesinin anlattığı şeyin bu iki nesnenin toplandığı olarak kullanılmasıdır. Bu operatorler içinde bu geçerlidir. Bu operator genelde pointer gibi kullanılan sınıflar ile kullanılıyor.

Örnek olarak SmartStringPtr sınıfı oluşturakım

~~~cpp
#include <string>
class SmartStringPtr
{                                                      // dinamik ömürlü string nesneleri için oluşuturulduğunu varsay
public:                                                // dinamik ömürlü nesne adresi istiyor
    explicit SmartStringPtr(std::string *p) : mp{p} {} // özel bir gerekçe yoksa explicit yap
    ~SmartStringPtr()
    {
        delete mp;
    }
    std::string &operator*()
    {
        return *mp;
    }
    std::string *operator->()
    {
        return mp;
    }

private:
    std::string *mp;
}
~~~

Bu sınıfın kullanımı 
~~~cpp
int main()
{
    {
        SmartStringPtr ptr{new std::string{"necati ergin"}};
        // std::cout << *ptr<<'\n' ; yapılabilirdi.
        std::cout << (*ptr).size() << '\n';

        std::cout << "uzunluk = " << ptr->length() << "\n";
        std::cout << "uzunluk =" << ptr.operator->()->length() << "\n";

        for (size_t i{}; i < (*ptr).size(); ++i)
        {
            std::cout << (*ptr)[i] << ' ';
        }
    }
    retun 0;
}
~~~

## Operator Parantez (Operator()) Overloading

~~~cpp
#include <iostream>
class Mycalss
{
public:
    void operator()()
    // void operator() (int x) {std::cout<<" Myclass::operator()(x) x = " << x " \n"; }
    void operator()(int x = 0)
    {
        std::cout << " Myclass::operator()(x) x = " << x " \n";
    }
    {
        std::cout << " Myclass::operator()()\n";
    }
    void operator()(double x)
     { std::cout << " Myclass::operator()(x) x = " << x " \n"; }
};

int main()
{
    Myclass mx;
    mx();
    mx(10.0);
    // mx.operator()(10.0);
    return 10;
}
~~~
## Tür Dönüştürme Operatorlerinin Overload Edilmesi
~~~cpp
class A
{
};
class Nec
{
public:
    operator int() const;
    // explicit operator int() cont;
    operator A() const;
};

int main()
{

    Nec mynec;

    int x;
    x = mynec; // explicitli olan açılırsa sentaks hatası
    x = static_cast<int>(mynec);
    x = mynec.operator int();
}
~~~

Bu örnek için int sınıfını sarmalayan bir counter sınıfı yazalım. 
~~~cpp
class Counter
{
public:
    explicit Counter(int val = 0) : m_c{val} {}
    Counter &operator--() // postfix
    {
        --m_c;  return *this;
    }
    Counter operator--(int)
    {
        auto temp{*this};
        --*this;   return temp;
    }

    Counter &operator++() // postfix
    {
        ++m_c;   return *this;
    }
    Counter operator++(int)
    {
        auto temp{*this};
        ++*this;    return temp;
    }

    Counter &operator+=(int val)
    {
        m_c += val;  return *this;
    }

    Counter &operator-=(int val)
    {
        m_c -= val;  return *this;
    }

    explicit operator int() const //operator tür dönüştürme fonksiyonumuz
    {
        return m_c;
    }
    friend std::ostream &operator<<(std::ostream &os, const Counter &cnt)
    {
        os << '[' << cnt.m_c << ']';
    }
private:
    int m_c;
}
~~~

~~~cpp
#include <iostream>
//counter sınıfını buraya kopyala
int main()
{
    std::cout << " c = " << c << "\n";
    ++c;
    ++c;
    ++c;
    ++c;

    std::cout << " c = " << c << "\n";
    c += 10;
    std::cout << " c = " << c << "\n";
    int ival = static_cast<int>(c); //
    std::cout << "ival " = << ival << "\n";
    return 0;
}
~~~

## Operator bool Overload edilmesi

~~~cpp
#include <iostream>
class Nec
{

public:
    // operator bool( )const
    explicit operator bool() const
    // explicit yazılmazsa bu durumda user defined + standart conversiondan dolayı x'in değeri 1 oldu
    if(mynec)
    if(mynec.operator bool())
    {
        std::cout << "Nec operator bool()\n";
        return true;
    }
}

int main()
{
    double x;
    Nec mynec;
    //x = mynec; //Sentaks hatası
    //  bunu önlemek için fonksiyon explicit yapılmalı
    std::cout << "x= "<< x << "\n";
    if (mynec)
    {
        std::cout << "YAPARIM DOGRU\n";
    }
    return 0;
}
~~~
Yukarıdaki örnektede bahsedildiği gibi burada dikkat edilmesi gereken bir husus boolean'ının int altu tür olmasıdır yani burada derleyici operator bool() fonksiyonunu kullanarak implicit conversion yapıyor olabilir.

~~~cpp
class Myclass
{
public:
    operator bool() const;
};

int main()
{
    Myclass m1, m2;

    // auto x = m1 + m2;
    // x değişkeninin türü int
    // nomrmalde operator bool() fonksiyonu ile implicit conversion yapılıyor
    // aslında bu kod
    auto x = m1.operator bool() + m2.operator bool(); // int altı tür olduğundan bool türden
    // olan operandlar integral promotion ile bool türünden int türüne yükseltilmiş oluyor.
}

~~~
## Operatorlerin Global Fonksiyonlar Olarak Overload Edilmesi

Burada friendlik verilerek fonksiyonların sınıf private bölümüne erişmesi sağlanıyor.
~~~cpp
friend Mint& operator--(Mint &mint)
{
   --mint.m_x;
   return mint;

}
friend Mint operator--(Mint &mint, int)
{
   Mint retval{mint};
   --mint;
   return retval;
}
~~~
## Operator Overloading Kullanım Örenkleri

- [Giriş Çıkış operatorü](#giriş--çıkış-işlemleri-için-kullanılan-operatorlerin-overload-edilmesi)

~~~cpp
#include "mint.hpp"
int main()
{
    Mint m1{25}, m2{457};
    Mint m3{}, m4{};
    std::cout << m1 << " " << m2 << "\n";
    std::cin >> m3;
    std::cin >> m4;
    std::ofstream ofs{"out.txt"};s
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        exit(EXIT_FAILURE);
    }
    ofs << m1 << " " << m2 << '\n';
    return 0;
}
~~~

- [Köşeli Parantez Operatörü Overload Örneği](#köşeli-parantez-un-overload-edilmesi)
~~~cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> ivec{1, 3, 5, 7};
    const vector<int> cvec{1, 3, 5, 7};

    ivec[2] = 12;
    // cvec[2] = 3; //SENTAKS HATASI salt okuma amaçlı kullanım
    auto i1 = ivec[2];
    auto i2 = cvec[2];
}
~~~

Ornek olarak bir int array sınıfı yazalım ve bu sınıf köşeli parantez operatörünü overload etsin.

~~~ cpp
#include <iostream>
class intarray
{
public:
    int &operator[](size_t) // const olmayan intarray nesneleri için bu
    {
        return mp[idx];
    }
    const int &operator[](size_t) const // const olan int array nesneleri için bu
    {
        return mp[idx];
    }
    std::size_t size() const
    {
        return msize;
    }
    explicit intarray(size_t size) : msize(size), mp(new int[msize])
    {
        std::memset(mp, 0, msize * sizeof(int));
    }

    friend std::ostream &operator<<(std::ostream &os, const intarray &ar)
    {
        os << '[';
        for (auto i = 0u; i < ar.size() - 1; ++i)
            os << ar[i] << ", "; // ar.mp[i]' de yazılabilirdi
        os << ar[ar.size() - 1] << "]";
    }
    ~intarray()
    {
        delete[] mp;
    }
    intarray(const intarray &) = delete;
    intarray &operator=(const intarray &) = delete;
    //
private:
    //.....
    int *mp;
    std::size_t msize;
};
~~~
Ve  bu sınıfın kullanımı

~~~cpp
int main()
{
    intarray a(10);
    cout << a << "\n";

    for (size_t i = 0; i < a.size(); i++)
    {
        a[i] = i * 2;
    }
    a.operator[](5) = 34;

    return 0;
}
~~~

[Parantez Operator'unun kullanımına örnek](#operator-parantez-operator-overloading)

Random sayı üreten bir sınıf yazalım
~~~cpp
#include <random>
class Random
{
    // fonksiyon operator fonksiyonun operandı olduğunda rastgele sayı üretsin
public:
    Random(int low, int high) : m_low{low}, m_high{high} {}
    int operator()()
    {
        ++m_count;
        return std::rand() % (m_high - m_low + 1) + m_low;
    }
    int get_call_count() const
    {
        return m_count;
    }

private:
    int m_low;
    int m_high;
    int m_count{};
};
~~~
Ve bu sınıfı maina içinde kullanalım. Ayrıca STL random sınıfı kullanılarakta bir örnekte verilmiştir.
~~~cpp
int main()
{
    mt19937 eng;
    uniform_int_distribution dist{700, 7600};
    Random rand1[37,56];

    for (int i = 0; i < 100; ++i)
    {
        cout << dist(eng) << " \n"; // dist( )
        cout<< "rand1: " << rand1()<< "\n";
    }   
}
~~~

[Tür dönüştürme operatörünün örneklerinin ](#tür-dönüştürme-operatorlerinin-overload-edilmesi)

String sınıfından bir örnek
~~~cpp
int main()
{
    string name{"cansin onder"};

    // eger tür dönüştürme fonksiyonu olsaydı => olabilirdi. const char *p = name;
    const char *p = name.toCString();
    return 0;
}
~~~

Enum sınıfları içinde tür dönüştürme operatörünü kullanabiliriz

~~~cpp
#include <iostream>
enum class Weekday
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

std::ostream &operator<<(std::ostream &os, const Weekday &wd)
{
    const char *const pdays[] =
        {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"};
    return os << pdays[static_cast<int>(wd)];
}
Weekday &operator++(Weekday &wd)
{
    return wd = (wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1));
}



int main()
{
    Weekday wd{Weekday::Sunday};
    for (;;)
    {
        ++wd;
        std::cout << wd << "\n";
        (void)getchar();
    }
}
~~~

[Operator bool() Örneği](#operator-bool-overload-edilmesi)

~~~cpp

int main()
{
    std::unique_ptr<std::string> uptr{new std::string{"cansin"}};
    if (uptr) // if(uptr != nullptr )aynı anlamda
    // if(uptr.operator bool()) aynı şey
    // if(! uptr)
    {
    }

    strd::cout << "bir tam sayi girin";
    int x;
    cin >> x;
    if (cin) // eğer akımda hata yoksa cin true döncek hata varsa false döncek
    // cin.operator bool()
    {
        std::cout << "giris basarili";
    }
    else
        std::cout << "giris basarisiz";

    while (cin >> x) // cagirilan fonksiyonun geri dönüş değeri cin nesnesinin kendisini referans olarak döndürüyor
    // o da operator bool fonksiyonun çağırıyor.
    // while(cin.operator>>(x).operator bool()) bunla yazmakla üstteki arasında fark yok
    {
        std::cout << x << " * " << x << " = " << (x * x);
    }

    optional<int> x; // c++ 17 ile dile eklendi
    // bir değere sahip olmaması veya olması gibi bir seçeneği var
    x.has_value(); // değeri tutuyorsa true döner

    if (x)
    {
        std::cout << "dolu";
    }
    else
        std::cout << "bos";
}
~~~

Operator boo