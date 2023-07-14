/*19 derste yazılan kodlar ve notlar*/

// nested namespace

namespace nec
{
    namespace proj
    {

    } // namespace proj
}
// modern cpp ile
namespace A::B::C
// inline bir namespace
{
    int x;
} // namespace A::B::C
namespace A::B
{
    int ival;
}
namespace A
{
    int *p;
} // namespace A

namespace proj = A::B::C;
int main()
{
    A::B::C::x;
    proj::x;
    A::p = nullptr;
    A::B::ival = 45;
}

// inline namespace
namespace nec // inline olabilir.
{
    // namespace erg
    inline namespace erg // 3->inline namespace
    {
        int x, y;
        inline namespace proj
        {
            int a;
        }

    } // namespace erg
    // 1 - using erg
    // 2- using namespace erg; -> bunun yetersiz olduğu senaryolar için

} // namespace nec

int main()
{
    nec::x; // bunun legal olması için
    nec::a; // inline ile geçerli olacak
}
/////örn

namespace nec
{
    inline namespace old_version
    {
        class Myclass
        {
        };
    } // namespace old
#ifdef NEW_VERSION
    inline
#endif // bu şekilde macrolarada bağlamak mümkün
        namespace new_version
    {
        class Myclass
        {
        };
    } // namespace new
} // namespace nec

int main()
{
    nec::Myclass mx; // old_version_daki
}

// örnek
#include <chrono>

namespace A::B::inline C
{

} // namespace A::B::inline C

int main()
{
    A::B::x = 20; // yazabiliriz.
}

//===2.faydaso

namespace nec
{
    // namespace Nested
    inline namespace Nested
    {
        class C
        {
        };
    } // namespace Nested
    // 1- comment out ettik using namespace Nested;
    void func(Nested::C);
} // namespace nec

int main()
{
    Nec::Nested::C x;
    func(x); // Sentaks hatası
    // modern c++ öncesi problemli bir durumdu bunu önlemek için
    //
}

////////NESTED TYPE

class Myclass
{
    using Word = int; // bunu global alanda yapmak ile
    // class içinde yapmak çok farklı
    // typedef ile olabilir
    // enum olabilir.
    // kapsamlandırılmış türde olabilir
    // class Nested'da olabilir.

    Word mx; // derleyici ismi burada bulabilir.

    /*
    Word mx;
    typedef int Word;
    olursa burada bulunamaz sentaks hatası
    */
};

//
struct Word
{
    /* data */
};

class Myclass
{
    Word m_a; // Word ismi arandığında Struct Word bulunuyor
    typedef int Word;
    Word m_b; // buradaki intin eşizmi
};

//
struct Word
{
    /* data */
};

class Myclass
{
    Word m_a; // Word ismi arandığında Struct Word bulunuyor
    void func()
    {
        typedef int Word;
        Word m_c; // buradaki int türden.
        // sınıfın üye fonksiyonu içinde yapılan arama aynı şekilde yapılıyor.
        // önce blok içinde
        // kapsıyan blok içinde
        // class içinde aranacak
        // be typedef bulunacak
    }
    typedef int Word;
    Word m_c; // buradaki intin eşizmi
};

/////
class List
{
    struct Node
    {
        /* data */
    };

}

////İteratorler
class Vector
{
public:
    class iterator //
    {
    };
    iterator begin();
    // class Vector::iterator begin();
};

///
#include <vector>

int main()
{
    // std::vector<int>::iterator
    std::vector<int>::allocator_type;
}

//

class Myclass
{
public:
    class Nested
    {
    private:
        friend class Myclass; // Bu durumda enclosing type Myclass
        // private bölüme erişebilir ve aşağıdaki durum sentaks hatası olmaz
        void fun();
    };
    // type'ı member definition olması ile
    // memberı' olması farklı bir durum
    void foo()
    {
        // m.func() SENTAKS HATASI
        // Nested type'in provate bölümüne o nested type'in private bölümüne ERİŞEMEZ.
    }

private:
    Nested m;
}

//

class Myclass
{
public:
    class Nested
    {
        void foo()
        {
            x = 5; // Burada private bölüme erişimde bir sentaks hatası yok
            // MODERN CPP ÖNCESİ nested type'in, enclosing type'in private bölümüne erişmesi geçerli değildi.
        }
    } private : static int x;
}

///
class Encloser
{
    struct Nested
    {
        int get_sizeof_x()
        {
            return sizeof(mx);
        }
        int get_x()
        {
            return mx; // non static veri elemanı olduğu için
            // member'a ihtiyaç var
        }
        int encloser_get_x(Encloser &enc)
        {
            return enc.mx; // Eskiden geçersizdi C++11 ile geçerli kılında
        }
    };
    int mx;
};

//
#include <iostream>

