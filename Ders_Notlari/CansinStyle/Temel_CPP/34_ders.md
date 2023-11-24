# 34.ders

```cpp
/* Yorum Baslik:date.h
ve nutility başlık dosyalarını eklemek lazım


 */

namespace ders_34
{
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
    /* Yorum Baslik:
    En az yarısı standart kütüphane onun için bunu öğrenmek lazım

    pointerlarda bir iterator kabul edilebilir
    Algoritmalar fonksiyon şablonları ve generic programlamanın türden bağımsız olarak kullanılan standart
    fonksiyon şablonları.

    Dejavantajları
    **************************************************************************************************************
    Hata mesajları çok karışık olabilir.C++ 20 ile dile eklenen konseptler ile hata mesajların kullanımını kolay
    hale getiriyor.

    Exception handling'ten yoğun olarak faydalanılmıyor. Örneğin range'in tanımının yanlış olması durumunda patlıyoruz.

    -Boost kütüphanesi 3rd party library:-
    */
    namespace iterators_
    {
        /*
        **************************************************************************************************************
   Range ( Aralık )

   Bir range bir veri yapısında N tane öğenin oluşturduğu bir birim. Bu öğelerin hangi veri yapısında olduğundan bağımsız bir
   soyutlama.

   Konum değerlerine ve konum tutan nesnelerine ihtiyacımız var

   Örneğin iki pointerdan biri dizinin başını diğeri ise sonunu tutuyorsa baştaki konumu arttırarak
   sona erişebiliriz ve bu [konum1, konum2) yani 1.konumu sürekli arttırıp 2.konuma eşit hale getirmemiz gerekiyor.

   void Print(const int *ps, cont int* pe)
   {
       while(ps != pe)
       {
           std::cout<< *ps++<< " ";
           //printf("%d", *ps++);
       }
       printf("\n");
   }

   int main()
   {
       int a[10] = {1,4,7,8,9,2,7,6,3,10};
       print(a, a+10); //
   }

   ve burada bir soyutlama var ve verilen iki konum arasındaki nesnler arasında işlemler yapabiliyoruz ve
   bunu genişletmek istersek

   template <typename Iter>
   void Print(Iter ps,, Iter pe)
   {
       while(ps != pe )
       {
           std::cout<<*pss++< " ";
       }
   }

   **************************************************************************************************************
        */
        /* Yorum Baslik:iterator_ornek
        vector için
        düğüm için yapılmış

         */

        namespace iterator_ornek {

            template <typename Iter>
            /* Yorum Baslik:Eğer verilen sınıf içinde
            aşağıdaki operatörleri destekliyorsa
            ben bu işlemleri hata vermeden gerçekleştirebilirim demek.
            burada bir container
             */



            void Print(Iter ps, Iter pe)
            {
                while (ps != pe)
                {
                    std::cout << *pss++ < " ";
                }
            }

            int main()//main'de cagir!!!
            {
                std::cout << "iterator_ornek main\n";
                std::vector<int> ivec{ 1,4,6,8,9,10,11,12,89,91 };
                std::list<int> list{ 1,4,6,8,9,10,11,12,89,91 };
                Print(ivec.begin(), ivec.end());
                Print(list.begin(), list.end());//bu sınıflar operator overloading ile begin() ile yapılan nesne
                //++ ve içerik operator'un işlemlerini yapabiliyor
                //bu çağrıyı yaptığımızda Iter'e karşılık gelen tür karşılığı olarak
                /*
                void Print(std::list<int>::iterator ps,std::list<int>::iterator pe)
                {
                    while (ps != pe) //bu nesnelerin bu karşılaştırmayı yapması lazım
                    {
                        std::cout << *ps++ < " "; burada
                        //son ek ++ operator'u yapması lazım
                        ve aynı zamanda içerik operatorünün operandı olması lazım
                    }
                }
                */

                /* Yorum Baslik:peki bu nasıl gerçekleştiriliyor
                template<typename T>
                class list
                {
                    public:
                        class iterator //list sınıfının nested type
                        çifte bağlı listenin konumlarını tutacak sınıf
                        {
                            T& operator*();
                            operator++();
                            operator!=();

                        };
                        iterator begin();
                        iterator end();
                };
                 */
                return 0;
            }

        }// iterator_ornek sonu    
        namespace iterato_devam {
#include <string>
#include "nutility.h"
            void call_sort()
            {
                using namespace std;
                vector<string> svec;
                rfill(svec, 20, rtown);//20 tane şehir ismi ile doldurduk
                print(svec);
                sort(svec.begin(), svec.end());//bu şekilde küçüktür operatorünü kullanıyor ve             
                //küçükten büyüğe sıralandı
                //buradaki kodların hepsi compile time'da yazdı yani herhangi bir sınıf için tekrar tekrar yazmamaıza gerek yok.
                //bu şekilde range kavramıyla bize bir esneklik  sağlıyor.
                // C++20 ile cpp ranges kütüphanesi ile bize range'i temsil eden sınıf alabiliyor.
            }
            void copy_call()
                /* Yorum Baslik:bir range'teki üyeleri bir range'e kopyalıyor.
                Farklı veri yapılar üstünde işlem yapabiliyoruz
                İterator'ler ile çalışmanın türünden farklı
                        template<typename Initer, typename OutIter>
                        OutIter Copy(Initer beg, Initer end, Outiter destbeg)
                        {
                            while(beg != end )
                            {
                                *destbeg++ = *beg++;
                            }
                            return destbeg;
                        }
                        1. ve 2. parametre Kopyalanacak kaynak/source okuma range'i
                        3. parametresi yazma işleminin başlangıcı
                        Eğer bir algoritma ona yazma yapıyorsa geri dönüş değeri mutlaka
                        en son yazdığı konumdan sonraki konum.
                    Önemli bir şey end'in geri dönüş değeri sentineltal, orada bir nesne yok onun tanımlandığını gösteriyor

                    Bu genreic koddan faydalanarak vector'den vector'e
                    vector'den linked list'e bağlanabiliriz.
                 */
            {
                using namespace std;
                vector<string> svec{ "eray", "cem", "deniz", "emirhan","musa","ferhat" };
                // vector<const char * > svec {"eray", "cem", "deniz", "emirhan","musa","ferhat"}; içinde geçerli 
                //string'e const char atanır
                list<string> slist(6);
                print(svec);
                copy(svec.begin(), svec.end(), slist.begin());
                //Initer-> vector<string>::iterator, Outiter-> list<string>::iterator
                print(slist);
                vector<int> ivec{ 1,2,3,4,5 };
                list<double> dlist(6);
                copy(ivec.begin(), ivec.end(), dlist.begin());
                print(dlist);
                auto iter_end = ivec.end(); //BUNU ASLA DEREFERANS ETME TANIMSIZ DAVRANIŞ         
                std::vector<int> ivec;
                auto ivec_start = std::begin(ivec);
                begin(ivec);//burada ADL geçerli  std:: yazmaya gerek yok
                //ivec.begin() ile aynı şey

                //neden global begin fonksiyonu eklendi
                int a[] = { 12,5,27,9,81,3,6,23 };
                std::sort(a, a + (sizeof(a) / sizeof(*a)));
                //std::sort(std::begin(a),std::end(a) ); ile çağırabiliriz yani c'dizisi söz konusu olduğunda 
                //bunun çağırılabilmesi için burada partial specilization yapılmış!
                for (auto i : a)
                    cout << i << " ";
            }

            int main()//main'de cagir!!!
            {
                std::cout << "numeric_algo main\n";
                std::vector<std::string>svec;
                rfill(svec, 200, rname);
                print(svec,/*burada string parmetresi alıyor ve ayraç olarak kullanılıyor*/ " "/*,*/
                /*burada string'in hangi çıkış kanalı olduğu*/);
                std::ofstream ofs{ "out.txt" };
                if (!ofs)
                {//ERROR 
                }
                print(svec, "\n", ofs);
                return 0;
            }
        }// iterator devam sonu
        /* Yorum Baslik:iterator_using
         */
        namespace iterator_category {
#include <forward_list>
#include <list>

            //using Con = std::vector<int>; //bunun türünü auto çıkarımınınki de değişir
            using Contvect = std::vector<int>;
            using Contlist = std::list<int>;
            using Contforwardlist = std::forward_list<int>;

            int main()//main'de cagir!!!
            {
                std::cout << "iterator_using main\n";
                Contvect cv;
                Contlist cl;
                Contforwardlist cfl;
                auto itervec = cv.begin();
                auto iterlist = cl.begin();
                auto x = *itervec;
                itervec++;
                itervec == itervec;
                itervec != itervec;
                itervec < itervec; //burada list yapınca bu iterator sınıfı operator< overloading'i eklemedi 
                itervec > itervec;
                //bütün bu operator fonksiyonları overload edilmiş
                //bunun nedeni iterator kategorisi
                auto xx = itervec - 5;
                xx = itervec--;
                auto iterforwardlist = cfl.begin();
                //iterforwardlist--;//SENTAKS HATASI
                cout << typeid(std::vector<int>::iterator::iterator_category).name();
                cout << typeid(std::list<int>::iterator::iterator_category).name();
                cout << typeid(std::forward_list<int>::iterator::iterator_category).name();
                cout << typeid(std::ostream_iterator<int>::iterator_category).name();
                cout << typeid(std::istream_iterator<int>::iterator_category).name();


                return 0;
            }

            /* Yorum Baslik:iterator category resimde paylaşılan gibidir.

                output iterator ile yapılabilecek işlemler:ostream_iterator
                -bir başka iterator copy ctor edilebilir
                ++x x++ işlemleri yapılabilir
                *x x-> işlemleri yapılabilir

                input iperator ise:istream_iterator
                ek olarak
                != == kategorisini de sunuyorlar

                forward iterator kategorisi:forwad_list
                Output ve input'un birleşimi gibi
                HALEN -- operator'ünün overload'u artıyor

                Bidirectional iterator: list ste multiste map multimap
                -- ön ek ve son ek işlemleri de kullanılabiliyior.

                Random Access iterator kategorisi:
                C'deki pointerların yapabildiği tüm işlemleri yapabiliyor.
                Vector deque array string C arrays

                iterator sınıflarının iterator_category nested type'ı var bu bir tür eş ismi
                struct output_iterator_tag
                struct input_iterator_tag
                struct forward_iterator_tag
                struct bidirectional_iterator_tag
                struct random_acces_iterator_tag
             */
        }// iterator_using sonu
        /* Yorum Baslik:iterator_tag
         */
        namespace iterator_tag {
            template<typename T>
            void func(Iter beg, Iter end)
            {
                typename Iter::iterator_category;//iterator'un yeteneğini sorgulamada bir araç olarak kullanılabiliyor

            }
            int main()//main'de cagir!!!
            {
                std::cout << "iterator_tag main\n";
                return 0;
            }

        }// iterator_tag sonu
    } // namespace iterator_category

    /* Yorum Baslik:Copy
     */
    namespace copy_ornek {

        template<typename Initer, typename OutIter> //Minimum input iter olmalı
        //onun için ilk kısma Initer dedik, fakat minimal destek için OutIter olmalı
        OutIter Copy(Initer beg, Initer end, OutIter destbeg)
        {

            while (beg != end)
            {
                *destbeg++ = *beg++;
            }
            return destbeg;
        }
        int main()//main'de cagir!!!
        {
            using namespace std;
            std::cout << "Copy main\n";
            //std::sort()//RanIt: minumim random iterator olmalı
            vector<int> ivec{ 1,3,4,5 };
            sort(ivec.begin(), ivec.end());
            list<int> lvec{ 1,3,4,5 };
            //sort(lvec.begin(),lvec.end());//SENTAKS HATASI!!!! çünkü iterator kategorisi fonksiyonun isteklerini 
            //karşılamıyor.        
            return 0;
        }
    }// Copy sonu

    /* Yorum Baslik: Eğer bir algoritma
    dereferencing işlemi yapıyorsa, dereference edildiğinde o konumun geçerli olup olmadığı,
    ve tanımsız davranış olup olmadığının kontrolü yapılmıyor.
    - Burada dilin bazı araçları var bu teknikleri göreceğiz.
     */

     /* Yorum Baslik:copy_with_if
     If ile biten algoritmalar bir koşulu sınayarak yapıyor. Bir predict'in verdiği true değeere göre gerçekleştirriyorlar
     orjinali std::copy_if()
      */
    namespace copy_with_if {
        template <typename InIter, typename OutIter, typename Pred>
        OutIter CopyIf(InIter beg, InIter end, OutIter destbeg, Pred f)
        {
            //f();//bu türlere callable denliyor ve bu fonksiyon çağrı operatörü oluyorsa f'e callable deniyor
            while (beg != end)
            {
                if (f(*beg))
                {
                    *destbeg++ = *beg;
                }
                ++beg;
            }
            return destbeg;
        }
        bool is_even(int x)//1
        {
            return x % 2 == 0;
        }
        class DivPred
        {
            public:
            //bool operator()(int x)const{return x % 2 == 0 ;} 2 
            bool operator()(int x)const{return x % m_x == 0 ;}//3
            DivPred(int val):m_x{val};
            private:
            int m_x;//3
        };
        /* Yorum Baslik:dilin bir aracı olsa ve bu sınıfın kodunu da derleyici yazsa
        derleyici bu ifadeyle karşılaştırınca bunu sınıfa değiştiriyor
        LAMBDA EXPRESSION : O ifade karşılığı derleyiciyi o sınıfı yazıcak ve onu geçici nesneye çevirecek
        
         */

        int main()//main'de cagir!!!
        {
            std::cout << "copy_with_if main\n";
            vector<int>ivec;
            rfill(ivec, 1e00, Irand{ 0,1000 });
            print(ivec);

            list<int> ilist(100);

            //auto iter = copy_if(ivec.begin(), ivec.end(), ilist.begin(), &is_even);
            {
            auto iter = copy_if(ivec.begin(), ivec.end(), ilist.begin(), DivPred{2});
            print(ilist.begin(),iter);
            //Burada ilist.begin() ile iter'in oluşturduğu range arasındakiler yazıuılmış olucak
            //burada is_even fonksiyonu yerine 
            //sınıf fonksiyonu yapabiliriz ve burada functer class/object tanımlaytabiliriz.
            }
            {
            auto iter = copy_if(ivec.begin(), ivec.end(), ilist.begin(), DivPred{7});
            print(ilist.begin(),iter);
            }
            {
            std::cout<< "kaca tam bolunenler koypyalansin: ";
            int  ival;
            cin>> ival;
            auto iter = copy_if(ivec.begin(), ivec.end(), ilist.begin(), DivPred{ival});
            print(ilist.begin(),iter);
            }
            {
            std::cout<< "kaca tam bolunenler koypyalansin: ";
            int  ival;
            cin>> ival;
            auto iter = copy_if(ivec.begin(), ivec.end(), ilist.begin(), [ival](int x ){return x % ival == 0; });
            //derleyici burada oluşturulan ifadeye closure type deniyor ve bu ifadenin oluşturduğu nesneye closure object deniyor.
            //ismini derleyicinin belirlediği bir ifade yazıyor 
            /*
            class xyz1867q4
            {
                    xyz1867q4(int x ): ival{x}{};
                    auto operator()(int x )const{return  x % ival == 0 ;}
            }
            lambda ifadeleri Modern C++ ile dile eklendi ve kısıtlamalar yavaş yavaş ilerledik
            */
            print(ilist.begin(),iter);
            }


            return 0;
        }

    }// copy_with_if sonu

    /* Yorum Baslik:numeric_algo
    bu kodlar için nutiliy.h lazım!!!
     */
} // namespace ders_34
```cpp
