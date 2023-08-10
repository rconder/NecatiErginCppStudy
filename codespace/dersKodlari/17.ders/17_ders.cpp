
#include <iostream>
#include <vector>

using namespace std;

namespace salt_okuma_array
{
    int main()
    {
        vector<int> ivec{1, 3, 5, 7};
        const vector<int> cvec{1, 3, 5, 7};

        ivec[2] = 12;
        // cvec[2] = 3; //SENTAKS HATASI salt okuma amaçlı kullanım
        auto i1 = ivec[2];
        auto i2 = cvec[2];
    }
}

namespace intarray_sinifi_operator_overloading
{
    /*
    basit bir array sınıfı
    sadece köşeli parantez operatoru
     */
    class intarray
    {

    public:
        int &operator[](size_t) // const olmayan intarray nesneleri için bu
        {
            return mp[idx];
        }
        const int &operator[](size_t) const // const olan int array nesneleri için bu
        {
            return mp[idx];
        }
        std::size_t size() const
        {
            return msize;
        }
        explicit intarray(size_t size) : msize(size), mp(new int[msize])
        {
            std::memset(mp, 0, msize * sizeof(int));
        }

        friend std::ostream &operator<<(std::ostream &os, const intarray &ar)
        {
            os << '[';
            for (auto i = 0u; i < ar.size() - 1; ++i)
                os << ar[i] << ", "; // ar.mp[i]' de yazılabilirdi
            os << ar[ar.size() - 1] << "]";
        }
        ~intarray()
        {
            delete[] mp;
        }
        intarray(const intarray &) = delete;
        intarray &operator=(const intarray &) = delete;
        //
    private:
        //.....
        int *mp;
        std::size_t msize;
    };

    int main()
    {
        intarray a(10);
        cout << a << "\n";

        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i * 2;
        }
        a.operator[](5) = 34;

        return 0;
    }

}

namespace sarmalayan_sinif_ornek
{
    // template <typnema T>
    class SmartPtr // derleyiciye kod yazdıran kod
    {
    };
    class SmartStringPtr
    {                                                      // dinamik ömürlü string nesneleri için oluşuturulduğunu varsay
    public:                                                // dinamik ömürlü nesne adresi istiyor
        explicit SmartStringPtr(std::string *p) : mp{p} {} // özel bir gerekçe yoksa explicit yap
        ~SmartStringPtr()
        {
            delete mp;
        }
        std::string &operator*()
        {
            return *mp;
        }
        std::string *operator->()
        {
            return mp;
        }

    private:
        std::string *mp;
    }

    int  main()
    {
        {
            SmartStringPtr ptr{new std::string{"necati ergin"}};
            // std::cout << *ptr<<'\n' ; yapılabilirdi.
            std::cout << (*ptr).size() << '\n';

            std::cout << "uzunluk = " << ptr->length() << "\n";
            std::cout << "uzunluk =" << ptr.operator->()->length() << "\n";

            for (size_t i{}; i < (*ptr).size(); ++i)
            {
                std::cout << (*ptr)[i] << ' ';
            }
        }
        retun 0;
    }
}

namespace operator_parantez_overloading
{
    // operator () overloading
    class Mycalss
    {
        public:
         void operator()()
                // void operator() (int x) {std::cout<<" Myclass::operator()(x) x = " << x " \n"; }
                void
                operator()(int x = 0)
        {
            std::cout << " Myclass::operator()(x) x = " << x " \n";
        }
        {
            std::cout << " Myclass::operator()()\n";
        }
        void operator()(double x) { std::cout << " Myclass::operator()(x) x = " << x " \n"; }
    };

    int main()
    {
        Myclass mx;
        mx();
        mx(10.0);
        // mx.operator()(10.0);
        return 10;
    }
}

namespace random_sayi_uretmece
{
    class Random
    {
        // fonksiyon operator fonksiyonun operandı olduğunda rastgele sayı üretsin
    public:
        Random(int low, int high) : m_low{low}, m_high{high} {}
        int operator()()
        {
            ++m_count;
            return std::rand() % (m_high - m_low + 1) + m_low;
        }
        int get_call_count() const
        {
            return m_count;
        }

    private:
        int m_low;
        int m_high;
        in m_cout{};
    }

    int
    main()
    {
        Random rand1{37, 56};
        for (int i = 0; i < 100; ++i)
        {
            std::cout << rand1() << " ";
        }
        std::cout << "\n";
        Random rand2{1987, 1999};
        for (int i = 0; i < 100; ++i)
        {
            std::cout << rand2() << " ";
        }
    }
} // namespace random_sayi_uretmece

namespace random_sayi_stl_ornek_
{
#include <random>
    int main()
    {
        mt19937 eng;
        uniform_int_distribution dist{700, 7600};

        for (int i = 0; i < 100; ++i)
        {
            cout << dist(eng) << " "; // dist( )
        }
    }
}
/** Tür dönüşüm operatorleri */
namespace tur_donusturme_1
{
    class A
    {
    };
    class Nec
    {
    public:
        operator int() const;
        // explicit operator int() cont;
        operator A() const;
    };

