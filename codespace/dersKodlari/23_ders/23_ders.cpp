#include <iostream>
#include <string>

namespace ders_23
{
/* Yorum Baslik:Kalıtımda özel üye fonksiyonların durumu   
    
    ilk olarak taban sınıf hayata geliyor.
    sonra memberlar bildirimdekiler hayata geliyor 
    daha sonra türemiş sınıfn ctor'una girmiş durumda oluyor.

    Bir nesnenin için de  hem kalıtım yoluyla hem de composition ile
    bir nesnenin içinde olabilr

    ilişkiler de ise has a relation composition
                      is a relation kalıtım

    Derleyici taban nesnenesinin adresini biliyor ve bunu kullanıyor.
*/

/* Yorum Baslik:nec_ornek_1 

    Eğer ctor init list ile taban nesnesini init edecek kod yazılmazsa
    türemiş sınıf ctor ve taban sınıfın init edilmediği kod da default ctor yapıyor
    Hayata daha sonra gelen daha önce veda ediyor
*/
namespace nec_ornek_1{

    class Base{
    public:
    Base()
    {
            std::cout<<"Base Default Ctor\n";
    }

    ~Base()
    {
            std::cout<<"Base Default destructor\n";
    }
    private:
        
    };

    class Der: public Base{
    public:
    Der()
    {
            std::cout<<"Der  default ctor\n";
    }        
    ~Der()
    {
            std::cout<<"Der destructor ctor\n";
    }        
    
    private:
        
    };

    int main_1()//main'de cagir!!!
    {
        std::cout<<"ornek 1 main\n";
        Der myder;

        return 1;
    }

}// nec_ornek_1 sonu

/* Yorum Baslik:nec_ornek_2 

    Eğer taban sınıfın special fonksiyonu delete
 */
}

/* Yorum Baslik:nec_ornek_3 

Eğer der nesnesi hayata gelirken bir exeception meydana gelirse
ctor bitmeden hayata gelemez.
 */
namespace nec_ornek_3{

    class Member{
    public:
    Member()
    {
            std::cout<<"Base Default Ctor\n";
    }

    ~Member()
    {
            std::cout<<"Base Default destructor\n";
    }

    };
    class Base{
    public:
    Base()
    {
            std::cout<<"Base Default Ctor\n";
    }

    ~Base()
    {
            std::cout<<"Base Default destructor\n";
    }
    private:
    
    };
    class Der: public Base{
    public:
    Der() //Önce base sonra member nesnesi hayata geliyor.
    {
            std::cout<<"Der  default ctor\n";
    }        
    ~Der()
    {
            std::cout<<"Der destructor ctor\n";
    }        
    
    private:
    Member mx;
    };

    int main_3()//main'de cagir!!!
    {
        std::cout<<"ornek 3 main\n";
        return 3;	
    }

}// nec_ornek_3 sonu



/* Yorum Baslik:nec_ornek_4 
 */
namespace nec_ornek_4{

    class Base{
    public:
    Base(int x)
    {
            std::cout<<"Base Default Ctor x: " << x <<"\n";
    }

    ~Base()
    {
            std::cout<<"Base Default destructor\n";
    }
    private:
    
    };
    class Der: public Base{
    public:
    Der(): /*eleman_ismi () {} init etmemiz lazım*/
    Base(13)
     //Önce base sonra member nesnesi hayata geliyor.
    {
    //Derleyicinin default ctoru çağırmasını söyledik fakat Base classın default ctor'u yok
    //
            std::cout<<"Der  default ctor\n";
    }     
    Der(int i): Base(i)
    {
                    std::cout<<"Der  default ctor i :"<< i << "\n";
    }   
    ~Der()
    {
            std::cout<<"Der destructor ctor\n";
    } 
    private:
    
    };

    int main_4()//main'de cagir!!!
    {
        std::cout<<"ornek 4 main\n";
        Der myder;
        return 4;
    }
}// nec_ornek_4 sonu

/* Yorum Baslik:nec_ornek_5 
 */
namespace nec_ornek_5{

    class Person{
        public :
        Person(); // Person():mname{"noname"}
        Person(const std::string &name);
    private:
    std::string mname{"noname"};

    };

