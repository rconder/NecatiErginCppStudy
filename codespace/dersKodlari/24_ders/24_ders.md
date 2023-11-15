# 24.ders

```cpp
#include <iostream>
#include <algorithm>
#include <random>
namespace ders_24
{
    /* Yorum Baslik:Geçen dersten run time polymorhpism'den devam edeceği
    Hangi fonksiyonun çağırıldığı dynamic binding ile çalışma zamanında belli oluyor.
    Virtual dispatch için sanal fonksiyona yapılan çağırının pointer ve referans yoluyla yapılması lazım

    OOP eski kodların yeni kodları kullanabilmesini sağlıyor

    Virtual dispatch mechanismasının derleyiciler tarafından nasıl implemente edildiği önemli
    hem maliyeti de önemli virtual dispatch'ten kaçınmak gereken durumlar olabilir.




    */

    /*

     Yorum Baslik:nec_ornek_1
        override keywordu: (Contextual keyword)
        a) çok tipik yapılan hatalar vardı:
        class Base{
            public :
            void func(int);
            ...
        };

        class Der: public Base
        {
            public:
             void func(int);//burada logic bir hata oluşacak çünkkü override yapmayacak
             //der'in func'ı da virtual değil

        };
    --------------------------------
        class Base{
        public :
            virtual void func(unsigned int);
            ...
        };

        class Der: public Base
        {
            public:
            virtual void func(int);// sentaks hatası da yok der'de ayrı bir sanal fonksiyon yaratıyor.
            //
            ...
        };
    -----------------------
        class Base{
        public :
            //virtual void func(int);
            //func'ın parametre yapısı değişirse
            virtual void func(int,int); daha önce override edilen sınıflarında fonksiyonların değişmesi gerekiyor. O sınıflarında değiştirilmeside gerekiyor.
            ...
        };

        class Der: public Base
        {
            public:

            ...
        };
    ------------------------------------
    override: bu fonksiyon taban sınıftaki fonksiyonun override' derleyici taban sınıfında bu fonksiyonu kontrol etmek zorunda
     */
    namespace nec_ornek_1
    {
        class Base
        {
        public:
            void func(int);
            virtual void foo(int);

        private:
        };
        class Der : public Base
        {
        public:
            // void func(int) override;// SENTAKS HATASI taban sınıfın böyle bir sanal fonksiyonu yok
            // void foo(unsigned int)override ; //SENTAKS HATASI taban sınıfın böyle bir sanal fonksiyonu yok
        private:
        };

        int main_1() // main'de cagir!!!
        {
            std::cout << "ornek 1 main\n";
            return 1;
        }
    } // nec_ornek_1 sonu

    /* Yorum Baslik:nec_ornek_2
        Derleyici koda bakarak çeviri sürecinde anlıyor.
        Aslolan static typing olsada
        static tür :derleyicinin koda bakarak anladığı tür
     */
    namespace nec_ornek_2
    {
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
            void open_sunroof();
            void start() { std::cout << "Volvo has just started\n"; }
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
        void car_game(Car *p) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        {
            p->start(); // p'nin türü CAR fakat derleme zamanında CAR, çalışma zamanında ise değişken
            p->run();
            p->stop();
            // p->open_sunroof();//BU SENTAKS HATASI OLUR. Derleyici *p'nin ait olduğu sınıfta arıyor
            // polymorphic bir sınıf olmalı dynamic tür
            // Eğer ortada bir sebep yoksa dinamik türün ne olduğunu anlamamız gerekmeyecek.
            // Tasarımda bunu yapmamak gerekiyor. Nesnenin dinamik türünün ne olduğunu bilme gereği olmadan bu geliştirmeyi yapmak lazım ve anlama yolu var
            // Bazı durumlarda gerekebilir.
            //!! RTTI: Run time type identification!!!
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
        int main_2() // main'de cagir!!!
        {
            std::cout << "ornek 2 main\n";
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
        private:
            virtual void vfunc();
        };

        class Der : public Base
        {
        public:
            void vfunc() override; // Taban sınıfın private ve protected sanal fonksiyonu override edilmesinde bir engel yok.
        private:
        };
        int main_3() // main'de cagir!!!
        {
            std::cout << "ornek 3 main\n";
            return 3;
        }
    } // nec_ornek_3 sonu

    /* Yorum Baslik:nec_ornek_4
     */
    namespace nec_ornek_4
    {
        class Base
        {
        public:
            virtual void vfunc();

        private:
        };
        class Der : public Base
        {
        public:
        private:
            void vfunc() override; // taban sınıfın fonksiyonu bu şekilde override edilebilir.
        };
        int main_4() // main'de cagir!!!
        {
            std::cout << "ornek 4 main\n";
            return 4;
        }

    } // nec_ornek_4 sonu

    /* Yorum Baslik:nec_ornek_5
     */
    namespace nec_ornek_5
    {
        class Base
        {
        public:
            virtual void vfunc() { std::cout << "Base::vfunc()\n"; }

        private:
        };

        class Der : public Base
        {
        public:
        private:
            virtual void vfunc() override
            {
                std::cout << "Der::vfunc()\n";
            }
        };
        void g(Base &baseref)
        {
            baseref.vfunc(); // isim arama ile bulunacak ve access control yapılacak public üye fonksiyonu olduğu için sentaks hatası olmayacak
        }
        int main_5() // main'de cagir!!!
        {
            std::cout << "ornek 5 main\n";
            Der myder;
            g(myder); // Virtual dispatch ile private olan override'ın çağırılmasında herhangi bir sorun yok.
            // access tür kontrolü static type : (isim arama, erişim kontrolü) ilişkin
            return 5;
        }
        /* Yorum Baslik:nec_ornek_6
         */

    } // nec_ornek_5 sonu

    namespace nec_ornek_6
    {
        class Base
        {
        public:
            virtual void vfunc(int x = 10) { std::cout << "Base::vfunc(int x ) x = " << x << "\n"; }

        private:
        };

        class Der : public Base
        {
        public:
            virtual void vfunc(int x = 77) { std::cout << "Der::vfunc(int x ) x = " << x << "\n"; }

        private:
        };

        void g(Base &baseref)
        {
            baseref.vfunc(); // isim arama ile bulunacak ve access control yapılacak public üye fonksiyonu olduğu için sentaks hatası olmayacak
        }

        int main_6() // main'de cagir!!!
        {
            std::cout << "ornek 6 main\n";
            Der myder;
            g(myder);
            // Varsayılan argüman da static türe elişkin ve tamamen compile zamanına ilişkin
            myder.vfunc();
            ; // varsayılan argüman 77 olucaktu
            return 6;
        }
    } // nec_ornek_6 sonu

    /* Yorum Baslik:nec_ornek_7

     */
    namespace nec_ornek_7
    {

        class Base
        {
        public:
            void foo() { vfunc(); } // türemiş sınıf nesneleri vfunc override çağırılıyor
        private:
            virtual void vfunc() { std::cout << "Base::vfunc()\n"; }
        };

        class Der : public Base
        {
        public:
            void vfunc() override { std::cout << "Der::vfunc()\n"; };

        private:
        };

        int main_7() // main'de cagir!!!
        {
            std::cout << "ornek 7 main\n";
            Der myder;
            myder.foo(); // virtual dispatch mechanisması devreye giriyor
            return 7;
        }
    } // nec_ornek_7 sonu

    /* Yorum Baslik:nec_ornek_8
       taban class'ın ctor içinde yapılan fonksiyon çağrısı
     */
    namespace nec_ornek_8
    {
        class Base
        {
        public:
            Base()
            {
                vfunc(); // Virtual dispatch mekanizması devreye girmez
                // bu noktada türemiş sınıf nesnesi hayata gelmedi daha
                // önce taban sınıfı hayata gelecek daha sonra memberlar hayata gelecek
                // ve daha sonra türemiş sınıfın ctor'u tamamlanacak
                // daha sonra kullanılacak
            }
            ~Base()
            {
                vfunc(); // Burada da virtual dispatch mekanizması girmez
                // çünkü türemiş sınıf nesnesi destroy olmuş durumda
            }

        private:
            virtual void vfunc() { std::cout << "Base::vfunc()\n"; }
        };

        class Der : public Base
        {
        public:
            void vfunc() override { std::cout << "Der::vfunc()\n"; }

        private:
        };

        int main_8() // main'de cagir!!!
        {
            std::cout << "ornek 8 main\n";
            Der myder;
            return 8;
        }
    }
    // nec_ornek_8 sonu
    /* Yorum Baslik:virtual dispatch devreye alınmama senaryoları
    Eğer çağrı base nesnesi ile yapılmışsa
    1-) base_object.vfunc(); ile devreye girmiyor.
    2-) Taban sınıfın ismi ile nitelenerek yapılırsa devreye girmez.   Bazı tasarımlarda türemiş override çağırılmasından önce
    3-) Taban sınıf ctor'u içinde yapılan sanal fonksiyon çağırıları.
    4-) Taban sınıf destroy içinde yapılan sanal fonksiyon çağırıları.
    */

    /*
     Cpp abstract machine davranışın ve kuralları anlatır implemantasyonu anlatılmaz.
     Derleyiciler tipik olarak en pratik ve kolay olarak virtual dispatch için aşağıdaki kodu üretiyorlar.
    */
    /* Yorum Baslik:nec_ornek_9
     */
    namespace nec_ornek_9
    {
        class Base
        {
        public:
            void f1();
            void f2();
            void f3();
            virtual void vf1(){};
            virtual void vf2(){};

        private:
            int x, y;
        };
        class Der : public Base
        {
        public:
        private:
        };
        int main_9() // main'de cagir!!!
        {
            std::cout << "ornek 9 main\n";
            std::cout << "sizeof(Base): " << sizeof(Base) << " \n"; // üye fonksiyonların uzaktan yakından bir ilgisi yok şu anda 8
            std::cout << "sizeof(Der): " << sizeof(Der) << " \n";
            // virtual eklendikten sonra  sizeof->12 byte oldu
            // virtual vf2() eklendikten sonra halen 12
            // Eklenen 4byte o sınıf polymorphic bir sınıf oluyor.
            // ve kalıtım yoluyla elde edilen sınıflarda polymorphic
            // polymorphic sınıfların sizeof değeri 4 byte daha fazla çünkü derleyici bu classların içine pointer gömüyor.
            // bu pointer'a vptr olarak isimlendiriyor.
            return 9;
        }
    } // nec_ornek_9 sonu
    /* Yorum Baslik:
    Car
    -----------------------------
    vptr => sanal fonksiyon tablo göstericisi
    derleyici compile time da vptr'yi sanal fonksiyon tablosu denen veri yapısı ile init ediyor.

    Car
    Mercedes ms;
    Audi au;
    hepsinin içinde vptr var

    vptr bir veri yapısı
    vptr nesne oluşturulduğunda initiliaze ediliyor
    -----------------------------
    virtual function table for class Toyota
    index|function name
    -----|------------
    0
    1 &toyota::start
    2 &toyota::run
    3 &toyota::stop
    virtual function table for class Dacia
    index|function name
    -----|------------
    0
    1 &Dacia::start
    2 &Dacia::run
    3 &Dacia::stop
    -----------------------------------------
    carptr->run();
    derleyici
    isim aramayla run sınıfını aradı buldu ve virtual func olduğunu gördüğünde
    burada virtual dispatch uygulanabiliyor.
    carptr->vptr[1](); -> bu bir function pointer olduğunu biliyor ve bu fonksiyonun adresi ile çağırıyor.

    maliyeti
    ---------
    dereferencing (taban sınıf içinde bulunan sanal fonksiyon nesnesine erişmiş olması gerekiyor) + 2. dereferencing(sanal fonksiyon tablosundaki fonksiyon adresine erişmek için)

    her polimorfik nesne için vptr'nin init edilmesi
    her sanal fonksiyon çağrısı için 2 x dereferencing
    Sanal fonksiyon tablosu sınıf sayısı kadar
    Run time'da tipik olarak heap içerisinde her poliformik sınıf için
    sanal fonksiyon veri yapısı oluşturuluyor.

    Bellek maliyeti her polimorfik için her nesne başına ekstra bir pointer oluyor.

    Daha çok dinamik ömürlü nesneler kullanılarak oluşturuluyor. Onlarda maliyeti aşırı derecede etkiliyor ve bu tür uygulamalarda nesnenin türü programın çalışma zamanında belli olucak
    o yüzden bu koşul new operatorunu kullanmayı zorunlu kılıyor.
    */

    /* Yorum Baslik:nec_ornek_10
        constructor virtual olabilir mi?
        HAYIR dilin kuralları bunu yasaklıyor. Ama virtual ctor ihtiyacı başka
        Destructor virtual olabilir mi?
        EVET OLMAK ZORUNDA!!!!!!
     */
    namespace nec_ornek_10
    {
/*

    destructor konusu 

*/
    class Base{
    public:
    virtual void vfunc(){    std::cout<<"Base::vfunc\n";}
      //~Base(){    std::cout<<"Base::desructor\n";}  
      virtual ~Base(){std::cout<<"Base::desructor\n";}
      protected:
       //~Base(){std::cout<<"Base::desructor\n";} böylece taban sınıfın destructor'ını çağırmak sentaks hatası veriyor.
    private:    
    };
    class Der: public Base{
    public:
    virtual void vfunc(){    std::cout<<"Der::vfunc\n";}
    ~Der(){    std::cout<<"Der::destructor\n";}        
    private:
    };

    int main_()
    {
        Base *ptr = new Der;
        ptr->vfunc();
        //destructor'a virtual eklemezsek!!!
        //delete ptr;//Base sınıfının destructor'ı çağırılacak ve bu TANIMSIZ DAVRANIŞ
        //Bir taban sınıf ptr ile Türemiş sınıf için kullanılıyorsa bu sorunlu bir durum
        // 2 yöntem var 1-)taban sınıf destructor'ı virtual olmalı %98
        // %2 hiçbir zaman uygulamada taban sınıf ptr ile türemiş ptr nesnei delete edilmek istenmiyorsa virtual olmasına gerek yok
        //fakat böyle durumlarda protected yapılıyor

        //virtual eklendikten sonra
        delete ptr;

        Der *derptr = new Der;
        delete derptr;//burada sorun yok client kodlar erişim kontrolüne takılıd
        //fakat türemiş sınıf taban sınıfın protected bölümüne erişebilir.
        
    }
/*
    Polimorfik sınıfların destructor'ları 
    ya public virtual.
    ya da protected non-virtual olmalı.

***    Herb Sutter ****



    destructor konusu sonu

*/
        class Car
        {
        public:
            virtual void start() = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            virtual Car *clone() = 0;
            // Artık türetilen sınıfların concrete olmaması için tüm virtual fonksiyonları implemente etmesi gerekiyor.
            // herhangi birini implemente etmezse o da abstract class olarak kalıyor.
            // Dinamik oluşturulursa taban sınıf ile delete edilmesi gerekiyor.
            // Resource leak ve nesne için bellek alanı ayrılarak yer edildi 
            // delete operator'unun çağırılması gerekecek.
        };

        class Bmw : public Car
        {
        public:
            void start() override { std::cout << "Bmw has just started\n"; }
            void run() override { std::cout << "Bmw is running now\n"; }
            void stop() override { std::cout << "Bmw has stopped \n"; }
            Car *clone() override { return new Bmw(*this); } // copy ctor ile aynısı hayata geliyor. o yüzden clone daha uygun
        };
        class Fiat : public Car
        {
        public:
            Car *clone() override { return new Fiat(*this); }
            void start() override { std::cout << "fiat has just started\n"; }
            void run() override { std::cout << "fiat is running now\n"; }
            void stop() override { std::cout << "fiat has stopped \n"; }
        };
        class Volvo : public Car
        {
        public:
            Car *clone() override { return new Volvo(*this); }

            void start() override { std::cout << "Volvo has just started\n"; }
            void run() override { std::cout << "Volvo is running now\n"; }
            void stop() override { std::cout << "Volvo has stopped \n"; }
        };
        class Toyota : public Car
        {
        public:
            Car *clone() override { return new Toyota(*this); }

            void start() override { std::cout << "Toyota has just started\n"; }
            void run() override { std::cout << "Toyota is running now\n"; }
            void stop() override { std::cout << "Toyota has stopped \n"; }
        };
        class Dacia : public Car
        {
        public:
            Car *clone() override { return new Dacia(*this); }
            void start() { std::cout << "Dacia has just started\n"; }
            void run() { std::cout << "Dacia is running now\n"; }
            void stop() { std::cout << "Dacia has stopped \n"; }
        };
        class VolvoS60 : public Volvo
        {
        public:
            Car *clone() override { return new VolvoS60(*this); }
            void start() override { std::cout << "S60 has just started\n"; }
            void run() override { std::cout << "S60 is running now\n"; }
            void stop() override { std::cout << "S60 has stopped \n"; }
        };
        void car_game(Car *p) // artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
        // void car_game(Car cr) //SENTAKS HATASI
        {
            // gelen arabanın hangi sınıftan olduğunu bilmiyoruz diyelim ki oyun senaryosu gereği
            // eğer buraya gelen araba hangi türdense o araçtan oluşturulması gerekiyor
            // bu da semantik olarak
            // p'nin dinamik türü her ne ise o türden değişken istiyoruz.
            // dynamictype(*p) x; gibi bir çözüm istiyoruz.
            // clone idiom'u deniyor
            Car *carptr = p->clone(); // clone fonksiyonun override çağırılcak
            // ve bu çağırılan sınıfı clonelarsa
            carptr->start();
            p->start();
            p->run();
            p->stop();
            std::cout << "----------------------------------------\n";
        }

        Car *create_random_car()
        {
            static std::mt19937 eng{std::random_device{}()};
            static std::uniform_int_distribution dist{1, 6};
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
            case 6:
                std::cout << "Dacia uretildi";
                return new VolvoS60;
            default:
                break;
            }
        }
        int main_10() // main'de cagir!!!
        {
            std::cout << "ornek 10 main\n";
            // Car mycar; //SENTAKS HATASI saf sanal olduğu için sentaks hatası.

            return 10;
        }
    } // nec_ornek_10 sonu

    /* Yorum Baslik:nec_ornek_11 
     */
    namespace nec_ornek_11{
    //using Word = int;
    //using namespace std;
    //using std::cout;

        class Base{
        public:
          void func(int x) {    std::cout<< "Base::func x: " <<  x <<" \n";};  
          protected:
          void foo(int x){    std::cout<< "Base::foo x: " <<  x <<" \n";};  
        private:
            
        };
        class Der: public Base{
        public:
        //eğer burada using Base::func yapılırsa örnek 12'de
        
         void func(int x){ Base::func(x);}
         void func(double x){    std::cout<< "Der::func(double) x: " <<  x <<" \n";};  
         void foo(int x){Base::foo(x);} //a1
        private:
            
        };
        int main_11()//main'de cagir!!!
        {
            std::cout<<"ornek 11 main\n";
            Der myder;
            myder.func(19);//türemiş sınıfın double parametreli fonksiyonu
            myder.func(19.12);
            //myder.func(int) base'inki çağırılsın
            //myder.func(double) der'inki çağırılsın
            //myder.foo(19);//SENTAKS HATASI
            //a1 eklendikten sonra
            myder.foo(10);
            return 11;
        }
    }// nec_ornek_11 sonu
    /* Yorum Baslik:nec_ornek_12 
     */
    namespace nec_ornek_12{
    class Base{
    public:
      void func(int x){    std::cout<<"Base::func(int x) "<<x<<" \n" ;}  
    private:
        
    };
    class Der: public Base{
    public:
    void func(double x){    std::cout<< "Der::func(double x) x = : " <<  x  <<" \n";}
    using Base::func;
    private:
        
    };
        int main_12()//main'de cagir!!!
        {
            std::cout<<"ornek 12 main\n";
            myder.func(12);
            myder.func(12.52);
            return 12;
        }
    
    }// nec_ornek_12 sonu
}

```
