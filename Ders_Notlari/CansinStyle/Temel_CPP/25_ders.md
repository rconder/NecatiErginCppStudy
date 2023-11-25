# 25.ders

```cpp
#include <iostream>
namespace ders_25
{
    /* Yorum Baslik:nec_ornek_1
     */
    using namespace std;
    namespace nec_ornek_1
    {
        // polymorhpic taban sınıfların destructorları
        // default olarak virtual olduğunu varsay
        class Base
        {
        public:
            virtual ~Base() = default;
            void func(int);
            void func(long);
            void func(char);

        private:
        };
        class Der : public Base
        {
        public:
            using Base::func;
            void func(int, int);

        private:
        };
        int main_1() // main'de cagir!!!
        {
            std::cout << "ornek 1 main\n";
            Der myder;
            myder.func(12); // taban sınıfın func fonksiyonu
            myder.func(12L);
            myder.func('1');
            // hepsi taban sınıfın fonksiyonu

            myder.func(12, 34); // türemiş sınıfın func fonksiyonu
            return 1;
        }
    } // nec_ornek_1 sonu

    /* Yorum Baslik:nec_ornek_2
     */
    namespace nec_ornek_2
    {
        class Base
        {
        public:
            virtual ~Base() = default;
            void func(int);

        private:
        };
        class Der : public Base
        {
        public:
            using Base::func;
            void func(int x) { std::cout << "Der::x: " << x << " \n"; }

        private:
        };
        int main_2() // main'de cagir!!!
        {
            std::cout << "ornek 2 main\n";
            Der myder;
            myder.func(12);
            return 2;
        }

    } // nec_ornek_2 sonu

    /* Yorum Baslik:nec_ornek_3
     */
    namespace nec_ornek_3
    {
        class Base
        {
        public:
        protected:
            using value_type = int; // type alias
            int mx;

        private:
            int px;
        };

        class Der : public Base
        {
        public:
            using Base::mx;
            using Base::value_type; // using taban sınıftaki ismin türemiş sınıf scope'una enjekte edilmesi için
            // private
            // using Base::px; //SENTAKS HATASI!!!!
        private:
        };

        int main_3() // main'de cagir!!!
        {
            std::cout << "ornek 3 main\n";
            Der myder;
            myder.x;
            // Der::value_type x; //using bildirimi eklenmezse sentaks hatası
            return 3;
        }

    } // nec_ornek_3 sonu

    /* Yorum Baslik: Inharited Constructor
    using bildiriminin daha önce olmayan şekilde ctor'a uygulanması

     */
    /* Yorum Baslik:nec_ornek_4
    kalıtım büyük çoğunlukla runtime polymorphisim ile kullanılırken
    bazen de run time polymorphisim olmadan taban sınıfın interface'ini alıp ekleme yapmak istiyoruz
     */
    namespace nec_ornek_4
    {
        class Base
        {
        public:
            Base() = default;
            Base(int x) { std::cout << " Base(int) x: " << x << " \n"; };
            Base(int, int);
            Base(double);

            void func(int);
            void foo(int);
            void g();
            void bar(double);

        private:
        };

        class Der : public Base
        {
        public:
            // Burayada aynı parametrik yapıda ctorlar yazabilirdik
            Der(int x) : Base(x) {}

        private:
        };
        int main_4() // main'de cagir!!!
        {
            std::cout << "ornek 4 main\n";
            Der myder; // Eğer base sınıfının default ctor'u olmazsa SENTAKS HATASI olur
            // Der myder(12,12);//SENTAKS HATASI çünkü türemiş sınıfın böyle bir ctor'u yok
            Der d1(1);
            // Der d2(2,3); Bu şekilde Der nesnelerinin oluşturulmasını istersek
            // İnherited ctor olmasaydı
            myder.func(12);
            // Tüm Base fonksiyonlarını çağırabiliriz ve ek fonksiyonlar ekleyebiliriz.
            return 4;
        }
    } // nec_ornek_4 sonu

    // using ile ctor kullanımı
    namespace nec_ornek_5
    {
        class Base
        {
        public:
            Base() = default;
            Base(int x) { std::cout << " Base(int) x: " << x << " \n"; };
            Base(int, int);
            Base(double);

            void func(int);
            void foo(int);
            void g();
            void bar(double);

        private:
        };

        class Der : public Base
        {
        public:
            using Base::Base;

        private:
        };
        int main_5() // main'de cagir!!!
        {
            std::cout << "ornek 5 main\n";
            Der myder(12);
            return 5;
        }
    } // nec_ornek_5 sonu
    /// NOT EĞER ctor taban sınıfın protected bölümde olursa bu kullanım SENTAKS HATASI

    /* Yorum Baslik: final KEYWORD'u

    Bazı durumlarda
    Kalıtım çok yüksek bir bağımlılık derecesi kalıtım yerine composition hemen her zaman daha iyi bir seçenek
    Her sınıfı kalıtım yoluyla taban sınıf olarak kullanarak yeni sınıf elde edileceğini düşünülmemeli

    -sınıfın protected bölümü varsa kalıtımda kullanılması söz konusu olduğu açık.
    -sınıfın sanal fonksiyonlarının olması da işaret

    a) bazen bir sınıftan kullanılmasını istemiyoruz
    b) bu sınıf kalıtımda kullanılması için yapılmadı diye düşünülebilir

    -eskiden bu yorum satırına final yazılarak yapıyordu ve derleyiciler bir sentaks hatası vermiyor

    Kendisinden kalıtım yoluyla yeni bir sınıf oluşturulması istenilmeyen classlara 'final class' deniyor.
    final class ihtiyacı belirli bir seviyeden sonra türemiş bir sınıftan yeni bir türemiş sınıf elde edinilmemesi için kullanılıyor.

    OOP'de
    final class başka
    final override başka : bir fonksiyonu niteliyor taban sınıfın fonksiyonun override eden türemiş sınııfın
    fonksiyonun override edilmesini engellemek için

    */
    /* Yorum Baslik:nec_ornek_6
     */
    namespace nec_ornek_6
    {
        class Base final
        {
        public:
        private:
        };

        // class Der : public Base{ //SENTAKS HATASI
        class Der
        {
        public:
        private:
        };

        int main_6() // main'de cagir!!!
        {
            std::cout << "ornek 6 main\n";
            return 6;
        }
    } // nec_ornek_6 sonu

    /* Yorum Baslik:nec_ornek_7
    Bir strateji olarak da kullanılabilirken
    bazı durumlarda derleyicinin optimizasyonu olarak kullanılabilir.
     */
    namespace nec_ornek_7
    {

        class Base
        {
        public:
        private:
        };

        class Der final : public Base
        {
        public:
        private:
        };

        // class SDer: public Der //SENTAKS HATASI
        class SDer
        {
        };

        int main_7() // main'de cagir!!!
        {
            std::cout << "ornek 7 main\n";

            return 7;
        }

    } // nec_ornek_7 sonu

    /* Yorum Baslik:nec_ornek_8
     */
    class Car
    {
    public:
        virtual void start() { std::cout << "Car has just started\n"; }
        virtual void run() { std::cout << "Car is running now\n"; }
        virtual void stop() { std::cout << "Car has stopped \n"; }
    };
    class Bmw : public Car
    {
    public:
        void start() { std::cout << "Bmw has just started\n"; }
        void run() { std::cout << "Bmw is running now\n"; }
        void stop() { std::cout << "Bmw has stopped \n"; }
    };
    class Fiat : public Car
    {
    public:
        void start() { std::cout << "fiat has just started\n"; }
        void run() { std::cout << "fiat is running now\n"; }
        void stop() { std::cout << "fiat has stopped \n"; }
    };
    class Volvo : public Car
    {
    public:
        void start() final override { std::cout << "Volvo has just started\n"; } // final ve override'ın yeri önemli değil
        void run() { std::cout << "Volvo is running now\n"; }
        void stop() { std::cout << "Volvo has stopped \n"; }
    };
    class VolvoS60 : public Volvo
    {
    public:
        // void start(){std::cout<<"Volvo has just started\n";}//SENTAKS HATASI Volvo'nun start implementasyonunu kullanmak zorunda
        // cannot override final function
        void run() { std::cout << "Volvo is running now\n"; }
        void stop() { std::cout << "Volvo has stopped \n"; }
    };
    class Toyota : public Car
    {
    public:
        void start() { std::cout << "Toyota has just started\n"; }
        void run() { std::cout << "Toyota is running now\n"; }
        void stop() { std::cout << "Toyota has stopped \n"; }
    };
    class Dacia : public Car
    {
    public:
        void start() { std::cout << "Dacia has just started\n"; }
        void run() { std::cout << "Dacia is running now\n"; }
        void stop() { std::cout << "Dacia has stopped \n"; }
    };
    void car_game(Car &cr) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
    {
        cr.start();
        cr.run();
        cr.stop();
        std::cout << "----------------------------------------\n";
    }
    Car *create_random_car()
    {
        static std::mt19937 eng{std::random_device{}()};
        static std::uniform_int_distribution dist{1, 5};
        switch (dist(eng))
        {
        case 1:
            std::cout << "Bmw uretildi";
            return new Bmw;
        case 2:
            std::cout << "Fiat uretildi";
            return new Fiat;
        case 3:
            std::cout << "Volvo uretildi";
            return new Volvo;
        case 4:
            std::cout << "Toyota uretildi";
            return new Toyota;
        case 5:
            std::cout << "Dacia uretildi";
            return new Dacia;
        default:
            break;
        }
    }
    namespace nec_ornek_8
    {
        class Base
        {
        public:
            virtual void f();
            virtual void g();
            virtual void h();

        private:
        };
        class Der : public Base
        {
        public:
            void f() override;
            void g() override;
            void h() final override;

        private:
        };
        class SDer : public Der
        {
        public:
            void f() override;
            void g() override;
            // void h()override; //SENTAKS HATASI SDer Der'in h() implementasyonunu kullanmak zorunda.
            // compiler burada devirtualization denilen optimizasyon tekniğini kullanabiliyor.
        };
        int main_8() // main'de cagir!!!
        {
            std::cout << "ornek 8 main\n";
            return 8;
        }
    } // nec_ornek_8 sonu

    /* Yorum Baslik:nec_ornek_9

    Soyut sınıflar pointer ve referans türünden değişkenler ile kullanılabiliyor
    böyle sınıflar için Java ve C# gibi dillerde interface gibi bir keyword kullanılıyor.

    taban sınıf polymorphic yapılmak isteniyor fakat bunun için kullanılabilecek bir interface olmadığı durumda
    destructor virtual yapılarak bu elde edilebilir.

    !!!!!Global fonksiyonlar virtual olamaz!!!!!!
    Fakat bazı durumlarda biz sanki global fonksiyonu kullanmak istiyoruz.

     */
    namespace nec_ornek_9
    {

        class Car
        {
        public:
            virtual Car *clone() = 0;
            virtual void start() = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            virtual void print(std::ostream &) const = 0;
            virtual ~Car() = default;
        };
        class Bmw : public Car
        {
        public:
            Car *clone() { return new Bmw(*this); }
            void start() { std::cout << "Bmw has just started\n"; }
            void run() { std::cout << "Bmw is running now\n"; }
            void stop() { std::cout << "Bmw has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Bmw"; }
        };
        class Fiat : public Car
        {
        public:
            Car *clone() { return new Fiat(*this); }
            void start() { std::cout << "fiat has just started\n"; }
            void run() { std::cout << "fiat is running now\n"; }
            void stop() { std::cout << "fiat has stopped \n"; }
            void print(std::ostream &) const override { return os << "I am a Fiat"; }
        };
        class Volvo : public Car
        {
        public:
            Car *clone() { return new Volvo(*this); }
            void start() { std::cout << "Volvo has just started\n"; }
            void run() { std::cout << "Volvo is running now\n"; }
            void stop() { std::cout << "Volvo has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Volvo"; }
        };
        class VolvoS60 : public Car
        {
        public:
            Car *clone() { return new VolvoS60(*this); }
            void start() { std::cout << "VolvoS60 has just started\n"; }
            void run() { std::cout << "VolvoS60 is running now\n"; }
            void stop() { std::cout << "VolvoS60 has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a VolvoS60"; }
        };
        class Toyota : public Car
        {
        public:
            Car *clone() { return new Toyota(*this); }
            void start() { std::cout << "Toyota has just started\n"; }
            void run() { std::cout << "Toyota is running now\n"; }
            void stop() { std::cout << "Toyota has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Toyota"; }
        };
        class Dacia : public Car
        {
        public:
            Car *clone() { return new Dacia(*this); }
            void start() { std::cout << "Dacia has just started\n"; }
            void run() { std::cout << "Dacia is running now\n"; }
            void stop() { std::cout << "Dacia has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Dacia"; }
        };
        void car_game(Car &cr) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            cr.start();
            cr.run();
            cr.stop();
            std::cout << "----------------------------------------\n";
        }
        Car *create_random_car()
        {
            static std::mt19937 eng{std::random_device{}()};
            static std::uniform_int_distribution dist{1, 5};
            switch (dist(eng))
            {
            case 1:
                std::cout << "Bmw uretildi";
                return new Bmw;
            case 2:
                std::cout << "Fiat uretildi";
                return new Fiat;
            case 3:
                std::cout << "Volvo uretildi";
                return new Volvo;
            case 4:
                std::cout << "Toyota uretildi";
                return new Toyota;
            case 5:
                std::cout << "Dacia uretildi";
                return new Dacia;
            default:
                break;
            }
        }
#include <thread>
#include <chrono>
        void collide(Car *p1, Car *p2)
        {
            //*p1 ve *p2 herhangi iki araba olabilir.
            // bu gerçekleştirilebilirse double dispatch yapılıyor.
        }
        std::ostream &operator<<(std::ostream &os, const Car &other) // a
        {
            other.print(os);
            return os;
        }

        int main_9() // main'de cagir!!!
        {
            std::cout << "ornek 9 main\n";
            for (int i = 0; i < 100; i++)
            {
                Car *cp = create_random_car();
                // std::cout << *cp; //Normalde bu ifadenin türü car ve bu deyim yürütüldüğünde
                // aracın modeli yazdırılcak
                // bu fonksiyon global olmalı bunu nasıl yapabiliriz.
                // a fonksiyonunu ekledik ve kod legal oldu.
                cp->start();
                cp->run();
                cp->stop();
                std::cout << "----------------------------------------\n";

                delete cp;                          // car sınıfının destructor virtual olmasaydı ub olurdu
                std::this_thread::sleep_for(100ms); // literal operator functions son ek ms() fonksiyon 100ms bekleme sağlanıyor.
            }
            return 9;
        }
    } // nec_ornek_9 sonu

    /* Yorum Baslik:Covariance variant return type

        Bir taban sınıfın fonksiyonu override etmek için imza aynı ve geri dönüş değeri türü de aynı olmalıydı
        overriding virtual function return type differs and is not covariant from 'Base::foo'

        Kuralın nedeni:
        Der myder;

        myder.foo(); olarak yapılsaydı Bu fonksiyonun geri dönüş değeri covariance olmasaydı
        D * derptr = myder.foo(); eğer bu fonksyionun geri dönüş değeri B* dönseydi sentaks hatası olmayacaktı ve
        tür dönüştürme operatoru kullanılması zorunluydu.
        D * derptr = static_cast<D*> myder.foo();
     */
    /* Yorum Baslik:nec_ornek_10
     */
    namespace nec_ornek_10
    {
        class B
        {
        };
        class D : public B
        {
        };
        class Base
        {
        public:
            virtual int foo(int);
            virtual B *foo();
            virtual B &bar();

        private:
        };
        class Der : public Base
        {
        public:
            // int foo(int);//bu kesinlikle override
            virtual int foo(int);  // bu da kesinlikle override
            int foo(unsigned int); // bu da kesinlikle override değil ama sanal versiyon
            // int foo(unsigned int );override//SENTAKS HATASI ne override ne de overload
            // double foo(int);//SENTAKS HATASI overriding virtual function return type differs and is not covariant from 'Base::foo'
            // bunun bir istisnası var
            /*
            Eğer taban sınıfın sanal fonksiyonunun geri dönüş değeri türü
            T bir sınıf türü olmak üzere T * ya da T & ise
            T* yerine D* döndürebiliyor.
            virtual T&foo();
            D& foo(); Eğer ki Dsınıfı T sınıfından kalıtım yoluyla elde edilmiş olabilir.
            */

            // normalde
            // virtual B* foo();
            D *foo() override;
            D &bar() override;
            // Burada referans ve pointer semantiği olur. Sadece pointer ve referans semantikleri için geçerli
        private:
        };
        int main_10() // main'de cagir!!!
        {
            std::cout << "ornek 10 main\n";
            return 10;
        }

    } // nec_ornek_10 sonu
    /* Yorum Baslik:nec_ornek_11

        Covariance örneği
     */
    namespace nec_ornek_11
    {
        class Car
        {
        public:
            virtual Car *clone() = 0;
            virtual void start() = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            virtual void print(std::ostream &) const = 0;
            virtual ~Car() = default;
        };
        class Bmw : public Car
        {
        public:
            Bmw *clone() { return new Bmw(*this); }
            void start() { std::cout << "Bmw has just started\n"; }
            void run() { std::cout << "Bmw is running now\n"; }
            void stop() { std::cout << "Bmw has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Bmw"; }
        };
        class Fiat : public Car
        {
        public:
            Fiat *clone() { return new Fiat(*this); }
            void start() { std::cout << "fiat has just started\n"; }
            void run() { std::cout << "fiat is running now\n"; }
            void stop() { std::cout << "fiat has stopped \n"; }
            void print(std::ostream &) const override { return os << "I am a Fiat"; }
        };
        class Volvo : public Car
        {
        public:
            Volvo *clone() { return new Volvo(*this); }
            void start() { std::cout << "Volvo has just started\n"; }
            void run() { std::cout << "Volvo is running now\n"; }
            void stop() { std::cout << "Volvo has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Volvo"; }
        };
        class VolvoS60 : public Car
        {
        public:
            VolvoS60 *clone() { return new VolvoS60(*this); }
            void start() { std::cout << "VolvoS60 has just started\n"; }
            void run() { std::cout << "VolvoS60 is running now\n"; }
            void stop() { std::cout << "VolvoS60 has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a VolvoS60"; }
        };
        class Toyota : public Car
        {
        public:
            Toyota *clone() { return new Toyota(*this); }
            void start() { std::cout << "Toyota has just started\n"; }
            void run() { std::cout << "Toyota is running now\n"; }
            void stop() { std::cout << "Toyota has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Toyota"; }
        };
        class Dacia : public Car
        {
        public:
            Dacia *clone() { return new Dacia(*this); }
            void start() { std::cout << "Dacia has just started\n"; }
            void run() { std::cout << "Dacia is running now\n"; }
            void stop() { std::cout << "Dacia has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Dacia"; }
        };
        void car_game(Car &cr) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            cr.start();
            cr.run();
            cr.stop();
            std::cout << "----------------------------------------\n";
        }
        Car *create_random_car()
        {
            static std::mt19937 eng{std::random_device{}()};
            static std::uniform_int_distribution dist{1, 5};
            switch (dist(eng))
            {
            case 1:
                std::cout << "Bmw uretildi";
                return new Bmw;
            case 2:
                std::cout << "Fiat uretildi";
                return new Fiat;
            case 3:
                std::cout << "Volvo uretildi";
                return new Volvo;
            case 4:
                std::cout << "Toyota uretildi";
                return new Toyota;
            case 5:
                std::cout << "Dacia uretildi";
                return new Dacia;
            default:
                break;
            }
        }
        int main_11() // main'de cagir!!!
        {
            std::cout << "ornek 11 main\n";
            Bmw *p1 = new Bmw;
            // Bmw *p2  = p1->clone(); //SENTAKS HATASI Car *'dan Bmw *'dan dönüşüm yok
            // clone fonksiyonun geri dönüş değerini Bmw * yaptık. ve sentaks hatası olmaktan
            // covariance kullandık
            Bmw *p2 = p1->clone();
            return 11;
        }

    } // nec_ornek_11 sonu

    /* Yorum Baslik:Polymorphic listeler.
     */

    /* Yorum Baslik:nec_ornek_12
     */
    namespace polymorphic_liste
    {
        class Car
        {
        public:
            virtual Car *clone() = 0;
            virtual void start() = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            virtual void print(std::ostream &) const = 0;
            virtual ~Car() = default;
        };
        class Bmw : public Car
        {
        public:
            Bmw *clone() { return new Bmw(*this); }
            void start() { std::cout << "Bmw has just started\n"; }
            void run() { std::cout << "Bmw is running now\n"; }
            void stop() { std::cout << "Bmw has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Bmw"; }
        };
        class Fiat : public Car
        {
        public:
            Fiat *clone() { return new Fiat(*this); }
            void start() { std::cout << "fiat has just started\n"; }
            void run() { std::cout << "fiat is running now\n"; }
            void stop() { std::cout << "fiat has stopped \n"; }
            void print(std::ostream &) const override { return os << "I am a Fiat"; }
        };
        class Volvo : public Car
        {
        public:
            Volvo *clone() { return new Volvo(*this); }
            void start() { std::cout << "Volvo has just started\n"; }
            void run() { std::cout << "Volvo is running now\n"; }
            void stop() { std::cout << "Volvo has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Volvo"; }
        };
        class VolvoS60 : public Car
        {
        public:
            VolvoS60 *clone() { return new VolvoS60(*this); }
            void start() { std::cout << "VolvoS60 has just started\n"; }
            void run() { std::cout << "VolvoS60 is running now\n"; }
            void stop() { std::cout << "VolvoS60 has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a VolvoS60"; }
        };
        class Toyota : public Car
        {
        public:
            Toyota *clone() { return new Toyota(*this); }
            void start() { std::cout << "Toyota has just started\n"; }
            void run() { std::cout << "Toyota is running now\n"; }
            void stop() { std::cout << "Toyota has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Toyota"; }
        };
        class Dacia : public Car
        {
        public:
            Dacia *clone() { return new Dacia(*this); }
            void start() { std::cout << "Dacia has just started\n"; }
            void run() { std::cout << "Dacia is running now\n"; }
            void stop() { std::cout << "Dacia has stopped \n"; }
            void print(std::ostream &) const override { os << "I am a Dacia"; }
        };
        void car_game(Car *p)
        {
            // Burada arabaları container'a alıp hepsi çalışsın hepsi  dursun gibi istiyoruz.

            // elemanları referans olan bir dizi oluşturulamaz.
            // en az  3 yolu var
            /*
                pointer semantiği kullanılarak - önerilmiyor dinamik nesneleri smart pointer ile yönetmek
                reference wrapper sınıfı kullanılabilir.
            */

            std::cout << "----------------------------------------\n";
        }
        Car *create_random_car()
        {
            static std::mt19937 eng{std::random_device{}()};
            static std::uniform_int_distribution dist{1, 5};
            switch (dist(eng))
            {
            case 1:
                std::cout << "Bmw uretildi";
                return new Bmw;
            case 2:
                std::cout << "Fiat uretildi";
                return new Fiat;
            case 3:
                std::cout << "Volvo uretildi";
                return new Volvo;
            case 4:
                std::cout << "Toyota uretildi";
                return new Toyota;
            case 5:
                std::cout << "Dacia uretildi";
                return new Dacia;
            default:
                break;
            }
            constexpr std::size_t size{100};
            int main_12() // main'de cagir!!!
            {
                std::cout << "ornek 12 main\n";
                Car *a[size];
                for (auto &p : a)
                {
                    p = create_random_car();
                }
                ////
                for (auto p : a)
                {
                    std::cout << *p;
                    p->start();
                    p->run();
                    p->stop();
                    delete p;
                }
                return 12;
            }
        } // nec_ornek_12 sonu

    

    }

    /* Yorum Baslik:rtti
    Programın çalışma zamanında tür belirlenmesi 
    polymorhpisim ile önce yazılmış kodlar daha sonra yazılmış kodları kullanabiliyor ve
    Üst katman kodlar alt katman kodlara bağımlı değil 
    Cpp'da da gereken durumlarda kullanılabilmesi için bir nesnein türünün tespit edilme olanağı veriyor fakat
    belli yerler dışında kullanılmaması gerekiyor. 
    SOLID: promise no less require no more ( Daha azını vaat etme daha çoğunu isteme )
    class Base{};
    void func(Base &base)
    {
        Buraya gelen her nesnenin base olduğu düşünülerek kod yazılıyor.
        Ve burada base'den daha azı sağlanırsa problem olur ( promise no less)

        //
        türemiş sınıfın override bir fonksiyon için belirli kısıtlamalar içeriyorsa
        bu kısıtlama (require no more oluyor.)
    }

    Bu araç setinde 
    dynamic_cast operator: programın çalışma zamanınıda downcasting yapılıp yapılamayacağına veriyor
    static_cast
    const_cast
    reinterpret_cast

    //
    dynamic_cast<target_type>(expr) => 

    : upcasting: yukarı doğru türemiş sınıftan taban sınıfa yapılan dönüşüm
      donwcasting: taban sınıf türünden türemiş sınıf türüne dönüşüm 
    typeid  operator
        typeinfo sınıfı var
     */
    namespace rtti
    /**/
    {
        class Car{
            public:
                virtual void start(){std::cout<<"Car has just started\n";}
                virtual void run(){std::cout<<"Car is running now\n";}
                virtual void stop(){std::cout<<"Car has stopped \n";}
        };
        class Bmw:public  Car{
            public:
                void start(){std::cout<<"Bmw has just started\n";}
                void run(){std::cout<<"Bmw is running now\n";}
                void stop(){std::cout<<"Bmw has stopped \n";}
        };
        class Fiat:public Car{
            public:
                void start(){std::cout<<"fiat has just started\n";}
                void run(){std::cout<< "fiat is running now\n";}
                void stop(){std::cout<<"fiat has stopped \n";}
        };
        class Volvo:public Car{
            public:
                void start(){std::cout<<"Volvo has just started\n";}
                void run(){std::cout<<"Volvo is running now\n";}
                void stop(){std::cout<<"Volvo has stopped \n";}
                void open_sunroof(){    std::cout<<"Volvo'nun cami acilsin\n";}
        };
        class Toyota :public Car{
            public:
                void start(){std::cout<<"Toyota has just started\n";}
                void run(){std::cout<<"Toyota is running now\n";}
                void stop(){std::cout<<"Toyota has stopped \n";}
        };
        class Dacia:public Car{
        public:
                void start(){std::cout<<"Dacia has just started\n";}
                void run(){std::cout<<"Dacia is running now\n";}
                void stop(){std::cout<<"Dacia has stopped \n";}
        };
        void car_game(Car * p) //artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            std::cout<<*p;
            p->start();
            p->run();
            //eger araba volvo ise cam tanvanı acilsin
            //eğer p'nin volvo nesnesi adresi olduğuna eminsek burada p'yi kullanabiliriz
            //acaba burada güvenli bir şekilde car * adresini volvo adresi nesnesi olarak kullanabilir miyiz? ever dynamic_cast

            auto vp = dynamic_cast<Volvo *>(p);//Eğer ürettiği değer Eğer *p volvo ise başarılı olucak ve Volvo *'ın adresini elde edeceğiz
            //Volvo *vp = dynamic_cast<Volvo *>(p);
            //eğer başarılı değilse ürettiği değer nullptr olur.
            //vp->open_sunroof();
            if(vp){vp->open_sunroof(); (void)getchar();}
            //Burada idomic bir yapı kullanılıyor ve vp if değiminin sonrasında da kullanılabiliyor
            //suni block kullanılabilir. 
            //eğer bu amaçla kullanılıyorsa
            if(auto vpp = dynamic_cast<Volvo *>(p))
            {
                vpp->open_sunroof();
                (void) getchar();
            }

            //dynamic_cast yerine static_cast kullanılabilir 
            //bu dönüşüm yapılabilir ve bu programın çalışma zamanına ilişkin değil 
            //ve run time hatası olur static_cast kullanma!!!!
            p->stop();
            std::cout<<"----------------------------------------\n";
        }
        Car *create_random_car()
        {
            static std::mt19937 eng{std::random_device{}()};
            static std::uniform_int_distribution dist{1,5};
            switch (dist(eng))
        {
            case 1:std::cout<<"Bmw uretildi";return new Bmw;
            case 2: std::cout<<"Fiat uretildi"; return new Fiat;
            case 3:std::cout<<"Volvo uretildi"; return new Volvo;
            case 4:std::cout<<"Toyota uretildi"; return new Toyota;
            case 5: std::cout<<"Dacia uretildi";return new Dacia;
            default:
            break;
        }
        }
        int main() // main'de cagir!!!
        {
            std::cout << "rtti main\n";
            for(int i = 0 ; i< 100; i++)
            {
                Car *p = create_random_car();
                car_game(p);
                delete p;
            }
            return 0;
        }
    } // rtti sonu
    /* Yorum Baslik:rtti_ornek 
     */
    namespace rtti_ornek{
    class Base{
    public:
        
    private:
        
    };
    class Der: public Base{
    public:
        void derfooo();
    private:
        
    };
    void func(Base* baseptr){
      //  if(Der *dp = dynamic_cast<Der *>(baseptr))//Sentaks hatası
      //Dynamic cast POLYMORPHIC Tür için kullanılmalır.
      //Eğer base class'ı polymorphic yapılırsa sentaks hatası kalkar.
        {
            dp->derfooo();
        }
    }
        int main()//main'de cagir!!!
        {
            std::cout<<"rtti_ornek main\n";
            return 0;
        }
    
    }// rtti_ornek sonu
}
// modern cpp ile eklemeler:
// taşıma semantiği
// perfect forwarding
// yeni bir memory modelin oluşturulması thread'ler 3.parti kütüphanelerle kullanılıyordu
// cpp abstract machine has a memory model
// artık threadleri kullanan bir kod yazılmak istendiğinde işletim sisteminden bağımsız kütüphaneler var.
// cpp araçlar ile pthread programlama yapılabiliyor.

// Global fonksiyonunu başlık dosyasında tanımlanırsa ODR ihlal edilmiş oluyor. ve link aşamasında hata oluştu.
// fonksiyonu inline yapıyoruz.

/**
for(auto &&x: con ){} range based for için ayrı bir yapı
böyle referanslara type deduction varsa ona forwarding / universal referans
x'e forwarding/universal referans deniyor.
*/
/*
    template <typename T>
    void func(T&&){}
*/

namespace ornek_ek
{

    class Myclass
    {
    public:
    private:
    };
    void func(Myclass &&r) // bu fonksiyona gelen nesnenin hayatının biteceğinden emin oluyor
    // ve bu nesnenin taşınabileceğini yapmak
    //
    {

        Myclass x(std::move(r)); // şimdi nesne taşınmış oldu ve burada x için move ctor çağırılacak ve kaynağını alıcak
        /* Ya da
            Myclass y();
            y = std::move(r);//taşıma yapıyor
        */

        Myclass y(r); // r lvalue olduğu için copy-ctor çağırılacak
    }
    int main()
    {
        Myclass m;
        func(std::move(m)); // Sağ taraf referansına bağlanmış oldu
    }
}

/*
Gelecek konu başlıkları
multiple ingeritance
    virtual inheritance
RTTI
private inheritance
protected inheritance
NVI idiom
--------------------------------
Exception handling
*/
```