    class Employee: public Person
    {
        public:
        Employee() : Person("noname"){};//taban sınıfın default ctoru
        Employee(const std::string &name) : Person(name){}
    };
    int main_5()//main'de cagir!!!
    {
        std::cout<<"ornek 5 main\n";
    return 5;
    }
}// nec_ornek_5 sonu

/* Yorum Baslik: Multi level inheritance

Sder -> Der -> Base
Her Sder nesnesi bir basedir

Der SDer'in taban sınıfıdır.
Base SDer'in taban sınıfıdır.
Der SDer'in direkt taban sınıfı
Base Sder'in indirekt taban sınıfı ( doğrudan ondan kalıtım ile elde edilmiş taban sınıfımın taban sınıfı )
 */

/* Yorum Baslik:nec_ornek_6 
 */
namespace nec_ornek_6{

    class Base{
    public:
    Base(){    std::cout<<"Base\n";}
    ~Base(){    std::cout<<"Base destr\n";}
    private:
    
    };
    class Der: public Base{
    public:
    Der(){    std::cout<<"Der\n";}
    ~Der(){    std::cout<<"der des\n";}
    private:
    
    };
    class SDer: Der
    {
        public:
        //SDer():Base(0){}//SENTAKS HATASI base indirect base class olduğu için
        //initialize edilemez

        //Sırası ise önce Base sonra Der Sonra SDer'in ana bloğuna girecek
        SDer(){    std::cout<<"Sder\n";}
        ~SDer(){    std::cout<<"Sder des\n";}
        private:

    };
    int main_6()//main'de cagir!!!
    {
        std::cout<<"ornek 6 main\n";
        SDer sx;
        return 6;
    }
}// nec_ornek_6 sonu


/* Yorum Baslik: COPY CTOR   
Bir türemiş sınıf copy ctor edildiğinde türemiş sınıfın copy ctoru çağır edilecek 
Eğer türemiş sınıfının copy ctor'u derleyici yazarsa taban sınıfın copy ctoru çağırılacak
 */

/* Yorum Baslik:nec_ornek_7 
 */
namespace nec_ornek_7{

    class Base{
    public:
    Base(){    std::cout<<"Base default ctor\n";}
    Base(const Base &){    std::cout<<"Base default copy ctor\n";}
    private:
    
    };
    class Der: public Base{
    public:
    //Taban sınıf nesne 
    private:
    
    };
    int main_7()//main'de cagir!!!
    {
        std::cout<<"ornek 7 main\n";
        Der der1;
        Der der2 = der1;        
        return 7;
    }

}// nec_ornek_7 sonu

/* Yorum Baslik:nec_ornek_8 
 */
namespace nec_ornek_8{

    class Base{
    public:
        Base(){    std::cout<<"Base default ctor\n";}
    Base(const Base &){    std::cout<<"Base default copy ctor\n";}
    private:
    
    };
    class Der: public Base{
    public:
    Der()= default;
    Der(const Der&other) : Base(other) //türemiş sınıfın içindeki base adresini geçmiş oldu ve
    //o adres çağırıldı    
    //taban sınıf için bir çağrı yapmak ve Der2'nin içindeki Base içinde default ctor'a çağrı yapacak
    //ve value semantik bozulacak Der1'in içindeki baseden almalıydı.
    //Her zaman special memberslarının derleyicinin yazması normal olanı 
    //
    {

    }
    private:
    
    };
    int main_8()//main'de cagir!!!
    {
        std::cout<<"ornek 8 main\n";
    return 8;
    }

}// nec_ornek_8 sonu

/* Yorum Baslik:nec_ornek_9 
move ctor
 */
namespace nec_ornek_9{

    class Base{
    public:
    Base(){    std::cout<<"Base default ctor\n";}
    Base(const Base &){    std::cout<<"Base default copy ctor\n";}
    Base(Base &&){    std::cout<<"Base move ctor\n";}
    private:
    
    };
    class Der: public Base{
    public:
        Der() =default;
        Der(Der && other) : Base(std::move(other)){}
        //Der(Der && other); bunu yapma 
        //move ctorun çağırılmasını sağlamak zorundayız
        
