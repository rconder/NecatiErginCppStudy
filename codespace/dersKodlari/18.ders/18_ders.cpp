// mini bilgi
namespace mini_bilgi
{
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
} // namespace mini_bilgi

namespace scoped_enum_with_operator_overloading
{
    std::ostream &operator<<(std::ostream &os, const Weekday &wd)
    {
        static const char *const pdays[] = // static yerel değişken olmalı bu da bu fonksiyon
                                           // her çağırıldığında ilk değerliğini yeniden ve sürekli olarak alacak
            // yerel lookup table'ları static yap.
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
    Weekday operator++(Weekday &wd, int)
    {
        Weekday ret{wd};
        ++wd;
        return ret;
    }
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

    int main()
    {
        Weekday wd{Weekday::Sunday};
        for (;;)
        {
            ++wd;
            std::cout << wd << "\n";
            (void)getchar();
        }
        return 2;
    }
}

/* İsim alanları Namespace */
namespace namespace_sentaksi_ve_kullanimi
{
    namespace cansin
    {
        void foo(int);
        int x = 10;
    }

    namespace nec{
        namespace cansin{
            int x = 19;
            namespace ali
            {
                double x = 10;
            }
        }
        void foo(int, int); // bu iki foo function overloading değil farklı scopetalar
        double x = 3.4;     // bunla üstteki farklı scope'ta ve her ikisi de global scope içinde gibi
    }

    namespace nec1
    {
        void foo(){}
        void func()
        {
            // nec::foo(); bu da kullanılabilir
            foo();
        }
    }

    void foo1(){}
    void func1(){
        //::foo1(); bu da kullanılabilir
        foo1();
    }

    void x()
    {
    }

#include <iostream>

    int main3()
    {
        x();
        nec::x;
        cansin::x;
        nec::cansin::x;
        cansin::foo(1);
        nec::foo(1, 2);
        nec::cansin::ali::x;
    }

    /* namespace ali {
        int x,y,z;
    }
    using ali::x;

    int x = 5;//SENTAKS HATASI bu sentaks hatası
    using ile ali::x nesnesi/değişkeni/ismi scope'a enjekte edilmiş oluyor.
     */

    namespace ali
    {
        int x, y, z;
    }

    void func3()
    {
        using ali::x
            x = 5; //alinin x'i
    }

    void foo3()
    {
        // x = 5;//SENTAKS HATASI bu bir sentaks hatası
    }

    namespace veli
    {
        using ali::x;

    }

    int main4()
    {
        veli::x = 10;
        // veli::ali //SENTAKS HATASI sentaks hatası
    }
    //========
    int g = 10;
    namespace nec1
    {
        using ::g; // global namespace içindeki g
    }

    namespace ali
    {
        using ::g; // global namespace içindeki g
        using nec::x;
        int y = 10;
    }

    int main5()
    {
        ali::g = 50;
        ali::x = 20;
        ali::y = 10;
    }
    ///======
    namespace string_vector_ornek
    {

#include <string>
#include <vector>
#include <iostream>

        int main_()
        {
            std::cout << "murat" << std::endl;
            // burada operator overloading var
            // endl var
            using ali::x;
            x = 10; // bu ali::x'in bildirimi aslında
            // ali::x'i diyebiliriz
            return 0;
        }
    }

    //======
    using ali::x, ali::y, ali::z; // sentaks hatası ise nedeni derleyicinin eski olması C++17 ile dile eklendi
    //===

    ///====Namespace
    namespace alii
    {
        int a, b, c;
    }

    int main_2()
    {
        using ali::a;
        double a; // bu sentaks hatası çünkü using enjekte ediyor
    }

    int main_3()
    {
        using namespace ali;
        a = 3;
    }

    //========

    namespace neco
    {
        namespace alii
        {
            int a, b, c;
        }
        using namespace neco::alii;
    }

    int main()
    {
        // neco::alii:a demek gerekirken
        neco::a = 10; // diyebiliriz çünkü using bildirimi kullanıdk
    }

    //==========
    namespace neco
    {
        namespace alii
        {
            int a, b, c;
        }
        using namespace neco::alii;
    }
    using namespace neco;

    int main()
    {
        // neco::alii:a demek gerekirken
        a = 10; // diyebiliriz
    }

    //==============

    namespace neco12
    {
        int x, y;
    }

    using namespace neco12;

    int x;

    int main()
    {
        x = 5; // ambiguity olur
    }

    ///==========
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

    //=====
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

    //====

    namespace ali
    {
        int a = 20;
    }

    // using namespace ali;

    int main()
    {
        using namespace ali; // global alandaki using namespace ali ile
        // aynı etki yaratılıyor
        int a = 10;
        std::cout << " a = " << a << "\n"; // a yerel a'dır
    }

    void foo()
    {
        using namespace ali;
        a = 6; // ali space'nin icindeki a
    }

    //=========

    namespace ali
    {
        int a = 20;
    }