class Myclass
{
public:
private:
    static void foo();
    class Nested
    {
    };
};

int main()
{
    Myclass::foo();    // SENTAKS HATASI Erişim kontrolüne takılır.
    Myclass::Nested b; ////SENTAKS HATASI Erişim kontrolüne takılır.
}

//
class Myclass
{
public:
    Nested foo();

private:
    class Nested
    {
    };
};

int main()
{
    // Myclass::Nested x = Myclass::foo(); //SENTAKS HATASI
    // FAKAT
    auto m = Myclass::foo(); // sentaks hatası değil!!!!
    // erişim kontrolü devre dışı kaldı
    // private bölümdeki isimler üstünde erişim kontrolü var
    // o ismi kullanmadığımız için bu legal olurdu
    // decltype(Myclass::foo()) y = Myclass::foo();
}

/*
    @konu_basligi: COMPOSITION
    containment ile

    Farklı sınıflar içerisindeki ilişkiler biçimine composition deniyor.
    Eğer bir işin gerçikleştirilmesi için 2 sınıf kullanılıyorsa
    bu sınıflar arasında association var denir.
    Fakat eğer association eğer nesnelerden biri diğer nesnenin sahibi ise
    buna aggregation deniyor. Her aggregation bir association'dur
    association ->
                    aggregation ->
                                    composition

    Örneğin arabanın motoru, araba bir sınıf motor bir sınıf, araba sınıfı
    motor sınıfının bir sahibi,
    composition: Sahip olan nesne ile sahip olunan nesne arasında ömürsel bir birliktelik
    var.

    İnsan beyin örneği composition :D ( Türkiye hariç )

    futbol klubü ile futbolcu ( aggregation )
    car - engine ( regilasyonun ne olduğuna bağlı olarak composition'da olabilir aggregation da olabilir. )

    CPP'de composition oluşturmanın oluşturmanın birden fazla yolu var

*/

/* Yorum_no:2
 İsim arama konusu nasıl? - Erişim kontrolü?
 Eleman olan sınıfın interface'ni kendine katabiliyor mu katamıyor mu?
 Veri elemanı nasıl ne zaman ctor olucak, taşınma semantiği nasıl?

*/

namespace composition_ornek_1
{

    class Engine
    {
    public:
        void start();
        void stop();
    };

    class Car
    {
    public:
        void start()
        {
            eng.start(); // elemanının interface'indeki fonksiyonları
            // kendi interface'mize dahil edebiliriz.
        }

    private:
        Engine eng; // Has a relationship.
    };

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 1\n;" Car mycar;
        // mycar.start(); //Sentaks hatası
        // bunu almanın yolu  yukardaki gibi çözebiliriz
    }
}

/* Yorum_no:2
    stack: bir container nesnesinin elemanı olarak alıp kullanıyor.
    queue
    private queue

*/
namespace composition_ornek_2
{

    class istack
    {
    public:
        void push(int val)
        {
            ivec.push_back(val);
        }
        bool empty() const
        {
            ivec.empty();
        }

    private:
        std::vector<int> ivec;
    } void main() // main'de cagir!!!
    {
        std::cout << "ornek 2\n;"
    }
}

/* Yorum_no:3
    Elemanın private bölümüne sahip olan nesnenin erişim hakkı yok
*/
namespace composition_ornek_3
{
    class Engine
    {
    private:
        void set_xyz();
        // friend class Car;
    };

    class Car
    {
    public:
        void carfunc()
        {
            // eng.set_xyz(); // SENTAKS HATASI
            // eğer engine sınıfı friendlik verirse sentaks hatası olmaz
        }
    };
    void main() // main'de cagir!!!
    {
        std::cout << "ornek 3\n;"
    }
}

/* Yorum_no:4

*/

namespace composition_ornek_4
{
    class Engine
    {
    public:
        Engine()
        {
            std::cout << "Engine ctor\n";
            // Veri elemanları hayata geldikten sonra buraya giriyor
        }
        ~Engine()
        {
            std::cout << "Engine destr \n";
        }
    };
    class Car
    {
    public:
    private:
        Engine m_eng; // default init edildi
    };                // Car Class
    void main()       // main'de cagir!!!
    {
        std::cout << "ornek 4\n;"
        {
            Car mycar;
        }
        std::cout << "main dewamke \n";
    }
}

/* Yorum_no:5
Ekran çıktısı
    Engine ctor
    Car ctor
    Car destor
    Engine destor
    En son üretilen nesne en son destroy ediliyor.
*/
namespace composition_ornek_5
{
    class Engine
    {
    public:
        Engine()
        {
            std::cout << "Engine ctor\n";
            // Veri elemanları hayata geldikten sonra buraya giriyor
        }
        ~Engine()
        {
            std::cout << "Engine destr \n";
        }
    };
    class Car
    {
    public:
        Car()
        //: m_eng() burada bu kod duruyor
        {
            std::cout << "Engine ctor\n";
            // Veri elemanları hayata geldikten sonra buraya giriyor
        }
        ~Car()
        {
            std::cout << "Engine destr \n";
        }

