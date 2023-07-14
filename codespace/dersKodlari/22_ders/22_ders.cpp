/* Yorum Baslik:String sınıfı dewamke   

 []
 at()
 front
 back

 reserve 
 resize hem büyütüp hem de küçültülebildiğini

 .insert
 iterator ve index interface var

 =
 assign

 +=
 append
 push_back

 erase
 
 find

 karşılaştırma fonksiyonları 
 int compare
*/

/* Yorum Baslik:nec_ornek_1 
 */
#include <string>
#include <iostream>
namespace 
{
    using namespace std;
} // namespace 

namespace nec_ornek_1{

    int main_1()//main'de cagir!!!
    {
        std::cout<<"ornek 1 main\n";
        string str{"nustafa aksoy"};
        //str.replace();//silme + insert işlemi yazının bir kısmını başka bir kısımla değiştiriyor
        str.replace(3,3,"XYZ"); //ilk iki argüman hangi indexten kaç karakter ve neyle
        str.replace(3,3,"XYZTU");//    
        std::cout<< "[" << str <<"]\n";

        string str1{"nustafa aksoy"};
        str.replace(3,3,10,'A');//    
        std::cout<< "[" << str1 <<"]\n";
        return 1;   
    }
}// nec_ornek_1 sonu

/* Yorum Baslik:nec_ornek_2 
Toplama operator fonksiyonları
 */
namespace nec_ornek_2{

    int main_2()//main'de cagir!!!
    {
        std::cout<<"ornek 2 main\n";
        string str{"ali"};
        string str1{"can"};
        str = str + str1; //str + str1 pr-val expr;
        std::cout<< "[" << str <<"]\n";
        
        auto result = ' ' + str + '_' + "necati";
        std::cout<< "[" <<result <<"]\n";
        //2 tane cstring toplayamayız
        const string txt{".txt"};
        std::cout << "["<< "necati" + txt<< "]\n";
        return 2;
    }
}// nec_ornek_2 sonu

/* Yorum Baslik:nec_ornek_3 
 */
namespace nec_ornek_3{

    int main_3()//main'de cagir!!!
    {
        std::cout<<"ornek 3 main\n";
        string s {"necati"};
        const string cs{"ali"};
        s.front() = '!';
        //cs.front() = '!'; //SENTAKS HATASI const üye fonksiyonun dönüş değeri 
    return 3;
    }

}// nec_ornek_3 sonu


/* Yorum Baslik:nec_ornek_4 
 */
namespace nec_ornek_4{

    int main_4()//main'de cagir!!!
    {   
        std::cout<<"ornek 4 main\n";
        string s1;
        string s2;

        /*BUNU YAPMA
            auto temp = s1;
            s1 = s2;
            s2 = temp;
        */
       s1.swap(s2);
       swap(s1,s2);
       //bu şekilde yap!!    
        return 4;
    }
}// nec_ornek_4 sonu

/* Yorum Baslik:nec_ornek_5 

    String sınıfından const char * türüne implicit dönüşüm yok 


 */
namespace nec_ornek_5{

    void foo(const char *p);
    int main_5()//main'de cagir!!!
    {
        std::cout<<"ornek 5 main\n";    
        string str{"necati ergin"};
        //foo(str); //SENTAKS HATASI
        foo(str.c_str());
        puts(str.c_str());
        //c_str çağırıldığında bir reallacation olursa patlar
        auto ptr = str.c_str(); // geri dönüş değeri const char *
        puts(ptr);
        str += "bugun cpp anlatiyor\n";
        //puts(ptr); //burada ptr eski bellek alanını gösteriyor 
        //pointer invalidation reference invalidation is critical.
        //str.data() -> char * ve const char * döndürüyor
        auto p1 = str.data();
        auto p2 = &str[0]; // string boş ise bunu çağırma 
        auto p3 = &*str.begin();
        auto p4 = str;//p4 string olur
        auto p5 = &str;//string * olur        
        return 5;
    }
}// nec_ornek_5 sonu

/* Yorum Baslik:nec_ornek_6 
contains fonksiyonu C++20 ile eklendi 
var mı yok mu cevabını döndürüyor
geri dönüş değeri boolean.

startswith ve ends_with fonksiyonları da eklendi
 */
namespace nec_ornek_6{

    int main_6()//main'de cagir!!!
    {
        std::cout<<"ornek 6 main\n";
        string str{"necati ergin"};
        //if(str.find('a' != string::npos))
        //if(str.contains('a'));
        string str1;
        //if(str1.starts_with("ali"));
        //if(str1.ends_with("ali"));
        return 6;
    }

}// nec_ornek_6 sonu

