/* Yorum_no:21.ders başlangıcı
==> String sınıfı parametreler <===
string const std::string &
string std::string &&
cstring parametre const char *
data const char *, string::size_type n
range [konum1, konum2)
fill string::size_type, char
char char
substring const string &, string size_type idx
substring const string &, string::size_type idx, string::size_type
initializer_list std::initializer_list
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace nec_ornek_1{
    void ornek_1()//main'de cagir!!!
    {
        std::cout<<"ornek 1 Main\n";
        std::string s1{"test"};
        std::string s2{"can"};
        //auto len = s1.length();
        //std::size_t len = s1.length();
        std::string::size_type len = s1.length(); 
        std::cout<< "s1.legth(): " << s1.length() <<" \n";
        std::cout<< "s1.size(): " << s1.size() <<" \n";
        /* Yorum_no:2
            String stl container'ı olduğu için ve bütün container'ların ortak olarak size'ı var
            bir tanesi hariç onu görücez
            size ve length aynı fakat generic programlama tarafında size() kullanmak gerekiyor.
        */
        //std::size(s1); böyle de kullanıldığı görülebilir iterator başlık dosyasını include etmek gerekebilir.
        std::cout << std::boolalpha << s1.empty() << "\n"; //eğer boş ise true dolu ise false döner
        std::cout << std::boolalpha << s2.empty() << "\n"; //eğer boş ise true dolu ise false döner
        //while(!s2.empty())
            //gibi kullanımları olabilir
        //container'ların bütün öğeleri silmek için clear çağırabilir.
        s2.clear();
        std::cout << std::boolalpha << s2.empty() << "\n"; //eğer boş ise true dolu ise false döner
        //kapasite fonksiyonu da var ==> geçen derse gidebilirsin
        std::string s3 {"cansin"};
        
        //
        auto p = new std::string{"necati ergin eskisehir"};
        //String nesnesinin tutulduğu bellek alanı ile 
        //yazının tutulduğu bellek alanı farklı
        //kapasite fonksiyonu 
        std::string str{"13 haziran 2022 pazartesi"};
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n";
        //size ve kapasite aynı olabilir ama kapasite o string'in alabileceği maksimumu karakter sayısı
        auto cap = str.capacity();
        int cnt{};
        while(true)
        {
            str.push_back('x');
            if(str.capacity()>cap)
            {   
                std::cout<< ++cnt<<"size = " << str.size()<< "cap = "<< str.capacity() << "\n";
                cap = str.capacity();
            }
            if(cnt == 5)
                break;
        }
        //eğer kapasite tahminen belli ise reserve fonksiyonu kullanılabilir.
        //ne kadar büyüyeceğini biliyorsan bunu reserve mantıklı
        std::string str1{"13 haziran 2022 pazartesi"};
        str1.reserve(2000);
        cap = str1.capacity();   
        while(true)
        {
            str1.push_back('x');
            if(str1.capacity()>cap)
            {   
                std::cout<< ++cnt<<"size = " << str1.size()<< "cap = "<< str1.capacity() << "\n";
                cap = str1.capacity();
            }
            if(cnt == 5)
                break;
        }
    }
} 
//7869234 => 7'869'234 şeklinde yazabilirsin.
//kapasite implicit olarak shrink olmuyor
namespace nec_ornek_2{
    void ornek_2()//main'de cagir!!!
    {
        std::cout<<"ornek 2 Main\n;";
        std::string str(2'000'000, 'A');
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n";
        str.erase(1); //bu indexten başlıyarak geri düşüyor
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n"; //kapasite shrink olmadı bunu manual olarak 
        //kullanmak lazım
        str.clear();
        std::cout<< "str.size(): " << str.size() <<" \n";
        std::cout<< "str.capacity(): " << str.capacity() <<" \n"; //kapasite shrink olmadı bunu manual olarak 
    }
}
namespace nec_ornek_3{
    std::string foo(); //duruma göre copy alision olucak ya da move ctor çağırılacak
    void ornek_3()//main'de cagir!!!
    {
        std::cout<<"ornek 3 Main\n;";
        using namespace std;
        string s1 {"mustafa"};//cstring ctor;
        std::cout<< "s1.size(): " << s1.size() <<" \n";
        cout << "["<<s1 <<"]";
        char c[] = "volkan gundogdu";
        string s2 {c+7};
        std::cout<< "[" << s2 <<"]";
        auto s3 = s1;
        string s3 = s1;
        auto s4 = std::move(s1); //s1 moved from state'de kendisine yeni bir atama yapılabilir.
        string str;
        str = foo();//taşıma semantiği devreye girecek
        ///data ctor
        char str1[] = "Bugun pazartesi haftanin ilk gunu";
        string s_1(str1,5);
        std::cout<< "[" << s_1 <<"]";
        //range ctor
        string s_2 (str1,str1+5);//iki tane konum
        std::cout<< "[" << s_2 <<"]"; //operator<< fonksiyonunu kullanabiliyoruz.
        
        ///
        //string str_1('A'); //parametresi char olan ctor yok dolayısıyla tek bir karakterle başlatmak için
        string str_1("A");
        string str_2(1,'A');
        string str_3{'C'};
        /*
            std::cout << std::string(50,'*'); 
        */
       //substring ctor
        string str_4 {"volkan gundogdu"};
        string substr_1 {str_4, 7};
        std::cout<< "[" << substr_1 <<"]\n";
        string substr_2{str_4,7,3};
        std::cout<< "[" << substr_2 <<"]\n";
    }
}
namespace nec_ornek_4{
    void ornek_4()//main'de cagir!!!
    {
        std::cout<<"ornek 4 Main\n";
        std::string str;
        std::cout<< "isminizi girin: ";
        std::cin >>str;
        std::cout<< "[" << str <<"]";    
        //eger karakterlerin tamamını almak istersek getline kullanabiliriz
        getline(std::cin, str); //adl devreye girdiği için std::getline yazmamıza gerek kalmadı
        std::cout<< "[" << str <<"]";    
    }
}
namespace nec_ornek_5{
    void ornek_5()//main'de cagir!!!
    {
        using namespace std;
        std::cout<<"ornek 5 Main\n;";
        /* Yorum:MPOS
            1. işlevi arama fonksiyonları 
            Stringin kendi arama fonksiyonları var
            Yazı işlemlerinde arama işlemleri en çok ihtiyaç duyulan şey
            Geri dönüş değerleri indextir         
             
        */
        std::cout << string::npos << "\n";
    }
}

