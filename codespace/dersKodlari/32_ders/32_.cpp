
namespace ders_32
{
    #include <iostream>   
    namespace most_vaxing_parse{
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
        class A{};
        class B{
            public: B(A){}
        };
        B   bx(A(*)()); //bununlar B bx(A()) ile aynı 
        A foo();
        int main()//main'de cagir!!!
        {
            std::cout<<"most_vaxing_parse main\n";
            B bx(A());//ctor'a A türünden nesne olucak nesneyi vermek istiyoruz fakat
            //burada fonksiyon tanımlanmış lokal düzeyde yapılmış bir fonksiyon ismi
            //B bx(A(*)()); şeklinde bildirilmemesini bir farkı yok 
            //burada nesne oluşturmuyor
            bx(foo);
            bx(&foo);
            return 0;
        }    
    }// most_vaxing_parse sonu

    namespace reference_qualifier{
    /* Yorum Baslik:reference_qualifier  | ref qualifier 
    Öyle durumlar varki sınıfın bazı üye fonks. sadece L value expr kategorisindeki nesneler
    için çağırılmasını istiyoruz.

    Peki neden 
     */    
    class Myclass{
    public:
        void func(); // Hem R Value olan sınıf nesneleri için Hem de L Value sınıflar için
        //çapırılabilir.
        void foo()&;//Bu sadece L value için çağırılabilir R val için sentaks hatası
        void bar()const &;// const sınıf değeri için çağırılabiliyor
        void boo()&&;//Bu sadece R value için çağırılabilir L val için sentaks hatası
        //Myclass &operator=(const Myclass &)& = default;
        //sınıfın atama operator fonksiyonunun hem default ettirdik hem
        //de L value reference qualifier ekledik
    private:
        
    };
        int main()//main'de cagir!!!
        {
            std::cout<<"reference_qualifier main\n";
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

} // namespace ders_32