    int main()
    {

        Nec mynec;

        int x;
        x = mynec; // explicitli olan açılırsa sentaks hatası
        x = static_cast<int>(mynec);
        x = mynec.operator int();
    }
} // namespace tur_donusturme_1

namespace tur_donusturme_2
{
    class A
    {
    };
    class Nec
    {
    public:
        operator int() const;
        // explicit operator int() cont;
        operator A() const;
    };

    int main()
    {
        Nec mynec;
        double dval = mynec; // User defined + standart
    }
}
/*

*/
namespace tur_donusturme_ornek_3
{

    class Counter
    {
        // Basit bir örnek domain içinden
        // bazı avantajları elde etmek için int yerine counter sınıfı yaratmak yerine
        // bu sınıfı kullanılacak

    public:
        explicit Counter(int val = 0) : m_c{val} {}
        Counter &operator--() // postfix
        {
            --m_c;
            return *this;
        }
        Counter operator--(int)
        {
            auto temp{*this};
            --*this;
            return temp;
        }

        Counter &operator++() // postfix
        {
            ++m_c;
            return *this;
        }
        Counter operator++(int)
        {
            auto temp{*this};
            ++*this;
            return temp;
        }

        Counter &operator+=(int val)
        {
            m_c += val;
            return *this;
        }

        Counter &operator-=(int val)
        {
            m_c -= val;
            return *this;
        }

        explicit operator int() const
        {
            return m_c;
        }
        friend std::ostream &operator<<(std::ostream &os, const Counter &cnt)
        {
            os << '[' << cnt.m_c << ']';
        }

    private:
        int m_c;
    } 
    int main()
    {
        std::cout << " c = " << c << "\n";
        ++c;
        ++c;
        ++c;
        ++c;

        std::cout << " c = " << c << "\n";

        c += 10;
        std::cout << " c = " << c << "\n";

        int ival = static_cast<int>(c);
    }
} // namespace tur_donusturme_ornek_2

namespace tur_donusturme_string_ornegi
{
    int main()
    {
        string name{"cansin onder"};

        // eger tür dönüştürme fonksiyonu olsaydı => olabilirdi. const char *p = name;
        contt char *p = name.toCString();
    }
} // namespace tur_donusturme_string_ornegi

namespace operator_bool_fonksiyonu
{
    class Nec
    {

    public:
        // operator bool( )const
        explicit operator bool() const
        // Eğer explicit yazılmazsa user defined + standart converison'dan dolayı 
        // tür dönüşümü yapılıyor.
        {
            std::cout << "Nec operator bool()\n";
            return true;
        }
    }

    int   main()
    {
        double x;
        Nec mynec;
        // x= mynec;//bu durumda user defined + standart conversiondan dolayı x'in değeri 1 oldu
        //  bunu önlemek için fonksiyon explicit yapılmalı
        // std::cout << "x= "<< x << "\n";
       // if (mynec)
       if
        {
            std::cout << "YAPARIM DOGRU\n";
        }
    }
} // namespace operator_bool_fonksiyonu

namespace operator_bool_fonksiyonu_2
{
    int main()
    {
        std::unique_ptr<std::string> uptr{new std::string{"cansin"}};
        if (uptr) // if(uptr != nullptr )aynı anlamda
        // if(uptr.operator bool()) aynı şey
        // if(! uptr)
        {
        }

        strd::cout << "bir tam sayi girin";
        int x;
        cin >> x;
        if (cin) // eğer akımda hata yoksa cin true döncek hata varsa false döncek
        // cin.operator bool()
        {
            std::cout << "giris basarili";
        }
        else
            std::cout << "giris basarisiz";

        while (cin >> x) // cagirilan fonksiyonun geri dönüş değeri cin nesnesinin kendisini referans olarak döndürüyor
        // o da operator bool fonksiyonun çağırıyor.
        // while(cin.operator>>(x).operator bool()) bunla yazmakla üstteki arasında fark yok
        {
            std::cout << x << " * " << x << " = " << (x * x);
        }

        optional<int> x; // c++ 17 ile dile eklendi
        // bir değere sahip olmaması veya olması gibi bir seçeneği var
        x.has_value(); // değeri tutuyorsa true döner

        if (x)
        {
            std::cout << "dolu";
        }
        else
            std::cout << "bos";
    }
} // namespace operator_bool_fonksiyonu_2

namespace operator_tur_donusturme_scoped_enum
{
    std::ostream &operator<<(std::ostream &os, const Weekday &wd)
    {
        const char *const pdays[] =
            {
                "Sunday",
                "Monday",
                "Tuesday",
                "Wednesday",
                "Thursday",
                "Friday",
                "Saturday"};
        return os << pdays[static_cast<int>(wd)];
    }
    Weekday &operator++(Weekday &wd)
    {
        return wd = (wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1));
    }

    enum class Weekday
    {
        Sunday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };
    int main()
    {
        Weekday wd{Weekday::Sunday};
        for (;;)
        {
            ++wd;
            std::cout << wd << "\n";
            (void)getchar();
        }
    }
} // namespace operator_tur_donusturme_scoped_enum