/* Yorum Baslik:nec_ornek_6
string'in npos'u 
arama bulunamadığında bu değer döndürülüyor
bu değer en uzun değeri
sentinel değer olarak kullanılabiliyor 
 */
namespace nec_ornek_6{

    int main_6()//main'de cagir!!!
    {        
        std::cout<<"ornek 6 main\n";

        std::string str{"eray goksu"};
        // std::string::size_type idx = str.find('a');
        auto idx = str.find('a');
        /*
            bulursa bulunduğu pozisyonun değerini döndürüyor
        */
            std::cout<< "idx: " << idx <<" \n";
            idx = str.find('t');
            /*
            */
            std::cout<< "idx: " << idx <<" \n";
            if(idx == std::string::npos) //idx'in scope if'ten de sonra kullanılacaktı
            {
                //Eğer yoksa anlamında 
            }
            //C++17 ile özel bir deyimi kullanılarak
            if(auto idx1 = str.find('t'); idx != std::string::npos)//if with initializer 
            {
                    //fakat idx1 sadece if'in doğru ve yanlış kısmında kullanılıyor.
            }
            return 6;
    }

}// nec_ornek_6 sonu

/* Yorum Baslik:nec_ornek_7 
    npos devamı
    geçilecek en güvenli değer    
 */
namespace nec_ornek_7{

    int main_7()//main'de cagir!!!
    {
        std::cout<<"ornek 7 main\n";
        
        return 7;
    }

}// nec_ornek_7 sonu