    private:
        Engine m_eng; // default init edildi
    };                // Car Class

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 4\n;"
        {
            Car mycar;
        }
        std::cout << "main dewamke \n";
    }
}

/* Yorum_no:6
    Derleyicinin yazacağı ctor:
    veri elemanlarının hepsini default init edilir:
*/

namespace composition_ctor_ornek_6
{
    class Member
    {
    public:
        Member(int);
    };

    class Owner
    {
    public:
        // bu sınıfın default ctoru delete edilmiştir.
        // Memberın default ctor'u olmadığı için
        // Owner() = delete derleyici tarafından yazıldı.

    private:
        Member mx;
    }; // Owner Class

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 6 Main\n;"
        // Owner x; //SENTAKS HATASI Delete edilmiş bir fonksiyona çağrı yapıldı hatası alırdık
    }
}

namespace composition_ornek_7
{
    class Member
    {
    public:
        Member(int);
        // privaet
        // Member(); olsaydıda sentaks hataları ve aynı durumlar oluşurdu.
    };

    class Owner
    {
    public:
        Owner(); // sentaks hatası yok
        // Owner(): mx{10} {} yapılabilir.
        /* Yorum
            Owner()
            ://mx()
            {
                SENTAKS HATASI OLUR
                Member'ın default ctor'u yok
                No appropriate default ctor
            }
        */
    private:
        Member mx = 10;
        // Member mx{10}; default member init 01:40:00
        // Inclass initializer kullanılabilir.

    }; // Owner Class

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 7 Main\n;"
    }
}

namespace composition_ornek_8
{

    class Student
    {
    public:
        Student(const char *pname, const char *psurname)
            : m_name{pname}, m_surname{psurname} {}
        // Ctor genellikle ctor init listi kullanarak elemanları init etmek için kullanabilir.
        /* Yorum
        Yukardaki yerine
            Student(const char* pname, const char* psurname)
            {
                m_name = pname;
                m_surname = psurname;
                m_name ve m_surname zaten init edildi
                gereksiz yere bir maliyet oluşturuyor
                not: veri elemanlarını init list ile init etmeye çalış
            }

        */
    private:
        std::string m_name, m_surname;
    };          // Student Class
    void main() // main'de cagir!!!
    {
        std::cout << "ornek 8 Main\n;"
    }
}

/* Yorum_no:
Copy ctor:
    Eger bir sinif icin copy ctor derleyici default ederse
    Implicitli olsun ya da programcı tarafından olsun
    Memberların copy ctor'ları çağırılır
*/
namespace composition_copy_ctor_ornek_9
{
    class Member
    {
    public:
        Member() = default;
        Member(const Member &)
        {
            std::cout << "Member copy ctor \n";
        }

    private:
    }; // Member Class

    class Owner
    {
    public:
        /* Yorum
            Owner(const Owner&other): mx(other.mx){}
        */
    private:
        Member mx;
    };             // Owner Class
    void ornek_9() // main'de cagir!!!
    {
        std::cout << "ornek 9 Main\n;" Owner x;
        Owner y = x; // Y için owner'ın copy ctoru-> bu kod içerisinde member'ın copy ctor'u çağırılıyor
    }
}

namespace composition_ornek_10
{
    class Member
    {
    public:
        Member()
        {
            std::cout << "Member default ctor \n";
        }
        Member(const Member &)
        {
            std::cout << "Member copy ctor \n";
        }

    private:
    }; // Member Class

    class Owner
    {
    public:
        Owner() = default;
        Owner(const Owner &other)
        //: mx() //mx(other.mx) DEĞİL bu kural farklı
        {
            std::cout << "Owner copy ctor \n";
        }

    private:
        Member mx;
    }; // Owner Class

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 10 Main\n;" Owner x;
        Owner y = x;
        // Çıkıt
        // Member default ctor
        // Member default ctor
        // Owner copy ctor
    }

    /* Yorum_no:
        EĞER Bir copy ctor'u biz yazıyorsak
        member'ın copyalanmasından biz sorumluyuz
        öbür türlü class'ta kullanılan member'ın kopyalanmasını engellemiş olabiliriz.
    */
}

namespace composition_copy_assignmentornek_11
{
    class Member
    {
    public:
        Member &operator=(const Member &)
        {
            std::cout << "Member copy assignment \n";
            return *this;
        }

    private:
    }; // Member Class

