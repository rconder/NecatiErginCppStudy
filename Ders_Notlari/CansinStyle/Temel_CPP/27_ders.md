# 27.ders

```cpp
namespace ders_27
{
#include <iostream>
#include <exception>
#include <stdexcept> //cogu sey burada tanımlanmış

    /* Yorum Baslik:Exception Handling
    Private ve Protected inheritance daha sonra
    */
    /* Yorum Baslik:exception_handling_
    programming errors: Run time'da işini yapması gereken bir kod işini yapamıyor ve bunun nedeni kodunyanlış yazılması bu tür hatalara
    Çözümü kodun düzeltilmesi baş etme yöntemi:
    assertions: programın çalışma zamanında devreye giren programın doğru çalışıp çalışmasını test etmek.
    İki kategori
    1.Programın çalışma zamanına yönelik doğrulamalar
    2.Static assertionlar: eğer bir kodalama hatası varsa compile zamanda anlaşılıyor. "Bir bildirim fonksiyon değil."

    İşleyeceğimiz konu run-time da oluşan hatalar.
    Fonksiyon çalıştığında işini sağlıklı bir şekilde yapamayacağını anlıyor ve bu durumda
    Kodun yanlış yazılması söz konusu değil. Fonksiyon işi ne yapıyor.
    1-) Program büyük değilse programın sonlandırması söz konusu olabilir. Fakat genellikle kabul edilebilir değil.
    Burada hangi derinlikte çağırıldığı belli değil. Karar yetkisi en üst kodda veya main fonksiyonunda olabilir.
    Böyle hatalara exception ( istisna ) bu durumda kendisnini çağıran koda bu bilgiyi vermesi gerekiyor.

    C'gibi bir dilde exception handling'in olmadığı kullanılmadığı durumda bunlara traditional error handling deniyor.
    Neden dilin içine gömülü bir araç seti var
    =====================================================================

    int do_something() //işini yapamadığında bir bildirim/geri dönüş veriyor. Alternatif başka bir kodun çağırılması gerekiyor.
    //happy path: olması gereken işini yapması gereken yol
    //unhappy path
    //a)fonksiyonun geri dönüş değeri hata'nın olduğunu anlatıyor olaiblir. Örneğin 0'ın başarı değeri olması
    //b)fonksiyonun geri dönüş değerinde öyle bir geri dönüş değeri varki kodun işini yapamadığını söylüyor. Geri dönüş değeri bir bilgi fakat özel bir değerde
    //başarı bilgisi oluyor olabilir.
    //FILE * fopen(const char *pname, const char* openmode); => burada başarısız olursa nullptr döndürüyor.
    //ilk araç geri dönüş değerinin kullanılması.
    //2.si ise Global bir hata değişkeni
    //int errno; ve fonksiyon çağırıldığında errno'nun değeri set edilmişse fonksiyon bir hata durumuyla karşılaşmış demek oluyor.
    {


    }
    =======================================================================
    Geleneksel hata işlemenin dezavantaj oluşturduğu yerler var:
    --------------------------------------------------------------------------------
    zorlayıcı bir faktör yok - not forcing: çağıran kodun geri dönüş değerini test edip/etmemesi
    zorlayıcı değil. Çağıran kod bunu discard edebilir ve yaptırımı yok. Hatanın handle edilmesi mecbur hale getirilmesi
    örneğin hata işlenmediğinde programın abort edilmesi sağlanabilir.

    --------------------------------------------------------------------------------
    İş gören kod ile, hata işleyen kod iç içe geçmiş durumda
    x = do_something();
    if(x == hata_kodu_mu)
    {}
    //Ne kadar if varsa hata yapma riski o kadar artar işlenmeyen hata ihtimali artar
    kodun anlaşılmasını ve test edilmesini de zoralaştırıyor

    Hata işleyen kod ve iş gören kod birbirinden ayrılsın.
    Exception handling'in en önemli araçlarından biri bu
    --------------------------------------------------------------------------------
    Çoğunlukla fonksiyonlar birbirini çağırıyor ve bu fonksiyonlardan biri işini yapamadığında
    en son çağırılan onu bir önceki çağırına haber verebiliyor. O yüzden hatayı işleyecek kodun
    öncekine iletmesi elden ele oluyor.

    Daha iyisi doğrudan programın çalışma zamanında hatayı tespit eden koddan direkt olarak hatayı handle edecek koda aktarılsın.
    --------------------------------------------------------------------------------
    Geri dönüş değeri bunun için uygun bile olmayabilir.
    int atoi(const char *); => Hata kodu olarak döndüreceği değer ile aynı veri olabilir.
    Out parametre kullanılabiliyor.
    C++'de iki 3 sınıfı birbirine pairlenen yapı türü kullanılabiliyor.

    Ya da bunun için
    strcut Data{
        int error_code;
        int data;
    }
    şeklinde de iletilebiliyor.
    ----------------------------------------------------------------------------------------
    Bazı domainlerde exception handling kullanılması yasaklanmış olduğu için kullanılamadığı senaryolarda var.
    =======================================================================
    Exception handling araç seti bu problemleri engelliyor. Bu aracın kullanılması Tasarım aşamasında belirlenen bilir

    ctor's çalışması için bir takım koşulların sağlanması gerekiyor olabilir. ve ctor'lar geri dönüş değeri kavramına sahip değil
    exception throw'da edilemediği zaman eskiden zombi gibi iş görmeyen bir şekilde kalıyor ve nesnenin state'inde bunu belirtiyoruz.
    ========================================================================
    Exception handling:
    forcing bir mekanizma
    Eğer fonksiyon exception gönderirse bu ya işlenecek ya da işlenecek yoksa std kütüphanenin abort fonksiyonu çağırılıp programın
    sonlanması sağlanıyor

    Happy path ve unhappy path birbirinden ayrı bir durumda

    Hatayı tespit eden kod ile hatayı handle edecek kod arasında direkt bir ilişki var.

    Müdahale etmeyeceğin bir hatayı(exception) müdahale etmeye çalışma!!!!
    Hangi kod handle edecekse hatayı o yakalayacak.

    Eğer yapılacak bir şey varsa hatayı orada yakalamaya çalış.


    Bu araç seti CPP'da programın çalışma zamanında bir hata olduğu için bu araç seti kullanılıyor.
    Kontrol deyimi olarak kullanmamaya çalış

    exception handling araç setinde 3 tane keyword var. Cpp'de final yok nedeni kendi finalımızı uğraştırabiliyoruz
    ## throw

    exception throw: Bir fonksiyon işini yapamadığında bir nesne oluşuturuyor ve bu nesnenin nedeni fonksiyonun işini yapamadığını anlatan bir nesneyi çağıran fonksiyonlara
    bunu yolluyor ve programın çalışma zamanında işini yapamayan koddan bu hatayı handle etcek exception object thwrow edilioyr.

    throw statement; İşini yapamayan ve bunları çağıran fonksiyonlara haber vermek istiyon kod throw expr; veriyor
    Hatayı işleyen koda exception handler ediliyor eğer kimse yakalamazsa buna uncaught exception deniyor.
        std::terminate isimli fonksiyonu çağırılıyor.
            std::abort çağırıyor.
        - Amaç davranışın özelleştirilebilmesi. ismi set terminate yapılarak abort yerine başka bir fonskiyon çağırılabiliyor.
    Gönderilen  herhangi bir hata mutlaka yakalanmalı, gerekli önlemler alınarak program sonlandırılmalı ve devam etmeli

    resumptive: Hata yakalanıor ve program çalışmaya devam ediyor. Kaynak sızıntısı olmadan devam etmesi lazım.
    terminative: Hata yakalanıyor fakat program sonlanmadan önce kaynakların geri vermesi gerekiyor

    try:
    Bir kod bloğu oluşturuyoruz ve buna try {} blok diyoruz
    try{
        - Eğer bu blok içinde çalışan kodlardan gelen hataları yakalama olasılığımız var.
        - Exception'ın çağırılan ilk fonksiyondan değil daha alt seviyelerdeki çağırılardan gelecek exception'ı da yakalıyor.
        - Try bloğu içinde de blok scope kuralları geçerli
    }

    Try bloğunu en az 1 catch bloğu izlemek zorunda
    catch: Fiilen hatayı yakalayıp müdahale edecek kod bloğu. Exception gönderildiğinde o exception'ı yakalayacak bir catch bloğu

    catch(-catch parametresi-)//kullanılmayacaksa isim vermeyede biliriz.
    {
        Yukardaki try bloğu içinden gönderilen hata nesnesinin türü int ise programın akışı bu catch bloğuna girsin ve
        gönderilen hata nesnesinin değeri int bloğuna girsin.
    }
    catch(int)
    {}
    catch(double)
    {}
    catch(unsigned int)
    {}
    //hangisine gireceği nesneye göre belirleniyor.
    // Catch parametresi için bu amaçla oluşturulmuş bir sınıf türü kullanıcak

    catch(MyException &r) //kopyalama yerine referans semantiği ile kullanıcak ve böylece polymorphic sınıf türleride yakalanabilir.

    Sentaks olarak fonksiyonu andırsada fonksiyon değil. Geri dönüş değeri yok
    Eğer catch parametresi kullanılmayacaksa isim verilmek zorunda değil
    Sadece tek parametreye sahip olabilir.

    Eğer cathc parantezi içine (...) elipsis atomu yazılırsa buna catch-all deniyor ve hangi türden hata gönderilirse gönderilsin
    tüm hatalar yakalanacak.

=====================================================================================================
    return statement
    exit / abort / terminate
    throw statement
    C++20 ile dile eklenen
    coroutine = Bu da bir fonksiyon ve çalışması durdurulup-çalıştırılabilen bir fonksiyon. Suspense olup Resume olabiliyor.
    -Böylece threadler dışına alternatif ve birlikle kullanılabilen bir araç seti
    subroutine = fonksiyon kodu çalışıyor ve çalışmasının akışı bittiğinde fonksiyonu çağıran koda geri dönüyor
=====================================================================================================
    */

    namespace exception_handling_
    {
        /* Yorum Baslik:terminate'in
            set terminate isimli bir fonksiyonu var
        */
        // using terminate_handler = void(*)();
        // typedef void(*terminate_handler)();
        // terminate_handler geri dönüş değeri olmayan parametresi olmayan bir function pointer
        // terminate_handler set_terminate(terminate_handler); Çağıran koddan geri dönüş değeri ve parametresi olmayan bir fonksyion istiyor.

        void f4()
        {
            std::cout << "f4 cagirildi.\n";
            throw 1; // çok büyük çoğunlukta böyle primitive türle dönme
            // program da yakalanmadığı için burada sonlanıyor
            std::cout << "f4 sonlandi.\n";
        }
        void f3()
        {
            std::cout << "f3 cagirildi.\n";
            f4();
            std::cout << "f3 sonlandi.\n";
        }
        void f2()
        {
            std::cout << "f2 cagirildi.\n";
            f3();
            std::cout << "f2 sonlandi.\n";
        }
        void f1()
        {
            std::cout << "f1 cagirildi.\n";
            f2();
            std::cout << "f1 sonlandi.\n";
        }

        int main() // main'de cagir!!!
        {
            std::cout << "exception_handling_ main\n";
            f1();
            std::cout << "exception_handling_ main sona erdi\n";
            return 0;
        }

    } // exception_handling_ sonu

    /* Yorum Baslik:terminate
     */
#include <iostream>
    namespace terminate
    {
        /* Yorum Baslik:terminate'in
        set terminate isimli bir fonksiyonu var
    */
        // using terminate_handler = void(*)();
        // typedef void(*terminate_handler)();
        // terminate_handler geri dönüş değeri olmayan parametresi olmayan bir function pointer
        // terminate_handler set_terminate(terminate_handler); Çağıran koddan geri dönüş değeri ve parametresi olmayan bir fonksyion istiyor.

        void f4()
        {
            std::cout << "f4 cagirildi.\n";
            throw 1; // çok büyük çoğunlukta böyle primitive türle dönme
            // program da yakalanmadığı için burada sonlanıyor
            std::cout << "f4 sonlandi.\n";
        }
        void f3()
        {
            std::cout << "f3 cagirildi.\n";
            f4();
            std::cout << "f3 sonlandi.\n";
        }
        void f2()
        {
            std::cout << "f2 cagirildi.\n";
            f3();
            std::cout << "f2 sonlandi.\n";
        }
        void f1()
        {
            std::cout << "f1 cagirildi.\n";
            f2();
            std::cout << "f1 sonlandi.\n";
        }
        void necfunc()
        {
            std::cout << "nec func cagirildi islevi std::terminate cagirdi\n";
            std::exit(EXIT_FAILIURE);
        }
        int main() // main'de cagir!!!
        {
            std::set_terminate(&necfunc);
            std::cout << " main bas\n";
            f1();
            std::cout << "main sonu\n";
            return 0;
        }
    } // terminate sonu

    /* Yorum Baslik:exception_yakalamaca
     */
    namespace exception_yakalamaca
    {

        void f4()
        {
            std::cout << "f4 cagirildi.\n";
            throw 1; // çok büyük çoğunlukta böyle primitive türle dönme
            // program da yakalanmadığı için burada sonlanıyor
            // Burada ne integral promotion ne de tür dönüşümü var
            // Gönderilen hata nesnesinin türü ile aynı olmak zorunda
            std::cout << "f4 sonlandi.\n";
        }
        void f3()
        {
            std::cout << "f3 cagirildi.\n";
            f4();
            std::cout << "f3 sonlandi.\n";
        }
        void f2()
        {
            std::cout << "f2 cagirildi.\n";
            f3();
            std::cout << "f2 sonlandi.\n";
        }
        void f1()
        {
            std::cout << "f1 cagirildi.\n";
            f2();
            std::cout << "f1 sonlandi.\n";
        }
        void necfunc()
        {
            std::cout << "nec func cagirildi islevi std::terminate cagirdi\n";
            std::exit(EXIT_FAILIURE);
        }

        int main() // main'de cagir!!!
        {
            std::set_terminate(&necfunc);
            std::cout << " main bas\n";
            try
            {
                f1();
            }
            catch (int x)
            // Kopyalama semantiği var ama çok büyük çoğunlukla referans semantiği kullanılacak
            {
                std::cout << "main de hata yakalandi x: " << x << " \n";
            }

            std::cout << "main sonu\n";
            return 0;
        }
    } // exception_yakalamaca sonu

    /* Yorum Baslik:birden_fazla_catch_blogu
     */
    namespace birden_fazla_catch_blogu
    {
        void f4()
        {
            std::cout << "f4 cagirildi.\n";
            throw 13;
            // throw 2.1;
            // throw 2u;
            std::cout << "f4 sonlandi.\n";
        }
        void f3()
        {
            std::cout << "f3 cagirildi.\n";
            f4();
            std::cout << "f3 sonlandi.\n";
        }
        void f2()
        {
            std::cout << "f2 cagirildi.\n";
            f3();
            std::cout << "f2 sonlandi.\n";
        }
        void f1()
        {
            std::cout << "f1 cagirildi.\n";
            f2();
            std::cout << "f1 sonlandi.\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "birden_fazla_catch_blogu main\n";
            try
            {
                f1();
            }
            catch (int x)
            {
                std::cout << "main de hata yakalandi x: " << x << " \n";
            }
            catch (double x)
            {
                std::cout << "double x" << x << "\n";
            }
            catch (unsigned int x)
            {
                std::cout << "unsigned int x: " << x << " \n";
            }

            return 0;
        }

    } // birden_fazla_catch_blogu sonu
    /* Yorum Baslik:polymorhic_istisna
    eğer catch parametresi taban sınıf türündense de exception yakalanıyor.
     */
    namespace inherit_istisna
    {
        class ExceptionBase
        {
        };
        class NecException : public ExceptionBase
        {
        };

        void f4()
        {
            std::cout << "f4 cagirildi.\n";
            throw 13;
            // throw 2.1;
            // throw 2u;
            std::cout << "f4 sonlandi.\n";
        }
        void f3()
        {
            std::cout << "f3 cagirildi.\n";
            f4();
            std::cout << "f3 sonlandi.\n";
        }
        void f2()
        {
            std::cout << "f2 cagirildi.\n";
            f3();
            std::cout << "f2 sonlandi.\n";
        }
        void f1()
        {
            std::cout << "f1 cagirildi.\n";
            f2();
            std::cout << "f1 sonlandi.\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "polymorhic_istisna main\n";
            try
            {
                f1();
            }
            // catch(const NecException &)
            catch (const ExceptionBase &)
            {
                std::cout << "hata yakalandi\n";
            }
            return 0;
        }

    } // polymorhic_istisna sonu

    /* Yorum Baslik: Hata Nesnesi
    Gönderilen hata nesnesi hata hakkında en önemli bilgi. Hatayı iletmek amaçlı bir tür zaten neden hata gönderildiğini anlatan en önemli bilgi.
    Örneğin
    class DividedByZeroError{}; Gibi olabilir.
    class BadDate{}; Geçersiz bir tarihin oluştuğu bilgisini iletiyor olucak.

    2 ayrı şekilde bilgi iletme şansımız var
    Hata nesnesinin türü çoğu zaman yeterli
    örneğin std::badalloc allocation'ının yapılamadığını anlatıyor.
    std::out_of_range()
    std::length_error()

    Dolayısıyla hangi sınıf türünden exception throw edildiğinde anlatıyor.

    Ve Sınıfın üye fonksiyonları ile örneğin
    const char * what() fonksiyonu çağırıldığında daha spesifik bir bilgi verilebilir.

    class FileReadError //dosya okuma ile ilgili bir hata olduğuu belli
    {
        getLine();//hangi satırda hata olduğunu belirtiyor.
    }

    Hangi hataya müdahale etmek istiyorsak ona yönelik bir catch bloğu oluşturmalıyız.

    özet olarak 2 şekilde hata hakkında bilgi var ilgili sınıfın ismi diğeri ise o sınıfın fonksiyonları

    std::Exception standart kütüphanenin gönderdiği tüm hata nesnesinin taban sınıfı yani
    catch parametresi std::exception &ex-> tüm hata nesnelerini yakalar. Standart kütüphanelerin bütün hata nesnelerini yakalama şansımız var
    Bu sınıfın what isimli bir virtual fonksiyonu var ve kalıtım yoluyla elde edilen tüm sınıflar bu fonksiyonu override ediyorlar.


    Eğer burada sanal bir fonksiyon varsa virtual dispatch'ten yararlanılabilmesi için bu parametrenin sınıf türünden referans olması lazım.
    Sıra dışı marjinal senaryolar sayılmazsa genel olarak
    catch parametrelerini referans yapın
    a) böyleyce hata yakalanması süresince object silicing olmasın, copy ctor'u devreye girmesin.
    ve what fonksyionu override ediliyor.
    Yazılar standart değil ve implementasyona bağlı
    b) copy ctor exception throw edebilir

    Sıradışı senaryolar dışında referans olarak kullan!
    catch(std::exception & ex)
    {
        cout << ex.what() <<"\n";
    }
    Eğer nesne kullanılmayacaksa isim verme.
    yakalanan hata nesnesinin set edilebilme şansı var
    catch(std::MyException &ex)
    {
        ex.set_value("....")
    }

    Eğer sadece sınıf nesnesinin const üye fonksiyonu çağırılacaksa parameter const olmalı
    catch(const std::MyException &ex){ex.what();}

    Bir sınıf hiyerarşisi kullanılıyor çünkü
        -Örneğin en tepede
        class exception
        {

        }


    Eğer run time hatalarını yakalanmak istiyorsak
     RunTimeError sınıfı türünden ya da ondan kalıtım yoluyla elde edilen sınıf türündense catch bloğu yakalayabilir.

    class exception{
        public:
        virtual const char* what() const;
    }


    Logic_error: Programlama yoluyla yakalanabilecek hatalar aşağı yukarı

    */
    /* Yorum Baslik:out_of_range
     */
    namespace out_of_range_ornek
    {

        void func()
        {
            std::string str("necati ergin");
            std::size_t idx = 450;
            auto c = str.at(idx);
            std::cout << "bu yazi görülmemeli\n";
        }
        int main() // main'de cagir!!!
        {
            std::cout << "out_of_range main\n";

            // func(); //Exception throw edildi ve yakalamazsak
            try
            {
                func();
            }
            // catch(const std::exception& e)
            // catch(const std::logic_error& e): warning logic_error caught by exception
            // buradaki sıralama daha özelden daha genele doğru olmalı.
            catch (const std::out_of_range &e)
            {
                std::cout << e.what() << '\n';
            }
            catch (const std::logic_error &e)
            {
                std::cout << e.what() << '\n';
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << '\n';
            }
            catch (...)
            {
                // herhangi bir sınıf türündense burası yakalar
            }
            return 0;
        }
    } // out_of_range sonu

    /* Yorum Baslik:
     throw expr; //Bu ifade bir L-val expression olabilir
     class BadDate{



     };
     ya da
     class BadDate: public logic_error{}; olabillir

     void func()
     {
         BadDate bd;
         throw bd; //Burada BadDate copy ctor'una çağrı yapılması gerekiyor.
     }
     Hata nesnesi bd nesnesi değil çünkü bloktan çıktığından bd nesnesinin hatası sona eriyor.
     Derleyici burada bir exception nesnsesi oluşturuyor
     İki şekilde kod üretme ihtimali var
     1-) Copy ctor'una çağrı yapmak
     2-) Move ctor'una çağrı yapmak
     3-) Copy elision

     throw ifadeleri genel olarak
     throw std::bad_alloc{}; //olarak yazılıp copy elision oluyor
    */

    /* Yorum Baslik:copy_elision_for_throw
     */
    namespace copy_elision_for_throw
    {
#include <stdexcept> //cogu sey burada tanımlanmış
        void func()
        {
            if (1)
            {
                throw std::out_of_range{"aralik disi deger\n"};
                // out_of_range sınıfının default ctor'u yok
                // artik const string & parametreli sınıfı da var
            }
        }
        void func1(const std::string &name)
        {
            if (1)
            {
                throw std::out_of_range{name + " yazisi "};
                // modern cpp öncesi    {name.c_str()};
                //  out_of_range sınıfının default ctor'u yok
                //  artik const string & parametreli sınıfı da var
            }
        }
        int main() // main'de cagir!!!
        {
            std::cout << "copy_elision_for_throw main\n";
            return 0;
        }
    } // copy_elision_for_throw sonu

    /* Yorum Baslik:  yapılabilecek tipik hatalar
    - Referans operatorünü yazmamak object slicing olabilir. Sentaks hatası olmayacak
    ve bu durumda copy ctor çağırılacak ve eğer burdada exception throw edilirse terminate fonksiyonu çağırılıcak.

    Eğer gönderilen hata Enum nesnesi ise


    */

    /* Yorum Baslik:enum_Alert
    olabilir ama çok istisnai
     */
    enum class Alert
    {
        Red,
        Green,
        Yellow
    };
    namespace enum_Alert
    {

        void func()
        {
            throw Alert::Red;
        }

        int main() // main'de cagir!!!
        {
            std::cout << "enum_Alert main\n";
            return 0;
        }
    } // enum_Alert sonu

    /* Yorum Baslik: Hata işleyen kod ( hatayı yakalayan kod) tipik olarak: 
    - try { foo(); }catch (const BadDate&)
    1. ilke her hata yakalamaya çalışma!!!!!!!!!!!!!!!! 
    Eğer catch bloğunda ne yapılacağı belli değilse yakalama
    
    - Eğer hatayı yakalandıktan sonra kaynak sızıntısı oluyorsa önerilen bir durum değil
    Exception safety = Gönderilen exception yakalanacak ve kaynak sızıntısı olmayacak

    2. Exception'ının yakalanması ve başka bir sınıf türünden exception gönderilmesi. NEDEN?
    Çok spesifik sistem seviyesinde bir exception geldiyse burada daha detaylı (yükse) bir exception gönderilebilir
    Exception translate

    3. Kısmi müdahale: Exception yakalanıyor bir takım işlemler yapılıyor. Ve aynı exception tekrar gönderiliyor.
    Exception rethrow.
    
    -Kaynakların geri verilmesi seyrek olarak var onun yerine RAI idiomu ile destructor çağırılmaması     
    
     */

    /* Yorum Baslik:exception_rethrow 
     */
    namespace exception_rethrow{
    
    void func()
    {
        try
        {
            /* code */
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;// re-throw sentaksı aynı hata üst seviyedeki kodlara yönlenioyr
            //throw ex; ile farklı burada yeni bir hata nesnesi oluşturuluyor. Copy-ctor çağırılacak ve dinamik tür kaybedilmiş olacak
            //burada örneğin out_of_range ise onun yerine exception türünden yollanacak.
        }
        
    }
        int main()//main'de cagir!!!
        {
            std::cout<<"exception_rethrow main\n";
        return 0;
        }
    
    }// exception_rethrow sonu
}
```