/* Yorum Baslik:nec_ornek_8 
    karaktere erişme

 */
namespace nec_ornek_8{

    int main_8()//main'de cagir!!!
    {        
        std::cout<<"ornek 8 main\n";
        using namespace std;
        string str{"eray goksu"};
        str[2] = '!';
        std::cout<< "str: " << str <<" \n";
        //str[20 ] //Undefined behavior
        //str[str.size()] eskiden tanımsız davranıştı. ama artık 
        //str[str.size()] null karaketr
        std::cout<< "static_cast<int>(str[str.size()]): " << static_cast<int>(str[str.size()]) <<" \n";
        
    return 8;
    }

}// nec_ornek_8 sonu

/* Yorum Baslik:nec_ornek_9 
    at() exception throw edebiliyor
 */
namespace nec_ornek_9{

    int main_9()//main'de cagir!!!
    {
        std::cout<<"ornek 9 main\n";
        std::string str{"eray goksu"};
        try
        {
            //auto c = str[230]; undefined behavior
            auto c = str.at(34);
        }
        catch(const std::exception& e)
        {
            std::cout <<"exception caught: "<< e.what() << '\n';
        }        
        return 9;
    }

}// nec_ornek_9 sonu


/* Yorum Baslik:nec_ornek_10 
    front() -> sequence container'daki ilk öğeye eriştiriyor
    back() -> yazının son karakteri
    Eğer yazı boş ise ub
 */
namespace nec_ornek_10{

    int main_10()//main'de cagir!!!
    {
        std::cout<<"ornek 10 main\n";
        std::string str{"eray goksu"};
        str.front() ='!';
        str.back()='!';
            std::cout<< "str: " << str <<" \n";
        return 10;
    }
}// nec_ornek_10 sonu

/* Yorum Baslik:nec_ornek_11 
begin() -> 
 */
namespace nec_ornek_11{

    int main_11()//main'de cagir!!!
    {
        std::cout<<"ornek 11 main\n";
                std::string str{"eray goksu"};

        for(auto iter = str.begin(); iter != str.end();++iter)
        {
            std::cout<< "*iter: " << *iter <<" \n";
        }
        //bunun yerine range based for loop kullanılabilir.
        //for(auto c:str) aşağıdaki ile aynı
        for(char c:str) 
        {
            std::cout<< "c: " << c <<" \n";
            c = '*'; //string nesnesinin karakteri değişmiş olmaz
        }
        std::cout<< "str: " << str <<" \n";
        for(const char c:str) 
        {
            std::cout<< "c: " << c <<" \n";        
        }
        for(auto& c:str) 
        {
            std::cout<< "c: " << c <<" \n";
            c = '*'; //string nesnesinin karakteri değiştirmiş oluruz 
            //çünkü c referans olarak kullandık.
        }
        std::cout<< "str: " << str <<" \n";            
        return 11;
    }
}// nec_ornek_11 sonu

/* Yorum Baslik:yazıyı değiştiren işlemler   
 */

/* Yorum Baslik:nec_ornek_12 
 */
namespace nec_ornek_12{

    int main_12()//main'de cagir!!!
    {
        std::cout<<"ornek 12 main\n";
        using namespace std;
        string str{"eray goksu"};
        string s = "metin erman";
        std::cout<< "str: " << str <<" \n";
        str = s;
        std::cout<< "str: " << str <<" \n";
        str = "murat";
        std::cout<< "str: " << str <<" \n";
        str = '2';
        std::cout<< "str: " << str <<" \n";
//Nicolai Jossulis
//  
    char c1 = 'A';
    char c2 = 'L';
    char c3 = 'P';
    str = {c1,c2,c3};//std::initializer_list'in atama operatör fonksiyonu
    std::cout<< "str: " << str <<" \n";

    return 12;
    }

}// nec_ornek_12 sonu

/* Yorum Baslik:nec_ornek_13    
Assign fonkiyonu 
 */
namespace nec_ornek_13{

