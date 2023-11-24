# 36.ders

```cpp
namespace ders_36
{

#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include "nutility.h"
    /* Yorum Baslik:Sık kullanılan arama uygulamaları
       find ve find_if algoritmaları var
       find_if_not var
       STL'de arama anlamında kullanılan iki fonksiyon
       hem search hem de find ismi kullanılıyor.
       Bilinen linear search algorithm veri yapısını dolaşarak O(n) yapıyor.

     */
    namespace find_alghoritma
    {
        template <typename Initer, typename T>
        Initer Find(Initer beg, Initer end, const T& tval)
            /*
            C'nin standard arama fonksiyonları adres döndürüyor
            C++'in standard arama fonksiyonları bulunan konumu döndürüyor, bulamazsa end konumunu döndürüyor
            */
        {
            while (beg != end)
            {
                if (*beg == tval)
                {
                    return beg;
                }
                ++beg;
            }
            return end; //return beg;'de aynı anlamda
        }

        template<typename Initer, typename Unpred>
        Initer FindIf(Initer beg, Initer end, Unpred f)
        {
            while (beg != end)
            {
                if (f(*beg))
                {
                    return beg;
                }
                ++beg;
            }
            return end;
        }

        //FindIfNot: Bunun dönüş değeri asal sayı örneği için ilk asal olmayan sayı bulunuyor.




    } // namespace find_alghoritması
    /* Yorum Baslik:arama_islemi
    bir container'da son öğeye erişebilmek için
    ivec.end()-1 şeklinde erişebilirdik fakat bunun için
    iterator'un Random Access  Iterator kategorisinde olmalı.
    Sequence container'ların front()-> ilk öğeye
    back()->son öğeye eriştiriyor.
    Bunun tanımsız davranış olmaması için vector'un boş olmaması lazım
    svec[svec.size()-1]  bu şekilde de son öğeyeye erişebiliriz.

     */

    namespace arama_islemi {

        using namespace std;
        void find_func()
        {

            std::cout << "arama_islemi main\n";
            vector<string> svec;
            rfill(svec, 20, rname);//nutility.h
            print(svec);//nutility.h
            string name;
            std::cout << "aranacak ismi girin\n";
            cin >> name;
            // find(svec.begin(),svec.end(),name);
             /* 1,2 noktada dikkat etmek lazım
             *beg ve T arasında yapılıyor ve bu iki değer aynı olmak zorunda değil
             ve bu iki değerin eşitlik karşılaştırılmasının yapılabilmesi gerekiyor.  Yoksa sentaks hatası olur.

              */
              //vector<string::iterator> iter = find(svec.begin(),svec.end(),name);//auto olmasaydı burada hata olabilirdi.
            auto iter = find(svec.begin(), svec.end(), name);
            if (iter != svec.end())
            {
                std::cout << "*iter: " << *iter << " \n";//RA Iterator
                std::cout << "indeksi " << iter - svec.begin() << "\n";
            }
            else
            {
                std::cout << "Bulunamadi";
            }
            svec.rbegin();//eger container boş değilse buradan alınan iterator 
            //dereference edilirse son öğeye erişebiliriz.
            //eger burada iter'in kullanımı bittiyse bu kötü bir kod eski cpp'de bunu engellemenin yöntemi suni blok oluşturulabilirdi

            //if with initilaizer
            if (auto ifiter = find(svec.begin(), svec.end(), name);ifiter != svec.end())
            {
                std::cout << "*iter: " << *ifiter << " \n";//RA Iterator
                std::cout << "indeksi " << ifiter - svec.begin() << "\n";
            }
            else
            {
                std::cout << "Bulunamadi";
            }


        }
        void find_if_func()
        {
            vector<int> ivec;
            rfill(ivec, 100, Irand(5'000'000, 6'000'000));
            print(ivec);
            find_if(begin(ivec), end(ivec), &isprime); //find_if(begin(ivec),end(ivec),isprime); bu aynı
            if (auto iter = find_if(begin(ivec), end(ivec), &isprime); iter != end(ivec))
            {
                std::cout << "ilk asal sayi: " << *iter << " \n";
            }
            else
            {
                std::cout << "asal sayi bulunamadi\n";
            }
            vector<string> svec;
            rfill(svec, 1000, rname);
            print(svec);
            char c;
            cout << "icinde hangi karakter olan";
            cin >> c;
            if (auto iter = find_if(begin(svec), end(svec), [c](const string& s) {return s.find(c) != string::npos;});iter != svec.end())
            {
                std::cout << "bulundu\n";
            }
            else
                std::cout << "bulunamadi\n";



        }
        int main()//main'de cagir!!!
        {
            find_func();
            find_if_func();
            return 0;
        }
    }// arama_islemi sonu

    namespace iterator_adapters
    {
        /* Yorum Baslik:
        Aslında başka bir sınıfı kullanarak o sınıftan başka bir sınıf kullanılan sınıflara deniyor.

        Örneğin container adaptörleri: container sınıflarını member olarak alıp daha özel bir amaçlı interface oluşturan sınıflara deniyor

        Aynı şekilde iterator adaptörelerde iterator sınıflarını alıyor
        reverse_iterator
            insert iterator adaptörleri
                stream iterator adap
         */
         /* Yorum Baslik:reverse_iterator
        Aslında reverse iterator sınıfları bir iterator türünden elemanı var
        rbegin çağırıldığında => öyle bir iterator döndürüyorki o endin konumu
        aslında iterator'ün içerik operatör fonksiyonu eleman olarak tuttuğu nesneye değil ondan bir önceki konuma eriştiriyor.
        rend fonksiyonun geri dönüş değeri aslında ilk konumu tutuyor ve derefenece edildiğinde hata oluyor.
        begin() - end()range yerine
        end() - begin() range elde edilmiş gibi oluyor



          */
        namespace reverse_iterator {
            using namespace std;
            template<typename Initer>
            void Print(Initer beg, Initer end, const char* psep = " ")
            {
                while (*beg != end)
                {
                    cout << *beg++ << psep;
                    beg++;
                    //burada reverse iterator kodunun yazılma biçiminden dolayı 
                    //container'daki başka bir öğeye erişiyoruz.
                }
                cout << "\n"
            }
            void ornek()
            {
                vector<string> svec{ "tekin","eray","cem","deniz","emirhan","suleyman","samet","volkan","nur" };
                //içinde alan ilk öğeyi bulmak istesek erayı bulmamız lazım
                //eğer 
                const auto f = [](const string& s) {return s.find('a') != string::npos;};
                if (auto iter = find_if(svec.begin(), svec.end(), f); iter != svec.end())
                {
                    cout << "bulundu: " << *iter << "\n";
                }
                else
                    cout << "bulunamadi";
                if (auto riter = find_if(svec.rbegin(), svec.rend(), f); riter != svec.rend())
                {
                    auto iter = riter.base();//çağırıldığında 
                    cout << "bulundu: " << *riter << "\n";
                    cout << *iter << "\n";
                }
                else
                    cout << "bulunamadi";
            }
            int main()//main'de cagir!!!
            {
                std::cout << "reverse_iterator main\n";
                vector<int> ivec = { 2,5,6,9,34,76,19 };//CTAD
                Print(ivec.begin(), ivec.end());
                Print(ivec.rbegin(), ivec.rend());//Print fonksiyonu bu sefer sondan başa doğru yazdırıyor.
                /* Eğer minimum bidirectional iterator ise
                Reverse iterator'u kullanabiliyoruz
                Nasıl oldu da bu kod çalışıyor.
                Bu containerların rbegin ve rend iterator değil reverse iterator döndürüyor
                 */
                auto iter = ivec.rbegin();//
                //sreverse_iterator<vector<int>::iterator> reviter;
                vector<int>::reverse_iterator rreeviter = ivec.rbegin();
                cout << *rreeviter; //vector'un son öğesine erişmiş olacağız
                //ve bu nesneyi artırırsak bir öncekki öğeye erişiyoruz 


                /* Yorum Baslik:vector'de belirli bir
                    Buradaki son 2'yi sileceğiz
                 */
                vector<int> ivec2{ 1,2,4,5,2,6,7,2,9 };
                auto riter = find(ivec2.rbegin(), ivec.rend(), 2);
                //bütün containerların eraese fonksiyonu var ve siliyor
                //ivec.erase(riter);//çünkü bu reverse iter istemiyor bu fonksiyon normal iterator istiyor.
                //ivec.erase(riter.base()); //2'y silmek yerine 9'u sildik
                ivec.erase(riter.base() - 1);//ile 2'yi sildik
                //elimizde sadece bunlar var
                auto riter_end = ivec.rbegin();
                auto riter_beg = ivec.rend();
                //ve print algoritmasını riter_end, riter_beg kullanarak nasıl baştan sona yazdırabilirdik.
                Print(riter_end.base(), riter_beg.base());//riter_beg aslında end konumunu sarmalıdı ve riter_end ise fiilen ilk öğeyi tutuyor.

                return 0;
            }
        }// reverse_iterator sonu
        namespace insert_adapters
        {
            using namespace std;
            /* Yorum Baslik:insert
             */
            namespace insert {
                template<typename c>
                BackInsertIterator<c> BackInserter(c& C)
                {
                    return BackInsertIterator<c>{C};
                }

                template<typename c>
                class BackInsertIterator
                {
                public:
                    BackInsertIterator(C& cr) : m_con(cr) {}
                    BackInsertIterator& operator++(int) { return *this; }
                    BackInsertIterator& operator++() { return *this; }
                    BackInsertIterator& operator*() { return *this; }
                    BackInsertIterator& operator=(const typename c::value_type& val)
                    {
                        m_con.push_back(val);
                        return *this;
                    }
                private:
                    C& m_con;//örneğin vector<int> açılımından bir referans tutuyor

                };
                int main()//main'de cagir!!!
                {
                    std::cout << "insert main\n";
                    vector ivec{ 2,5,7,1,9,3 };
                    vector<int> destvec;
                    //copy(ivec.begin(),ivec.end(),destvec.begin());//destvec boooooooooş TANIMSIZ DAVRANIŞ
                    //kaynak olarak gönderileni kullanmak lazım 
                    copy(ivec.begin(), ivec.end(), back_inserter(destvec));
                    /* Bunun gerçekleşmesinin nedeni
                    back_insert_iterator<vector<int>> iter;

                     */
                    vector<int> destvec1;
                    back_insert_iterator<vector<int>> backiter{ destvec1 };
                    back_insert_iterator backiter{ destvec1 };
                    *backiter++ = 10;
                    copy(ivec.begin(), ivec.end(), BackInserter(destvec1));//BackInserter(destvec)
                    //back_insert_iterator => sarmaladığı container'ın push_back fonksiyonunu çağırıyor | back_inserter
                    //front_insert_iterator => sarmaladığı container'ın push_front fonksiyonunu çağırıyor | front_inserter
                    //insert_iterator => sarmaladığı container'ın con.insert(iter,value) çağırıyor | inserter
                    list<int> dlist;
                    list<int> flist;
                    copy(ivec.begin(), ivec.end(), back_inserter(dlist));
                    print(dlist);
                    copy(ivec.begin(), ivec.end(), front_inserter(flist));
                    print(flist);
                    set<int> myset;
                    copy(ivec.begin(), ivec.end(), inserter(myset, myset.begin()));
                    return 0;
                }
            }// insert sonu                        
            /* Yorum Baslik:const
             */

        } // namespace insert_adapters
        namespace const_iterator_nested {
            using namespace std;
            int main()//main'de cagir!!!
            {
                std::cout << "const main\n";
                int x = 10;
                vector ivec{ 2,5,7,1,9,3 };
                /*

                 */
                const vector<int>::iterator iter = ivec.begin();//burada iter const anahtar sözcüğü ile tanımlandığı için
                //iter const bir sınıf nesnesidir.
                //sadece const üye fonksiyonlarını çağırabiliriz. iter++ yaparsak sentaks hatası olmalı
                //const olmayan üye fonksiyonunu çağırılma hatası olur
                *iter; //hata olmaz
                *iter = 75; //sentaks hatası olmaz çünkü nesneye erişiyoruz ve eriştiğimiz nesne const değil
                //eğer const keyword ile bir iter oluşturursak top lewel const'un karşılığı 
                //low level const pointer karşılığı iterator kullanabilir miyiz
                // KUllanmamız gereken iterator const_iterator 
                vector<int>::const_iterator iter1 = ivec.begin();
                iter1++;
                //*iter1 = 10; const referans bir geri dönüşü oluyor salt okumak amaçlı kullanabiliriz
                cout << *iter1;
                //modern cpp ile auto type deduction kullanımı ile begin()'geri dönüş değeri const değil ::iterator türü
                //bunun için cbegin() eklendi
                //bir range'i sadece salt okuma amaçlı bir iş yapmak istiyoruz. Hem daha güvenlisi hem de niyeti belli eden cbegin()' kullanmak
                list<int> mylist{ 10,20,30,50,60 };
                for (auto citer = mylist.cbegin();citer != mylist.cend(); ++citer)
                    //auto olmasaydı (list<int>::const_iterator citer ) şeklinde yazmalıydık
                {
                    cout << *citer << "\n";
                }

                return 0;
            }
        }// const sonu
    } // namespace iterator_adapters 
    /* Yorum Baslik:
    iterator
    .begin(),.end()

    const_iterator
    cbegin(),cend()

    reverse_iterator,
    rbegin(),  rend()

    const_reverse_iterator   : hem sondan başa hem de salt okuma amaçlı dolaşmak istiyoruz
    crbegin(), crend()

    hepsi için auto'yu kullanabiliriz
    */
    namespace iteratorFunctioin
    {
        /*
        advance: Bir iteratoru belirli bir mesafe kadar arttırıyor ya da azaltıyor

        distance:2 iterator arasındaki mesefa 
        Container'ların size üye fonksiyonu var
        forward_list'in size'ı yok
        next
        prev
        iter_swap
        */
        using container = std::vector<std::string>;
        void ornek_advavnce() //negatif bir değerlede çağırabiliriz.
        {
            using namespace std;
            vector<string> svec{ "eray","deniz","fatih", "selda","ece" };
            auto iter = svec.begin();
            cout << *iter << "\n";
            //*iter fatih olsun istiyoruz.
            //vector söz konusu olduğu zaman iter += 3; yazabiliyoruz
            //eğer bu list olsaydı +=' yazamıyorduk
            iter += 3;
            cout << *iter << "\n";
            list<string> slist{ "eray","deniz","fatih", "selda","ece" };
            auto siter = slist.begin();
            //slist += 3; //Sentaks hatası 
            //yapmanın bir yolu n kez dönen bir döngü oolması lazım
            advance(siter, 2);//burada hangi kodun çalışacağı compile time'da belli oluyor.
            cout << *siter << "\n";
        }
        //compile time'da kodun seçimini yapmaya tag dispatch deniyor
        template<typename Iter>
        void Advance(Iter& iter, int n)
        {
            //iter += n; //şeklinde olsa listenin iterinde hata olur 
            Advance_impl(iter, n, typename Iter::iterator_category{});
        }
        template<typename Iter>
        void Advance_impl(Iter& iter, int n, std::random_access_iterator_tag)
        {
            std::cout << "random access iterator\n";
            iter += n;
        }
        template<typename Iter>
        void Advance_impl(Iter& iter, int n, std::bidirectional_iterator_tag)
        {
            std::cout << "bidirectional_iterator_tag\n";
            while (n--)
                ++iter;
        }
        template <typename Iter>
        void algooo(Iter beg, Iter end)
        {
            int n = 3;
            std::advance(beg, n);
        }

        int main()
        {
            using namespace std;
            vector<int> x{ 1,3,5,6,23,8,63,2 };
            auto iter = x.begin();
            Advance(iter, 4);
            list<int> xl{ 1,3,5,6,23,8,63,2 };
            auto liter = xl.begin();
            Advance(liter, 4);
            return 0;
        }
        void ornek_distance()
        {
            using namespace std;
            vector<int> ivec{1,3,6,7,8,12};
            cout <<distance(ivec.begin(),ivec.end())<<"\n";
            forward_list<int> mylist{1,3,6,7,8,12};//c dilinde yazılan tekli bağlı liste
            //stl'de size constant bir zamanda elde edilsin istiyoruz
            //ve size'a erişmek istiyorsak size kullanmamız lazım.
        }
    }
} // namespace ders_36
```
