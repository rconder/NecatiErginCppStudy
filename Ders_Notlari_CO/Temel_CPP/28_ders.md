# 28.ders

```cpp
#include <iostream>
#include <stdexcept>

namespace ders_28
{
    /* Yorum Baslik:Exception handling'ten devam

    */
    /* Yorum Baslik:rethrow
     */
    namespace rethrow
    {

        void func()
        {
            try
            {
                throw std::out_of_range{"range hatasi"};
            }
            catch (const std::exception &ex)
            {
                std::cout << " hata func icinde yakalandi " << ex.what() << "\n";
                throw ex;
                // throw; //eğer böyle yollarsak dinamik tür korunuyor. ve out_of_range ile yakalanıyor

                //
            }
        }

        int main() // main'de cagir!!!
        {
            std::cout << "rethrow main\n";
            try
            {
                func();
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "hata out_of_range ile yaaklandi! " << e.what() << '\n';
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            return 0;
        }
    } // rethrow sonu

    /* Yorum Baslik:rethrow2
     */
    namespace rethrow2
    {
        class NecEx
        {
        public:
            NecEx() = default;
            NecEx(const NecEx &)
            {
                std::cout << " copy ctor \n";
            }
        };

        void func()
        {
            try
            {
                {
                    throw NecEx{};
                }
            }
            catch (const std::exception &e)
            {
                throw e; // copy ctor çağırılacak
                // throw;
            }
        }
        int main() // main'de cagir!!!
        {
            std::cout << "rethrow2 main\n";
            try
            {
                func();
            }
            catch (const NecEx &e)
            {
                std::cout << "std::cerr << e.what() << '\n';";
            }
            return 0;
        }
    } // rethrow2 sonu

    /* Yorum Baslik:rethrow3

     */
    namespace rethrow3
    {
        void foo()
        {
            std::cout << "fooooo cagirildi\n";
            throw; // rethrow fonksiyonu bruradad bulunabiir.
        }

        void func()
        {
            try
            {
                /* code */
                std::runtime_error{"hata hata hata"};
            }
            catch (const std::exception &e)
            {
                std::cout << "hata func icinde yakalandi\n";
                std::cerr << e.what() << '\n';
                foo();
            }
        }
        int main() // main'de cagir!!!
        {
            std::cout << "rethrow3 main\n";
            try
            {
                foo();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            return 0;
        }
    } // rethrow3 sonu
    /* Yorum Baslik:foo_yu_catch_de_yakalamamak
     */
    namespace foo_yu_catch_de_yakalamamak
    {

        void foo()
        {
            std::cout << "fooooo cagirildi\n";
            throw; // rethrow fonksiyonu bruradad bulunabiir.
        }

        void func()
        {
            try
            {
                /* code */
                std::runtime_error{"hata hata hata"};
            }
            catch (const std::exception &e)
            {
                std::cout << "hata func icinde yakalandi\n";
                std::cerr << e.what() << '\n';
                foo();
            }
        }
        void n_terminate()
        {
            std::cout << "n_terminate\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "foo_yu_catch_de_yakalamamak main\n";
            std::set_terminate(&n_terminate);
            foo();
            return 0;
        }
    } // foo_yu_catch_de_yakalamamak sonu

    /* Yorum Baslik:
        Eğer bir fonksiyon çağırıldığında rethrow statement yürütülüyorsa
        terminate fonksiyonu çağırılıyor.
        Exception dispatcher idiom'u
     */
    /* Yorum Baslik:exception_dispatcher
     */
    namespace exception_dispatcher
    {
        class NecException
        {
        };
        class ErgException
        {
        };
        class CsdException
        {
        };

        void handle_exception()
        {
            try
            {
                throw; // burada rethrow ediyoruz
            }
            catch (const NecException &e)
            {
            }
            catch (const ErgException &e)
            {
            }
            catch (const CsdException &e)
            {
            }
            // bu catch fonksyionlar ile handle edilmiş oluyor.
        }
        void func()
        {
            try
            {
                /* code */
            }
            catch (...)
            {
                handle_exception(); // burada rethrow aktif hale geliyor
            }
        }
        int main() // main'de cagir!!!
        {
            std::cout << "exception_dispatcher main\n";
            return 0;
        }
    } // exception_dispatcher sonu

    /* Yorum Baslik:Terminate'in 3. çağırılma methodu
    Eğer catch bloğunda exception handle edilirken
    yani catch parametresi oluşması sırasında exception olursa terminate çağırılıcak
    */

    /* Yorum Baslik: Stack'de onlarca nesne oluşturulmuş olabilir.

    f1 => f2 => f3 => ...... => f16
     örneğin f16'da exception oluşturuldu ve f1'de yakıldı bu arada oluşturulmuş otomatik ömürlü nesnelerin exception'dan sonra destructor'ının çağırılma
     garantisi yok. Oysa bu destructorlar kaynak yönetimlerini yapıyor olabilir ve bunlar yapılmadığı zaman kalıcı zararlar olabilir.

     Eger programda exception yakalanırsa programının akışı catch bloğuna girmeden otamatik ömürlü nesnelerinin destructorları
     cagiriliyor "stack unwinding"!!!!!

     */
    /* Yorum Baslik:ornek_destructor_cagirilmamasi"
     */
    namespace destructor_cagirilmamasi
    {

        struct A
        {
            A()
            {
                std::cout << "A'nın ctoru\n";
            }
            Ã()
            {
                std::cout << "A'nin destructor'i\n";
            }
        } struct B
        {
            B()
            {
                std::cout << "B'nın ctoru\n";
            }
            B()
            {
                std::cout << "B'nin destructor'i\n";
            }
        } struct C
        {
            C()
            {
                std::cout << "C'nın ctoru\n";
            }
            C()
            {
                std::cout << "C'nin destructor'i\n";
            }
        } void foo()
        {
            std::cout << "foo cagirildi\n";
            A ax;
            bar();
            std::cout << "foo sona erdi\n";
        }
        void bar()
        {
            std::cout << "bar cagirildi\n";
            B bx;
            baz();
            std::cout << "bar sona erdi\n";
        }
        void baz()
        {
            std::cout << "baz caagirildi\n";
            C cx;
            // throw 1;//burada destructorlar cagirilmiyor
            throw std::runtime_error{"baz fonksiyonu icinde hata"} std::cout << "baz sona erdi\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "ornek_destructor_cagirilmamasi main\n";
            // foo();
            try
            {
                foo();
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << "\n";
            }
            return 0;
        }
    } // ornek_destructor_cagirilmamasi sonu

    /* Yorum Baslik:Stack unwinding RAI idiomu ile ayrılmaz bir bütün
    Resource Acusition is initialization.
    Böylece bir nesne için destructor çağırıldığında kaynakların ge

    Klasik C tarzı bir programlamada bir kaynak edinip kaynağıda pointer'a bağlıyoruz

    void func()
    {
        FILE *f = std::fopen("a.txt","w");
        //örneğin burada bir exception throw edilirse
        //programın akışı burdan çıkacak ve
        //fclose çağırılmıyıcak
        //artık kaynakları samarlayan sınıf yazıyoruz.
        std::fclose(f);
    }
     */
    /* Yorum Baslik:rai_catch_ornek
     */
    namespace rai_catch_ornek
    {

        struct A
        {
            A()
            {
                std::cout << "A'nın ctoru\n";
            }
            Ã()
            {
                std::cout << "A'nin destructor'i\n";
            }
        } struct B
        {
            B()
            {
                std::cout << "B'nın ctoru\n";
            }
            B()
            {
                std::cout << "B'nin destructor'i\n";
            }
        } struct C
        {
            C()
            {
                std::cout << "C'nın ctoru\n";
            }
            C()
            {
                std::cout << "C'nin destructor'i\n";
            }
        } void foo()
        {
            std::cout << "foo cagirildi\n";
            A *aptr = new A;
            bar();
            delete aptr;
            std::cout << "foo sona erdi\n";
        }
        void bar()
        {
            std::cout << "bar cagirildi\n";
            B *bptr = new B;
            baz();
            delete bptr;
            std::cout << "bar sona erdi\n";
        }
        void baz()
        {
            std::cout << "baz caagirildi\n";
            std::unique_ptr<C> upptr{new C};
            // throw 1;//burada destructorlar cagirilmiyor
            throw std::runtime_error{"baz fonksiyonu icinde hata"} std::cout << "baz sona erdi\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "ornek_destructor_cagirilmamasi main\n";
            // foo();
            try
            {
                foo();
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << "\n";

                // exception yakalansa daha
                /* Yorum: dinamik ömürlü nesnelerin delete edilmiyor ve kaynak sızıntısı oluyor.
                onun icin buurada smart pointer kullanılabilir.

                 */
            }
            return 0;
        }
    } // rai_catch_ornek sonu

    /* Yorum Baslik: Dilin semantik kurallarına göre belirli garantileri vermek zorunda
    Bunlara Exception Guarantees deniyor
    En zayıftan -> En güvenlik olana doğru:
    ============
    no gurantee: kaynak sızıntısı olabilir ve kabul edilebilir bir durum değil nesnenin kullanılmaz durumda kalması
    void func()
    {
        Fıle *f = fopen....
        foo(); //exception gönderme ihtimali var
        fclose(f);
    }
    burada örneğin kaynak sızıntısı riski var.
    ============
    basic gurantee: temel garanti. Kabul edilebilir minimum garanti
    Eğer fonksiyondan exception edilerek çıkılması durumunda kaynak sızdırılmaması garantisi var
    - (!!!!!no resource leak!!!!!)
    - Hayatı devam eden nesnelerin hepsi valid state de olmalı.
    - Sınıfların ya da programların invariant'ları (değişmezleri) var ve öyle bir satate program boyunca korunucak. Nesne hayata geldiğinde
    invariantlar oluşucak ve nesnenin işini yapabilmesi için bunların korunması da olmak zorunda.

    temel garanti bunları tutacak. Burada nesne geçerli bir değerde kalacak fakat!!!! nesnenin state'i değişmiş olabilir.
    ve nesneini destructor'ının çağırılması    bir problem yaratmayacak

    En zor kısım bu mutlaka bu sağlanmalı
    ============

    Strong Guarantee (commit or rollback): Exceptionla çıkıldığında
    programın state'inde de bir değişiklik yani Söz konusu fonksiyon ya işini yapacak
    ya da programın state'ini fonksiyon çağırılmadan önceki haline çekecek.

    Strong garanti her zaman mümkün olmayabilir. Örneğin vector'ü sıralarken bir hata olabilir. Bazı durumlarda çok
    yüksek bir maliyet getirebilir.

    ============

    no throw guarantee:
    bu durumda ilgili fonksiyon diyorki benim exception göndermeyeceği garanti
    Verilebilecek en net garanti ve bunu gösteren bir araçta
    Dilin sentatik bir tarafıda var!!!!!!!!!!!!!!!
    Öyle fonksiyonlar var ki bu fonksiyonlar mutlaka bu garantiyi sağlamalı
    - DESTRUCTOR'lar bu garantiyi vermeli.!!!!!!!!!!!!!!!!!!!! Otomatik olarak öyle kabul ediliyor
    - SWAP fonksiyonları
    - MOVE MEMEBERS Özellikle de MOVE CTORS!!!!!!
    - Operator delete fonksiyonları
    - Cleanup fonksiyonları !!!!!!!!!!!!!
     */
    /* Yorum Baslik:strong_and_basic_guarantee
     */
    namespace strong_and_basic_guarantee
    {

        class Message
        {
        private:
            /////
        public:
            std :.string to_string() const
            {
                std::string result;
                // may throw exception
                return result;
            }
        };

        void log(const std::vector<Message> &mvec) // üyeleri mesajların dinamik dizisi
        // log'da mesajı string'e dönüştürüp log dosyasına yazıyor.
        {

            std::ofstream logfile;
            logfile.open("log.txt", std::ios_base::app);
            for (const auto &m : mvec)
                logfile << m.to_string();
            // burada log file'ın state değişmiş durumda
            // bu fonksiyon basic garanti veriyor
            // eğer strong garanti istiyorsa fonksiyon exception throw ederse
            // geri dönmesi lazım
            // değişikliği kalıcı hale
        }
        void log_strong(std::vector<Message> &mvec)
        {
            std::ofstream log_file;
            log_file.open("log.txt", std::ios_base::app);

            std::string result;
            for (const auto &m : mvec)
            {
                result += m.to_string();
                // böylece strong garanti verilmiş oluyor
            }
            log_file << result;
        }
        int main() // main'de cagir!!!
        {
            std::cout << "strong_and_basic_guarantee main\n";
            return 0;
        }
    } // strong_and_basic_guarantee sonu

    /* Yorum Baslik:dynamicExceptionSpecification
    BUNLAR yok hükmünde fonksiyonun bildiriminde gösteriliyordu ve hangi türlerden olucağı gösteriliyordu
    Artık yok
     */
    namespace dynamicExceptionSpecification
    {

        void func(); // herhangi bir except gönderebilir.
        void func() throw(std::bad_alloc, /* ve diger exceptionlar */);
        void func() throw(); // NO-THROW GARANTİ
        int main()           // main'de cagir!!!
        {
            std::cout << "dynamicExceptionSpecification main\n";
            return 0;
        }

    } // dynamicExceptionSpecification sonu

    /* Yorum Baslik: noexcept :
    İki ayrı anlamda noexcept specifier ve
    noexcept operator ve aynı kontekste kullanılabiliyor.
    exception_gondermeme_garantisi

    Ya exception göndermez garantisi ya da Exception gönderebilir
    ==========
    bir fonksiyon bildirildiğin üye fonksiyon olsun ister free func olsun noexcept ile bildirilirse
    bu fonksiyonun exception göndermeme garantisi veriyor. Olmadığı durumda gönderebilir demek


    Bir fonksiyonun
     */
    namespace no_except_ornek
    {

        void foo() noexcept;

        // void foo(){} //SENTAKS HATASI

        // void foo(); //SENTAKS HATASI!! çelişkili

        void func() noexcept(/*buraya const ifadesi veriliyor ve bu ifade dogru ise noexcept garantisi veriyor*/)
            // void func()noexcept(true) ile void func()noexcept; aynı
            // void func()noexcept(false) ile void func(); aynı
            // ornegin void func()noexcept(constant expression) => expression doğru ise noexcept garantisi veriyor
            // ya da vermiyor yani noexcept bir koşula bağlanabiliyor.
            void func() noexcept
        {
            // eger exception lokal olarak yakalanırsa da sorun yok
            // fonksiyondan emit etmediği sürece problem yok babbbbaaaa
            // onun için bundan %100 emin olmak lazım
            throw 1;
        }
        int main() // main'de cagir!!!
        {
            std::cout << "exception_gondermeme_garantisi main\n";
            func(); // Eğer func fonksiyon çalıştığında bir exception throw ederse
            // dogrudan terminate fonksiyonu çağırılıyor ve bu compile tamda kontrol edilmiyor.
            try
            {
                func();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            return 0;
        }
    } // exception_gondermeme_garantisi sonu

    /*
        Eğer destructor'dan exception throw edilirse terminate edilmiş olucak
        yani destructor'lar nothrow garantisi vermek zorunda ve dilin kuralı gereği
        nedeni:
        Destructor
            Hayatı bittiği için çağırılabilir.
            Stack unwinding ile destructorları cagiriliyor ama cagirilan destructor throw ederse
            terminate cagiriliyor. Bu nedenle bir destructorın exception throw etmesi bu anlama denk geliyor.

        Diger özel üye fonksiyonların noexcept olup olmadığı koda bakarak anlaşılıyor

        class Myclass
        {
            public:
            Bütün üye fonksiyonlar noexcept
        }
    */
    /* Yorum Baslik:type_traits
     */

    namespace type_traits
    {
        class Nec
        {
        public:
            Nec();
        };

        class Myclass
        {
        public:
            // Myclass() = default;//burada derleyici garanti vermiyor fakat
            Myclass() noexcept = default; // olarak yapabilir.
        private:
            Nec necx;
        };

        int main() // main'de cagir!!!
        {
            std::cout << "type_traits main\n";
            using namespace std;
            const auot b = is_nothrow_default_constructible<Myclass> return 0;
        }
    } // type_traits sonu

    /* Yorum Baslik:Derleyici ile noexcept arasında bir optimizasyon var
     Fakat derleyicinin compile time da koda bakarak kod seçiyor.
     Örneğin
        28.ders => 02:00:00'ı izle
     */

    /* Yorum Baslik:noexcept_operatoru

    tipik olarak noexcept specifier'ının bir koşula bağlanmasında işlevsel hale geliyor
    bu operator true ya da false bu ifadenin ürettiği değer compile tamda bir compile değişken üretiyor
    Bu ifadenin elemanı olan ifade UNEVALUATED Operator
    sizeof()
    decltype()
    typeid() veeeee
    noexcept()
     */
    namespace noexcept_operatoru
    {
        class Nec
        {
        public:
            void foo();

        private:
        };
        class Myclass
        {
        };
        //                       -specifier- -operator-
        void func(const Myclass &r) noexcept(noexcept(Myclass{})); // eğer myclass'ın default ctor'u noexcept garantisi veriyorsa
        // func fonksiyonu da bu garantiyi veriyor.!!!

        int main() // main'de cagir!!!
        {
            std::cout << "noexcept_operatoru main\n";
            Nec nec;
            int x = 19;
            constexpr auto b = noexcept(x + 5);
            constexpr auto bn = noexcept(nec.foo());
            return 0;
        }
        /* Yorum Baslik:islendigi yer templateler
            template <typeename T>
            void func(T); //Buraya gelen parametrenin ne olduğu compile zamanında anlaşılacak
            //burada da type_trait denilen araçlar  işlevsel oluyor
            void func(T)noexcept(std::is_nothrow_copy_assignable_v<T>);
            //func fonksiyonu T olan türün copy assignment fonksiyonunun nothrow garantisi vermesi durumunda nothrow garantisi veriyor.
         */
    } // noexcept_operatoru sonu

    /* Yorum Baslik:
    function pointer ile noexcept arasında ilişki bu fonksiyon specifier'I da nitelenebiliyor
    int (*fp)(int)noexcept; bu fonksiyon no throw garantisi veren bir fonksiyonu gösteriyor.
    Böylece bu fonksiyon göstergeci ile bir fonksiyon çağırısı yapıldığında no throw garantisi ile kod yazılabilecek
     */
    /* Yorum Baslik:func_ptr_noexcep_ilsikisi
     */
    namespace func_ptr_noexcep_ilsikisi
    {
        int foo(int);
        int func(int) noexcept;
        int main() // main'de cagir!!!
        {
            std::cout << "func_ptr_noexcep_ilsikisi main\n";
            int (*fp)(int) noexcept;
            // fp = &foo;//SENTAKS HATASI çünkü bu fp noexcept garantisi veriyor
            auto fpp = &foo;
            auto fppp = &func;
            int (*fp2)(int);
            fp = &func(); // burada herhangi bir sorun yok
            return 0;
        }
    } // func_ptr_noexcep_ilsikisi sonu

    /* Yorum Baslik:kalitim_ile
     */
    namespace kalitim_ile
    {
        class Base
        {
        public:
            virtual void func() noexcept;
            virtual void foo() noexcept;

        private:
        };
        class Der : public Base
        {
        public:
            // void func()override;//SENTAKS HATASI türemiş olan sınıfın override noexcept değil ve bu tahüte güvenenler nanay olabilir.
            void func() noexcept override;
            void foo() noexcept override;

        private:
        };
        int main() // main'de cagir!!!
        {
            std::cout << "kalitim_ile main\n";
            return 0;
        }

    } // kalitim_ile sonu

    /* Yorum Baslik:
    Constructor'a gelince ise exception göndermeye en fazla aday fonksiyon çünkü
    Nesne hayata getiriliyor ve bunu tutması gerekiyor eğer burada exception throw edemezse
    zombi nesne oluşturuluyor. Eğer exception throw edilirse nesne hayata getirilmemiş oluyor.
    Ve hayata gelmiş bir nesne yok ve bu da demektirki destructor çağırılmayacak
     */
    /* Yorum Baslik:ctor_exception
         Burada dikkatli olmakt gerekiyor çünkü eğer ctor içinde elde edilen kaynak nesne hayata gelmeden exception throw edince
         nesne hayata gelmeyecek ve destructor'ı çağrılmayacak böylece kaynak sızıntısı olacak
     */
    namespace ctor_exception
    {
        class Nec
        {
        public:
            Nec()
            {
                std::cout << "Nec default ctor\n";
                throw 1;
            }
            ~Nec()
            {
                std::cout << "Nec destructor \n";
            }

        private:
        };
        int main() // main'de cagir!!!
        {
            std::cout << "ctor_exception main\n";
            try
            {
                Nec mynec;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            return 0;
        }
    } // ctor_exception sonu

    /* Yorum Baslik:dinamik nesne için ise   
    Eğer bir sınıf türünden dinamik ömürlü bir nesne operator new fonksiyonu ile elde edilen adres this ptr ile kullanılıyor fakat burada bir garanti var ve 
    operator delete fonksiyonu çağırılacak.
    */
}
```