    int main_13()//main'de cagir!!!
    {
        std::cout<<"ornek 13 main\n";
        std::string str{"eray goksu"};
        std::string s = "metin erman";
        //assign fonksiyonuna char dışında her şey atabiliriz.

        str.assign(20, 'W');
        std::cout<< "str: " << str <<" \n";
        
        std::vector<char> vec{'a','b','c'};
        str.assign(vec.begin(),vec.end());
        std::cout<< "str: " << str <<" \n";

        s.assign(str,5);
        std::cout<< "s: " << s <<" \n";


        return 13;
    }

}// nec_ornek_13 sonu

/* Yorum Baslik:nec_ornek_14 
 */
namespace nec_ornek_14{

    int main_14()//main'de cagir!!!
    {
        std::cout<<"ornek 14 main\n";
        
        string str{"eray goksu"};
        //str.assign(10,'A');//geri dönüş değeri string&
        std::cout<< "[" << str <<"]\n";
        
        str += 'n';
        std::cout<< "[" << str <<"]\n";
        
        string s {"erede"};
        str += s;
        std::cout<< "[" << str <<"]\n";

        str += "biliyor musun";
        std::cout<< "[" << str <<"]\n";

        return 14;
    }
}// nec_ornek_14 sonu

/* Yorum Baslik:nec_ornek_15 
 */
namespace nec_ornek_15{

    int main_15()//main'de cagir!!!
    {
        std::cout<<"ornek 15 main\n";
        string str{};
        for(char c='a';c<='z';++c)
        {
            str.push_back(c);
            std::cout<< "[" << str <<"]\n";
        }        
        return 15;
    }
}// nec_ornek_15 sonu

/* Yorum Baslik:nec_ornek_16 
    Append fonksiyonu
*/
namespace nec_ornek_16{
    int main_16()//main'de cagir!!!
    {
        std::cout<<"ornek 16 main\n";
        string str{"ali"};
        string s{"mustafa"};
        //alinin sonu 5 x karakteri
        str.append(5,'X');
        std::cout<< "[" << str <<"]\n";

        str.append(" necati ");
        std::cout<< "[" << str <<"]\n";

        str.append(s,3);
        std::cout<< "[" << str <<"]\n";

        str.append(s,3,4);
        std::cout<< "[" << str <<"]\n";
        return 16;
    }
}// nec_ornek_16 sonu

/* Yorum Baslik:nec_ornek_17 
    RESIZE fonksiyonu
    size'ı arttırıyor
    hem büyütme hem de küçütme yönünde işlem yapabiliyor.
    Kapasite size arttırıldığında artırılıyor fakat küçültme yönünde bu değişmiyor.
 */
namespace nec_ornek_17{

    int main_17()//main'de cagir!!!
    {
        std::cout<<"ornek 17 main\n";
        
        string str {"ali"};
        std::cout<< "str.length(): " << str.length() <<" \n";

        str.resize(20);
        std::cout<< "str.length(): " << str.length() <<" \n";

        str.resize(20, 'X');
        std::cout<< "str.length(): " << str.length() <<" \n";

        str.resize(6);
        std::cout<< "str.length(): " << str.length() <<" \n";

    return 17;
    }

}// nec_ornek_17 sonu

/* Yorum Baslik:nec_ornek_18 
 */
namespace nec_ornek_18{

    int main_18()//main'de cagir!!!
    {
        std::cout<<"ornek 18 main\n";
        string str {"murat"};
        std::cout<< "[" << str <<"]\n";
        //str.insert(1,) bu indexe ekleme yapılması demek
        str.insert(1,"ali"); //maliurat olmalı
        std::cout<< "[" << str <<"]\n";

        str.insert(0,"haci "); //maliurat olmalı
        std::cout<< "[" << str <<"]\n";

        str.insert(str.size(),"haci "); //maliurat olmalı
        std::cout<< "[" << str <<"]\n";

        string s{"aysegul"};
        str.insert(3,s);
        std::cout<< "[" << str <<"]\n";

        str.insert(0,s,4);
        std::cout<< "[" << str <<"]\n";

        str.insert(0,s,2,3);
        std::cout<< "[" << str <<"]\n";
        //index parametreli insert fonksiyonlar *this döndürüyor.        
        return 18;
    }
}// nec_ornek_18 sonu