/* Yorum Baslik:max size   
bir container'in tutabileceği maksimum size'ı döndürüyor
*/

/* Yorum Baslik:nec_ornek_7 dönüşümler 
sayıdan yazıya 
yazıdan sayıya dönüşüm
c'deki atoi
itoa
 */
namespace nec_ornek_7{

    int main_7()//main'de cagir!!!
    {
        std::cout<<"ornek 7 main\n";
        int ival = 3'546'536;
        
        //str = to_string(ival);//geri dönüş değeri string    
        //function overloading olduğu için her basic tür için var
        string str{"necati_" + to_string(ival)};

        //fakat tersi biraz daha karmaşuk
        //stringten tamsayı elde etmek için
        /*
            stoi
            stol
            stoul
            .....                            
        */
        string str = "9871alican";
        //eğer amaç index değerini kullanılmayan karakterin değerini elde etmek istiyorsak 
        //set edilcek parametreyi 2.argüman olarak yolluyoruz.
        //2. parametrenin varsayılan argumanı 
        auto ival = stoi(str);
        //auto ival = stoi(str,nullptr,10); yukardaki fonksiyon çağırısı aslında bu.
        std::cout<< "ival: " << ival <<" \n";
        //kullanılmayan karakterin indexini elde etmek istiyorsak
        //std::size_t türünden değişken tamamlayıp onun adresini istiyor
        std::size_t idx;
        string str1 = "9871alican";
        auto ival2 = stoi(str,&idx);
        std::cout<< "ival2: " << ival2 <<" \n";
        std::cout<< "idx: " << idx <<" \n";

        auto ival3 = stoi(str1,&idx,16);
        std::cout<< "ival3: " << ival3 <<" \n";
        std::cout<< "idx: " << idx <<" \n";

       return 7;
    }
}// nec_ornek_7 sonu

/* Yorum Baslik:shrink_to_fit
    container'ın size küçüldüğünde kapasite otomatik olarak shrink olmuyor
    dolayısıyla gereksiz kapasiteyi geri verilmeli
*/

/* Yorum Baslik:nec_ornek_8 
 */
namespace nec_ornek_8{

    int main_8()//main'de cagir!!!
    {
        std::cout<<"ornek 8 main\n";
        string str(1'000'000,'A');
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n";
        
        str.erase(20);        
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n";

        str.shrink_to_fit();//zorlayıcı değil 
        //hemende bunu yapmayabilir. pratikte var ama keh keh
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n";
        return 8;
    }
}// nec_ornek_8 sonu

/* Yorum Baslik:nec_ornek_9 
 */
#include <algorithm>
namespace nec_ornek_9{

    int main_9()//main'de cagir!!!
    {
        std::cout<<"ornek 9 main\n";

        //yazıyı ters cevirmek 
        string str{"necati ergin"};
        //nigre itacen olmasını istiyoruz
        std::cout<< "[" << str <<"]\n";
        //STL'de algoritma generic türden bağımsız fonksiyon şablonları var
        reverse(str.begin(),str.end());
        
        std::cout<< "[" << str <<"]\n";
        reverse(str.begin(),str.end());
        std::cout<< "[" << str <<"]\n";
        
        sort(str.begin(),str.end());
        std::cout<< "[" << str <<"]\n";

        sort(str.begin(),str.end(),greater<char>{});
        return 9;
    }

}// nec_ornek_9 sonu

/*
cpp 20 ile yeni eklemeler yapıldı
artık doğrudan global erase fonksiyonu eklendi 
erase remove yerine
string str{"ankara'dan amcam ve halam antalya'ya vardilara"};
        std::cout<< "[" << str <<"]\n";
auto n_deleted = erase(str,'a'); //geri dönüş değeri silinmiş karakter sayısı
        std::cout<< "[" << str <<"]\n";
        cout<<"n_deleted:"<<n_deleted;
*/
/********************************************************************************/


/* Yorum Baslik: Nesne yönelimli programlama 
    INHERITANCE
    Kalıtım 
    OOP'aşan farklı amaçlarlada kullanılabilen bir araç seti
    CPP kalıtım araçları nesne yönetimli programlamadaki araçları kapsar

*/  

