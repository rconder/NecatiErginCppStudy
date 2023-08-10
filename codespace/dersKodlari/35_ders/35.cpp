namespace ders_35
{
#include <iostream>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <vector>
 #include <list>
#include "nutility.h"
    /* Yorum Baslik:
    Lambda ifadesi nedir
    derleyici ifadenin bulnduuğu yerde bir sınıf tanımlar, tanımladığı sınıfa bir üye operator() işlevi yazar ve koddaki lambda ifadesini oluşturduğu
    sınıfın türünden bir geçici nesneye (temporary object) dönüştürür.

    PR value category'sinde bir nesne oluşturuyor

    int main()
    {
    //lambda expression
    derleyici burada local class sınıf tanımladı ve burada kendi oluşturduğu sınıf türünden
    nesneyi oluşturuyor.

    nested fonksiyona bir alternatif oluşturuyor
    }
     */
    namespace lambda_giris
    {
        /*
            Oluşturulan sınıfa: closure type deniyor.
            Oluşturulan nesneye: closure object deniyor.
            Burada biz sınıfın operator(){} fonsiyonunu kullanıyoruz
            ve buna lambda function deniyor
         */
         /* Yorum Baslik:sentaks_inceleme
          */
        namespace sentaks_inceleme {

            int main()//main'de cagir!!!
            {
                using namespace std;
                std::cout << "sentaks_inceleme main\n";
                //[]  -> LAMBDA ifadesinin olmazsa olmazı lambda introducer deniyor
                //içine yazılan ifadelere capture clause deniyor
                //<typename T> sentaksı C++20 ile eklendi
                //() -> derleyicinin yazacağı operator() fonksiyonun parametre parantezi mecburi değil
                //eğer anahtar sözcüklerden biri yoksa parantez mecburi değil
                //->return type, mutable,noexcept,constexpr ve hepsi bir arada bulunabilir.
                //{fonksiyonun anabloğunun kodu}
                //[]<typename T>()->int/mutable/noexcept/constepxr{}
                []() {}();//hiç bir şey yapmıyor sırf ilginçlik olsun diye 
                []() {};
                /*    [](){} bu ifadeyi geçici nesneye dönüştürdü ve
                () ifadesi ile operator overload fonksiyonu çağırılacaktı

                 */
                []() {std::cout << "ali";}();
                []() {return 1;}(); //burada deduction ile fonksiyonun geri dönüş değeri çıkarımını yapıp int yazdık
                auto f = [](int a) {return a * a;};//bu ifade sınıf türünden geçici nesne
                //f'in türü derleyici tarafından oluşturulan sınıfın türü
                /* Yorum Baslik:

                class xyzm13t_
                {
                    public:
                    int operator()(int a)
                    {
                        return a*a;
                    }
                };
                    - Fonksiyonun kodu lokalize edilmiş oluyor.
                auto f = xyzm13t_{};
                önemli bir nokta burada üye fonksiyon default olarak const bir üye fonksiyon
                Eğer bu sınıfın bir veri elemanı olası
                sınıfın veri elemanı mutable olduğunda const nesneler değiştirebilir anlamına geliyordu
                fakat buradaki mutable'ın anlamı derleyicinin yazdığı üye fonksiyonun non-const olmasını istiyorduysak
                auto f  = [](int a)mutable{return a*a;}; olarak kullanılabilir
                Sınıfın non-static veri elemanlarının değiştirilmesine istiyoruz
                 */
                cout << typeid(f).name() << "\n";
                std::cout << f.operator()(12) << "\n";
                std::cout << f(34) << "\n";
                /*
                kodu daha okunabilir için nesneye isim verebiliriz
                ama isim vermeden de çağırılabilir
                 */
                cout << [](int b) {return b * b * b;}(10) << "\n";//böyle lamba ifadelerine stateless lambda diyoruz
                //derleyiciyi implemente edenler tarafından var olan keyword'e göre 
                //yenisini eklemekten daha kolaymış :D bunu niye sordular bilmiyorum

                /* Dilin kuralları sınıfın hangi ctor'a sahip olup olmadığını belirliyor.
                Fakat memberlar'ı için []'parantezin içine bir şeyler yazdırmamız lazım
                 */

                 /* Yorum Baslik:3 sık kullanılan yer
                 bulunduğu yerde fonksiyonu çağırıyoruz.

                  */
                auto x = [](int a) {return a * a;}(12);
                auto y = [](int a) {return a * a;};
                //burada f ve y'nin türleri farklı
                //özdeş lambda ifadelerinden oluşturulan closure typelar birbirinden farklı
                is_same_v<decltype(f), decltype(y)>;

                //[](int x ){ if(x> 10) return 10;  return 4.5;} //burada sentaks hatası 
                /* Return statementlarında tür farklı ise derleyici typededuction yapamıyor
                birden fazla return statement var ve return ifadelerinin türleri farklı olacak

                ---
                [](int x ){return x*x} derleyici tür çıkarımı yapıyor fakat biz fonksiyonun geri dönüş
                değerini biz belirlemek istiyoruz.
                 */
                auto f1 = [](int x)->double { if (x > 10) return 10;  return 4.5;};
                auto y1 = [](int a)-> double {return a * a;};
                //noexcept ise nothrow garantisini vermiş oluyoruz (exception ile alakalı )


                /* Generilazed lambda statements

                 */
                auto f3 = [](auto x) {return x + x;};//burada fonksiyon çağrı operator fonksiyonun template olmasını istiyorsak auto yazıyoruz
                /* Yorum Baslik:
                class abcxyz
                {
                    template<typename T>
                    T operator()(T x)const
                    {
                        return x + x;
                    }
                };
                 */
                cout << f3(12) << "\n";
                cout << f3(1.2) << "\n";
                string s{ "ali" };
                cout << f3(s) << "\n";
                return 0;
            }
        }// sentaks_inceleme sonu
        /* Yorum Baslik:lambda_with_veri_elemani
         */
        namespace lambda_with_veri_elemani {
            int x = 5;
            int y = 12;
            int main()//main'de cagir!!!
            {
                std::cout << "lambda_with_veri_elemani main\n";
                /* Yorum Baslik:lambda ifadesi içerisinde statik ömürlü nesneler içinde kullanılabilir.
                Eğer global bir değişken varsa ana blok içinde global isim alanı
                 */
                auto f = [](int a) {return a * (x + y); };
                //otomatik ömürlü bir değişkenin sınıf içerisinde kullanılması mümkün değil
                //bunun nedeni ise değişkenin static/olup olmamasından kaynaklı oluyor.
                //bunu yaparken derleyiciye
            /* class abc_yter_
            {
                abc_yter_(int a, int b):x(a), y(b){}
                private:
                int x, y;
            }
            gibi bir kod yazdırmak istiyoruz
            bu kod
            auto operator(int a)()const
            {
                return( a) * (x+y);
            }
            bu yapıya capture clouse deniyor
             */
                int x_l = 10;
                int y_l = 20;
                auto f1 = [x_l, y_l](int a) {return a * (x_l + y_l)};
                //(eğer sadece değişken ismi yazılırsa copy capture deniyor)
                //derleyicinin oluşturduğu sınıfın member variable'ları olmuş oluyor
                //auto f1 = [x_l,y_l](int a){return a*(x_l++)};//Üye fonksiyon const olduğuu için 
                //sentaks hatası oluyor.
                auto f2 = [x_l]()mutable {(x_l++);};//buraada
                f2();
                std::cout << "x_l: " << x_l << "\n";
                //x_l'in değerini nasıl arttırabiliriz
                //veri elemanını referans yaparak ve ctor'u referans şeklinde olursa yapılabilir.
                /*
                class abc_ytr_
                {
                    abc_ytr_(int& a): x(a){}
                    void operator()(int a)const
                    {
                        ++x;//bu referansın yerine geçtiği neseneyi set edebiliriz
                    }
                    private:
                    int& x;
                }
                 */
                auto f5 = [&x_l](int a) {return a * x_l;};
                //eğer bir nedenden yerel değişken değiştirilecekse onu referans semantiği 
                //ile yapılacaksa referans operatorü konularak yapılacak
                std::string str{ "cansin" };

                //auto f6 = [str](){str.append(" onder");}; //Const üye fonksiyon elemanın const-olmayan üye fonksiyonu
               //çağırdığı için sentaks hatası oldu.
                auto f6 = [str]()mutable {str.append(" onder");};
                auto f7 = [&str]() {str.append(" onder");};
                return 0;
            }
        }// lambda_with_veri_elemani sonu   
        /* Yorum Baslik:ozetimsi
         */
        namespace ozetimsi {
            int global_x = 0;
            //
            void func(int x)
            {
                auto f = [&x]() {++x;};
                f();//burada x halen hayatta

            }
            auto func1(int x)
            {
                auto f = [&x]() {++x;};
                return f;
            }

            int main()//main'de cagir!!!
            {
                std::cout << "ozetimsi main\n";
                int a{}, b{}, c{}, d{};
                [a, b, c, d]() {};//4 değişkende kopyalama yoluyla capture edildi 
                [a, &b, c, &d]() {d = 2;};
                //burada 
                auto f = [=](int x) {return (x * (a + b + c + d));}; //görünür bütün yerel değişkenleri kopyalama semantiği ile capture et
                auto f = [&](int x) {
                    a = x * b;
                    b = x * a;
                    c = x * d;
                    d = x * c;
                    x = a * b * c * d;
                    return x;
                    }; //görünür bütün yerel değişkenleri referans semantiği ile capture et
                [] {    std::cout << "necco\n";}();
                //bırada eğer belirteç kullanılacaksa parantez zorunlu 
                //referans yoluyla yaparken dangling referans çok kritik olabilir                    

                auto f = func1(10);//burada x'in hayatı bitiyor
                //f(); böyle yazılınca artık dangling reference oluyor
                //bundan %100 emin olmak gerekiyor
                return 0;

            }
        }// ozetimsi sonu
        /* Yorum Baslik:tipik_kullanim_bicimi
        En sık kullanıldığı yol algoritmalara argüman olarak gönderil
         */
        namespace tipik_kullanim_bicimi {

            int main()//main'de cagir!!!
            {
                std::cout << "tipik_kullanim_bicimi main\n";
                using namespace std;
                vector<string> svec;
                rfill(svec, 50, &rname); //rname fonksiyonun geri dönüş değeri olan fonksiyon iile svec doldurulucak
                print(svec);
                //isim ve soy isim olsun  rname() + ' ' + rsname();
                vector<string> svec_sname;
                rfill(svec, 500, [] {return (rname() + ' ' + rfname());});//parametre parantezini yazmıyoruz
                //uzunluğu belirli bir uzunluk olanları kopyalayalım
                vector<string> destvec(50);
                size_t len;
                std::cout << "uzunluk degerini giriniz: \n";
                cin >> len;
                auto dest_end = copy_if(svec.begin(), svec.end(), destvec.begin(),
                    [len](const string& s) {return s.length() == len;}
                );
                //predicit son parametre,
                //eğer 1 parametresi varsa unary-> bu örnek için unary olmalı ve parametre string olmalı
                //eğer 2 parametresi varsa binary predict 
                print(destvec.begin(), dest_end, "\n");
                //ofs ile yazdırabiliriz

                vector<int>ivec;
                rfill(ivec, 1'000'000, Irand{ 0,10'000 });
                int ival;
                std::cout << "sayilacak degeri girin\n";
                cin >> ival;
                cout << "count: " << count(ivec.begin(), ivec.end(), ival);
                //fighter'dan kaçtane var o da sayılabilir.
                int low, high;
                std::cout << "sayilacak deger araligini giriniz\n";
                cin >> low >> high;

                cout << "count_if: " << count_if(begin(ivec), end(begin), [low, high](int i) {return (i >= low && i <= high);}) << "\n";
                auto my_pred = [low, high](int i) {return (i >= low && i <= high)};
                cout << "count_if: " << count_if(begin(ivec), end(begin), my_pred) << "\n";
                //cpp'de nesneler doğrudan unmutable, genellikle inmutable değişkenleri const yapıyoruz.
                //burada default const olması daha güzel


                //içinde yazı geçenler copy_if(svec.begin(),svec.end(),destvec.begin(),[str](const string &s){return s.find(str)!= string::npos;}) //cpp 20 de contains fonksiyonu da çağırılabilir.

                return 0;

            }// tipik_kullanim_bicimi sonu
        }
    } // namespace lambda_giris 
    namespace transform_algo
    {
        /* Yorum Baslik:
        callable üyleri argüman olarak gönderiyor ve geri dönüş değerini range'e yazıyor
        yani range'teki üyeleri alıyor ve onu tekrar hedef olarak aldığı range'e yazıyor.
        */
        template<typename InIter,typename OutIter, typename UnFunc>
        OutIter Transform(InIter beg, InIter end, OutIter destbeg, UnFunc f)
        {
            while(beg != end)
            {
                *destbeg++ = f(*beg++); //burada önemli olan
                //
            }
            return destbeg;
        }
        /* Yorum Baslik:2.overload
        2 tane  range var ve bunları karşılıklı olarak gönderiyoruz ve dönüşünü de gene bir range'e yazıoyruz

        
         */
        template<typename InIter1,typename InIter2, typename OutIter, typename BiFunc>
        OutIter Transform(InIter1 beg1,InIter1 end,InIter2 beg2,OutIter destbeg, BiFunc f)
        {
            while (beg1 != end)
            {
                *destbeg++ = f(*beg1++, *beg2++);
            }
            return destbeg;
        }
        void bi_transform_ornek()
        {
            using namespace std;
            vector<string> name_vec;
            vector<string> surname_vec;

            rfill(name_vec,100,rname);
            rfill(surname_vec,100,rfname);
            list<string> dest_list(100);
            transform(name_vec.begin(),name_vec.end(),surname_vec.begin(),dest_list.begin(),
            [](const string&s1,const string&s2){return (s1+" "+ s2);});
            print(dest_list.begin(),dest_list.end(),"\n");
        }


        int main()
        {
            using namespace std;
            vector<string>svec;
            rfill(svec,100,rname);
            print(svec);
            vector<string>destvec(100);
            string suffix;
            cin >>suffix;
            transform(svec.begin(),svec.end(),destvec.begin(),
            [suffix](const string &s){return s + suffix ;});
            print(destvec);
            vector<size_t>lenvec(100);
            transform(svec.begin(),svec.end(),lenvec.begin(),
            [](const string &s){return s.size();});
            print(lenvec);

            return 0;
        }
    }
    //namespace transform_algo
    namespace immediately_invoc_function_expression
    {
        /* Yorum Baslik:lambda ifadesi oluşturulup doğrudan 
        fonksiyonu kullanıyoruz    
        ideal'i nesnelere ilk değer vermek
         */
        //class Myclass m = [&]{return 1}(); //buna ilk değer vereceğiz fakat bu değer bir takım hesaplamalardan elde edilecek.
        // geri dönüş değeri type get_xyza() bir takım işlemlerle geri dönüş değeri olacak ve sonrada çağırılan yerde const Myclass mx = get_xyaza(a,b,c,d); yapacağız 
        //fakat bunun kötü yanı kodu takip etmek çok zor.
        //burada yerel değişken kullanacağız ve işimiz zorlaşmış olacaktı
        //derleyicinin yazdığı sınıfın kodunu göremiyoruz fakat dilin kurallarını biliyorsak bunu görebiliriz.
        //Eğer lambda stateless lambda ise ve herhangi bir değişken capture edilimioyrsa bir tür dönüştürme fonksiyonu var 
        void stateless_lambda(){
        auto f_square = [](int x) {return x*x;}; //stateless lambda
        int (*fptr)(int) = f_square;//bunun olmasının nedeni burada örtülü dönüşüm olması 
        std::cout << fptr(46);
        }
    }
    //C++20 ile yeni şeyler eklendi
    
        int mian()
        {
            auto fsquare = [](int x){return x*x;};
            decltype(fsquare) fx;//C++20'den önce default ctor'u delete edilmiş kabul ediliyordu. lambdaların default ctor'u yoktu. Fakat C++20'den sonra işe yarıyor.
        }
    
    class tekrar_const_uye_fonks
    {
    public:
        void func()const {

            *ptr = 56;//bu sentaks hatası değil çünkü pointer'a değer atamoyoruz
            //eğer ptr'yi değiştirmeye çalışsaydık sentaks hatası olur
            ir = 3;

        }
    private:
        int* ptr;
        int& ir;
    };
}