    // using namespace ali;
    int main()
    {
        using namespace ali; // global alandaki using namespace ali ile
        // aynı etki yaratılıyor
        std::cout << " a = " << a << "\n"; // Alttaki a görülür olmadığı için
        // ali namespace'i içindeki a'yı yazdırıyor.
        int a = 10;
        std::cout << " a = " << a << "\n"; // a yerel a'dır
    }

    /// ADL Argument dependent look up

    namespace ali
    {
        class A
        {
        };
        void func(A);
    }

    namespace veli
    {
        class B
        {
        };
    }

    int main()
    {
        ali::A ax;
        func(ax); // func ismini nitelenmeden kullanmamıza rağmen
        // yine de func ismini unqualified olarak kullanmamız sorun olmadı
        // ADL: isliyor
        //
    }

    int main()
    {
        ali::A ax;
        veli::B bx;

        foo(ax, bx); // foo hem ali namespace'inde hemde b namespace'inde de aranıyor.
    }

    //===

    namespace ali
    {
        enum Color
        {
            Blue,
            Black,
            White
        };
        void func(Color);
    }

    int main()
    {
        func(ali::Color::Blue);
    }
    //=====

    int main()
    {
        std::cout << "Merhaba dünya";
        // bu kod legal ama bu kodun legal olmaması gerekir
        // cout'u niteliyoruz fakat operator'u nitelemedik
        std::operator<<(std::cout, "merhaba dunya");
        operator<<(std::cout, "merhaba dunya2 "); // ADL'den dolayı sentaks hatası olmadı.
    }

    //======

    namespace nec
    {
        class X
        {
        };
        void func(X)
        {
            std::cout << "necin funci\n";
        }
    }

    void func(nec::X)
    {
        std::cout << "global func\n";
    }

    int main()
    {
        nec::X nx;
        //func(nx); // SENTAKS HATASI AMBUGUITY OLUYOR
    }

    //======
    namespace nec
    {
        class X
        {
        };
        void func(std::vecotr<X>);
    } // namespace nec

    int main()
    {
        int func = 5;
        nec::X nx;
        //func(nx); inf func = 5 bir fonksyion değildir hatası veriyor.
        // SENTAKS HATASI OLUR
        // Fakat nedeni ambiguity değil
        // nedeni name hiding blok içinde func ismi gizliyor
    }

    int main()
    {
        int func(int);
        nec::X nx;
        func(nx);
        // Gene isim gizlemesi parametresi int olan bir fonksiyon
        // Eğer -operator int() const- tür dönüştürme operator fonksiyonu konsaydı
        // sentaks hatası olmazdı.
    }

    //=====
    namespace nec
    {
        class X
        {
        };
        void func(std::vecotr<X>); // func'in parametresi vector türünden nec namespace'inde değil
    }                              // namespace nec

    int main()
    {
        std::vector<nec::X> myvec;
        func(myvec); // argüman olan türün ilişkin olduğu namespace'te de aranır.
    }

    //=====

    class Myclass
    {
    public:
        friend void func(int); // bu fonksiyon namespace içinde
    }

    int main()
    {
        func(10); // Sentaks hatası func ismi aranıp bulunamıyor.
    }

    //======
    class Myclass
    {
    public:
        friend void func(Myclass); // bu fonksiyon namespace içinde
    }

    int main()
    {
        Myclass m;
        func(m);
    }

#include <iostream>
    namespace /*hidden*/
    {
        int a, b, c;
        // bunlar dış bağlantıya ait değil
        // iç bağlantıya ait

        //c'deki static bildirimi ile bildirilmiş fonksiyonlar/değişkenler gibi

    }

    namespace /*hidden*/
    {
        int x;
        // kümülatif olabilir
    }
    // using namespace hidden;

    int main()
    {
        a = 45;
    }

    // BAŞLIK:   namespace alias
    // tür ismi yerine geçecekse type alias
    using Word = int;

    namespace ali
    {
        namespace veli
        {
            namespace necati
            {
                int x = 5;
            } // namespace necati
        }
    }

    namespace project = ali::veli::necati;

    int main_()
    {
        ali::veli::necati::x = 45;
        std::cout << x << " \n";
        project::x = 5;
        std::cout << x << " \n";

        return 0;
    }

    // versiyon controlü içinde kullanılabilir.

    namespace Can
    {

        namespace Oldversion
        {
            class Myclass
            {
            };

        } // namespace Oldversion

        namespace NewVersion
        {
            class Myclass
            {
            };
        }

        // bunun için bir namespace alias oluşturup
        void func(Myclass);
    }

    namespace Current = Can::Oldversion;

    // sadece yukardaki alias'ı kullanarak versiyonu değiştirebiliriz.

    int main__()
    {
        Current::Myclass x;
    }

    // namespace kulanarak isim çakışması %99 engellenebilir. Fakat namespace ismi de isim çakışmasına sebeb olabilir.
    // namespace ismini daha spesifik bir isim yapılırsa çakışma ismi çok yüksek değil.
    // kullanıcı kodlarda bu ismi daha kısa bir şekilde kullanabilir.
}