    private:
    
    };
    int main_9()//main'de cagir!!!
    {
        std::cout<<"ornek 9 main\n";
        Der der1;
        Der der2 = std::move(der1);
        return 9;
    }

}// nec_ornek_9 sonu

/* Yorum Baslik:Atama operator fonksiyonlar   

 */
/* Yorum Baslik:nec_ornek_10 
türemiş sınıfın copy assignment fonksiyonu derleyici yazarsa
taban sınıfı içindeki fonksiyonu çağırıır.

 */
namespace nec_ornek_10{

    class Base{
    public:
    Base & operator=(const Base&)
    {
            std::cout<<"Base copy assignment\n";
            //*this = other recursive bir çağrı olur.
            return *this;
    }
    private:
    
    };
    class Der: public Base{
    public:
    Der & operator=(const Der &other)
    {
        //Derleyici hiçbir zaman buraya kod eklemez 
        //x'in içindeki base olduğu gibi kalır
        //bunun için niteleyerek çağrı yapmak lazım
         
         /*
            *(Base *) this //türemiş sınıf içindeki base nesnesi oldu
            *(Base *) this = other;            
         */
        Base::operator=(other);//Bunu kullanarak çağır
         return *this;
    }
    private:
    
    };
    int main_10()//main'de cagir!!!
    {
        std::cout<<"ornek 10 main\n";
        Der x,y;
        x =y;
        return 10;
    }

}// nec_ornek_10 sonu

/*  HATIRLATMA 
    eğer şu 3 fonksiyondan biri bildirilmişse derleyici sınıfın move memberlarını yazmaz
    not declared

    copy ctor
    move ctor
    destructor

    Eğer 2 işlevden biri bildirilmişse derleyici move memberları delete eder
    move ctor
    move assignment

    class Base{};
    class Base{public Base()};
    ----
    class Base{
        Base(const Base&);
        //default ctor yok
        //destructor var
        //copy assignment var !!!!! 
        //Move memberlar not declared
        
    };
        class Base{
        Base( Base&&&);
        //default ctor yok
        //destructor var
        //copy assignment ve ctor delete edildi !!!!! 
        //Move assignment not declared    
    };
*/

/* Yorum Baslik:nec_ornek_11 
Move assignment
 */
namespace nec_ornek_11{

    class Base{
    public:
    Base & operator=(Base  &&)
    {
            std::cout<<"Base move assignment\n";
            return *this;
    }
    private:
    
    };
    
    class Der: public Base{
    public:
    
    private:

    };

    int main_11()//main'de cagir!!!
    {
        std::cout<<"ornek 11 main\n";
        Der x,y;
        x =std::move(y);
        return 11;
    }

}// nec_ornek_11 sonu
/* Yorum Baslik:nec_ornek_12 
 */
namespace nec_ornek_12{

    class Base{
    public:
    Base & operator=(Base  &&)
    {
            std::cout<<"Base move assignment\n";
            return *this;
    }
    /*
    Base & operator=(const Base&other)
    {
            std::cout<<"Base copy assignment \n";
            return *this;        
    }
    Sentaks hatası kalkar ve bu fonksiyon çağırılır.
    */
    private:
    
    };
    
    class Der: public Base{
    public:
    Der & operator=(Der && other)
    {
        Base::operator=(std::move(other));
        //Base::operator=((other));//SENTAKS HATASI copy assignment deleted durumda 
        return *this;
    }
    private:

    };
    int main_12()//main'de cagir!!!
    {
        std::cout<<"ornek 12 main\n";
    return 12;
    }

}// nec_ornek_12 sonu