/* Yorum Baslik:nec_ornek_19 
 */
namespace nec_ornek_19{

    int main_19()//main'de cagir!!!
    {
        std::cout<<"ornek 19 main\n";
        string str{"murat"};
        std::cout<< "str: " << str <<" \n";
        str.insert(str.begin(),'!');
        std::cout<< "str: " << str <<" \n";
        str.insert(str.begin(),{'w','x','j'});
        std::cout<< "str: " << str <<" \n";
        str.insert(str.begin(),20,'Z');
        std::cout<< "str: " << str <<" \n";
    return 19;
    }
}// nec_ornek_19 sonu

/* Yorum Baslik:SİLME İŞLEMLERİ   

 */
/* Yorum Baslik:nec_ornek_20 
iterator interface bütün container'ların 
2 tane silme işlemi var
konumu iterator olarak alır ve o konumu siler

Hepsinin geri dönüş değeri silenen konumun silinmiş öğenin konumu döndürülür.
 */
namespace nec_ornek_20{

    int main_20()//main'de cagir!!!
    {
        std::cout<<"ornek 20 main\n";
        string str{"omer ozbek"};
        
        str.erase(str.begin()+2);        
        std::cout<< "[" << str <<"]\n";

        str.erase(str.begin());        
        std::cout<< "[" << str <<"]\n";

        str.erase(str.end()-1);        
        std::cout<< "[" << str <<"]\n";
        return 20;
    }
}// nec_ornek_20 sonu

/* Yorum Baslik:nec_ornek_21 
 */
namespace nec_ornek_21{

    int main_21()//main'de cagir!!!
    {
        std::cout<<"ornek 21 main\n";
        string sline;
        std::cout<<"bir yazi girin:";
        getline(std::cin, sline);
        while(!sline.empty())
        {
            std::cout<< "[" << sline <<"]\n";
           // sline.erase(sline.begin());                
            sline.erase(sline.end()-1);//de olabilir        
        }
        return 21;
    }

}// nec_ornek_21 sonu

/* Yorum Baslik:nec_ornek_22 
    range alıp o range'teki öğeleri silende olabilirdi
 */
namespace nec_ornek_22{

    int main_22()//main'de cagir!!!
    {
        std::cout<<"ornek 22 main\n";
        string s {"SULEYMAN"};
        std::cout<< "[" << s <<"]\n";
        s.erase(s.begin()+1, s.end()-1);
        std::cout<< "[" << s <<"]\n";
        return 22;
    }
}// nec_ornek_22 sonu

/* Yorum Baslik:nec_ornek_23 
Index parametrede o indexten başlayarak geri kalan hepsi siliniyor
 */
namespace nec_ornek_23{

    int main_23()//main'de cagir!!!
    {
        std::cout<<"ornek 23 main\n";
        string s {"SULEYMAN"};
        std::cout<< "[" << s <<"]\n";    
        s.erase(3,1);
        std::cout<< "[" << s <<"]\n";
        s.erase(3);//idx, n alıyor n default olarak npos alıyor.
        std::cout<< "[" << s <<"]\n";

        s.erase(); // == s.clear(); gibi geri dönüş değeri *this
        //s.erase(stri)
        return 23;
    }
}// nec_ornek_23 sonu

/* Yorum Baslik:nec_ornek_24 
pop_back fonksiyonu
 */
namespace nec_ornek_24{

    int main_24()//main'de cagir!!!
    {
        std::cout<<"ornek 24 main\n";
        string s{"Suleyman sirri kundak"};
        while(!s.empty())
        {
            s.pop_back();
            std::cout<< "[" << s <<"]\n";
        }               
        return 24;
    }
}// nec_ornek_24 sonu

/* Yorum Baslik:nec_ornek_25 
Stringin karakterlerini silme :D 
 */
namespace nec_ornek_25{

