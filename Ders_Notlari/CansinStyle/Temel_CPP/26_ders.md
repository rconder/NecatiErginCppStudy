# 26.ders

```cpp
namespace 26_ders
{
#include "Utility/car.hpp"
#include <typeinfo> //typeinfo sınıfı için
    /* Yorum Baslik:run_time_type_identification
     */
    namespace run_time_type_identification
    {
        void car_game(Car *carptr) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            std::cout << *carptr << "\n" carptr->start();
            carptr->run();
            if (auto *p = dynamic_cast<Volvo *>(carptr)) // carptr sınıfının polymorphic bir sınıftan olmalı
            {
                // buraya gelen Volvo
            }
            else
                // p'yi burdada kullanabilirdik. if parantezinde tanımlanan değişken burada da kullanılabilir.
                cr.stop();
            std::cout << "----------------------------------------\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "run_time_type_identification main\n";
            for (int i = 0; i < 100; i++)
            {
                Car *p = create_random_car();
                car_game(p);
                delete p; // Taban sınıfın destructor'ı virtual olduğu için Car ptr'yi delete edebiliriz.
                // Eğer virtual olmasaydı bu tanımsız davranış olurdu.
                (void)getchar();
            }
            return 0;
        }

    } // run_time_type_identification sonu

    /* Yorum Baslik:referans_semantigi_ile_yapilmasi
    Pointer ve referans arasındaki en büyük fark  pointer'lar için nullptr'nin olması
    nullptr kullanılan senaryolarda bu bir sorun oluşturabilir
     */
    namespace referans_semantigi_ile_yapilmasi
    {
        void car_game(Car &cr) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            std::cout << cr << "\n" cr.start();
            cr.run();

            Volvo &vref = dynamic_cast<Volvo &>(cr);
            // Eğer buraya gelen Volvo ise tür dönüşümü başarılı olucak ve kullanabileceğiz
            // Fakat değilse burada exception throw edilecek. Exception throw ederse eğer
            // Exception yakalınırsa handling edilebilir ya da terminate isimli fonksiyona atıfta bulunacak

            cr.stop();
            std::cout << "----------------------------------------\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "referans_semantigi_ile_yapilmasi main\n";
            VolvoXC90 vs;
            car_game(vx);
            std::cout << "Main devam ediyor\n";
            /*
            Fiat f;
            car_game(f);
            std::cout<<"Main devam ediyor\n";
            //exception handle edilmiyor. program abort fonksiyonuna yapılan çağırı ile sonlanıac
            */
            try
            {
                Fiat f;
                car_game(f);
                std::cout << "Main devam ediyor\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            return 0;
        }
    } // referans_semantigi_ile_yapilmasi sonu

    /* Yorum Baslik: typeid operatörü
        Kod aracın hangisi olduğunu nasıl olup olmadığını nasıl anlıyor?
        typeid bir anahtar sözcük
        typeid operatörünün ürettiği değer ismi std::type_info olan bir sınıf türünden const referans'tır
        typeid(x)
        typeid(x).=> typeinfo sınınfının üye fonksiyonlarını çağırabiliriz.
        type_info sınıfı türünden bir nesne kullanmanın tek yolu typeid operatörünü kullanmaktır
        Hem çalışma zamanı hem de static olarak kullanılıyor
        Kullanmanın iki yolu var:
        1-)   typeid(tür bilgisi olabilir)
        Basic tür veya Sınıf türüde olabilir
        herr tür için bir type_info nesnesi var her türün type_info nesnesi ayrı


        type_info std library'de olduğu için
        == operator fonksyiyonu typeid(double) == typeid(double) -> true döndürüyor ve
        2 type_info nesnesini sorguluyor.

        2-)typeid(expr) => Buradaki i

        type_info sınıfının ismi name olan bir üye fonksiyonu var ve bu fonksiyon const char *'döndürüyor.
        döndürdüğü cstring type_info'nun türünü anlatan bir yazı. Fakat bu standart değil
        Bu yazı standart değil ve verdiği yazı birbirinden farklı olabilir

        class type_info
        {
            public:
            type_info(const type_info &) = delete;
            bool operator==(const type_info&) const;
            const char* name()const;
        }

        UNEVALUATED Consept=> derleyici bunun için bir işlem kodu üretmiyor.

     */
    /* Yorum Baslik:typeid_ornek
     */
    namespace typeid_ornek
    {

        int main() // main'de cagir!!!
        {
            std::cout << "typeid_ornek main\n";
            int x = 10;
            // std::typeinfo x; //SENTAKS HATASI!!! Çünkü default ctor'u yok
            // std::type_info ti = typeid(x); //SENTAKS HATASI!! Copy ctor'u da delete edilmiş
            // std::type_info& rx = typeid(ival);//SENTAKS HATASI!! const bir nesneye referans
            const std::type_info rx = typeid(ival);

            int x2 = 10;
            if (typeid(x) == typeid(int))
            {
                std::cout << "true mu: " << true << " \n";
            }
            std::cout << "typeid(x).name() : " << typeid(x + 1.2).name() << " \n";

            int y = 56;
            std::cout << "typeid(y++): " << typeid(y++) << " \n";
            std::cout << "y: " << y << " \n";
            return 0;
        }
    } // typeid_ornek sonu

    /* Yorum Baslik:typeid_kalitim_ile
    Eğer bir sınıf polymorp
    hic değilse ve derefence edilmiş bir türü verirsek
    static türü saptıyor.
    typeid türü hiç bir zaman dinamik türe ilişkin bir bildirim yapmıyor
     */
    namespace typeid_kalitim_ile
    {
        class Base
        {
        public:
        private:
        };
        class Der : public Base
        {
        public:
        private:
        };
        int main() // main'de cagir!!!
        {
            std::cout << "typeid_kalitim_ile main\n";
            Der myder;
            Base *baseptr = &myder;
            std::cout << typeid(*baseptr).name();
            << "\n";
            if (typeid(*baseptr) == typeid(Base))
            {
                std::cout << "dogru\n";
            }
            return 0;
        }
    } // typeid_kalitim_ile sonu
    /* Yorum Baslik:type_id_polymorphic_tur_icin
     */
    namespace type_id_polymorphic_tur_icin
    {
        class Base
        {
        public:
            ~virtual Base() = default;

        private:
        };
        class Der : public Base
        {
        public:
        private:
        };

        void car_game(Car &cr)
        {
            std::cout << "cr: " << cr << " \n";
            cr.start();
            cr.run();
            if (typeid(cr) == typeid(Volvo)) // Sadece Volvo için if'in doğru kısmına girer
                // Her volvoXC90 bir Volvo'dur fakat her Sınıfın typeinfo nesnesi farklıdır.
                // Dynamic_cast içinde böyle bir kod üretiliyor.
                static_cast<Volvo &>(cr).open_sunroof();
            cr.stop();
        }
        int main() // main'de cagir!!!
        {
            std::cout << "type_id_polymorphic_tur_icin main\n";
            Der myder;
            Base *baseptr = &myder;
            std::cout << typeid(*baseptr).name();
            << "\n";
            if (typeid(*baseptr) == typeid(Base))
            {
                std::cout << "dogru\n";
            }

            for (int i = 0; i < 100; ++i)
            {
                Car *carptr = create_random_car();
                std::cout << "*carptr: " << *carptr << " \n";
                std::cout << "typeid(*carptr).name(): " << typeid(*carptr).name() << " \n";
                (void)getchar();
                delete p;
            }
            return 0;
        }

    } // type_id_polymorphic_tur_icin sonu

    /* Yorum Baslik:derleyici_calisma_zamaninda_turu_anlamasi
    Derleyici polymorphic sınıf türleri için bir typeinfo nesnesi oluşturuyor.
    ve bu typeinfo nesnesinin adresini de bu tabloda tutuyor.
    Dolayısıyla nasıl virtual dispatch'te sanal fonksiyonun adresi elde ediliyorsa
    Derleyici sanal fonksiyonun kısmına erişiyor daha sonra o typeinfo nesnesine eriştiriyor.
    Derleyici dökümanına bakmak gerekiyor => Hem bellek hem de zaman maliyeti var.
    Eğer RTTI' kullanılamayacaksa (Run time type identification) bu özelliği iptal ederek, bundan kurtulunabilir.
    dynamic_cast ve typeid() kullanılması derleyici tarafından engelleniyor.

    A kalıtım yoluyla
    B kalıtım yoluyla
    C kalıtım yoluyla
    D kalıtım yoluyla
    E
    derleyici E'ye kadar gidicek typeid sınamasıyla. Sınamanın maliyeti dynamic_cast'e göre daha yüksek.


     */
    /* Yorum Baslik:rtti_exception_throw_2
     */
    namespace rtti_exception_throw_2
    {
        void car_game(Car *ptr)
        {
            std::cout << "*ptr: " << *ptr << " \n";
            if (typeid(*ptr) == typeid(Volvo)) // eğer bu durumda ptr'nin değeri nullptr'e ise exception thro ediliyor
            {
            }
        }
        Car *foo()
        {
            return nullptr;
        }

        int main() // main'de cagir!!!
        {
            std::cout << "rtti_exception_throw_2 main\n";
            try
            {
                /* code */
                car_game(foo());
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            return 0;
        }
    } // rtti_exception_throw_2 sonu

    /* Yorum Baslik: Multiple Inheritance
    Bir çok programlama dilinde yok
        Multi Level inheritance DEĞİL!!!!
    Burada kast edilen bir sınıfın birden fazla sınıftan kalıtım yoluyla elde edilmesi
    BaseX BaseY
        Der
    Her ikiside public olursa her Der nesnesi hem BaseX nesnesi hem de BaseY
    public interfacesine tüm taban sınıfın public alanını implemente edecek
    2 - 3 çok yaygın kullanılan taban sınıf sayısı

    Bir sınıfa birden fazla sınıfın interface'ni katmak istiyorsak işimizi kolaylaştırıyor
     */
    /* Yorum Baslik:multipleinheritance
        Incomplete type'lar taban sınıf olarak kullanılamaz.
    */
    namespace multipleinheritance
    {
        class BaseA
        {
        public:
            BaseA() { std::cout << "A'nin ctor\n"; }

        private:
        };

        class BaseB
        {
        public:
            BaseB() { std::cout << "B'nin ctoru\n"; }

        private:
        }

        // class Der: BaseA, BaseB {//private kalıtılım
        // class Der: private  BaseA, private BaseB {//private kalıtılım
        // struct Der: BaseA, BaseB {//public kalıtılım
        // tüm inheritance için belirtilmesi gerekiyor

        class Der : /*inheritance şekli*/ public BaseA,
                    /*inheritance şekli*/ public BaseB
        {
            // Her Der bir BaseA'dır ve BaseB'dir.
            // Hem bir A'nesnesi hem de bir B nesnesi var.
            // Ctor'un çağırılma sırası bildirimdeki yazılma sırasıyla alakalı
        public:
            // Der():BaseB(),BaseA(){} //Buradaki sıra hala yukarıdaki bildirimden elde ediliyor
        private:
        };
        int main() // main'de cagir!!!
        {

            std::cout << "multipleinheritance main\n";
            Der cx;
            BaseA *aptr = &cx;
            BaseB *bptr = &cx;

            BaseA &aref = &cx;
            BaseB &bref = &cx;
            return 0;
        }
    } // multipleinheritance sonu
    /* Yorum Baslik:multipleinheritance_ornek
     */
    namespace multipleinheritance_ornek
    {
        class A
        {
        public:
            virtual void a_foo();
            void a_bar();
            void a_baz();
            void foo(int, int);
        };
        class A
        {
        public:
            void b_foo();
            virtual void b_bar();
            void b_baz();
            void foo(int);
        };
        class C : public A, public B
        {
        public:
            void a_foo() override;
            void b_bar() override;

            void func()
            {
                // foo() //SENTAKS HATASI
                static_cast<A *>(this)->foo(12, 12);
                static_cast<B *>(this)->foo(12);
            }
        };
        int main() // main'de cagir!!!
        {
            std::cout << "multipleinheritance_ornek main\n";
            C cx;
            cx.a_foo();
            cx.a_bar();
            cx.a_baz();
            cx.b_foo();
            cx.b_bar();
            cx.b_baz();

            /* Yorum Baslik:foo fonksiyonları için açıklama
                Çoklu kalıtımda isim arama belirli bir sıraya sahip değil
                derleyici foo ismini arıyor ve bu isim birden fazla sınıfta varsa bu ambiguity oluyor.
                fonksiyon veya değişken olmasından bağımsız burada ambuguity oluşuyor.
                İsim kullanıldığında ambiguity oluyor

                bunu çözümlemenin yolu ismi nitlenmiş isim olarak kullanmak
             */
            // cx.foo(1,2);
            // cx.foo(1);
            cx.A::foo(1, 2);
            cx.B::foo(1);

            return 0;
        }
    } // multipleinheritance_ornek sonu

    /*
    Yorum Baslik:DiamondFormtaion
        DDD (dreadful diamond of derivation):Kalıtımın ölümcül elması
        Eğer bir sınıfı çok kaltım yoluyla elde ettiğimizde
        Ve bu sınıfların ortak bir taban sınıfı varsa
         A
        B C
         D
         Bu durumda D'sınıf nesnesinin içinde Hem bir B Hem bir C nesnesi olucak ve
         Hem B' sınıfından Hem de C'sınıfından bir A nesnesi gelicek

         Bunu %99.9 istemiyoruz
         1 - static problemler Eğer herhangi bir kod D'nin içindeki A'yı kullanıyorsa ve nitelenmiş bir isim kullanılmıyorsa
         Derleyicinin koda bakarak Hangi A nesnesini anlama olanağı yok ambuguity hatası olucak.

         2 - Asıl problem run-time'a ilişkin

           Device
        Fax     Modem( Device gereken yerde bunları kullanabiliyoruz. )
          Fax-Modem ( Hem fax'ın hem de modem olarak kullanılabilmesini istiyoruz. )

        Fax'tarafında ve modem tarafında bir işlem yapıldığında Fax'tarafında yapılan değişiklikler
        Modem tarafında yapılmamış olabilir.

        Virtual inheritance: sanal kalıtım ile çözülebiliyor.
     */
    namespace DiamondFormtaion
    {

        class Base
        {
        public:
            void foo() { std::cout << "this: " << this << " \n"; }
        };
        class Der1 : public Base
        {
        };
        class Der2 : public Base
        {
        };
        class MDer : public Der1, public Der2
        {
        };
        void func(Base *);
        int main() // main'de cagir!!!
        {
            std::cout << "DiamondFormtaion main\n";
            MDer md;
            // md.foo()//SENTAKS HATASI Bu fonksiyon çağırıldığında bir Base ptr gerekiyor.
            // Burada iki tane Base nesnesi var ve derleyici hangisini kullanacağını bilemiyor
            md.Der1::foo();
            md.Der2::foo();
            static_cast<Der1 *>(&md)->foo();
            static_cast<Der2 *>(&md)->foo();
            // func(&mx);//SENTAKS HATASI!!! ambuguity hangi Base gönderiliyor belli değil.
            return 0;
        }
    } // DiamondFormtaion sonu
    /* Yorum Baslik:diamond_problem
     */
    namespace diamond_problem
    {
        class Device
        {
        public:
            void turn_on()
            {
                m_flag = true;
                std::cout << "deviced turned on\n";
            }
            void turn_off()
            {
                m_flag = false;
                std::cout << "deviced turned off\n";
            }
            bool is_on() const { return m_flag; }

        private:
            bool m_flag{};
        } class Fax : public Device
        {
        public:
            void turn_on()
            {
                Device::turn_on();
            }
            void send_fax()
            {
                if (is_on())
                {
                    std::cout << "cihaz acik faks gonderildi\n";
                }
                else
                {
                    std::cout << "cihaz kapali oldugundan fax gonderilemedi.\n";
                }
            }
            void receive_fax();
        } class Modem : public Device
        {
        public:
            void send_data()
            {
                if (is_on())
                {
                    std::cout << "cihaz acik faks gonderildi\n";
                }
                else
                {
                    std::cout << "cihaz kapali oldugundan fax gonderilemedi.\n";
                }
            }
            void receive_data();
        } class FaxModem : public Fax, public Modem
        {

        } int main() // main'de cagir!!!
        {
            std::cout << "diamond_problem main\n";
            FaxModem fm;
            fm.Fax::turn_on();
            fm.send_fax();
            fm.send_data(); // Cihaz acik olmasına rağmen 2 tane device olduğu için yazdırıldı.
            return 0;
        }
    } // diamond_problem sonu
    /* Yorum Baslik:virtual Inheritance
    Çoklu kalıtım da eğer tek bir Base nesnesi olmasını istiyorsak Bütün bu taban sınıfları virtual inheritance olarak elde
    etmemiz gerekiyor.

    Tüm hepsinin virtual olması gerekiyor
     */
    namespace virtual_Inheritance
    {
        class Base
        {
        public:
            void foo();

        private:
        };
        class Der1 : virtual public Base
        {
        public:
        private:
        };
        class Der2 : virtual public Base
        {
        public:
        private:
        };
        class MDer : public Der1, public Der2
        {
        };
        int main() // main'de cagir!!!
        {
            std::cout << "virtual Inheritance main\n";
            Mder md;
            md.foo(); // Artık sentaks hatası değil virtual kullandık!!
            return 0;
        }

    } // virtual Inheritance sonu
    /* Yorum Baslik:virtual_fax_modem
     */
    namespace virtual_fax_modem
    {
        class Device
        {
        public:
            void turn_on()
            {
                m_flag = true;
                std::cout << "deviced turned on\n";
            }
            void turn_off()
            {
                m_flag = false;
                std::cout << "deviced turned off\n";
            }
            bool is_on() const { return m_flag; }

        private:
            bool m_flag{};
        } class Fax : virtual public Device
        {
        public:
            void turn_on()
            {
                Device::turn_on();
            }
            void send_fax()
            {
                if (is_on())
                {
                    std::cout << "cihaz acik faks gonderildi\n";
                }
                else
                {
                    std::cout << "cihaz kapali oldugundan fax gonderilemedi.\n";
                }
            }
            void receive_fax();
        } class Modem : virtual public Device
        {
        public:
            void send_data()
            {
                if (is_on())
                {
                    std::cout << "cihaz acik faks gonderildi\n";
                }
                else
                {
                    std::cout << "cihaz kapali oldugundan fax gonderilemedi.\n";
                }
            }
            void receive_data();
        } class FaxModem : public Fax, public Modem
        {

        } int main() // main'de cagir!!!
        {
            std::cout << "diamond_problem main\n";
            FaxModem fm;
            fm.Fax::turn_on();
            fm.send_fax();
            fm.send_data(); // Cihaz acik olmasına rağmen 2 tane device olduğu için yazdırıldı.
            return 0;
        }
        int main() // main'de cagir!!!
        {
            std::cout << "virtual_fax_modem main\n";
            return 0;
        }

    } // virtual_fax_modem sonu
    /* Yorum Baslik:fstream_ornek 
     */
    namespace fstream_ornek{
    #include <fstream>
        int main()//main'de cagir!!!
        {
            std::cout<<"fstream_ornek main\n";
            fstream fs{"necati.txt"};
            fs <<"ali"; //ostream
            int x;
            fs>>x; //istream
            fs.width(20);//ios_base sınıfından geliyor
            //sanal kalıtım olduğu için aynı sınıf nesnesinin width fonksiyonu çağırılıyor.
            return 0;
        }
    }// fstream_ornek sonu

    /* Yorum Baslik:virtualInheritance_zor_ornek
    Burada ortada ayrı ayrı nesneler olmadığı için 
     */
    namespace virtualInheritance_zor_ornek{
    
    class Base{
    public:
        Base(int x){    std::cout<< "Base(int x) x: " << x <<" \n";}
    private:
        
    };
    class Der1:virtual public Base{
    public:
        Der1(): Base(0){    std::cout<<"Der1 default ctor\n";}
    private:
        
    }; 
    class Der2: virtual public Base{
    public:
        Der2(): Base(1){    std::cout<<"Der2 default ctor\n";}
    private:
        
    };
    class MDer:public Der1, public Der2
    {
        public:
        Mder():Base(3){}
        
    };
    class MCDer: public MDer{
        public:
        MCDer(): Base(4){}s 
    };
        int main()//main'de cagir!!!
        {
            std::cout<<"virtualInheritance_zor_ornek main\n";
            //MDer md;
            //SENTAKS HATASI virtual base'i kimin init edeceği problemi var
            //çoklu kalıtımda çoklu kalıtımla elde edilen bütün sınıflar 
            //virtual Base class nesnesini init etmeli
            MCder mcd;
            Mder md;

        return 0;
        }
    
    }// virtualInheritance_zor_ornek sonu
} // namespace 26_ders
```