/* Yorum Baslik: RUN TIME POLYMORPHISIM

1.kategorideki üye fonksiyonlar taban sınıf
    Ben size aynı zamanda hem kodu hem de implementasyonu veriyorum

    Airplane classı
    void fly()=>bu fonksiyonu zorluyor 
    her airplane classından türemiş classlar bu kodu kullanarak uçmak zorundalar.

2.kategori
    ben size hem bir interface veriyorum hem de bir default code veriyorum
    ister default code kullanılabilir hem de kendi kodunu kendisi sağlayabilir.

    taban sınıf türemiş sınıflara bir seçim hakkı veriyor. Türemiş sınıfın kendi kodunu yapmasına 
    function overwriting(kod sağlanması) ya da taban sınıfın kodunun kullanılması


3.kategori
    Taban sınıf sadece interface veriyor. Bir implementasyon verilmiyor
    Türemiş sınıfın kendi fonksiyonu yazması gerekiyor.

    2. veya 3.Kategoride en az bir fonksiyon varsa polymorhpic sınıf deniyor

    3.kategoride en az bir sınıf varsa abstract class deniyor
    her abstract class bir polymorphic class

abstrcat classlar türünden instance oluşturulamaz --- sentaks hatası olur
concrete class(somut sınıflar) -->nesneleri oluşturulan sınıflar
abstract class ( soyut sınıflar)-->pointer ve referans semantiği ile kullanılabilşr

*/


/* Yorum Baslik:nec_ornek_13 
 */
namespace nec_ornek_13{

    class Airplane{//airplane bir implemantasyonda vermiş hem interface hem de kod veriyor
    //bu fonkstiyon olduğu gibi alınacak airplane sınıfının kodunu kullanarak kalkış yapıcak.
    public:
        void takeoff(); //hem interface hem implemantasyon
        //virtual fonksiyonun geri dönüş türünden önce kullanılırsa 
        //bu bir virtual function
        virtual void land(); //bu fonksiyon yerine override edilebilir. 2.kategori
        //abstract bir anahtar sözcük değil özel bir sentaks ile belirtiliyor
        //inline olarak tanımlanabilir. cpp dosyasında tanımlanacaksa virtual anahtar sözcüğü yok.
        virtual void fly() = 0; //bu sembolik bir sentaks 
        //pure virtual function. 
        //türemiş sınıflara diyor ki bana kod yazmalısın ki concrete olasın 
        //taban sınıfın tüm fonksiyonlarını override etmeli ki nesne oluşturulabilirsin
    };
    int main_13()//main'de cagir!!!
    {
        std::cout<<"ornek 13 main\n";
        return 13;
    }
}// nec_ornek_13 sonu

/* Yorum Baslik:nec_ornek_14 
    Eğer bir fonksyionun derleyicinin koda bakarak anlamasına static/ early binding deniyor
    Çağırılan bir fonksiyonun hangi fonksiyon çağırıldığı koşan bir kodda anlaşılıyorsa late/dynamic binding deniyor.
    function overwriting tamamen dynamic binding
 */
namespace nec_ornek_14{

    class Car{
        public:
        void start()
        {
                std::cout<<"Car has just started\n";
        }
        void run()
        {
                std::cout<<"Car is running now\n";
        }
        void stop()
        {
                std::cout<<"Car has stopped \n";
        }
    };
    class Bmw:public  Car{};
    class Fiat:public Car{};
    class Volvo:public Car{};
    class Toyota :public Car{};
    class Dacia:public Car{};
    void car_game(Car & cr)
    {
        cr.start();
        cr.run();
        cr.stop();
        std::cout<<"----------------------------------------\n";
    }
    int main_14()//main'de cagir!!!
    {
        std::cout<<"ornek 14 main\n";
        Bmw bmw;
        Toyota toyota;
        Dacia dacia;

        car_game(bmw);
        car_game(toyota);
        car_game(dacia);

        return 14;
    }

}// nec_ornek_14 sonu

namespace nec_ornek_14_1{

    class Car{
    public:
        void start(){std::cout<<"Car has just started\n";}
        void run(){std::cout<<"Car is running now\n";}
        void stop(){std::cout<<"Car has stopped \n";}
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
    void run(){std::cout<<"fiat is running now\n";}
    void stop(){std::cout<<"fiat has stopped \n";}    
    };

    class Volvo:public Car{
    public:
    void start(){std::cout<<"Volvo has just started\n";}
    void run(){std::cout<<"Volvo is running now\n";}
    void stop(){std::cout<<"Volvo has stopped \n";}
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

