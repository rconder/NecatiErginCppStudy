# 30.ders

```cpp
namespace ders_30
{
#include <iostream>
    /* Yorum Baslik:
        template parameter:
        template <class T, typenmate U> => eğer T yerine gelecek tür int seçilirse onun adı
        template argument deniyor.
        fonksiyon şablonu:
        T func(T x, U y)
        {   }
        derleyicinin bilmesinin iki yolu var
        1) deduction derleyici dilin kurallarına göre contexten template argümanını çıkarım yapabilir
           Modern c++'tan önce function templates için kullnaıyordu
            Modern c++'tan sonra
            class template (CTAD)'içinde kullanılmaya başladı.
        2)  Template argümanlarının açık olarak bildirilmesi. Örneğin T'nin yerine int kullan U yerine dobule kullan deniyor
        ve buna explicit template argüman deniyor
        2. template parametre biçimi ise non-type parameter: Derleyici bu ismi bir sabitin yerine kullanıyor.
        Kodu yazarken burada
        template <int x> //Burada template argümanı yerine 10 seçilirse örneğin
        derleyici x'in olduğu yere 10 kullanacak.
        a) Bu iki parametre birlikte bulunabilir ve bir den fazla
        classs Myclass
        {};

     */
     /* Yorum Baslik:template_argumant_ornek
      */
    namespace tempalte_parametre_bicimleri_ve_argument_deduction {

#include <vector>
#include <array> //std::array c dizilireni sarmalak için oluşturulan bir sınıf şablonu
#include <bitset>
        template <typename T, std::size_t size>
        class Array1
        {
        private:
            T m_a[size];
        };
        int main()//main'de cagir!!!
        {
            std::cout << "template_argumant_ornek main\n";
            //std::vector<int> //burada template argümanı int explicit olarak veriliyor
            int x = 10, y{ 32 };
            std::swap(x, y);//Burada template argümanlarını bildirmemize rağmen int olması gerektiğini çıkardı.
            std::vector vec{ 1,4,5,7,9 }; //bu bir sınıf şablonu olmasına rağmen derleyici argümanı çıkardı.
            std::array<int, 10> ax;//
            Array1<double, 20> bx;// Gerçek kodu yazarken T gördüğü yerde double türünü
            //size gördüğü yerde 20 yazıcak
            std::bitset<32>x;//
            return 0;
        }

    }// template_argumant_ornek sonu
    /* Yorum Baslik:
    Derleyicinin gerçek kodu yazabilmesi için gerçek kodu görmesi gerekiyor.
    Template kodlar büyük çoğunlukta 'header' dosyası içinde olacak ve
    bunlar ODR'ı ihlal ediyor olmayacak.
    Gerçek kodu templatten hareket ile compile zamanında yazıyor.
    Algoritmalarda çoğunlukla türden bağımsız fakat c/c++ gibi dirlerde kod türe bağımlı.
    örneğin swap fonksiyonunun ele alalım
    Swap fonksiyonunun biz şablon olarak ifade edelim ve derleyiciyi buradan ilgili tür için kodu üretsin
    Biz meta kod tanımlıyoruz ve derleyici bize o fonksiyondan sonsuz sayıda kod üretiyor.
    Eğer bu kodları tek tek yazmış olsaydık bir değişiklikte tüm kodu değiştirmemiz gerekecekti.
    Her template her tür için uygun olmayabilir.
    template <typename T>
    voif func(T x)
    {
        x.foo(); //eğer burada foo fonksiyon kodu T içinde yoksa SENTAKS HATASI veriyor
    }
     */
     /* Yorum Baslik:Derleyici nasıl derliyor
     Derleyici template kodun ne olduğunu bilmeden ilk başta template kodu derliyor.
     void func(T x)
     {
         x.foo();
         ++x;
         if(x > 10 )
             x.func();
     }
     İlk aşamada çok temel kontrolleri yapıyor küme parantezleri doğru kapaatılmış mı gibi, Eğer içinde kullanılan üye
     template parametresine bağlı değilse onun için isim arama yapıyor. YUkarıdaki bar fonksiyonu aranıyor.
     İkinci aşama ise gerçek kodu yazıyor ve buna template instantiation deniyor. Derleyici template'ten fiilen kodu üretecek
     yani derleyici o kodu oluşturuyor.
     template name
     template <typename T>
     void func (){}
     template specialization örneğin T'yerine int olarak seçilmesi ile yazılacak fonksiyona template specialization deniyor
     template'in açılımından bahsedilerken kullanılan id'ye template id deniyor.
     template id' demek template specialization'ı temsil eeden id konumunda
     T'isminin de bir scope'u var.
     template <typename T>
     void func(T x){}
     template <typename T>
     void func(T x)
     buraaa iki tane fonksiyonu var,
     Fonksiyon şablonu ve gerçek fonksiyonlar bir arada bulunabilir ya da birden fazla aynı isimli
     fonksiyon şablonu bulunabilir.
     Specilization için fonksiyon şablonuna çağrı yapılması gerekiyor.
      */
      /* Yorum Baslik:explicit_olarak_belirtme
       */
    namespace explicit_olarak_belirtme {
        template<typename T> //template parameter
        void func(T x) {}//function parameter
        int main()//main'de cagir!!!
        {
            std::cout << "explicit_olarak_belirtme main\n";
            func<int>(10);//bu yapıya explicit template argüman
            func<int>(3.4);//int olsa bile double yolluyoruz
            return 0;
        }
    }// explicit_olarak_belirtme sonu

   /* Yorum Baslik:template_argument_deduction
   Derleyicinin template parametresi karşılığı kullanılacak argümanların ne olduğunun
   çıkarımını yapması.
   auto typededuction aslında template argument deduction arasında 1 istisna dışında
   bir fark yok.
   Derleyicinin bir kod üretmesi için template parametresinin ne olduğunun bilmek zorunda

   */
    namespace template_argument_deduction {
        template <typename T>
        void func(T x) {}
        int main()//main'de cagir!!!
        {
            std::cout << "template_argument_deduction main\n";
            func(10);//argüman olan ifadenin türünden hangi türün kullanıldığını anlamak zorunda
            //aynı 
            auto x = 10;//ilk değer veren ifadenin türünden yapılıyor
            //aynı çıkarım template argüman çıkarımında da yapıyor
            return 0;
        }
        /* Yorum Baslik:
           3 kategoriye ayrılabilir
           1. fonksiyonun parametre türü doğrudan T'türünden
           referans ve pointer deklatörü yok.
            2. Fonksyion parametre referans ve pointer varsa
            3. fonksiyonun parametresinde 2 tane && var ve bu sağ taraf referansı değil
            Forwarding referans

         */
        template<typename T>
        class TypeTeller;
        namespace ornek1
        {
            template <typename T>//1
            void func(T x)
            {
                //TypeTeller<int> x; //eğer tanımı TypeTeller'ın tanımı yoksa sentaks hatası
                TypeTeller<T> t;//burada gene sentaks hatası verecek fakat hata mesajından T'nin türünü görebiliriz
                //T'nin türünü compile time da derleyiciye yazdırabiliriz
            }
            template <typename T>//2
            void foo(T& x) {}
            template <typename T>//3
            void bar(T&& x) {}

            int baz(int);
            int main()
            {
                //auto x  = expr;
                //1. ile kural aynı yani 
                func(12);//eğer bir left 
                const int ival = 10;
                func(ival);//constluk düşer ve T türü int olur
                int x1 = 10;
                int& r1 = x1;
                func(r1);//Referanslık düşer ve T türü int olur.                 
                const int x2 = 10;
                const int& r2 = x2;
                func(r2);//hem Const'luk hem de Referanslık düşer.
                int a[]{ 1,4,5 };
                func(a); //burada fonksiyonu array dikey ile çağırılırsa 
                //a fonksiyonu dizinin ilk adresine dönüştürülücek int * oldu 
                const int ca[]{ 1,4,5 };
                func(ca);
                func("erray");//const char [5] olduğundan const char * olacak
                func(foo);//int(int) dikey ile ==> int(*)(int) olucak

                //auto& y = expr; 2 
                //parametre değişkini kesinlikle ve kesinlik sağ taraf refereansı oalbilir.
                int x2 = 10;
                foo(x2);// bu durumda T'int olacak ve parametre int &
                const int cx2 = 10;
                foo(x2);//T const int olacak !!CONST'LUK düşmüyor!!!
                int a2[3]{ 1,2,3 };
                foo(a);//T'nin türü int[3] yani foo(int(&x)[3]) şeklinde bir kod yazacak 
                //fonksiyonun parametresi 3'elemanlı diziye referans 
                //Burada constluk'ta korunuyor.
                //Bu önemli çünkü 
                /*
                    T y; // int y[3] olucak
                    //Eğer referans  deklaratörü olsaydı bu bir pointer olucaktı
                */
                //kritik hata
                foo(baz);//T'nin türü int(int) func(int (&x)int) olucak
                //3. auto &&z = expr; sonra anlatılacak
            }

            /* Yorum Baslik:kritik_hata
             */
            namespace kritik_hata {
                template<typename T>
                void func(T x, T y);

                template<typename T>
                void foo(T& x, T& y);
                /* Yorum Baslik:Eğer burada x ve y'nin türleri farklı olursa sentaks hatası olucak
                template kodlar otomatik generate edildiği için çok karmaşık bir hata mesajı görüyor.
                Hatanın kaynağı çok karışık olabilir ve derleyicinin neye kızdığını anlaması zor.

                 */
                int main()//main'de cagir!!!
                {
                    std::cout << "kritik_hata main\n";
                    //func(10, 1.20); //SENTAKS HATASI ve ambugiuty olucak T'hem int hem double olamayacağına göre
                    //func("ali","veli"); //Burada T'türü her iki tür içinde const char * fakat 
                    //foo("ali","veli");
                    //T'nin birinci arguman için const char [4] olması gerekirken 2.arguman için const char[4] olmalı

                    //Eğer gönderilen 2.argümanının  bağımsızlık için bir aracımızı var typeidentity

                    return 0;
                }

            }// kritik_hata sonu
        } // namespace ornek1

        /* Yorum Baslik:ornek2
         */
        namespace ornek2 {
            template <typename T, int size>
            void func(T(&r)[size])
            {
                TypeTeller<T> t;
            }
            int main()//main'de cagir!!!
            {
                std::cout << "ornek2 main\n";
                int a[5]{};
                func(a);//deduction T'türü int oldu ve size 5 olmak zorunda 
                //Burada derleyici hem T'nin çıkarımını hem de size sabitinin çıkarımını gerçekleştirdi.
                return 0;
            }
        }// ornek2 sonu    
        /* Yorum Baslik:ornek3
         */
        namespace ornek3 {
            template<typename T>
            void func(T x) {}

            template<typename T>
            void foo(T* x) {}

            template<typename T>
            void bar(T** x) { TypeTeller <T> t; }

            template<typename T, typename U> //argüman olan türler aynı olabilir            
            void baz(T(*)U) { TypeTeller <T> t; }
            //yani T'nin de U'nun türü de int,double,float da olabilir

            template<typename T>
            T func(int);

            int test(double);
            int main()//main'de cagir!!!
            {
                std::cout << "ornek3 main\n";
                int x = 10;
                int* p = &x;
                int** ptr = &p;
                func(x);     //T'nin türü int
                func(p);//T'nin türü int *
                func(ptr);//T'nin türü int **

                foo(p); //T'nin türü int
                foo(ptr); //T'nin türü int *

                bar(ptr);//T'nin türü int
                baz(test);//T'nin int U'nun dobule

                int (*fp)(double) = &baz; //bazı durumlarda fonksiyon pointer'ı türünden fonksiyona 
                //çağrı yapmak yerine fonksiyona şablonundan çıkarımı yapabiliriz.

                //func(1);//SENTAKS HATASI!! BUrada argument deduction yapılamıyor o yüzden sentaks hatası 
                //bazı templatelerde template argümanını anlaşılamadığı için hata veriyor
                return 0;
            }
        }// ornek3 sonu
        /* Yorum Baslik:_ornek4
         */
        namespace _ornek4 {
#include <memory>
            template <typename T>
            void func(T x)
            {
                std::cout << "typeid(T).name(): " << typeid(T).name() << " \n";
            }
            int main()//main'de cagir!!!
            {
                std::cout << "_ornek4 main\n";
                //std::make_unique<int>; //burada zorunlu olarak bildirmek zorunda kalıyoruz.
                func(12);
                func('A'); //Burada her farklı tür için derleyici yeni kod yazıyor.
                func<int>('A');
                return 0;
            }
        }// _ornek4 sonu
        /* Yorum Baslik:_ornek5
         */
        namespace _ornek5 {
            class Myclass {//böyle classlara functer class deniyor.
            public:
                void operator()()const { std::cout << "Myclass::operator()()\n"; }
            private:

            };
            template <typename T, typename U = int, typename Z = T>
            void func() {}
            template <typename T>
            T foo() {}
            template <typename T>
            T func1(T x) //bu durumda 
            {
                x();//x'bir function pointer olabilir
                // ya da sınıfın operator()() overload edlimiş olabilir.
            }
            int baz() { std::cout << "int foo()\n"; }

            int main()//main'de cagir!!!
            {
                std::cout << "_ornek5 main\n";
                //     int x = foo();//burada template argument deduction yapılamaz değişkenin geri dönüş değerinden anlama şansı yok
                func1(foo);//T türünün çıkarımı function pointer olacak ve çağırılan fonksiyon foo türünün olacak
                Myclass mx;
                func1(mx);
                return 0;
            }

        }// _ornek5 sonu

    /* Yorum Baslik:kural_3
     */
        namespace kural_3 {
            template <typename T> 
                class TypeTeller;
            /* Yorum Baslik:T'türünün çıkarımı fonksiyona gönderilen argümanın
            value kategorisi ile ilgili
            eğer buraya sol taraf değeri (L value ) ise T'türünün çıkarımı sol teraf referansı

             */
            template <typename T>
            void func(T&& x) //forwarding reference     
                //varlık nedeni perferct forwarding için 
                //daha sonra bunun başka amaçlarlada kullanılabilir oluyor ve buna 
                //universal reference denmiş. 
                //eğer böyle bir parametrik yapıya çağrı yapılırsa 
                //ancak forwarding referans ancak template'lar ile mümkün
                // Bu fonksiyon her türden argümanı kabul eder.!!!
                // void func(const T&&) olsaydı universal referans yoktu

            {
                TypeTeller <T> t;
            }

            template<typename T>
            void foo(T& x)
            {}
            int main()//main'de cagir!!!
            {
                std::cout << "kural_3 main\n";
                int x = 10;
                func(x);//Eğer sağ taraf referansı olsaydı sentaks hatası olurdu. 
                //T'nin türü int& olur
                //yani T& && x 
                /* Yorum Baslik:Nomral oalrak C++ dilinde reference to reference yoktur.
                Fakat type deduction olduğu zaman bu durum çıkabiliyor. ve burada reference collapsing kuralları devreye giriyor

                T&  & => T&  | sol taraf referansına sol taraf referansı oluşursa => sol taraf referansı olur
                T& && => T&  | sol taraf referansına sağ taraf referansı oluşursa => sol taraf referansı olur
                T&& & => T&  | sağ taraf referansına sol taraf referansı oluşursa => sol taraf referansı olur
                T&& && => T&&| sağ taraf referansına sağ taraf referansı oluşursa => sağ taraf referansı olur
                 */
                using LRef = int&;//LRef int& typedef ismi
                using Nec = int&&;
                int y = 10;
                LRef& x = y;//böylece sol taraf referansı olmuş oluyor.
                LRef&& x1 = y;
                Nec&& x = 10;//xin türü int && oluyor
                foo<int&>(y);//func'ın parametre türü olan x'in türü int&
                func<int&&>(100);//x'in türü int&& oluyor.
                //RVAL Expr => (PR VAL + X VAL expression) Bu durumda T
                func(10);//T'nin türü int ve x'in türü sağ taraf referans
                const int cz = 10;
                int z = 20;
                func(z);
                func(cz);
                func(10);//bunun auto&& x = 10 ile arasında bir fark yok 

                return 0;
            }
        }// kural_3 sonu
        /* Yorum Baslik:zor_ornek 
         */
        namespace zor_ornek{
        template<typename T>
        void func(T&&,T){}
            int main()//main'de cagir!!!
            {
                std::cout<<"zor_ornek main\n";
                int x = 4;
                //func(x,x); //SENTAKS HATASI!!! Ambiguity olur ilk x için T int& olmalı fakat ikinci için T'nin int olması gerekir.
                //dolayısıyla ambiguity olur.
                func(3,3); //Burada Rvalue ile int çıkarımı yapacak ve her iki argüman içinde tür çıkarımı int oldu.            
                return 0;
            }
        }// zor_ornek sonu

        /* Yorum Baslik:auto_ile_farki 
         */
        namespace auto_ile_farki{
            #include <initializer_list>
            template<typename T> 
            void func(T x);
            int main()//main'de cagir!!!
            {
                std::cout<<"auto_ile_farki main\n";
                auto x  = {1,2,3,5};
                std::cout<<typeid(x).name()<<"\n";
                //func({1,2,3,5,});//bu durumda tür çıkarımı yapılamıyor.              
                return 0;    
            }    
        }// auto_ile_farki sonu

    }// template_argument_deduction sonu
    /* Yorum Baslik:template_tip_ornek 
     */
    namespace template_tip_ornek{
        #include <iostream>
        #include <vector>
        #include <initializer_list>
            template<typename T> 
            void func(T x, int y);
            template<typename T> 
            void foo(std::vector<T> y);
            template<typename T> 
            void foo(std::vector<T> &y);

        int main()//main'de cagir!!!
        {
            std::cout<<"template_tip_ornek main\n";
            std::vector<dobule> dvec;
            func(dvec);//T'nin parametre türü double oldu
        return 0;
        }
    }// template_tip_ornek sonu

    /* Yorum Baslik:typename_parametresi

     */
    namespace typename_parametresi{
        template<typename T>
        void func()
        {
            T a[10];
            T(*fp)(T)= nullptr;//T'yi bir türün içinde bir bilişen olarak kullanılabilir
            T* p =nullptr;//T int ise p int * olur, T int * ise p int ** olur.
        }
        
        template<typename T>
        void foo()
        {
            T::nec* p;//T myclass ise myclass'ın nec isminden bir pointer'ı var
            //eğer bu sınıfın bir statik bir veri elemanıysa 
            //burada ambiguity olmaması için tür bilgisi kullanılıyorsa.
            //Template parametresein bağlı olarak kullanmak içiçn 
            typename T::nec x; //Bu durumda derleyici çözünürlük operatörünün sağındaki ismin
            //burada class kullanamıyoruz.
            //type ismi olduğunu ve bunun bir tür bilgisi olduğunu anlatıyor.
            //bu bir tür bilgisi olması nediniyle typename bilgisi kullanmak zorunluydu.
            //C++20 ile bu kurallar biraz gevşetildi.
            using mytype = typename T::nec; //C++20 ile using bildirimi olduğu için typename için gerek yok diyebiliriz.
        }
        
        int main()//main'de cagir!!!
        {
            std::cout<<"typename_parametresi main\n";
            return 0;
        }
    }// typename_parametresi sonu

    /* Yorum Baslik:uye_fonksiyonda_sablon_olabilir 
     */
    namespace uye_fonksiyonda_sablon_olabilir{
        class Myclass{
        public:
            void func(int);
            template<typename T> 
            void foo(T x){ sdfs }//eğer çağrı yapılmazsa derleyici bunun kodunu yazmayacak

        private:
            
        };
        int main()//main'de cagir!!!
        {
            std::cout<<"uye_fonksiyonda_sablon_olabilir main\n";
            Myclass mx;
            mx.foo(10);
            mx.foo(129.24);
            //foo fonksiyonu farklı bir yapıda olabilir.

        return 0;
        }
    
    }// uye_fonksiyonda_sablon_olabilir sonu
} // namespace ders_30
```
