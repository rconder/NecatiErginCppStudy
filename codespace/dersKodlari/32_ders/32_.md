# 32.ders

```cpp
namespace ders_32
{
#include <iostream>   
#include <utility>
    namespace most_vaxing_parse {
        /* Yorum Baslik:most_vaxing_parse
        Uydurulmuş bir terim
        Temel sentakstan kaynaklanan bir özel bir yapısı var
        eğer bir kod fonksiyon bildirimi ve hem de aynı zamanda değişken tanımlaması anlamına geliyorsa
        fonksiyon bildiriminin parsing'te önceliği var
        Bu kurala göre bir nesne tanımlaması yerine function declaration olabilir
        Ana akım derleyiciler artık bir uyarı mesajı veriyor
        -prototype function not called( was a variable definition intended! )

        Nasıl oluyorda B bx(A()); bir fonksiyon bildirimi oluyor.
        Bu C'de de C++'ta da fonksiyon türü ile fonksiyon adresi türü birbirinden farklı
        int(int) türü | int(*)(int) fonksiyon adresi türü
        eğer bir fonksiyon bildirilirken void func(int x[]) bildirilirse decay oluyor
        ve aynı şey fonksiyon türü içinde geçerli void func(int x()); bildirilirse derleyici bunu
        void func (int (*x)()) şeklinde ele alıyor.

        Peki most vaxing parse oluyorsa bunu nasıl düzeltiriz
        Modern C++ öncesi klasik yol:
        B bx((A())) olarak yazılıyordu

        Modern C++ ile
        B bx1(A{});
        B bx2{A()};
        B bx3{A{}};

        şeklinde yapılarak çözülebilir.


        */
        class A {};
        class B {
        public: B(A) {}
        };
        B   bx(A(*)()); //bununlar B bx(A()) ile aynı 
        A foo();
        int main()//main'de cagir!!!
        {
            std::cout << "most_vaxing_parse main\n";
            B bx(A());//ctor'a A türünden nesne olucak nesneyi vermek istiyoruz fakat
            //burada fonksiyon tanımlanmış lokal düzeyde yapılmış bir fonksiyon ismi
            //B bx(A(*)()); şeklinde bildirilmemesini bir farkı yok 
            //burada nesne oluşturmuyor
            bx(foo);
            bx(&foo);
            return 0;
        }
    }// most_vaxing_parse sonu

    namespace reference_qualifier {
        /* Yorum Baslik:reference_qualifier  | ref qualifier
        Öyle durumlar varki sınıfın bazı üye fonks. sadece L value expr kategorisindeki nesneler
        için çağırılmasını istiyoruz.
        Referenced qualified overload ile referenced qualified olmayan overload bir arada bulunamaz

        Peki neden
        -

         */
        class Myclass {
        public:
            void func(); // Hem R Value olan sınıf nesneleri için Hem de L Value sınıflar için
            //çapırılabilir.
            void foo()&;//Bu sadece L value için çağırılabilir R val için sentaks hatası
            void bar()const&;// const sınıf değeri için çağırılabiliyor
            void boo()&&;//Bu sadece R value için çağırılabilir L val için sentaks hatası
            //void boo(); //SENTAKS HATASI 
            //Myclass &operator=(const Myclass &)& = default;
            //sınıfın atama operator fonksiyonunun hem default ettirdik hem
            //de L value reference qualifier ekledik
        private:
        };
        int main()//main'de cagir!!!
        {
            std::cout << "reference_qualifier main\n";
            Myclass m1;
            m1.func();
            Myclass{}.func();

            Myclass{} = m1;//burada çağırılan sınıfın atama operator fonk.
            //burada qualifier taşımıyor
            //Bunun legal olması iyi bir fikir değil
            //illegal yapmak için
            return 0;
        }

    }// reference_qualifier sonu

    /* Yorum Baslik:
    En son explicit specializationı konuştuk:
    Derleyicicye specialization oluşturulmayacak benim sana verdiğim koddu kullanacaksın
    hem fonksiyon hem de sınıf şablonları için daha sık kullanılıyor.
    */
    /* Yorum Baslik:expilicit_sinif_specialization
     */
    namespace expilicit_sinif_specialization {
        template <typename T> //template <typenmae T, typeName U
        class Nec { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.

        public:

        private:

        };
        template<>
        class Nec<int>
        {
            //interface farklı olabilir
        };
        class Nec<double>
        {
            //interface farklı olabilir
        };


        template <typename T, typename U> //template <typenmae T, typeName U
        class Nec1 { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.
        public:
            Nec1()
            {
                std::cout << "primary template\n";
            }
        };
        template<>
        class Nec1<int, double>
        {
        public:
            Nec1()
            {
                std::cout << "exp. spec. <int,double>\n";
            }
        };
        template<int x>
        class Nec2 { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.
        public:
            Nec2()
            {
                std::cout << "primary template\n";
            }
        };
        template<>
        class Nec2<5>
        {
        public:
            Nec2()
            {
                std::cout << "exp. spec. <int,double>\n";
            }
        };


        int main()//main'de cagir!!!
        {
            std::cout << "expilicit_sinif_specialization main\n";
            Nec1<int, int> n1;
            Nec1<double, int> n2;
            Nec1<int, double> n3;
            Nec2<3> m1;
            Nec2<4> m2;
            Nec2<5> m3;
            Nec2<1> m4;
            return 0;
        }

        /* Yorum Baslik: TMP
        template meta programming
        bazı değerlerin ve türlerin hesaplanması ile alakalı bir alan

        Type traits için anlaşılabilmesi ve kullanılması için bahsedilecek.
        Modern c++ ile bir çok araç eklendi

         */

        namespace TMP_teknikleri {
            /* Yorum Baslik:TMP_teknikleri
            Meta function. compile time da bir değer üretmek ve tür bilgisi elde etmek için oluşturulan sınıflara meta function deniyor.
            eskiden constexpr yokken faktiriyel değerini compile time da hesaplatmak istiyoruz
             */
            template <int n>
            struct Factoriel
            {
                const static int value = n * Factoriel<n - 1>::value; //static veri elemanı const ise ilk değer verilebiliyor
                // 5 * factoriel<4> 
                // 5 * 4 * 3 * 2 * 1 acilimi için ve bu şekilde gidicek burada recursive bir yapı var
                //compile time recursivitesi 
                //Burada derleyicinin yeni bir sınıf oluşturmasını explicit specilization ile engelliyebiliyoruz
                //bu durumda
            };

            template<>
            struct Factoriel<0>
            {
                const static int value = 1;

            };
            int main()//main'de cagir!!!
            {
                std::cout << "TMP_teknikleri main\n";
                Factoriel<5>::value;
                return 0;
            }

            /* Yorum Baslik:sifir_dan_100_e_kadar_ekrana_yazdir
             */
            namespace sifir_dan_100_e_kadar_ekrana_yazdir {
                struct Nec
                {
                    Nec()
                    {
                        static int x = 0;
                        std::cout << x++;
                    }
                };

                template<int n>
                struct Nec2 :public Nec2<n - 1>
                {
                    Nec2()
                    {
                        std::cout << n << " ";
                    }
                };

                template<>
                struct Nec2<0>
                {

                };
                int main()//main'de cagir!!!
                {
                    std::cout << "sifir_dan_100_e_kadar_ekrana_yazdir main\n";
                    Nec a[100];
                    Nec2<100> x;
                    return 0;
                }
            }// sifir_dan_100_e_kadar_ekrana_yazdir sonu

            /* Yorum Baslik:
            co
             */
            namespace tur_hesaplama {
                //eğer TMP tür hesaplamak ise burada ki türe type ismini veriyoruz
                int main()//main'de cagir!!!
                {
                    std::cout << " main\n";
                    return 0;
                }

            }//  sonu
        }// TMP_teknikleri sonu

        /* Yorum Baslik:fonksiyonlar_icin
         */
        namespace fonksiyonlar_icin {
            template<typename T>
            void func(const T&)
            {
                std::cout << "primary template\n";
            }
            template <>
            void func(const int&)
            {
                std::cout << "explicit speecialization\n";
            }
            void func(double)
            {
                std::cout << "ordinary function\n";
            }
            int main()//main'de cagir!!!
            {
                std::cout << "fonksiyonlar_icin main\n";
                func(10); //fonksiyon şablonu seçilcek ve int türü için explicit spec kullanılacak
                func(0.42); //arrgüman olarak double gönderildiğinden ordinary function çağırılcak
                func('a'); //char türden bir çağrı yaptık ve primary template'ten bir spec oluşturulacak
                func("10"); //

                return 0;
            }

            namespace programcidan_9_yanlis_cevapladigi_soru {
                /* Yorum Baslik:programcidan_9
                Explicit specilization overload resulotion'a katılmıyor
                !!!!!Fonksiyon şablonu seçildikten sonra yazılımcı tarafından verilen kodun çalışması için
                O yüzden 3 çağırılıoyr
                 */
                template<typename T>
                void func(T)
                {
                    std::cout << "1\n";
                }
                template<>
                void func(int*)
                {
                    std::cout << "2\n";
                }
                template<typename T>
                void func(T*)
                {
                    std::cout << "3\n";
                }

                template<typename T>
                void foo(T)
                {
                    std::cout << "1\n";
                }
                template<typename T>
                void foo(T*)
                {
                    std::cout << "3\n";
                }
                template<>
                void foo(int*) //bu explicit spec foo 3'tekinin explicit specilization
                    //T'nin int olması durumunda bu kullanılacak
                    //eğer bu func'taki gibi olsaydı bu func(T)'nin explicit spec
                {
                    std::cout << "2\n";
                }

                template<typename T>
                void bar(T)
                {
                    std::cout << "1\n";
                }
                template<>
                void bar(int*)
                {
                    std::cout << "2\n";
                }
                template<typename T>
                void bar(T*)
                {
                    std::cout << "3\n";
                }
                template<>
                void bar(int*)
                {
                    std::cout << "4\n";
                }
                /* Yorum Baslik:her iki template içinde explicit spec var
                ve daha spesifik olarak olan seçiliyor.
                 */
                int main()//main'de cagir!!!
                {
                    std::cout << "programcidan_9 main\n";
                    int* p = nullptr;
                    func(p);
                    foo(p);
                    bar(p);
                    return 0;
                }
            }// programcidan_9 sonu
        }// fonksiyonlar_icin sonu

        /* Yorum Baslik:sinifin_uye_fonksiyonu_icin
         */
        namespace sinifin_uye_fonksiyonu_icin {

            template <typename T>
            struct Nec
            {
                void func() { std::cout << "primary template\n"; }
            };

            template <>
            void Nec<double>::func() { std::cout << "explicit spec for Nec<double>\n"; }

            int main()//main'de cagir!!!
            {
                std::cout << "sinifin_uye_fonksiyonu_icin main\n";
                Nec<int>{}.func();
                Nec<double>{}.func();

                return 0;
            }

        }// sinifin_uye_fonksiyonu_icin sonu

        /* Yorum Baslik:static_veri_ele
        static bir veri elamanı konunca
        her specialization için ayrı bir veri elemanı var
         */
        namespace static_veri_ele {

            template<typename T>
            class A
            {
            public:
                static int x;
                inline static int y{};
            };
            template<typename T>
            int A<T>::x = 99;

            template<>
            int A<int>::x = 20;

            int main()//main'de cagir!!!
            {
                std::cout << "static_veri_ele main\n";
                std::cout << "A<double>::x: " << A<double>::x << " \n";
                std::cout << "A<int>::x: " << A<int>::x << " \n\n";

                std::cout << "A<double>y++: " << A<double>::y++ << " \n";
                std::cout << "A<double>y++: " << A<int>::y++ << " \n";
                std::cout << "A<double>y++: " << A<long>::y++ << " \n";
                std::cout << "A<double>y++: " << A<double>::y++ << " \n";
                std::cout << "A<double>y++: " << A<long>::y++ << " \n";

                return 0;
            }
        }// static_veri_ele sonu
    }// expilicit_sinif_specialization sonu

    namespace partial_specilization {
        /* Yorum Baslik:partial_specilization
        Sadece sınıf şablonları için var
        Explicit spec'te template argümanın belirli bir tür olması koşulunda
        o spec'in kodunu derleyiciye veriyoruz.
        fakat partial_spec'te bir tür kümesi için veriyoruz
        örneğin T'nin pointer olması durumunda bunu kullan
        T'nin dizi olması durumunda bunu kullan
        partial=> kısmı özelleştirme
         */
        template <typename T>
        class Myclass {
        public:
            Myclass()
            {
                std::cout << "primary template\n";
            }
        };

        template <typename T>
        class Myclass<T*>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
        {
        public:
            Myclass()
            {
                std::cout << "partial spec T *n";
            }

        };

        template <typename T>
        class Myclass<T&>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
        {
        public:
            Myclass()
            {
                std::cout << "partial spec T &n";
            }

        };

        template <typename T>
        class Myclass<T&&>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
        {
        public:
            Myclass()
            {
                std::cout << "partial spec T &&n";
            }

        };
        template <typename T>
        class Myclass<T[5]>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
        {
        public:
            Myclass()
            {
                std::cout << "partial spec T &&n";
            }

        };

        template <typename T, typename U>
        class A {
        public:

            A()
            {
                std::cout << " primary spec A\n";
            }
        };
        template <typename T>
        class A<T, T> {
        public:
            A()
            {
                std::cout << " partial  spec A\n";
            }
        };
        template <typename T>
        class A<T, int> {
        public:
            A()
            {
                std::cout << " partial  spec A\n";
            }
        };
        template<typename T>
        class A<T*, T*> {
        public:
            A()
            {
                std::cout << " partial  spec A\n";
            }
        };
        template<typename T, typename U>
        class Myclass<std::pair<T, U>>
        {
        public:
            Myclass()
            {
                std::cout << "pair partial spece\n";
            }
        };

        int main()//main'de cagir!!!
        {
            std::cout << "partial_specilization main\n";
            Myclass<int> m1;
            Myclass<int*> m2;
            Myclass<int**> m3;
            Myclass<double> m4;
            Myclass<double*> m4;
            Myclass<int&> m5;
            Myclass<int&&>m6;
            Myclass<double[5]>m7;
            Myclass<int[6]>m8;
            Myclass<int[5]>m9;
            Myclass<std::pair<int, double>> m10;

            A<int, double> a1;
            A<int, int> a2;
            A<int*, int*>a3;
            A<int*, double*>a4;
            A<double, int> a5;
            A<int, double> a6;
            A<long*, long*>a7;
            return 0;
        }
        /* Yorum Baslik:ismi_power_olan_meta_fonksiyon
        compile time da A üzeri B hesaplaması yapsın
         */
        namespace ismi_power_olan_meta_fonksiyon {

            int main()//main'de cagir!!!
            {
                std::cout << "ismi_power_olan_meta_fonksiyon main\n";
                constexpr auto val = power<2, 5>::value;
                constexpr auto val = power<5, 7>::value;
                return 0;
            }
        }// ismi_power_olan_meta_fonksiyon sonu
    }// partial_specilization sonu

    /* Yorum Baslik:
    Burada sınıf şablonunun üye fonksiyonu ve template fonksiyonun parametresi ile belirleniyor.
     */
    namespace member_template {
        template<typename T>
        class Myclass {
        public:
            void func(Myclass);
            template<typename U>//Burada başka bir template parametre ismi vermemiz gerekiyor
            //bu şekilde member template yapılıyor.
            void func(Myclass<U> x)
            {
                std::cout << "typeid(*this) : " << typeid(*this).name();
                std::cout << "typeid(*this) : " << typeid(x).name();
            }//

        };
        int main()//main'de cagir!!!
        {
            std::cout << " main\n";
            Myclass<int> m1, m2;
            Myclass<double> m3;
            //m3.func(m1);//SENTAKS HATASI geçersiz çünkü myclass'ın int açılımı ayrı double açılımı ayrı bir sınıf
            m2.func(m1);
            m3.func(m1);
            //
            return 0;
        }
        namespace ders_32
        {
#include <iostream>   
#include <utility>
            namespace most_vaxing_parse {
                /* Yorum Baslik:most_vaxing_parse
                Uydurulmuş bir terim
                Temel sentakstan kaynaklanan bir özel bir yapısı var
                eğer bir kod fonksiyon bildirimi ve hem de aynı zamanda değişken tanımlaması anlamına geliyorsa
                fonksiyon bildiriminin parsing'te önceliği var
                Bu kurala göre bir nesne tanımlaması yerine function declaration olabilir
                Ana akım derleyiciler artık bir uyarı mesajı veriyor
                -prototype function not called( was a variable definition intended! )

                Nasıl oluyorda B bx(A()); bir fonksiyon bildirimi oluyor.
                Bu C'de de C++'ta da fonksiyon türü ile fonksiyon adresi türü birbirinden farklı
                int(int) türü | int(*)(int) fonksiyon adresi türü
                eğer bir fonksiyon bildirilirken void func(int x[]) bildirilirse decay oluyor
                ve aynı şey fonksiyon türü içinde geçerli void func(int x()); bildirilirse derleyici bunu
                void func (int (*x)()) şeklinde ele alıyor.

                Peki most vaxing parse oluyorsa bunu nasıl düzeltiriz
                Modern C++ öncesi klasik yol:
                B bx((A())) olarak yazılıyordu

                Modern C++ ile
                B bx1(A{});
                B bx2{A()};
                B bx3{A{}};

                şeklinde yapılarak çözülebilir.


                */
                class A {};
                class B {
                public: B(A) {}
                };
                B   bx(A(*)()); //bununlar B bx(A()) ile aynı 
                A foo();
                int main()//main'de cagir!!!
                {
                    std::cout << "most_vaxing_parse main\n";
                    B bx(A());//ctor'a A türünden nesne olucak nesneyi vermek istiyoruz fakat
                    //burada fonksiyon tanımlanmış lokal düzeyde yapılmış bir fonksiyon ismi
                    //B bx(A(*)()); şeklinde bildirilmemesini bir farkı yok 
                    //burada nesne oluşturmuyor
                    bx(foo);
                    bx(&foo);
                    return 0;
                }
            }// most_vaxing_parse sonu

            namespace reference_qualifier {
                /* Yorum Baslik:reference_qualifier  | ref qualifier
                Öyle durumlar varki sınıfın bazı üye fonks. sadece L value expr kategorisindeki nesneler
                için çağırılmasını istiyoruz.
                Referenced qualified overload ile referenced qualified olmayan overload bir arada bulunamaz

                Peki neden
                -

                 */
                class Myclass {
                public:
                    void func(); // Hem R Value olan sınıf nesneleri için Hem de L Value sınıflar için
                    //çapırılabilir.
                    void foo()&;//Bu sadece L value için çağırılabilir R val için sentaks hatası
                    void bar()const&;// const sınıf değeri için çağırılabiliyor
                    void boo()&&;//Bu sadece R value için çağırılabilir L val için sentaks hatası
                    //void boo(); //SENTAKS HATASI 
                    //Myclass &operator=(const Myclass &)& = default;
                    //sınıfın atama operator fonksiyonunun hem default ettirdik hem
                    //de L value reference qualifier ekledik
                private:
                };
                int main()//main'de cagir!!!
                {
                    std::cout << "reference_qualifier main\n";
                    Myclass m1;
                    m1.func();
                    Myclass{}.func();

                    Myclass{} = m1;//burada çağırılan sınıfın atama operator fonk.
                    //burada qualifier taşımıyor
                    //Bunun legal olması iyi bir fikir değil
                    //illegal yapmak için
                    return 0;
                }

            }// reference_qualifier sonu

            /* Yorum Baslik:
            En son explicit specializationı konuştuk:
            Derleyicicye specialization oluşturulmayacak benim sana verdiğim koddu kullanacaksın
            hem fonksiyon hem de sınıf şablonları için daha sık kullanılıyor.
            */
            /* Yorum Baslik:expilicit_sinif_specialization
             */
            namespace expilicit_sinif_specialization {
                template <typename T> //template <typenmae T, typeName U
                class Nec { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.

                public:

                private:

                };
                template<>
                class Nec<int>
                {
                    //interface farklı olabilir
                };
                class Nec<double>
                {
                    //interface farklı olabilir
                };


                template <typename T, typename U> //template <typenmae T, typeName U
                class Nec1 { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.
                public:
                    Nec1()
                    {
                        std::cout << "primary template\n";
                    }
                };
                template<>
                class Nec1<int, double>
                {
                public:
                    Nec1()
                    {
                        std::cout << "exp. spec. <int,double>\n";
                    }
                };
                template<int x>
                class Nec2 { //burada sadece int ve double için istiyorsak sadece !class Nec;! ile bildirebiliriz.
                public:
                    Nec2()
                    {
                        std::cout << "primary template\n";
                    }
                };
                template<>
                class Nec2<5>
                {
                public:
                    Nec2()
                    {
                        std::cout << "exp. spec. <int,double>\n";
                    }
                };


                int main()//main'de cagir!!!
                {
                    std::cout << "expilicit_sinif_specialization main\n";
                    Nec1<int, int> n1;
                    Nec1<double, int> n2;
                    Nec1<int, double> n3;
                    Nec2<3> m1;
                    Nec2<4> m2;
                    Nec2<5> m3;
                    Nec2<1> m4;
                    return 0;
                }

                /* Yorum Baslik: TMP
                template meta programming
                bazı değerlerin ve türlerin hesaplanması ile alakalı bir alan

                Type traits için anlaşılabilmesi ve kullanılması için bahsedilecek.
                Modern c++ ile bir çok araç eklendi

                 */

                namespace TMP_teknikleri {
                    /* Yorum Baslik:TMP_teknikleri
                    Meta function. compile time da bir değer üretmek ve tür bilgisi elde etmek için oluşturulan sınıflara meta function deniyor.
                    eskiden constexpr yokken faktiriyel değerini compile time da hesaplatmak istiyoruz
                     */
                    template <int n>
                    struct Factoriel
                    {
                        const static int value = n * Factoriel<n - 1>::value; //static veri elemanı const ise ilk değer verilebiliyor
                        // 5 * factoriel<4> 
                        // 5 * 4 * 3 * 2 * 1 acilimi için ve bu şekilde gidicek burada recursive bir yapı var
                        //compile time recursivitesi 
                        //Burada derleyicinin yeni bir sınıf oluşturmasını explicit specilization ile engelliyebiliyoruz
                        //bu durumda
                    };

                    template<>
                    struct Factoriel<0>
                    {
                        const static int value = 1;

                    };
                    int main()//main'de cagir!!!
                    {
                        std::cout << "TMP_teknikleri main\n";
                        Factoriel<5>::value;
                        return 0;
                    }

                    /* Yorum Baslik:sifir_dan_100_e_kadar_ekrana_yazdir
                     */
                    namespace sifir_dan_100_e_kadar_ekrana_yazdir {
                        struct Nec
                        {
                            Nec()
                            {
                                static int x = 0;
                                std::cout << x++;
                            }
                        };

                        template<int n>
                        struct Nec2 :public Nec2<n - 1>
                        {
                            Nec2()
                            {
                                std::cout << n << " ";
                            }
                        };

                        template<>
                        struct Nec2<0>
                        {

                        };
                        int main()//main'de cagir!!!
                        {
                            std::cout << "sifir_dan_100_e_kadar_ekrana_yazdir main\n";
                            Nec a[100];
                            Nec2<100> x;
                            return 0;
                        }
                    }// sifir_dan_100_e_kadar_ekrana_yazdir sonu

                    /* Yorum Baslik:
                    co
                     */
                    namespace tur_hesaplama {
                        //eğer TMP tür hesaplamak ise burada ki türe type ismini veriyoruz
                        int main()//main'de cagir!!!
                        {
                            std::cout << " main\n";
                            return 0;
                        }

                    }//  sonu
                }// TMP_teknikleri sonu

                /* Yorum Baslik:fonksiyonlar_icin
                 */
                namespace fonksiyonlar_icin {
                    template<typename T>
                    void func(const T&)
                    {
                        std::cout << "primary template\n";
                    }
                    template <>
                    void func(const int&)
                    {
                        std::cout << "explicit speecialization\n";
                    }
                    void func(double)
                    {
                        std::cout << "ordinary function\n";
                    }
                    int main()//main'de cagir!!!
                    {
                        std::cout << "fonksiyonlar_icin main\n";
                        func(10); //fonksiyon şablonu seçilcek ve int türü için explicit spec kullanılacak
                        func(0.42); //arrgüman olarak double gönderildiğinden ordinary function çağırılcak
                        func('a'); //char türden bir çağrı yaptık ve primary template'ten bir spec oluşturulacak
                        func("10"); //

                        return 0;
                    }

                    namespace programcidan_9_yanlis_cevapladigi_soru {
                        /* Yorum Baslik:programcidan_9
                        Explicit specilization overload resulotion'a katılmıyor
                        !!!!!Fonksiyon şablonu seçildikten sonra yazılımcı tarafından verilen kodun çalışması için
                        O yüzden 3 çağırılıoyr
                         */
                        template<typename T>
                        void func(T)
                        {
                            std::cout << "1\n";
                        }
                        template<>
                        void func(int*)
                        {
                            std::cout << "2\n";
                        }
                        template<typename T>
                        void func(T*)
                        {
                            std::cout << "3\n";
                        }

                        template<typename T>
                        void foo(T)
                        {
                            std::cout << "1\n";
                        }
                        template<typename T>
                        void foo(T*)
                        {
                            std::cout << "3\n";
                        }
                        template<>
                        void foo(int*) //bu explicit spec foo 3'tekinin explicit specilization
                            //T'nin int olması durumunda bu kullanılacak
                            //eğer bu func'taki gibi olsaydı bu func(T)'nin explicit spec
                        {
                            std::cout << "2\n";
                        }

                        template<typename T>
                        void bar(T)
                        {
                            std::cout << "1\n";
                        }
                        template<>
                        void bar(int*)
                        {
                            std::cout << "2\n";
                        }
                        template<typename T>
                        void bar(T*)
                        {
                            std::cout << "3\n";
                        }
                        template<>
                        void bar(int*)
                        {
                            std::cout << "4\n";
                        }
                        /* Yorum Baslik:her iki template içinde explicit spec var
                        ve daha spesifik olarak olan seçiliyor.
                         */
                        int main()//main'de cagir!!!
                        {
                            std::cout << "programcidan_9 main\n";
                            int* p = nullptr;
                            func(p);
                            foo(p);
                            bar(p);
                            return 0;
                        }
                    }// programcidan_9 sonu
                }// fonksiyonlar_icin sonu

                /* Yorum Baslik:sinifin_uye_fonksiyonu_icin
                 */
                namespace sinifin_uye_fonksiyonu_icin {

                    template <typename T>
                    struct Nec
                    {
                        void func() { std::cout << "primary template\n"; }
                    };

                    template <>
                    void Nec<double>::func() { std::cout << "explicit spec for Nec<double>\n"; }

                    int main()//main'de cagir!!!
                    {
                        std::cout << "sinifin_uye_fonksiyonu_icin main\n";
                        Nec<int>{}.func();
                        Nec<double>{}.func();

                        return 0;
                    }

                }// sinifin_uye_fonksiyonu_icin sonu

                /* Yorum Baslik:static_veri_ele
                static bir veri elamanı konunca
                her specialization için ayrı bir veri elemanı var
                 */
                namespace static_veri_ele {

                    template<typename T>
                    class A
                    {
                    public:
                        static int x;
                        inline static int y{};
                    };
                    template<typename T>
                    int A<T>::x = 99;

                    template<>
                    int A<int>::x = 20;

                    int main()//main'de cagir!!!
                    {
                        std::cout << "static_veri_ele main\n";
                        std::cout << "A<double>::x: " << A<double>::x << " \n";
                        std::cout << "A<int>::x: " << A<int>::x << " \n\n";

                        std::cout << "A<double>y++: " << A<double>::y++ << " \n";
                        std::cout << "A<double>y++: " << A<int>::y++ << " \n";
                        std::cout << "A<double>y++: " << A<long>::y++ << " \n";
                        std::cout << "A<double>y++: " << A<double>::y++ << " \n";
                        std::cout << "A<double>y++: " << A<long>::y++ << " \n";

                        return 0;
                    }
                }// static_veri_ele sonu
            }// expilicit_sinif_specialization sonu

            namespace partial_specilization {
                /* Yorum Baslik:partial_specilization
                Sadece sınıf şablonları için var
                Explicit spec'te template argümanın belirli bir tür olması koşulunda
                o spec'in kodunu derleyiciye veriyoruz.
                fakat partial_spec'te bir tür kümesi için veriyoruz
                örneğin T'nin pointer olması durumunda bunu kullan
                T'nin dizi olması durumunda bunu kullan
                partial=> kısmı özelleştirme
                 */
                template <typename T>
                class Myclass {
                public:
                    Myclass()
                    {
                        std::cout << "primary template\n";
                    }
                };

                template <typename T>
                class Myclass<T*>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
                {
                public:
                    Myclass()
                    {
                        std::cout << "partial spec T *n";
                    }

                };

                template <typename T>
                class Myclass<T&>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
                {
                public:
                    Myclass()
                    {
                        std::cout << "partial spec T &n";
                    }

                };

                template <typename T>
                class Myclass<T&&>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
                {
                public:
                    Myclass()
                    {
                        std::cout << "partial spec T &&n";
                    }

                };
                template <typename T>
                class Myclass<T[5]>//derleyici template argümanı bir pointer türü olması durumunda bunu kullan
                {
                public:
                    Myclass()
                    {
                        std::cout << "partial spec T &&n";
                    }

                };

                template <typename T, typename U>
                class A {
                public:

                    A()
                    {
                        std::cout << " primary spec A\n";
                    }
                };
                template <typename T>
                class A<T, T> {
                public:
                    A()
                    {
                        std::cout << " partial  spec A\n";
                    }
                };
                template <typename T>
                class A<T, int> {
                public:
                    A()
                    {
                        std::cout << " partial  spec A\n";
                    }
                };
                template<typename T>
                class A<T*, T*> {
                public:
                    A()
                    {
                        std::cout << " partial  spec A\n";
                    }
                };
                template<typename T, typename U>
                class Myclass<std::pair<T, U>>
                {
                public:
                    Myclass()
                    {
                        std::cout << "pair partial spece\n";
                    }
                };

                int main()//main'de cagir!!!
                {
                    std::cout << "partial_specilization main\n";
                    Myclass<int> m1;
                    Myclass<int*> m2;
                    Myclass<int**> m3;
                    Myclass<double> m4;
                    Myclass<double*> m4;
                    Myclass<int&> m5;
                    Myclass<int&&>m6;
                    Myclass<double[5]>m7;
                    Myclass<int[6]>m8;
                    Myclass<int[5]>m9;
                    Myclass<std::pair<int, double>> m10;

                    A<int, double> a1;
                    A<int, int> aa2;
                    A<int*, int*>a3;
                    A<int*, double*>a4;
                    A<double, int> a5;
                    A<int, double> a6;
                    A<long*, long*>a7;
                    return 0;
                }
                /* Yorum Baslik:ismi_power_olan_meta_fonksiyon
                compile time da A üzeri B hesaplaması yapsın
                 */
                namespace ismi_power_olan_meta_fonksiyon {

                    int main()//main'de cagir!!!
                    {
                        std::cout << "ismi_power_olan_meta_fonksiyon main\n";
                        constexpr auto val = power<2, 5>::value;
                        constexpr auto val = power<5, 7>::value;
                        return 0;
                    }
                }// ismi_power_olan_meta_fonksiyon sonu
            }// partial_specilization sonu

            /* Yorum Baslik:
            Burada sınıf şablonunun üye fonksiyonu ve template fonksiyonun parametresi ile belirleniyor.
             */
            namespace member_template {
                template<typename T>
                class Myclass {
                public:
                    void func(Myclass);
                    template<typename U>//Burada başka bir template parametre ismi vermemiz gerekiyor
                    //bu şekilde member template yapılıyor.
                    void func(Myclass<U> x)
                    {
                        std::cout << "typeid(*this) : " << typeid(*this).name();
                        std::cout << "typeid(*this) : " << typeid(x).name();
                    }//

                };
                int main()//main'de cagir!!!
                {
                    std::cout << " main\n";
                    Myclass<int> m1, m2;
                    Myclass<double> m3;
                    //m3.func(m1);//SENTAKS HATASI geçersiz çünkü myclass'ın int açılımı ayrı double açılımı ayrı bir sınıf
                    m2.func(m1);
                    m3.func(m1);
                    //
                    return 0;
                }
            }
            /* Yorum Baslik:tipik_ornek
            pair: iki tane aynı türden veya farklı türden değeri bir arada tutabilen bir sınıf değeri
            biz 2tane değeri birbiriyle ilişkili olarak tutmak istiyoruz ve aralarında özel bir ilişki yok
            buradaki amaç bu 2 değeri birbiriyle ilişkili olarak kullanmak bunun çoklusu ise tuple
            STL'de iki tane çok sık kullanılan
            pair'de iki öğe
            tuple'da ise istediğimiz kadar tutabiliyoruz.

            C'de Bir fonksiyonun 2 tane değer döndürmesini
            struct retVal{
                int x;
                double y;
            };

            struct retVal foo(void)//böyle 2 tane değişken döndürebiliriz
            {}
            ve böylece sadece int,double için döndürebiliriz

            Fakat C++'ta geri dönüş değeri istediğimiz gibi olabilir.
            En çok kullanıldığı yer burası

            diğer bir tipik kullanımı ise veri elemanın pair olması.

            Ağırlıkl
             */
            namespace tipik_ornek {
                template<typename T, typename U >
                struct Pair
                {
                    //Pair & operator=(const Pair&);//*this nensnesinin türü ile aynı tür
                    template<typename X, typename Y>
                    Pair& operator=(const Pair<X, Y>& other)
                    {
                        first = other.first; //burada firstlerin birbirine assignable olması lazım!!!!!
                        second = other.second;
                        return *this;
                    }
                    T first;
                    U second;
                };

                int main()//main'de cagir!!!
                {
                    std::cout << "tipik_ornek main\n";
                    std::pair<int, double> px;
                    px.first;//bunun türü int
                    px.second;//bunun türü second 
                    //default init edilebilir ve bunlar value init ediliyor
                    std::pair<int, std::string> ps;
                    std::cout << "p.first: " << ps.first << " \n";
                    std::cout << "ps.second.length(): " << ps.second.length() << " \n";
                    ps.first = 45;
                    ps.second = "mustafa"; //string atama operator fonksiyonu çağırılıyor
                    //ps.operator=() //member 
                    Pair<double, double> p1;
                    Pair<int, int> p2;
                    //p1 = p2;//bu legal değilken 
                    return 0;
                }

            }// tipik_ornek sonu
        }//  sonu
        /* Yorum Baslik:pair_ornekgi_cok_yaygin
        Sınıf şablonları için deduction kullanmak istiyoruz
        fonksiyon şablonu ile yapılabiliriz ve bütün bu kodlar compile time'da açılacak run time'a
        bir etkisi olmayacak

        Dolaylı olarak kullanabiliriz

        ve pair içinde bu yöntem kullanılabiliyor.

         */
        namespace pair_ornekgi_cok_yaygin {
            template<typename T, typename U>
            class Myclass {
            public:
                Myclass(const T&, const U&);

            };
            template<typename T, typename U>
            Myclass<T, U> make_myclass(const T& t, const U& u)
            {
                return Myclass<T, U>{t, u};
            }

            template<typename T, typename U>
            std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
            {
                return os << "[" << p.first << ", " << p.second << "]";

            }
            template<typename T, typename U >
            bool Operator < (const std::pair<T, U>& lhs, const std::pair<T, U>& rhs)
            {

                //return lhs.first< rhs.first || ; bu kodlar genelde 
                return lhs.first < rhs.first || !(rhs.first < lhs.first) && lhs.second < rhs.second;
                //birincil karşılaştırma  operatörü '<' ve genellikle kullanılıyor
            }


#include <bitset>
#include <iostream>
#include <string>
            int main()//main'de cagir!!!
            {
                std::cout << "pair_ornekgi_cok_yaygin main\n";
                //Myclass<int,double>mx;
                auto mx = make_myclass(12, 5.65);
                std::string str{ "ali" };
                double dval{};
                auto my = make_myclass(str, dval);


                std::pair<long, char> p2{ 32L,'A' };
                //C++20 ve daha s   onrası için
                std::pair p3{ 3.4f,6.7 };
                auto p4 = std::make_pair(34, 4.5);
                std::pair<std::pair<int, double>, std::pair<std::string, std::string>> xx;

                xx.first.second;
                /* Yorum Baslik:bundan sonraki derste kendi modülümüzü oluşturucağız
                ve pairin insertırı yok
                std::cout<<make_pair(12,4.5);
                bu yok
                 */
                std::cout << std::make_pair(std::make_pair(12, 4.5),
                    std::make_pair("ali", std::bitset<16>(23))) << "\n";
                std::pair p_1{ 3,4.5 };
                std::pair p_2{ 13,1.2 };
                std::cout << (p_1 < p_2)
                    return 0;
            }
        }// pair_ornekgi_cok_yaygin sonu
    }
    /* Yorum Baslik:alias_template
    Neden using typedef'e tercih edilmeli
    int(*)(const char *, const char *);
    typedef int(*FCMP)(const char *, const char *); fakat using ile
    using FCMP = int(*)(const char *, const char *); geri dönüş değeri int parametreleri const char const char olan bu

    --Typedef C'den geldiği için template haline getirilemiyor fakat
    using için bu mümkün



     */
    namespace alias_template {
        template<typename T>
        using Ptr = T*;
        template<typename T, int size>
        using Array = T[size];
        template<typename T>
        using Array5 = T[5];
        int main()//main'de cagir!!!
        {
            std::cout << "alias_template main\n";
            int x{};
            Ptr<int> p = x;//int *p ;
            Array<double, 5> a; //double a [5];
            Array<int, 20> b; //int b[20];
            Array<int, 20> a1[5]; //int a[5][20]
            Array<int> b;

            return 0;
        }

        /* Yorum Baslik:ihtiyac_noktasi
        Mesela sık sık pair türünü kullanacağız ve bu pair türleri hep aynı olucak
         */
        namespace ihtiyac_noktasi {
            template<typename T, typename U>
            class Myclass {};

            template<typename T>
            using Nec = Myclass<T, int>;

            template <typename T>
            using epair = std::pair<T, T>;
            int main()//main'de cagir!!!
            {
                std::cout << "ihtiyac_noktasi main\n";
                Nec<double> //Myclass<double,int>
                    epair<int> ep;//std::pair<int,int>
                /* Yorum Baslik: set kutuphanesi  3 template parametresine sahip bir tür

                set<int> x;
                fakat bazı durumlarda küçüktürle değil büyüktürle yapmak istersek
                std::set<int,st::greater<int>> myset; şeklinde yazmamız gerekiyor
                bunu alias template ile

                template<typename Key>
                using gSet=  std::set<Key, std::greater<Key>>;

                gset<int> myset;

                 */
                return 0;
            }
        }// ihtiyac_noktasi sonu

        /* Yorum Baslik:container_adaptoru: container :belirli verileri bir veri yapısı biçiminde tutan yapılar
        bir de container adaptör sınıfları var bunlar uyumlandırıcı bir containment nesnesini alark
        bir abstract veri yapısını oluşturuyor.
        Bunlar container'ı alıp stack, queue ve variaty-queue
        2.eleman ise container türü ve
        stack<int, deque<int>> açılımını kullanıyor büyük çoğunlukla bunda bir sorun yok
        Ama bazı durumlarda vector kullanmak istiyoruz
        std::stack<std::string, std::vector<std::string>> s_stack;
        yazma ve okuma zorluğu
        Nerede zahmet orada eziyet + risk :D
        Risk var ve Cpp gibi bir dilde bir şeyi yazmak yerine başka bir şey yazarsak ve
        niyet dışında bir kod oluşma riski var.


         */

        /* Yorum Baslik:type traits
        typename std::add_pointer<int>::type   
        template<typename T>
        using add_pointer_t = typename std::add_pointer<T>::type 
        add_pointer_t<int>
         */
        namespace container_adaptoru {
#include <stack>
            template<typename T>
            using stack = std::stack<T, std::vector<T>>;


            int main()//main'de cagir!!!
            {
                std::cout << "container_adaptoru main\n";
                //std::stack<int>;
                return 0;
            }
        }// container_adaptoru sonu
    }// alias_template sonu
} // namespace ders_32
```