    void car_game(Car & cr)
    {
        cr.start();
        cr.run();
        cr.stop();
        std::cout<<"----------------------------------------\n";
    }
    int main_14()//main'de cagir!!!
    {
        std::cout<<"ornek 14 main\n";
        Bmw bmw;
        Toyota toyota;
        Dacia dacia;

        car_game(bmw); //buarada car sınıfının strat run stop çağırılacak şekilde kod üretiyor
        car_game(toyota);
        car_game(dacia);
        //bir önceki örnek ile aynı durum var
        return 14;
    }

}// nec_ornek_14_1 sonu

/* Yorum Baslik:nec_ornek_15
virtual ekliyoruz 
hangi kodun çağırıldığının kanıtı  bunu kanıtlama çalıştığını 
programının çalışma zamanında rastgele üretilmesi rastgele olsun
 */
#include <random>
namespace nec_ornek_15{

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
    void run(){std::cout<<"fiat is running now\n";}
    void stop(){std::cout<<"fiat has stopped \n";}    
    };

    class Volvo:public Car{
    public:
    void start(){std::cout<<"Volvo has just started\n";}
    void run(){std::cout<<"Volvo is running now\n";}
    void stop(){std::cout<<"Volvo has stopped \n";}
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

    void car_game(Car & cr) //artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
    {
        cr.start();
        cr.run();
        cr.stop();
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
    int main_15()//main'de cagir!!!
    {
        std::cout<<"ornek 15 main\n";
        Bmw bmw;
        Toyota toyota;
        Dacia dacia;
        for(;;)
        {
            auto p = create_random_car();
            car_game(*p); //runtime da çalıştığı gözüküyor
            (void)getchar();
        }        
        car_game(bmw); //bmw'nin üye fonksiyonları çağırılacak
        car_game(toyota);
        car_game(dacia);
        return 15;
    }
}// nec_ornek_15 sonu

/* Yorum Baslik:nec_ornek_16 
 */
namespace nec_ornek_16{

    class Base{
    public:
    virtual void vfunc();
    virtual void vfunc(int);
    virtual void vfunc(int,int);
    private:    
    };

    class Der: public Base{
    public:
        //Eğer bu fonksiyon sanal olmasaydı 
        //parametrik yapısı aynı geri dönüş değeri farklı fonksiyon farklı fonksiyon bildirebilirdi.
        //Taban sınıfın fonksiyonu ile aynı imzaya sahip fonksiyon ( geri dönüş değeri farklı olursa sentaks hatası )
        void vfunc(double);//Bu başka bir fonksiyon sentaks hatası da değil
        //void func();//override edilmiş fonksiyon AYNI PARAMETRİK YAPIDA AYNI GERİ DÖNÜŞ DEĞERİNE SAHİP FONKSİYON
        //artık bu fonksiyo virtual keyword olsa da olmasada aynı bu keyword'u kullan
        void vfunc();
        //constextual keyword: Belirli bir bağlamda kullanıldığında anahtar sözcük
        //ama düz kullanabilirsin bir de final var. Legacy codelar için var identifier'ların sentaks hatasını olmasını
        //engellemek için eklendi geçmişe doğru uyumluluk için   
        void vfunc(int);//int parametreli fonksiyonu override etmiş olucaktı
        void vfunc(int,int);// yapabilirdi        
    private:
    
    };

    int main_16()//main'de cagir!!!
    {
        std::cout<<"ornek 16 main\n";
        int override = 10;
        return 16;
    }

}// nec_ornek_16 sonu

/* Yorum Baslik:nec_ornek_17 
 */
namespace nec_ornek_17{

    class Base{
    public:
    virtual void vfunc(){    std::cout<<"Base::vfunc()\n";;}

    private:    
    };
    class Der:public Base{
    public:
        void vfunc(){    std::cout<<"Der::vfunc()\n";}
    private:
        
    };
    int main_17()//main'de cagir!!!
    {
        std::cout<<"ornek 17 main\n";
        Der myder;
        Base *baseptr = &myder;
        //baseptr->vfunc(); //virtual dispatch mechanism 
        //programın çalışma zamanında baseptr'nin değeri hangi türemiş sınıfın değeri ise
        //çağırılan vfunc() derin vfunc()'ı olucak
        baseptr->vfunc();
        Base &baseref = myder;
        baseref.vfunc();//yine Der'in vfunc'ı

        Base base = myder;
        base.vfunc();//OBJECT SILICING oluyor ve virtual dispatch mechanism devreye girmiyor
        //base vfunc()'ın fonksiyonu olucak.
        return 17;
    }
    void func(Base &r){r.vfunc();}
    void foo(Base *ptr){ptr->vfunc();}
}// nec_ornek_17 sonu

/* Yorum Baslik:nec_ornek_18 
 */
namespace nec_ornek_18{