/* Nesne yönelimli programlamada kalıtım
is -a relational -> bir nesnenin aynı zamanda başka bir nesne olarak kullanabileceğini ifade ediyor
mercedes araba, audi araba
has -a relationship ->composition'ı anlatıyor araba'nın motoru

problem domainindeki nesneleri ayrıştırma biçimi
farklılıklar içeren sınıf nesnelerine ortak özelliklerini kullanmak istediğimiz zaman kullanıyoruz

İki ana fayda 
-Üst seviyedeki kodların alt seviyedeki kodların bağımlılığını kaldırıyor. Eskiden yazılmış kodların yeni yazılmış kodların kullanabilmesi
-Bonus olarak ise kod reuse yapabiliyoruz

kaynak classa Parent class/super class
Employee class => Parent class
Child class/ Subclass 
Software developer => child class
///CPP'da 
Kaynak class => Base class
Kalıtım yoluyla elde edilen => Derived class
derivation => kalıtım işlemi

CPP'de kalıtımın 3 kategorisi var
public inharitance => Java/C#'daki katılım
protected inheritance => başka amaçlar ile kullanılıyor.
private inheritance
*/


/* Yorum Baslik:nec_ornek_10 
a->b
c->b
d->b : one level inharitance
a -> b -> c: multi level inharitance
her mercedes bir arabadır, her merceedes_SS500 bir mercedestir.

Multiple inharitance: bir sınıfı yine kalıtım yoluyla inharitance edip
2 ya da daha fazla kaynak kullanılarak yapılıyor.
a->b
a->c : a sınıfı hem 
*/

// Bir incomplete type'tan inharitance YAPILAMAZ!!!!!!!!!!!!!!!
//Taban sınıf complete olmak zorunda 

/* private ve protected çok daha az kullanıldığında bu konu hakkında sonra anlatılacak. */
//default olarak public inharitance 
namespace nec_ornek_10{
    class Base{
    public:        
    private:        
    int a,b;
    };

    class Der : public Base/*public|private|protected olabilir */
    //Der=>türeyen sınıf, türemiş sınıf
    /*class kullanılarak oluşturulduğunda keyword kullanılmazsa private kalıtım oluyor*/
    //class Der : private Base
    //class Der : Base => oluyor
    //Eger sınıfı -struct- ile oluşturursak 
    //struct Der : Base {};
    {
    public:
    int c;
    private:
    //her der nesnesi içinde base nesnesi olucak
    };

    int main_10()//main'de cagir!!!
    {
        std::cout<<"ornek 10 main\n";
        std::cout<< "sizeof(Base): " << sizeof(Base) <<" \n";
        std::cout<< "sizeof(Der): " << sizeof(Der) <<" \n";//8Byte Base nesnesinin size + Der'in elemanlarının sizeof'u
        return 10;
    }
}// nec_ornek_10 sonu

/* Yorum Baslik:nec_ornek_11 
public interface'in seçerek değil 
komple public interface'i komple alıyoruz
 */
namespace nec_ornek_11{
    class Base{
    public:
      void foo();
      void func();  
    private:        
    };

    class Der: public Base{
    public:        
    private:        
    };

    int main_11()//main'de cagir!!!
    {
        std::cout<<"ornek 11 main\n";
        Der myder;
        myder.foo();
        myder.func();        
        return 11;
    }
}// nec_ornek_11 sonu


/**
 * isim arama ve scope
 * erişim kontrolü
 * türemiş sınıf türünden taban sınıf türüne yapılan örtülü dönüşüm
 * bir türemiş sınıf nesnesi hayata gelmesi için taban sınıf nesnesinin de hayata gelmesi de lazım 
 * ctor'ların durumu nasıl  olucak
 * atama işlemleri
*/


/* Yorum Baslik:nec_ornek_12 
 */
namespace nec_ornek_12{
    class Base{
    public:
      void foo();  
    private:
        
    };
    class Der: public Base{
    public:
        void bar();
    private:
        
    };
    int main_12()//main'de cagir!!!
    {
        std::cout<<"ornek 12 main\n";
        Der myder;
        myder.foo();
        myder.bar();
        return 12;
    }
}// nec_ornek_12 sonu

/* Yorum Baslik:sınıfın protected kısmı özel:

client'lara kapalı fakat kalıtım yoluyla elde edilen classlara açık
protected bölüm varsa kalıtım yoluyla kullanılacağı açık
 */

/* Yorum Baslik:nec_ornek_13 İsim arama
 */
namespace nec_ornek_13{

 class Base{
 public:
    int x;
    void foo(int);
 private:
    
 };
 class Der: public Base{
 public:
    int x;//burada bildirilmeseydi base classta aranacaktır.
    //türemiş ve taban fonksiyonlar içinde bildirilen aynı isimli fonksiyonlar function overloading değil
    void foo(double);
 private:
    
 };
 //eğer bir isim nitelendirilimiş olarak kullanılırsa 
 //isim arama kuralları farklı
    int main_13()//main'de cagir!!!
    {
        std::cout<<"ornek 13 main\n";
        Der myder.x; //önce Der sınıfında aranıyor eğer bulunamazsa 
        //Der'in taban sınıfında aranıcak
        //türemiş sınıfın ismi
        myder.foo();//Double fonksiyon çağırılır.
    return 13;
    }
}// nec_ornek_13 sonu