    class Owner
    {
    public:
        /*
        Owner & operator=(const Owner&other)
        {
            usign cstr = std::cout;
            cstr<<"Owner copy assignment";
            //burada nesnenin elemanı atanmamış değeri ile kalır.
            //atama işlevi yapılmaz
            //sentaks hatası olmaz
            //!!!!ATAMA YAPILMASI İÇİN BÜTÜN HEPSİNİN YAPILMASI LAZIM
            return *this;
        }

        derleyicinin yazdığı
        Owner &operator=(const Owner & other)
        {
            mx = other.mx;
            //member sınıfının copy assignmentı çağırılcak
        }
        */
    private:
        Member mx;
    }; // Owner Class

    void main() // main'de cagir!!!
    {
        std::cout << "ornek 11 Main\n;" Owner x, y;
        y = x;
    }
}

/* Yorum_no:11
namespace nec_ornek_12{
    class Student{
        public:
        Student &operator=(const Student &other)
        {
            //s1'in doğum tarih değeri
            //s2'ninkine atanmadı bunun için
            mbdate =other.mbdate; yazılmalı
        }
        private:
        Date mbdate;
    }
    void ornek_12()//main'de cagir!!!
    {
        std::cout<<"ornek 12 Main\n;"
        Student s1 = s2;
    }
}
*/

#include <iostream>
// 2:13:00'sonrasi

namespace composition_ornek_12
{

    class Member
    {
    public:
        Member() = default;
        Member(const Member &)
        {
            std::cout << "Member copy ctor\n";
        }
        Member(Member &&other)
        {
            std::cout << "Member move ctor\n";
        }

    private:
    };
    class Owner
    {
    public:
        // Derleyicinin yazdığı move ctor
        // Owner(Owner &&): mx(std::move(other.mx)){}
        // burada eğer mx işlevi yapılmazsa default ctor edilir
        // eğer mx(other.mx) yazılırsa taşınmaz kopyalanır
        // Derleyicinin yazdığı copy ctor
        // Owner(const Owner &): mx(other.mx){}

        Owner() = default;
        Owner(const Owner &other) : mx(other.mx) {}
        Owner(Owner &&other) {}
        // Owner(Owner && other): mx(other.mx){}
        // Owner(Owner && other): mx(std::move(other.mx)){}
        // En iyi yönte
    private:
        Member mx;
    };
    int main() // main'de cagir!!!
    {
        std::cout << "ornek 1 main\n";
        Owner x;
        Owner y = std::move(x);
        return 0;
    }

} // nec_ornek_1 sonu

namespace composition_move_assignment_ornek_13
{
    class Member
    {
    public:
    private:
    };
    class Owner
    {
    public:
        // derleyinicin yazdığı move assignment
        Owner &operator=(Owner &&other)
        {
            mx = std::move(other.mx);
            // mx = ( other.mx);//bu şekilde olursa copy ctor çalışır.
        }

    private:
        Member mx;
    };
    int main() // main'de cagir!!!
    {
        std::cout << "ornek 13 main\n";
        return 0;
    }

} // composition_ornek_13 sonu

/* Yorum Baslik:
    Çok sık yapılan bir hata sınıfın veri elemanlarından birinin
    kopyalamaya kapatılmış olması
*/

namespace composition_ornek_14
{
    class Member
    {
    public:
        Member() = default;
        Member(const Member &) = delete;
        Member &operator=(const Member &) = delete;
        // Copy ctor ve copy assignment iptal edilmiş
        // bunlar bildirilmemişse
        // Move ctor ve move assignable da değil
        // Bu class ne kopyalanabilir ne de taşınılabilir.
        // Daha çok copyalnamaz fakat move edilebilir.

        Member(Member &&);
        Member &operator=(Member &&);
        // Bu durumda member nesneleri kopyalanamaz fakat taşınılabilir.
    private:
    };
    class Owner
    {
    public:
        // Derleyicinin yazdığı copy ctor delete edilmiş olacak
    private:
        Member mx;
    };
    int main() // main'de cagir!!!
    {
        Owner x;
        // Owner y = x; //SENTAKS HATASI
        Owner y = std::move(x);

        std::cout << "ornek 14 main\n";
        return 3;
    }

} // nec_ornek_3 sonu

#include <memory>
namespace composition_ornek_15
{
    class Myclass
    {
    public:
        // Derleyici copy ctor yazmaz
        // Bunu biz yapmalıyız
        Myclass(const Myclass &) //: uptr(new int(*other.uptr))
        // İdeali bu sınıfında copy ctor olmaması.
        {
            // uptr için copy ctor cagırılmıycak
            // default ctor cagırılıcak
        }

    private:
        std::unique_ptr<int> uptr;
    };
    int main() // main'de cagir!!!
    {
        std::cout << "ornek  main 4\n";
        return 4;
    }

} // nec_ornek_ sonu