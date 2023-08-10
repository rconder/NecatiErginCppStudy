namespace ders_31313131131313131313131
{
#include <iostream>
    namespace fonksiyon_sablonu
    {
        /* Yorum Baslik:_ornek1
         */
        namespace _ornek1 {
            template<typename T>
            T sum(T x, T y) {
                return x + y;

            }//Bu fonksiyon aynı türden iki değişken istiyor

            template<typename T, typename U>
            T sum1(T x, U y)
            {
                return x + y;

            }
            /* Yorum Baslik:burada ayrı bir type parametresi ekleyebiliriz.

             */
            template<typename T, typename U, typename R>
            R sum2(T x, U y) { return x + y; }

            template<typename R, typename T, typename U>
            R sum3(T x, U y) { return x + y; }


            int main()//main'de cagir!!!
            {
                std::cout << "_ornek1 main\n";
                int ival = 3;
                double dval = 3.4;
                //sum(ival,dval);//SENTAKS  HATASI
                auto result = sum1(ival, dval);
                //burada dilin buna destek veren bir kaç aracı var
                auto result2 = sum2<int, double, double>(12, 4.5);
                //şeklinde yaparak geri dönüş parametre türünü belirtebiliriz.
                auto result3 = sum3<double>(12, 4.5);

                return 0;
            }
        }// _ornek1 sonu
        /* Yorum Baslik:trailing return type ve auto return type ile
        alakalı iki araç dile eklendi bu araçların asıl varlık nedenleri
        fonksiyon şablonu olmasına rağmen normal fonksiyonlar ile de kullanılabilir.
         */
         /* Yorum Baslik:trailing_return_type
         2 nedenle kullanılıyor.
         1. artistlik :D
         normal bir senaryoda geri dönüş değeri function pointer olan bir tüp

          */
        namespace trailing_return_type {

            auto func(int x, int y) -> int
                //int auto func(int x, int y)
            {
                return x + y; //bu fonksiyonun geri dönüş değeri
            }
            int foo(int, int);
            //ismi func olan bir fonksiyon tanımla geri dönüş değeri foo olsun
            //int(*)(int,int);
            //C'de typedef int(*Fptr)(int,int); olabilir. Fptr func(){return & foo;} yazilabilir
            //C++'Da  int(*func())(int,int){return &foo}
            //auto func()->int(*)(int,int) gibi bir şekilde yazılabilir.

            //fakat esas nedeni
            template<typename T, typename U>
            /* 'decltype(t+u)' Sentaks hatası scopetan kaynaklı*/
            auto sum(T t, U u) -> decltype(t + u)//Bunun türü t + u'nun türü o olsun C++11'e kadar tek olanak buydu
            {
                ////
            }
            int main()//main'de cagir!!!
            {
                std::cout << "trailing_return_type main\n";
                return 0;
            }
        }// trailing_return_type sonu

        /* Yorum Baslik:auto_return_type
        C++14 ile eklendi
        fonksiyonun tanımı gerekiyor
        birden fazla return statement varsa
        bunun sentaks hatası olmaması için aynı tür olmalı

         */
        namespace auto_return_type {
            auto func(int x, double y)
            {
                return x + y;//derleyici return ifadesine bağlı olarak çıkarımını yap demek 
                //buradaki tür çıkarımı auto tür çıkarımı 
                //return x; olsaydı int olurdu
            }
            //void func(auto y) //C++20 ile eklenen bir araç 
            //bu yine bir template abbraviated template syntax template'in kısaltması gibi daha çok 
            //fonksiyon şablonlarının daha kolay yazılması için eklendi auto func(auto)'da geçerli

            int main()//main'de cagir!!!
            {
                std::cout << "auto_return_type main\n";
                return 0;
            }
        }// auto_return_type sonu        
    } // namespace fonksiyon_sablonu

    /* Yorum Baslik:void_ptr_func
     */
    namespace void_ptr_func {
        template <typename T>
        class TypeTeller;
        template <typename T>
        T func(T* p)
        {
            TypeTeller <T> t;
        }
        int main()//main'de cagir!!!
        {
            std::cout << "void_ptr_func main\n";
            void* vp{};
            //func(vp);
            //func(&vp);//void * olur türü ve geri dönüş değeri de void * olur
            return 0;
        }
    }// void_ptr_func sonu    

    /* Yorum Baslik:fonksiyonun_sablon_icinde_sablon
    Tek bir fonksiyon şablonuyla
    ayrı ayrı şablondan kod yazabiliyor.
    Örneğin swap fonksiyonu
     */
    namespace fonksiyonun_sablon_icinde_sablon {
        template <typename T>
        void fun    c(T x, T y)
        {
            std::swap(x, y);
        }

        template <typename T>
        auto func(T& x)
        {
            //return x;//Eğer T'türü int olursa geri dönüş değeri int olurdu 
        }

        int main()//main'de cagir!!!
        {
            std::cout << "fonksiyonun_sablon_icinde_sablon main\n";
            return 0;
        }

    }// fonksiyonun_sablon_icinde_sablon sonu
    /* Yorum Baslik:onemli_decltype
     */
    namespace onemli_decltype {

        struct Nec
        {
            int a;
        };

        // burada değişkenin türü decltype'ın kurallarına göre elde edilecek
        int&& foo();


        template <typename T>
        decltype(auto)func_decl(T& x)
        {
            return x;
        }
        template <typename T>
        auto func_auto(T& x)
        {
            return x;
        }
        int main()//main'de cagir!!!
        {
            std::cout << "onemli_decltype main\n";
            //decltype()//ile bir tür veriyorduk
            int x = 10;
            decltype(x); //int türü

            int& r = x;
            decltype(r); //int ref türü

            const int cx = 10;
            decltype(cx) y = 20; //const int y olucaktı

            //decltypte a  iki durum var burada isim türünden olması durumu vardı
            Nec mynec{};
            decltype(mynec.a);//int hala isim kuralları söz konusu

            //eğer bu bir ifade formundaysa 
            /* Operandı olan ifadenin value kategorisni bağlı olarak elde ediliyor.
            PR value T
            L val T&
            X val   T&&
            türü

             */

            decltype(x + 5) y1 = 12;//Bu int türü 

            decltype((x)) y2 = y1;//L value expression oluyor int & türü oldu

            int* p = &x;
            decltype(*p)y = x; //L value expr. ve türü int & oluyor.
            decltype(std::move(x)) y = 10; //geri dönüş değeri X value fonksiyon olursa 
            //olduğu için elde edilen tür int &&
            decltype(auto) y = x;//burada tür int olucak 
            decltype(auto) y5 = (x);//bu durumda int & olucaktı
            decltype(auto) y = *p; //int ref olucak
            decltype(auto) y = foo();//ifade X value olduğu için y'nin türü int &&    


            auto ret = func_auto(x); //ret'in türü int

            auto ret1 = func_decl(x); //ret'in geri dönüş değeri int & türü oldu
            //auto &ret2 = func_auto(x);//SENTAKS Hatası olacak çünkü geri dönüş değeri int
            return 0;
        }

    }// onemli_decltype sonu
    /* Yorum Baslik:
    constexpr fonksiyonlar online olmak zorundaydı
    artık çok az kısıtlamaya tabi
     */

     /* Yorum Baslik:
     fonksiyon şablonlarının overload edilmesi
     Sınıf şablonları

     -explicit specialization
     -partial specialization
     -defautl template argument
      */


      /* Yorum Baslik: Sınıf şablonları
      ---------------------------------------------------------------------
      Burada oluşturduğumuz metakod  bizim için sınıfı oluşturucak         |
      Burada genellikle data structure için yapılıyor.                     |
      Salt bunun için kullanılıyor diyemeyiz bir çok yerde karşımıza çıkar |

      Eğer bu araç olmasaydı ayrı ayrı benzer kodlar olan bir sürü sınıf olucaktı
      Ve Örneğin string sınıfı yapısı gereği çok fazla fonksiyonu olan bir sınıf ve eğer sınıf şablonu olmasaydı
      bütün fonksiyonlar teker teker derlenecekti ve bu durum sadece çağırılan fonksiyonların kodu yazılıp derlenecek

      Kod hacminin artmamasını sağlıyor. Ve kodun legal olması gerekmiyor
       */
       /* Yorum Baslik:sinif_sablonu
        */
    namespace sinif_sablonu {

        //struct ya da class keyword'ü kullandık
        /* Yorum Baslik:Burada Nec bir sınıf şablonu
        derleyici compile zamanda T'türünü öğrencek ve kodu yazıcak
        - Bu olmasaydı bizim birbirine benzer bir sürü sınıf kodu yazmamız gerekecekti
        Derleyiciye sınıf kodu nasıl yazılır onu öğreten bir kod yazıcaz

        - Çok sayıda üye fonksiyonu olan sınıf şablonlarında eğer olmasaydı buradaki tüm kod derlenecekti
        fakat şimdi sadece çağırılan fonksiyonların kodu yazılacak. Kod hacminin artmamasını sağlıyor.
        - Kodun legal olması gerekmiyor.
        - Üye fonksiyonlarında Nec'in

        Sınıf şablonu bir template burada specilization olan sınıf kullanılıyor.
        CTAD: class template argument deduction
        - Eski C++'ta yoktu
        - Sınıf şablonlarında ctor'dan tür çıkarımı yapılıyor
         */
         /* Yorum Baslik:sentaks_ve_bazi_kurallar
          */
        namespace sentaks_ve_bazi_kurallar {
            template<typename T>
            class Nec
            {
            public:
                void foo()//inline olarak yazarsan Template argüman kullanmak zorunda değiliz
                {
                    T x, y;
                    auto z = x + y; //Örneğin burada T myclass türü olması durumunda ve Myclass sınıfının 
                    //+ operatoru olmaması durumunda sentaks hatası olur FAKAT eğer burada foo fonksiyonu çağırılmadıysa sentaks 
                    //hatası olmaz!!!!           
                }
                void func()
                {
                    Nec x; //Nec<T> x; burada sınıf şablonunun kodu içinde sınıf şablonunu ismini kullanabiliyoruz
                    //Nec<T> x; için yazılmış gibi aslında
                }
                void baz(T x);
                void bar(T& x);
            };
            //eğer baz ve bar inline olararak tanımlanmayacaksa
            //Eğer başlık dosyasında olursa bunlar ODR'ihlal etmeyecek
            template<typename T>
            void Nec<T>::baz(T x) {        }
            template<typename T>
            void Nec<T>::bar(T& x) {        }

            Nec<intA> func(Nec int& x);
            class class {
            public:

            private:
                Nec<int> mx;
            };
            bool operator<(const Nec<T>&, const Nec<T>&);
            //her bir speciliization ayrı bir tür
#include <vector>
#include <array>
            int main()//main'de cagir!!!
            {
                std::cout << "sentaks_ve_bazi_kurallar main\n";
                Nec<int> n1;

                //Nec x;//Bunu yapamayız çünkü Nec bir şablon
                //Nec<int> //Bu ise bir sınıf.
                //Nec<Nec<int>> //Bu da başka bir sınıf.
                Nec<double> dx, dy;
                Nec<int> di;
                //dx = di; //A sınıfından B sınıfı türünden atamayı yapacak özel bir fonksiyonu yoksa 
                //atayamayız
                dx = dy;//aynı şablonun specilizationları farklı sınıflar. Bu fonksiyonlar otomatik olarak yazılmaz.

                std::vector<dobule> dvec(100);
                std::vector<int> ivec(100);
                //dvec = ivec;
                //bunlar farklı türler
                arrray<int, 5> ax;
                array <int, 4> ay; //bunlar birbirinden farklı sınıflar.

                //ax = ay; //Bunlar normalde sentaks hatası var fakat bellli araçlar ile sağlanabilir
                //

                return 0;
            }

        }// sentaks_ve_bazi_kurallar sonu

        namespace CTAD {
#include <vector>
#include <pair>
            template<typename T>
            class Nec {
            public:
                Nec(T);
            private:

            };
            //template <typenmae T, typename U>
            //struct Pair{}

            int main()//main'de cagir!!!
            {
                std::cout << "CTAD main\n";
                Nec mynec(12);//burada ctor'a gönderilen değişkenden çıkarımla yapılabiliyor.
                std::pair<int, double> x;
                std::pair x1{ 12,4.5 }; //derleyici burada ctor'a gönderilen argmanlardan anlıyor.
                std::vector ivec{ 2,4,5,6,78 };//derleyici vector'un 
                return 0;
            }

        }// CTAD sonu


        /* Yorum Baslik:sinif_sablonu_specilization
         */
        namespace sinif_sablonu_specilization {
#include <array>
#include <vector>
#include <list>

            template<typename T>
            class A {};

            int main()//main'de cagir!!!
            {
                std::cout << "sinif_sablonu_specilization main\n";
                A <int> x;
                A <A<int>> x1;
                A <A<A<A<int>>>> x2;

                cout << typeid(x).name() << "\n"
                    cout << typeid(x1).name() << "\n"
                    cout << typeid(x2).name() << "\n"
                    std::list<std::vector<A<int>>> b;//list şablonuu içinde 
                cout << typeid(b).name() << "\n"
                    return 0;
            }
        }// sinif_sablonu_specilization sonu

    }// sinif_sablonu sonu
    /* Yorum Baslik: default_argüman_türünden çıkarım yapmak
        Varsayılan argümanın türüne bakılarak bu çıkarım yapılamaz
        Burada T'türünün çıkarımı çağırıya göre yapılacak
     */
     /* Yorum Baslik:default_arguman_ile_cikarim
      */
    namespace default_arguman_ile_cikarim {
        template <typename T>
        void func(T = 0);
        int main()//main'de cagir!!!
        {
            std::cout << "default_arguman_ile_cikarim main\n";
            int x = 100;

            func(12);
            func(1.2);
            func(&x);
            //func();//tür çıkarımı yapılamaz ve sentaks hatası olur    
            return 0;
        }


    }// default_arguman_ile_cikarim sonu


        /* Yorum Baslik:C++ 20'dan önce non type parametre olarak sadece tam sayı türleri
        kullanılabiliyordu. C++20'den sonra tüm hepsi kullanılabilir durumda
         */
         /* Yorum Baslik:nontype_parameter_ornek
          */
    namespace nontype_parameter_ornek {

        template<auto x>
        class class {
        public:

        private:

        };
        template<typename T, T x>//ikincisi non-type parametre 
        //ilk typeparametreye gelen ne ise onun aynısı non-type parameter oluyor
        class class {
        public:

        private:

        };
        int main()//main'de cagir!!!
        {
            std::cout << "nontype_parameter_ornek main\n";

            return 0;
        }
    }// nontype_parameter_ornek sonu

    /* Yorum Baslik:varsayilan_template_argumanlari
    gerek sınıf gerek fonksiyon şablonlarında template parametresi default argüman alabilir
    Moder C++'öncesinde bu çok mümkün değildi ve sadece sınıf şablonları alabiliyordu
    artık fonksiyon şablonlarında da alabiliyor.
    Bütün type parametreler varsayılan argüman alabilir
     */
    namespace varsayilan_template_argumanlari {
#include <string>
        template<typename T> //
        void func(T x = 10) {}//x call parameter. burada varsayılan argüman geçilmediğinde 10'değeri geçilmiş olucak

        template<typename T = int>//eğer template argüman belirtilmezse int olarak kullan
        class Myclass
        {
        public: private:
        };

        template<int x = 20, int y = 50>
        class nonTypeParameterClass {};
        //        template<typename T = int, typename U> //Sentaks hatası 
        //tıpkı fonksiyonların parametre değişkenlerinin varsayılan argüman alması gibi
        // ya sondakiler alablir ya da hepsi almak zorunda 
        template<typename T = double, typename U = int>
        class M2_default_argument_class {
        public:

        private:

        };
        template<typename T, typename U = T>
        class defaulTTClass {

        };
        template <typename T, typename U = Myclass<T>>
        class Nec
        {

        };
        //vector açılıımı 
        template<typename T, typename A = std::allocator<T>>
        class Ivector {};

        //string 
        //using String = std::basic_siring<char>;

#include<set>
//Standart kütüphanenin set sınıfı
        template<typename Key, typename Comp = std::less<Key>, std::allocator<Key>>
        class Set {

        };
        template<typename T = std::string>
        void func(T x = {})//template parametresi de varsayılan argüman alırken 
            //fonksiyonun parametreside default argüman alıyor.
        {

        }


        int main()//main'de cagir!!!
        {
            std::cout << "varsayilan_template_argumanlari main\n";
            func<int>();
            Myclass<double> x;
            Myclass<> y; //Myclass<int> y aynı anlamda 
            M2_default_argument_class<int, long> x1;
            M2_default_argument_class<int> y1;
            M2_default_argument_class<> z;
            nonTypeParameterClass<> n1;
            std::cout << typeid(n1).name() << "\n";
            nonTypeParameterClass<90> n2;
            std::cout << typeid(n2).name() << "\n";
            nonTypeParameterClass<90, 20> n3;
            std::cout << typeid(n3).name() << "\n";
            defaultTTClass<int> dm1;
            std::cout << typeid(dm1).name() << "\n";
            Nec<int> nec1;
            std::cout << typeid(nec1).name() << "\n";

            std::vector<int> vec; //vector<int, std::allocator<int>> olarak kullanıyoruz
            //çoğunlukla allocator template parametresi genellikle int açılıımı yapıyoruz

            //string 
            basic_string<char, char_traits<char>, std::allocator<char>> str;
            // string str; ile aynı aslında

            //set 
            set<int> myset; //set<int, less<int>, allocator<int>> aslında

            return 0;
        }
    }// varsayilan_template_argumanlari sonu

    /* Yorum Baslik:fonksiyon_sablonlarinin_overload_edilmesi
        A-) gerçek fonksiyonlu ve fonksiyon şablonları ile overload oluşturabilir.
        Fonksiyonu sadece int türden argümanla çağırılması gerekiyor
     */
    namespace fonksiyon_sablonlarinin_overload_edilmesi {
        template<typename T>
        void func(T x)
        {
            std::cout << "function template type T is" << typeid(T).name() << " :\n";
        }
        void func(int x)
        {
            std::cout << "non template function func(int)\n";
        }

        template <typename T>
        void foo() = delete;
        //ya da void foo(auto ) = delete;

        void foo(unsigned int)
        {}

        template <typename T>
        void boo(T){     std::cout<<" functionn template func(T)\n";}
        template <typename T, tpyename U>
        void boo(T,U){     std::cout<<" functionn template func(T,U)\n";}
        int main()//main'de cagir!!!
        {
            std::cout << "fonksiyon_sablonlarinin_overload_edilmesi main\n";
            func(12);//eğer argümanın türü gerçek fonksiyon parametresi ile birebir aynı ise 
            //gerçek fonksiyon çağırılıyor ve kod yazıılmıyor.
            func<int>(20);
            func<>(29);

            func('A'); //int olmayan tüm argümanlar için fonksiyon şablonundan bir specilization oluşturulacak
            func("ali");

            foo(23u);
            //foo(2.3);//SENTAKS HATASI

            boo(12);
            boo(3,5);


            return 0;
        }
    }// fonksiyon_sablonlarinin_overload_edilmesi sonu

    /* Yorum Baslik:partial_ordering_rules 
        Burada pratikte fonksiyon parametresi daha fazla spesifik olan seçiliyor
        burada T*'daha spesifik oluyor. Burada bir kural setine göre daha spesifik. Burada bir koşulun
        sağlanması lazım ambiguity olacak 

     */
    namespace partio_ordering_rules{
        template <typename T>//burada T türünden
        void boo(T){     std::cout<<" functionn template func(T)\n";}
        template <typename T>//burada T* türünden
        void boo(T *){     std::cout<<" functionn template func(T *)\n";}
        template <typename T, int size>//burada T* türünden
        void boo(T(&)[size]){     std::cout<<" functionn template func(T *)\n";}
        

        int main()//main'de cagir!!!
        {
            std::cout<<"partio_ordering_rules main\n";
            int x = 10;
            func(&x);//
            int a[10]{};//eğer en üstteki olsaydı T'nin türü T* olurdu 
            //
            func(a);//T'nin türü int size 10 çıkarılacaktı 
            return 0;
        }
    
    }// partio_ordering_rules sonu

    /* Yorum Baslik:explicit_specialization:
    Burada teknik terim also da daha çok kullanılan terim full specialization.
    specialization bir template'in instantiate edilmesi ile oluşan bir ürün.

    Ama dil bize belirli template argümanları için derleyiciye bu specialization için kodu yazılımcı yazılabilir
    Örneğğin myclass şablonu var ve bu sınıf için int explicit specilization'ı biz verirsek olabilir.

    Explicit specialization hem sınıf hem de fonksiyon şablonları için verilebiliyor.
    Fonksiyonlar için genellikle overloading kullanılıyor.
    Genel olark bunu sınıflar için kullnaacağız

    BU BİR TEMPLATE DEĞİL Bu özel bir tür için oluşturulmuş specialization!!!!!!
    */
    namespace explicit_specialization{
        #include <cstring>
        template<typename T>
        T Max(T x, T y)
        {
            return x>y ? x: y;
        }

        template<> //eexplicit specialization için içi boş => buna diamond(içi boş angular bracet) deniyor.
        const char* Max(const char* p1, const char *p2) //aynı ismi kullanmalısın
        //const char* Max<const char *>(const char* p1, const char *p2) //aynı ismi kullanmalısın
        {
                std::cout<<"explicit spec func.\n";
            return std::strcmp(p1,p2) > 0 p1 : p2;
        }
        
        /* Yorum Baslik:Sınıf şablonu için ana template interface ile
        explicit specialization da başka isimli fonksiyonlar olabilir   
        
         */
        template<typename T>
        struct Myclass
        {
            Myclass()
            {
                    std::cout<<"primary template T is"<< typeid(T).name()<<"\n";
            }
        };
        template<>
        struct Myclass<int>
        {
            Myclass()
            {
                    std::cout<<"explicit specilization int\n";
            }
        };

        template<>
        struct Myclass<double>
        {
            Myclass()
            {
                    std::cout<<"explicit specilization int\n";
            }
        };
        
        int main()//main'de cagir!!!
        {
            std::cout<<"explicit_specialization main\n";
            std::cout<< Max(12,56)<<"\n";
            std::cout<< Max(56,12)<<"\n";
            std::cout<< Max(5.6,1.2)<<"\n";
            std::cout<< Max(10u,12u)<<"\n";
            
            

            std::cout<< Max("yesim","belgin")<<"\n"; //yesim döndü
            std::cout<< Max("belgin","yesim")<<"\n";   //belgin döndü bunlar string nesnesi olsaydı 
            //burada biz adresleri karşılaştırmış olduk ve pointerları karşılaştırmış olduk
            //const char * türü için 
            //1 - explicit spec  veririz 
            //2 - gerçek fonksiyon çağırılabilir.

            std::cout<< Max("yesim"s,"belgin"s)<<"\n"; //yesim döndü
            std::cout<< Max("belgin"s,"yesim"s)<<"\n"; //yesim döndü


            Myclass<unsigned> m1;
            Myclass<int> m2;
            Myclass<double> m3;
            return 0;
        }
    
    }// explicit_specialization sonu

} // namespace ders_31
