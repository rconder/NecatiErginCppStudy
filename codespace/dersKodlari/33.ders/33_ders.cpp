namespace ders_33
{
#include <iostream>
#include <type_traits>
#include <string>
#include <bitset>
    /* Yorum Baslik:variable_template
    Her bir oluşturduğu specialization bir değişken
     */
    namespace variable_template
    {
        /* Yorum Baslik:cpp_reference_ornek
         */
        namespace cpp_reference_ornek
        {
            template <typename T>
            constexpr T pi = T(3.141592653589L); // T floatsa float türden bir değişken
            // constexpr T pi = static_cast<T>(3.141592653589L);

            template <class T>
            T circular_area(T r)
            {
                return pi<T> * r * r; // pi<T> is a variable template instantiation
                // Tnin int olması durumunda oluşturuluyor
            }
            int main() // main'de cagir!!!
            {
                std::cout << "cpp_reference_ornek main\n";
                pi<double> return 0;
            }
        } // cpp_reference_ornek sonu
        /* Yorum Baslik:esas_kullanim_sekli
        Bazı meta fonksiyonlarda bazı değerlerin yazılmasını kolaylaştırmak.
         */
        namespace esas_kullanim_sekli
        {
            template <typename T>
            constexpr bool IsPointer_v = std::is_pointer<T>::value;
            // T'nin ne olduğunu bağlı olarak ilk değeri is_pointer'ın T açılımının value'sü ile değer vermiş olduk
            template <typename T>
            void func(T x)
            {
                std::is_pointer<T>::value; // yada std::is_pointer_v<T>
            }
            int main() // main'de cagir!!!
            {
                std::cout << "esas_kullanim_sekli main\n";
                std::is_pointer<int *>::value; // eğer template olan tür pointer ise value elemanı true olacak
                IsPointer_v<int *>;            // ile yukarıdaki gösterim aynı
                // std::is_pointer<int *>::value;
                return 0;
            }
        } // esas_kullanim_sekli sonu
    }     // variable_template sonu

    namespace perferct_forwarding
    {
        /* Yorum Baslik:

        Amacımız func'a gönderilcek argümanları doğrudan func'a göndermek yerine
        func'ı çağıracak fonksiyona çağrı yapmamız gerekiyor
        void func(P1, P2, P3); bu fonksiyona doğrudan çağırabiliriz
        call_func(x): bizden aldığı argümanlarla func'ı çağıracak
        tek iş bu olmak zorunda değil burada bizden aldığı argümanlarla çağırması gerekebilir.
        func'a gönderdiğimiz argümanları doğrudan göndermek ile
        call_func'un göndermesi arasında herhangi bir fark olmaması gerekiyor
        Yani parametre L-Val' ise l-val olarak göndermek zorunda func'ı doğrudan çağırmak ile call_func'a çağırmak ile
        arada herhangi bir fark olsun istemiyoruz.
        int main()
        {
            call_func(x,y, 12)
        }
         */
        class Myclass
        {
        public:
        private:
        };

        void func(Myclass &) // 1
        {
            std::cout << "func(Myclass&)\n";
        }
        void func(const Myclass &) // 2
        {
            std::cout << "func(const Myclass&)\n";
        }
        void func(Myclass &&) // 3
        {
            std::cout << "func(Myclass&&)\n";
        }

        void call_func(Myclass &x)
        {
            func(x);
        }
        void call_func(const Myclass &x)
        {
            func(x);
        }
        void call_func(Myclass &&x)
        {
            // func(x); //bu şekilde çağırırsak sol taraf referans olan çağırılır onun için
            // aşağıdaki gibi çağırmamız lazım
            // nedeni ise value category ile value type birbirinden farklı
            func(std::move(x));
        }
        /* Yorum Baslik:AMA AMA AMA Yukarıdaki yöntem kötü
        Eğer burada func fonksiyonun birden fazla parametresi olsaydı.
        func(T1 t1, T2 t2, T3 t3, T4 t4); Bu durumda mükemmel bir şekilde çağırılabilmesi için 4! tane fonksiyon yazılması gerekir.
        ve burada bu karmaşıklıkla baş edilemez. Ayrıca burada tek bir fonksiyon üzerinden değil bir'den fazla fonksiyon ile iletilebilirdi
        Moder C++ ile bunun tek yolu yollamaktı

        O zaman bunu basitleştirecek bir yapıya ihtiyacımız var
        Burada yapılan olay derleme zamanına yönelik bir mekanizma var
        bunun için
        template<typename T, typename U, typename V, typename W>
        void call_func(T&& t, U&&,u,  V&& v, W&& w )
        {
            func(std::forward<T>(x),std::forward<U>(u),std::forward<V>(v),std::forward<W>(w));
        }
         */
        template <typename T>
        void call_func_wrong(T x) // Burada her zaman L'value ile gönderilmiş olur
        // constluk da düştü, sağ taraf değeri ile çağırılmada düştü.
        {
            func(x);
        }
        template <typename T>
        void call_func_wrong2(T &x) // Burada her zaman L'value ile gönderilmiş olur
        // Sentaks hatası yaratır
        //
        {
            func(x);
        }
        template <typename T>
        void call_func_wrong3(T &&x) // Burada her zaman L'value ile gönderilmiş olur
        // Son fonksiyonda sağ referansı sol referans yapıyor.
        //
        {
            func(x);
        }

        // forward fonksiyon şablonu
        template <typename T>
        T &&Forward(typename std::remove_reference<T>::type &param)
        {
            return static_cast<T &&>(param);
        }
        // forward fonksiyon şablonu sonu

        // Fonksiyonun her türlü argümanı kabul etmesi için universal referans olmalı
        template <typename T>
        void call_func_perfect_forwarding(T &&x)
        {
            func(std::forward<T>(x)); // std::forward bir fonksiyon şablonu
            // ilki deductionla çıkarılamadığo için ilk argümanın türün ne olduğu söylenmek zorunda
            func(Forward<T>(x));
        }

        int main()
        {
            Myclass m;
            const Myclass cm;
            func(m);         // 1 numaralı fonksiyon çağırılır
            func(cm);        // 2 numaralı fonksiyon çağırılır
            func(Myclass{}); // 3 numaralı fonksiyon çağırılır

            call_func(m); // buradaki çağırıların üstteki ile aynı şekilde gerçekleşmesini istemiyoruz
            call_func(cm);
            call_func(Myclass{});
        }
        /* Yorum Baslik:en_tipik_ornegi
        Container sınıfların emblace fonksiyonları
        bir container'a ekleme yapmak için argümanları kullanarak nesne oluşturuyor ve onu da copy ctor ile
        container'ın oluşturduğu bellek alanında oluşturuluyor
        vector<Fighter> fvec;
        Fighter f(a,b,c,d);
        fvec.push_back(f); buraya fighter nesnesini değilde biz argümanları yolluyalım ve
        bu argümanları kullanarak container'ın kullandığı bellek alanında yapılması
        fvec_emplace_back(a,b,c,d); perfect forwarding ile container'ın bellek alanında Fighter'ın ctorunun
        çağırılmasını sağlıyor.
         */
        template <typename T>
        namespace hatali_kullanim
        {
            class Myclass
            {
            public:
                void func(T &&); // Bu universal referans değil
            private:
            };
            class Vector
            {
            public:
                template <typename U> // bu şekilde yapıyoruz.
                void emplace_bac(U &&u);
            };

            template <typename T>
            void func(const T &&); // bu forwarding referans parametre değil!!!!!;

            int main() // main'de cagir!!!
            {
                std::cout << "en_tipik_ornegi main\n";
                Myclass<int> x;
                x.func(x);
                return 0;
            }
        } // en_tipik_ornegi sonu
    }     // namespace perferct_forwarding

    namespace variadic_templateler
    {
        /* Yorum Baslik:
        tüm hepsi için ortak yapı genel olarak bu
        yani template'in kaç parametresi varsa o kadar sayıda template argümanı verebiliyoruz.

        template <typename T>
        class Myclass{};

        int main()
        {
            Myclass<int> x;
        }

        Öyle bir template olsunki o template'den kodu üretilecek kod istediği kadar argüman alabilsin
        yani
        Myclass<>
        Myclass<int>
        Myclass<int, double>
        Myclass<int, double, long>
        gibi gibi en basitinden emblace fonksiyonları
        örneğin öyle bir fonksiyon yazılması lazımki istediğimiz kadar argüman göndermemiz lazım

        C'de variadic fonksiyon için kaç tane argüman gönderdiğimizi söylüyoruz
        Öyle bir templateki dilediğimiz kadar template argümanı belirleyebiliyoruz

         */
        /* Yorum Baslik:tuple_en_belirgin
        make_uniqe'te öyle
         */
        namespace tuple_en_belirgin
        {
            std::tuple<int> x1;
            std::tuple<double, double> x2;
            std::tuple<double, double, int> x3;
            std::tuple<double, double, int, int> x4;

            int main() // main'de cagir!!!
            {
                std::cout << "tuple_en_belirgin main\n";
                return 0;
            }

        } // tuple_en_belirgin sonu
        /* Yorum Baslik:sentaksi
        Sizeof operatoru
         */
        namespace sentaksi
        {

            template <typename... Args> //... -> elipsis C'de variadic macrolarda ve fonksiyonlarda kullanılıyor.
            // exception handling'de catch-all bloğu oluşturulurken oluşuyor ve buna template parameter pack deniyor.
            //  Buradaki args ismi template tür paramter paketini temsil ediyor ve burada birden fazla tür olabilir
            class Myclass
            {
            public:
            private:
            };
            template <typename... Ts> // template paramtrelerinin oluşturduğu paket
            void func(Ts... args)     // Bu fonksiyonun da variadicte kaç tane template parametresi var ise
            // func fonksiyonun da o kadar parametresi var
            // fonksiyon şablonun fonksiyon parametreleri referans değil
            // Ts&...args => sol referans
            // Ts&&...args => universal referans
            {
                sizeof...(Ts); // bir compile time sabiti ve pakette kaç üye var onu gösteriyor
                sizeof...(args);
                // Dilin kurallarınca garanti altına alınmış ve derleyici kendi yazdığı kodda
                // bunu virgüllerle ayrılmış yapıya dönüştürüyor
                // pack expansion deniyor.
                std::tuple<Ts...> x; // burada 3 tane type parametresi var ise (int double, long açılımım olur)
                std::cout << typeid(x).name();
                constexpr auto val = sizeof...(args); // eğer constexpr sentaks hatası olurdu
            }

            template <typename... Ts>
            class Mycls : public Nec<Ts...>
            {

            } template <int... X>
            class intVarMyclass
            {
            };

            template <typename... Ts>
            class Nec
            {
            public:
                constexpr static int value = sizeof...(Ts);

            private:
            };

            template <typename T, typename... Ts>
            std::unique_ptr<T> MakeUnique(Ts &&...args)
            {
            }

            int main() // main'de cagir!!!
            {
                std::cout << "sentaksi main\n";
                Myclass<int, int, double> x;
                constexpr auto x = Nec<int, int>::value;
                constexpr auto x = Nec<int, int, double, double>::value;
                Mycls<int, int, int> // kalıtım yoluyla int int int Nec classından elde ediliyor.
                    intVarMyclass<1> m1;
                intVarMyclass<1, 2, 3, 4> m2;
                return 0;
            }
        } // sentaksi sonu
        /* Yorum Baslik:oruntuler
        Expansion loci paketi.
         */
        namespace oruntuler
        {
            template <typename... Ts>
            void func(Ts... args)
            {
                foo(args...);   // foo(p1,p2,p3,p4); şeklinde çağırmış olacaktık.
                foo(&args...);  // foo(&p1,&p2,&p3,&p4); şeklinde çağırmış olacaktık.
                foo(++args...); // foo(++p1,++p2,++p3,++p4); şeklinde çağırmış olacaktık.
            }
            int main() // main'de cagir!!!
            {
                std::cout << "oruntuler main\n";
                return 0;
            }

        } // oruntuler sonu

        /* Yorum Baslik:nasil_kullanilabiliriz
         */
        namespace nasil_kullanilabiliriz
        {
            // recursive fonksiyon oluşturma tekniği
            /* Yorum Baslik: variadic parametreye sahip fonksiyon şablonundan
            derleyiciye 2,3,4,5,6,... fonksiyon yazıyor ve burada gerçek fonksiyon veya
            variadic fonksiyon kullanıoyruz
            1. template parametresi variadic değil
            2. template parametresi ise variadic

             */
            // tek argümanla çağırılan print fonksiyonu bu
            template <typename T>
            void print(const T &r)
            {
                std::cout << r << "\n";
            }
            // print x d 9L için
            template <typename T, typename... Ts>
            void print(const T &r, const Ts &...args) // r = x olarak gönderildi args için ise d 9L gönderildi
            {
                std::cout << "__FUNCSIG__: " << __FUNCSIG__ << " \n"; // burada funcsig fonksiyonun makrosuna açılıyor
                print(r);
                print(args...); // daha sonra burada d ve 9L gönderilmiş olacak
                // parametre paketinde 1 tane argüman kaldığında
                // bu fonksiyon şablonundan yeni fonksiyon yazmak yerine
                // yukarıdaki fonksiyonu yazarak tamamlanıyor.
            }
            template <typename T>
            T summer(T v)
            {
                return v;
            }
            template <typename T, typename... Args>
            T summer(T &first, const Args &...args)
            {
                return first + summer(args...);
            }
            // initializer_list sınfı ile
            template <typename... Ts>
            void print_2(const Ts &...args)
            {
                // 1            (std::cout<< args)...//((std::cout<< p1),(std::cout<< p2),.....
                // 2                ((std::cout<< args), 0)...//((std::cout<< p1), 0),((std::cout<< p2), 0)
                // parantez içindeki , operator oldu
                // C'de sequence point oluyor önce sol operandı olan ifade yürütülecek daha sonra
                // ve ürettiği değer sağ ifadenin değeri
                // 3         int a[] = {(std::cout<<args,0)...}; //bu durumda parametre paketinde 4 elemanlı bir dizi oluşturulacak
                // ve dizinin tüm elemanları 0 sol operandı olan ifadeyi yürütmek zorunda
                (void)std::initializer_list<int>{(std::cout << args << " ", 0)...};
            }
            // fold expression (katlama ifadeleri)
            // constexpr if compile time if de örneklenecek
            template<typename ...Ts>
            void foon(Ts &&... args)
            {
            //    std::forwad<Ts>(args)...//std::forwad<A>(p1),std::forwad<B>(p2) 
                std::tuple<Ts...> x(args...);
            }
            template<typename ...Ts>
            void funcy(Ts &&... args)
            {
            //    std::forwad<Ts>(args)...//std::forwad<A>(p1),std::forwad<B>(p2) 
                foo(std::forwad<Ts>(args)...);
            }

            int main() // main'de cagir!!!
            {
                std::cout << "nasil_kullanilabiliriz main\n";
                int x = 10;
                double d = 23.5;
                print(x, d, 9L);
                print(x, d, 9L, "necati");
                std::string str1{"cem"};
                print(x, d, 9L, "necati", str1);
                print(x, d, 9L, "necati", str1, bitset<16>{432});
                print("===================================\n");
                std::cout < summer(10, 20, 30, 80, 17) << "\n";
                std::string s1 = "nec", s2 = "ati", s3 = "Er";
                std::cout < summer(s1, s2, s3, "gin") << "\n";
                print("===================================\n");
                print_2(12);
                print_2(12, 5.6)
                    print_2(12, 5.6, "oguzhan", bitset<16>(562));
                return 0;
            }
        } // nasil_kullanilabiliriz sonu
    } // namespace variadic_


    /* Yorum Baslik:STL : Standard Template Library
    STL aslında C++ standartın kütüphanesinin tamamı olması    
    ============================================================================================
    =     Containers : Veri yapılarını implemente edilen sınıf şablonları.                     =
    ============================================================================================
    Kaç container var?
    Sequence containers
    =============================
    --vector: dinamik dizi veri yapılarımız
    --dequeu: dinamik dizilerin dizisi 
    --list: double linked list: 2 pointer var biri bir sonrakini diğeri de bir öncekini gösteriyor 
    --forward_list: tekli bağlı liste 
    --array: c dizilerini sarmalayan bir sınıf şablonu ve stl'in container gerekliklerini de sağlıyor
    --string: yazı işlemleri için özelleştirilmiş bir dizi sınıfı
    =============================
    Associative containers
    ===============================
    --set: Bir anahtar var ve bu anahtarı kullanarak logaritmik karmaşıklıkta
    --multi_set: bir anahtardan bir den fazla olabiliyor 
    binary search tree 
    --map: key value pairi tutuyor ve anahtarla o value erişebiliyoruz
    --multi_map
    =======================
    Unordered 
    =======================
    unordered_set
    unordered_multi_set
    unordered_map
    unordered_multi_map
    =============================================================================================
    = Iterators: Konum tutan sınıf nesnesinin şablonları kaplarda tutulan üyelerin konumlarını  =
    = tutmak (pointerlarda iterator olarak kullanılabilir                                       =
    = STL'deki containerların iteratorlaru nested type'ı                                        =
    = 
    ============================================================================================
    Algorithms: Gerçekten algoritmaları implemente eden fonksiyon şablonları olarak kullanıyor.
    
    Bu 3 yapı birbirleri ile de ilişki
    Algoritmalar genelde parametreleri iteratorler olan ve containerlar üzerinde genişletilmiş işlem yapılıyor.

    --container adapters
    Eleman olarak container alıp onu abstract data interface yapıyor
    stack
    queue
    priority queu
    --iterator adapters
    --funciton adapters
    --function objects
    
     */


} // namespace ders_33
