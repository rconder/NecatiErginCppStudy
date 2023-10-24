# 20.ders

```cpp
/*
#include <exception>
    İlk sınıf tasarım ödevi Date sınıf implementasyonu 
    class Date{
        public:
            class BadDate : public std::exception{
                public:
                    const char* what()const
                    {
                        return "bad date!!!!";                        
                    }                            
            };
        Date & set_month_day(int day)
        {
            //Geçersiz bir tarih varsa 
            throw BadDate{}; //Exception throw etmek için    
        }            
    };
    noexcept operatoru var
    tek parametreli ctor'ları explicit
    tür dönüştürme operator fonksiyonu explicit olsun 


    Eger bir nesneyi değiştirmeden kullanacaksak 
    const auto i = 0;
    dogal kod yazma biçiminde bunu kullnabilirsin 
    eger zaten bu degisken kullanılacaksa compiler hata verir.

    Kod niyeti anlatmalı yorum satına ihtiyaç bırakmamalı //doxygen için geçerli değil 
    

    awoid raw loops

    //static code analyzer'ın bazı uyarı mesajları doğru olmayabilir.

    nodiscard attr: fonksiyonlarının geri dönüş değerlerinin discard edilmesi gereken yerlerde bunu kullan:
    [[nodiscard]] bool isprime(int) //bunun geri dönüş değerinin kullanılmaması logic bir hata
    {

    }
    int main()
    {int x =234522; isprime(x);}//logic bir ata olduğu kesin

    bir türün kendisinide nodiscard olarak isaretlenebilir.

    [[nodiscard]] class Myclass{};
    bu durumda geri dönüş değeri Myclass olan fonksiyonlar nodiscard olucak.
*/

/* 
Eğer bir sınıfın başka sınıf türünden bir eleman varsa
Bir nesne içinde nesne bulunacak->embedded object | member object

Yorum Baslik:STL STRING SINIFI
    yazi islemleri için özelleştirilmiş veri sınıfı
    dinamik bir yazı sınıfı
    string sınıfını iyi kullanabilmek için dinamik dizi veri yapısını iyi anlamak gerekiyor.
    dynamic array kullanıyor
    öğeler ardışık olarak bir bellek bloğunda tutuluyorlar

    tutulabilecek öğe sayısı dinamik dizinin kapasitesi.
    arka planda 3 pointer var

    birincisi => pointer olması zorunlu başlangıcı tutuyor
    ikincisi => son elemanı tutuyor
    üçüncüsüde kapasitenin sonunu tutuyor.

    eğer size == kapasite olursa ve insertioin talebi gelirse
    arka planda reallocation yapılacak ve yeni allocate edilen hafıza alanına taşınacak
    reallocationdan mümkün olduğunca kaçınmak gerekiyor çünkü çok fazla bir maliyet istiyor.

    kapasitenin hafızayı ne kadar artıracağını derleyici belirleyebilir => sınıfn reserve isimli fonksiyonu çağırabilirsin kapasiteyi belirlemek için
    
    Gerek string gerek vector sınıfında reallocation temel görevlerinden biri
    reallocation takes time
    reallocation invalidates references.

    Amorte edilmiş constant time => eğer size kapasiteye edilirken reallocation olucak fakat bu durumda amorti ediliyor.
*/

/* Yorum Baslik:nec_ornek_1 
 */
#include <string>
#include <iostream>
namespace nec_ornek_1{

//string içerisinde derleyiciye kod yazdıran bir kod var
//bir sınıf şablonu var
    template<typename C, typename T = std::char>  
    using strting = std::basic_string<char,std::char_traits<char>, std::allocator<char>>;

        //ilk parametre karakterlerin türü
        //İkincisi trait parametresi parametre verilmezse char_trait<char> açılımı
        //Arka plandaki dinamik bellek yönetiminin nasıl olduğu allocator

    int main_1()//main'de cagir!!!
    {
        std::cout<<"ornek 1 main\n";
        std::string s1;
        std::basic_string<char,std::char_traits<char>, std::allocator<char>> s2;
        std::basic_string<char>s3; //3'u aynı 
        /*
            wstring wchar_t acılımının tür eş ismi
        */
        return 1;
    }
}// nec_ornek_1 sonu

//string 
//wstring => basic string şablonundan edilmiş basic_string<wchar_t //wide string
/*
    Sınıf şablonu ile sınıflar arasındaki fark 
    derleyici sınıfın bütün kodlarını derlemiyor
    hangi fonksiyonlar çağrılıyorsa o fonksiyonlar çağırılıyor.
    
    string sınıf fat interface 

*/

/* Yorum Baslik:nec_ornek_2 
 */
namespace nec_ornek_2{

    int main_2()//main'de cagir!!!
    {
        std::cout<<"ornek 2 main\n";
        using namespace std;
        string str = "necati ergin";
        str+="can";
        //sadece ctor'un ve operator+= fonksiyonu ve destructor kodu derlendi
        //yani sadece çağırılan kodların kodu derleyici tarafından derleniyor.
        return 2;
    }

}// nec_ornek_2 sonu

//sınıfın cohesive olması tüm öğeleriyle aynı amaca yönelik fonksiyonlar içeriyor.
//bazı işlemler için global fonksiyonlar çağırılırken bazı işlemler için üye fonksiyonlar çağırılabilir.

//STL'de bir veri yapısı ilkesiyle bir arada tutan sınıflara container diyor.
//container olmanın bir takım şartları ve sonuçları var
//string is an STL container algorithm => türden bağımsız std'nin fonksiyon şablonu

/* Yorum Baslik:nec_ornek_3 
 */
#include <algorithm> 
namespace nec_ornek_3{

    int main_3()//main'de cagir!!!
    {
        std::string str;
        //yazıyı ters cevirmek ya da sıralamak için
        //std'nin algorithmaları var, diğer container için kullanılabilirken 
        //eğer bir işi hem algorithma hem de sınıfın üye fonksiyonu varsa SINIFIN ÜYE FONKSİYONU İLE YAP.
        //%100 uyumlu stl algorithması, string sınıfı içinde char tutan bir container sınıfı.
        /*stl ( STANDARD Olan) containerları: 
        vector,deque,list,forward_list,array,string ====> sequential containers
        set, multi_set, map, multi_map =====>          associative containers                 
        unordered_set, unordered_multi_set, unordered_map, unordered_multi_map ==> unordered associative containers
        */
        std::cout<<"ornek 3 main\n";
    return 3;
    }

}// nec_ornek_3 sonu

//Operator ve function overloading'ten maksimum düzeyde yararlanıyor.
 

 /* 
    String genel bir terim contex'ten anlaşılmıyorsa
    ====
    i) std::string sınıfı türünden bir nesne
    ii) genel olarak bir yazı
    iii) sonunda null karakter olan bir yazı adresi null terminated bite strean 
 */

/* Yorum Baslik:nec_ornek_4 
 */
namespace nec_ornek_4{

    int main_4()//main'de cagir!!!
    {        
        std::cout<<"ornek 4 main\n";
        char str[100] = "ali ekrem";
        str; //cstring =>char dizi adresi yazının sonunda null character var                       
        return 4;
    }
}// nec_ornek_4 sonu


/* Yorum Baslik: string parametreleri   
    -> string => const std::string &
    
    -> cstring parametre => parametrenin const char * olması demek 
    ama o yazının sonunda null character olduğunu düşünerek işlem yapıyor

    string str(a); //argüman yazısının sonudna null chracter olmalı
    null character yoksa undefined behavior

    -> data const char*, std::size_type n: bu adresten başlayarak , bu kadar sayının ol

    -> range iki tane konum veriyoruz [konum1,konum2) konum1 dahil konum2 dahil değil
    //konum1 konum2'den daha uzak olsaydı tanımsız bir davranış olurdu
    konum1 konum2'ye hiçbir zaman eşit olmuyorsa tanımsız bir davranış olurdu.

    -> fill Bu karakterden bu kadardır std::size_type(size_t), char
                                     string::size_type

    -> char : tek bir karakter.

    substring: fonksiyon bir const string& istiyor, bir de tam sayı istiyor size_t idx| const string&, size_t idx |
               String'in verilen indexten başlayarak geriye kalan karakterlerin tamamı 

            | const string&, size_t idx, string::size_t type n | 3.parametre karakter sayısı
            Eger 3.parametreye geçtiğimizde geriye kalan karakterlerden daha büyükse 
            geriye kalan karakterlerin hepsi demek

 */


/* Yorum Baslik:nec_ornek_5 
 */
namespace nec_ornek_5{

    int main_5()//main'de cagir!!!
    {
        std::cout<<"ornek 5 main\n";
        char str[100];
        str[0] = 'O';
        str[1] = 'K';
        //std::string s_cstring(str); // TANIMSIZ DAVRANIŞ!!!!!!!!!!!!!!

        char str1[100] = "mustafa";
        //str null terminated değil
        std::string s(str1,2);   //mu
        std::string s(str1+1,2); //us

        char str_range[100] = "mustafa"; //usta
        std::string s_range(str+1,str+5); 
        std::cout << "[" << s << "]"; 

        std::string s_fill(20, 'a');
        std::cout << "["<< s_fill <<"]";

        std::string s_string = "murat gunay";
        std::string s_substring (s_string, 6); // "gunay"
        std::cout << "["<< s_substring <<"]\n";

        std::string s_substring1 (s_string, 3); // "at gunay"
        std::cout << "["<< s_substring1 <<"]\n";

        std::string s_string1 = "eray goksu";
        std::string s_substring3(s_string1,2,2);//"ay"
        std::cout << "["<< s_substring3 <<"]\n";

        std::string s_substring3(s_string1,2,90000);//"ay goksu"
        return 5;

    }
}// nec_ornek_5 sonu 



/* Yorum Baslik:    intializer_list -> std::initializer_list   

    Modern c++ ile eklendi.

    #include <initializer_list> header'ı include edilmeli 
    
    arkaplanda bir dizi oluşturtuyoruz.
    derleyiciye arka int const olsun ve bellekte bir yer ayır
    2tane pointer olsun 
        biri listenin başını tutuyor
    ve 
    diğeri listenin sonunu tutuyor 
    fonksiyona initializer list ile cagrı yapılır

    std::initializer_list<int> x{1,4,6,7,9};
    derleyici listede verilen öğeleri diziye çeviriyor
    
    SALT OKUMA ARAÇLI

    container sınıfının çoğu initializer list üstünden

 */

/* Yorum Baslik:nec_ornek_6 
 */
namespace nec_ornek_6{

    class Myclass{
    public:        
    private:        
    };

    int main_6()//main'de cagir!!!
    {
        std::cout<<"ornek 6 main\n";
        
        std::initializer_list<int> x{1,4,6,7,9}; //const int*
        std::initializer_list<double> y{1,4,6,7,9};        
        std::initializer_list<Myclass> mx{Myclass{},Myclass{}};

        std::cout<< "sizeof(x): " << sizeof(x) <<" \n";
        std::cout<< "sizeof(y): " << sizeof(y) <<" \n";
        std::cout<< "sizeof(int*): " << sizeof(int*) <<" \n";

        x.size(); //listede tutulan öğe sayısını dönüyor
        std::cout<< "x.size(): " << x.size() <<" \n";
        auto ptr_begin = x.begin();
        auto ptr_end   = x.end(); //SALT OKUMA AMACLI
        std::cout<< "ilk oge:    " <<*(x.begin())<<"\n";
        std::cout<< "ikinci oge: "<<*(x.end())<<"\n";

        for(auto i: x)
        {
                std::cout<< "x_i: " << i <<" \n";
        }
        for(const auto i: x)
        {
                std::cout<< "x_i: " << i <<" \n";
        }
        
        return 6;
    }
}// nec_ornek_6 sonu



/* Yorum Baslik:nec_ornek_7 
 */
namespace nec_ornek_7{
    void func(int); 
    void func2(int a, int b, int c, int d)
    {
        for(auto val: {a,b,c,d})
        {
                std::cout<< "val: " << val <<" \n";
        }
    }
    int main_7()//main'de cagir!!!
    {
        for(auto i: {2,3,5,7,11})
        {
            func(i);
        }

        std::cout<<"ornek 7 main\n";
        return 7;
    }

}// nec_ornek_7 sonu

/* Yorum Baslik:nec_ornek_8 
 */
namespace nec_ornek_8{
    void func(std::initializer_list<int>x)
    {
            std::cout<< "x.begin(): " << x.begin() <<" \n";
            std::cout<< "x.end(): " << x.end() <<" \n";
    }
    int main_8()//main'de cagir!!!
    {
        std::cout<<"ornek 8 main\n";

        std::initializer_list<int> mylist {2,5,6,7,9,13};
        std::cout<< "mylist.begin(): " << mylist.begin() <<" \n";
        std::cout<< "mylist.end(): " << mylist.end() <<" \n";
        //*mylist.begin() = 56;  // SENTAKS HATASI
        func(mylist);//sadece 2 tane pointer kopyalandı        
        return 8;
    }

}// nec_ornek_8 sonu


/* Yorum Baslik:nec_ornek_9 

 */
namespace nec_ornek_9{

    int main_9()//main'de cagir!!!
    {
        std::cout<<"ornek 9 main\n";
        auto x = {1,3,5,6,7}; // bu durumda derleyici tur cıkarımını listedeki tur neyse ona gore cıkarım yapacak
        //std::initializer_list<int> x{1,4,6,7,9}; //const int*
        //auto x = {1,3,5,6.0,7}; //SENTAKS HATASI
        auto x1 {10};//bu durumda tur cıkarımı initializer list çıkarımı yapılmıyor.
        auto y = {10}; // bu durumda initializer list
        // y {10,20} //SENTAKS HATASI // y  = {10,20} şeklinde yazılmalı.        
        return 9;   
    }
}// nec_ornek_9 sonu



/* Yorum Baslik:nec_ornek_10 
 */
namespace nec_ornek_10{
    int main_10()//main'de cagir!!!
    {
        std::cout<<"ornek 10 main\n";
        std::vector<int> vec1{1,3,5,7,10}; //initializer list container.
        vec1.insert(vec1.begin(),{3,7,9});
        vec1 = {7,9,11}; 
        return 10;  
    }
}// nec_ornek_10 sonu

/* Yorum Baslik:nec_ornek_11 
 */
namespace nec_ornek_11{
    class Myclass{
    public:
        Myclass(std::initializer_list<int> x)
/*         {
            double sum{};
            for(auto val : x)
            {
                sum += val;
            }
            m_mean = sum/x.size();
        }
 */
        {
                std::cout<<"Myclass(init_list)\n";
        }
        Myclass(int)
        {
                   std::cout<<"Myclass(int)\n";
        }
    private:
        double m_mean;    
    };

    int main_11()//main'de cagir!!!
    {
        std::cout<<"ornek 11 main\n";
        Myclass m1 = {1,3,5,6,7}; //initlist ctor calisti
        Myclass m2 { 10 };//burada da init list ctor cagırıldı
        Myclass m3 (3); //
        //Eger sınıfın hem init_list parametreli hem de tam sayılı bir parametreli ctor'u varsa
        //init list parametreli ctor çağırılır {}
        return 11;
    }
}// nec_ornek_11 sonu


/* Yorum Baslik:nec_ornek_12 
 */
namespace nec_ornek_12{

    int main_12()//main'de cagir!!!
    {
        std::cout<<"ornek 12 main\n";
        std::vector<int>ivec1(100); //100 tane 0 değeri ile başlatıyor.
        std::vector<int>ivec2{100}; //Sadece 1 tane 100 değeri var.

        std::vector<int>ivec3(100,5);//100 tane 5 degeri ile başlatıyor
        std::vector<int>ivec4{100,5}; //2tane parametresi var 100 ve 5
        
        std::cout<< "ivec1.size(): " << ivec1.size() <<" \n";//
        std::cout<< "ivec2.size(): " << ivec2.size() <<" \n";//1
        
        return 12;
    }
}// nec_ornek_12 sonu

/* Yorum Baslik:nec_ornek_13 
 */ 
namespace nec_ornek_13{

    int main_13()//main'de cagir!!!
    {           
        std::cout<<"ornek 13 main\n";
        
        std::string s1(55,'A');        
        std::cout<< "s1.size(): " << s1.size() <<" \n";
        std::cout << "["<<s1<<"]";

        std::string s2 {55, 'A'};
        std::cout<< "s2.size(): " << s2.size() <<" \n";
        std::cout << "["<<s2<<"]";
        return 13;  
    }   
}// nec_ornek_13 sonu   

```