    int main_25()//main'de cagir!!!
    {
        std::cout<<"ornek 25 main\n";
        string s{"Suleyman"};
        s.clear();
        s.erase();
        s.erase(0,string::npos);
        s.erase(0,s.size());
        s.erase(s.begin(),s.end());
        s.resize(0);
        s = "";
        s = {};
        s = string{};
        s.assign("");

    return 25;
    }

}// nec_ornek_25 sonu


/* 
    Yorum Baslik:ARAMA FONKSİYONLARI

    regex => regular expression ile bir kuralı ifade ediyoruz
    arka planda bir kutuphane regex stringini alıp işlemler yapıyor
    =>validation: yazı tanımlanan kurala uyuyor mu uymuyor mu?
    =>research: yazıda ilgili kural geçiyor mu
    =>replacement: 
*/
/* Yorum Baslik:nec_ornek_26 
 */
namespace nec_ornek_26{

    int main_26()//main'de cagir!!!
    {
        std::cout<<"ornek 26 main\n";
        string s{"ANKARA ANKARA GUZEL ANKARA"};
        //s.find();//karakter aranır yazı aranır substring aranır cstring aranır 
        //find ile search aynı anlamda
        //geri dönüş değeri index döndürüyor.
        //bulamazsa npos dönüyor.
        
        //bir yazı içinde direkt karakteri arayacak bir şey yapılabilir.
        //yazıyı sondan arayacak 
        //bir yazının içinde bir karakter grubundan olan birini arayabilirsin
        //
        /*
        s.find();
        s.rfind();
        
        s.find_first_of(); //bunun içindeki karakterlerden birinin ilk bulundugu yer
        s.find_last_of();
        s.find_first_not_of();
        s.find_last_not_of();
        ilk argümanlar aranacak değeri temsil ediyor
        string         substring         cstring         data        char ....
        
        */
       //index parametresine arguman geçmezsen 0 default argümanını yolluyorsun
       //if(auto idx = s.find(??);idx == string::npos) //bulunmamışsa

        s.find('A',15);//15 indexinden başlayarak A karakterini ara
        string str{"necati ergin"};
        str.find_first_of("tmks");
        str.find_first_not_of("tmks");//n
        str.find_last_of("tmks");
        str.find_last_not_of("tmks");        
        return 26;
    }
}// nec_ornek_26 sonu

/* Yorum Baslik:nec_ornek_27 
substring işlemleri maliyetli 
string view sınıfı daha az maliyetli olabilir
 */
namespace nec_ornek_27{

    int main_27()//main'de cagir!!!
    {
        std::cout<<"ornek 27 main\n";
        string s{"musa sertkaya"};
        auto str = s.substr(5,4);//sert
        auto str1 = s.substr(5);
        auto str2 = s.substr();
        std::cout<< "[" << str <<"]\n";
        std::cout<< "[" << str1 <<"]\n";
        std::cout<< "[" << str2 <<"]\n";         
        return 27;
    }

}// nec_ornek_27 sonu

/* Yorum Baslik:nec_ornek_28 
    lexicrophigical compare 
 */
namespace nec_ornek_28{

    int main_28()//main'de cagir!!!
    {
        std::cout<<"ornek 28 main\n";
        string s{"alican"};
        if(s == str){}
        if(s > str){}
        if(s == "alican"){}
        return 28;
    }

}// nec_ornek_28 sonu

/* Yorum Baslik:nec_ornek_29
compare fonksiyonu 
 */
namespace nec_ornek_29{

int strcmp(const char* p1, const char *p2);
//eğer p1 == p2 -> 0 
//eğer p1 > p2 -> +
//eğer p1 < p2 -> -

//int str::compare(); 
//tıpkı strcmp gibi kesin sonucu veriyor.
//a kesin sonucu b) binary ile ifade edilemen kompleks karşılaştırma için kullanılacak
    int main_29()//main'de cagir!!!
    {
        std::cout<<"ornek 29 main\n";

        return 29;
    }

}// nec_ornek_29 sonu


//case insensitivi karşılaştırma doğrudan yok.