/* Yorum Baslik:nec_ornek_14 
 */
namespace nec_ornek_14{

class Base{
    void func(int);
public:
  void foo(int);  
private:
    
};
class Der: public Base{
public:
  void foo(int, int);  
  
private:
  void func(double);   
};
    int main_14()//main'de cagir!!!
    {
        std::cout<<"ornek 14 main\n";
        Der myder; 
        //myder.foo(12)//SENTAKS HATASI!!!! çünkü isim aram daha önce yapılıyor
        //myder.func(12);//SENTAKS HATASI!!! çünkü access control'e takılıcak
        //myder.func(12); //SENTAKS HATASI!! türemiş sınıfta aranıp buluncak ve private olduğu için erişim kontrolüne takılacak.
        return 14;
    }

}// nec_ornek_14 sonu


/* Yorum Baslik:nec_ornek_15 
 */
namespace nec_ornek_15{
    class Base{
    public:
      void foo(int)
      {
            std::cout<<"base::foo(int)\n";
      }  
    private:
        
    };
    class Der: public Base{
    public:
        void foo(int)
        {
                std::cout<<"Der::foo(int)\n";
        }
    private:
        
    };
    int main_15()//main'de cagir!!!
    {
        std::cout<<"ornek 15 main\n";
        Der myder;
        myder.foo(12);
        myder.Base::foo(12);
    return 15;
    }
}// nec_ornek_15 sonu

/* Yorum Baslik:nec_ornek_16 
 */
namespace nec_ornek_16{
    class Base{
    public:
        
    private:
      void foo()
      {

      }  
      protected:
      void func()
      {

      }
    };
    class Der: public Base{
    public:
        void derfunc()
        {
            //foo();//SENTAKS HATASI!!!! Erişim kontrolü 
            //taban sınıfın private bölümü türemiş sınıfın bölümüne kapalı
            func();//türemiş sınınfın içinde hem public hem de protected kısmına erişebiliriz
        }
    private:
        
    };
    int main_16()//main'de cagir!!!
    {
        std::cout<<"ornek 16 main\n";
        Base mybase;
        //mybase.foo();//Sentaks hatası!!!
    return 16;
    }

}// nec_ornek_16 sonu

/* Yorum Baslik:nec_ornek_17 
 */
namespace nec_ornek_17{
    class Base{
    public:
        
    protected:
        void foo(){};
    };
    class Der: public Base{
    public:
        void foo(){
        //foo();//recursive çağrı olur
        Base::foo();//Bu şekilde çağırabiliriz.
        }
    private:
        
    };
    int main_17()//main'de cagir!!!
    {
        std::cout<<"ornek 17 main\n";
    return 17;
    }
 

/**
 * isim arama sırası 
 * blok -> kapsayan blok -> türemiş sınıf -> taban sınıf -> namespace
 * İSİM ARAMA ÖNCE YAPILIYOR!!!!!!!!!!!!!
 * 
*/

/* Yorum Baslik:nec_ornek_18 

Eğer der sınıfını base sınıfından public kalıtım yoluyla elde edildiyse
burada implicit type conversion 
upcasting deniyor => yukarı doğru dönüşüm
herhangi bir araca gerek duymuyor
-> Eğer 
    Base
     ^
     |
    Der
-
Eğer taban sınıfından türemiş sınıfa yapılacaksa downcasting deniyor
 */
namespace nec_ornek_18{
    class Base{
    public:
        
    private:
        
    };
    class Der: public Base{
    public:
        
    private:
        
    };
    int main_18()//main'de cagir!!!
    {
        std::cout<<"ornek 18 main\n";
        Der myder;        
        Base *baseptr = &myder; //taban sınıf türünden bir pointer türemiş sınıf türünden bir nesneyi gösterebilir
        Base &baseref = myder; //Tür dönüştürme operator kullanılmasına gerek yok
        //Tersi geçerli olmak zorunda değil
        
        //Base mybase;
        //Der* derptr = &mybase; SENTAKS HATASI böyle bir örtülü dönüşüm yok
        
        //Base mybase;
        //Der myder1;
        //mybase = myder1; // Bu legal fakat bunu çok özel durumlar haricinde kullanma
        //object slicing deniyor //derin içindeki base kısmı atanıyor. 
        //böyle bir atama yapmıyoruz denir. Pointer veya referans semantiği kullanıyoruz
        return 18;
    }
}// nec_ornek_18 sonu

/* Yorum Baslik:
void car_gamptr(Car*ptr);    
void car_gameref(Car&cr)
{
    
}
*/