    class Base{
    public:
    virtual void vfunc(){std::cout<<"Base::vfunc()\n";}  
    void foo(){
        vfunc();
    //bu çağrı Base::vfunc() şeklinde yapılsaydı virtual dispatch devreye girmezdi 
    //nitelenmemiş isimle çağırılıyor çünkü
    }
    private:};

    class Der: public Base{
    public: void vfunc(){std::cout<<"Der::vfunc()\n";}
    private:    
    };
    int main_18()//main'de cagir!!!
    {
        std::cout<<"ornek 18 main\n";
        Der myder;
        myder.foo();//foo'nun gizli base* parametresi var
        //bu durumda da virtual dispacth mechanisması devreye giriyor
    return 18;
    }
}// nec_ornek_18 sonu


/* Yorum Baslik:nec_ornek_19 
 */
namespace nec_ornek_19{

    class Base{
    public:
    virtual void vfunc(){std::cout<<"Base::vfunc()\n";}      
    private:

    };
    class Der: public Base{
    public:
    void vfunc(){std::cout<<"Der::vfunc()\n";}  
    //artık Der'den kalıtım yoluyla elde edilen türemiş sınıf içinde bu fonksiyon 
    private:
    
    };
    int main_19()//main'de cagir!!!
    {
        std::cout<<"ornek 19 main\n";
    return 19;
    }

}// nec_ornek_19 sonu



/* Yorum Baslik:nec_ornek_20 
    !!fonksiyonun virtual olması için virtual keywordüne gerek yok!!
*/
namespace nec_ornek_20{
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
      //  void stop(){std::cout<<"Volvo has stopped \n";} //Artık Car sınıfının fonksiyonu çağırılacak.
};
class Toyota :public Car{
    public:
/*         void start(){std::cout<<"Toyota has just started\n";}
        void run(){std::cout<<"Toyota is running now\n";}
        void stop(){std::cout<<"Toyota has stopped \n";} 
        Bunlar yorum dışında olursa CAr has**** olanlar yazılırdı.
*/
};
class Dacia:public Car{
public:
        void start(){std::cout<<"Dacia has just started\n";}
        void run(){std::cout<<"Dacia is running now\n";}
        void stop(){std::cout<<"Dacia has stopped \n";}
};

class VolvoS60:public Volvo
{
    public:
        /* 
        void start(){std::cout<<"VolvoS60 has just started\n";}
        void run(){std::cout<<"VolvoS60 is running now\n";}
        void stop(){std::cout<<"VolvoS60 has stopped \n";} 
        */
        //Burada taban sınıfın çağırıldıığını yani Volvo has **** çalışıyor
        void start(){std::cout<<"VolvoS60 has just started\n";}
        
};

void car_game(Car & cr) //artık buraya hangi arabayı gönderirsek o fonksiyonlar çağırılacak
{
    cr.start();
    cr.run();
    cr.stop();
    std::cout<<"----------------------------------------\n";
}

Car *create_random_car()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution dist{1,6};
    switch (dist(eng))
    {
    case 1: std::cout<<"Bmw uretildi";return new Bmw;
    case 2: std::cout<<"Fiat uretildi"; return new Fiat;
    case 3: std::cout<<"Volvo uretildi"; return new Volvo;
    case 4: std::cout<<"Toyota uretildi"; return new Toyota;
    case 5: std::cout<<"Dacia uretildi";return new Dacia;
    case 6: std::cout<<"Volvo S60\n"; return new VolvoS60;
    default:
    break;
    }
}
    int main_20()//main'de cagir!!!
    {
        std::cout<<"ornek 20 main\n";
        for(;;)
        {
            auto p = create_random_car();
            car_game(*p); //runtime da çalıştığı gözüküyor
            (void)getchar();
        }        
        return 20;
    }
}// nec_ornek_20 sonu