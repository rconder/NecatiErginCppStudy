# 8.hafta

## Format Fonksiyonu

### Precision

```c++
int main()
{
    string name {"Deneme"};
    cout << format("{:24.4}", name) << "\n"; // Dene ekrana bastırılıcak.
}
```

### Format Fonksiyonları

- `fomat_to` : bir adres alıyor ve formatlı yazıyı oraya insert ediyor.

```c++
int main()
{
    using namespace std;
    int x = 2'435'345;
    format_to(ostream_iterator<char>{cout}, "x = {:^#16X}", x);
    string str;
    format_to(back_inserter(str), "|x = {:^#16X}|",x);
    cout << str.size() << "\n";
    cout << str << "\n";
}
```

- Aşağıdaki gibi de kullanılabilir:

```c++
int main()
{
    using namespace std;
    string str;
    for(char c = 'A'; c<= 2 'Z'; ++c)
    {
        format_to(back_insterter(str),"{{{0},{0:d}}},c\n");
    } 
    cout << str << "\n";
}
```

- `std::locale` sınıfı ile lokalizasyon yapılabilir.

```c++
#include <locale>
int main()
{
    using namespace std;
    locale::global(locale{turkish});
    cout << 12.96854;
    cout << fomrat("{:L}\n",4.56)<< "\n";
    cout << fomrat("{:L}\n",7412214124)<< "\n";
    cout << fomrat(std::loclae("turkish"),"{:L}\n",4.56)<< "\n";
}
```

- formatted_size ile formatlamak istediğim string'in size'ını alabiliriz.

```c++
int main()
{
    using namespace std;
    int x = 435466;
    auto len = formatted_size("{:#x},x");
    cout << "len =" << len << "\n";
}
```

- `format_to_n`ile verilen adrese yazdırılabilir, geri dönüş değeri bir yapı türünden. size ve out(pointer) döndürüyor 

```c++
int main()
{
    using namespace std;
    string name {"den"};
    string surname{"deneme"};
    array<char,10>ar{};    
    auto x = format_to_n(ar.data(),ar.size()-1,"{} {}",name, surname ) //sadece size()-1 kadar karakter ekrana yazdırılabilir.
    for (char c : ar)
        cout << c ;
    cout << "x.size"<<  x.size << "\n";
    cout << "index" << x.out - ar.data() << "\n";
}
```

### Custom Formatting

Kendi türlerimiz içinde bu kütüphaneden destek olabiliyoruz.

- `std::formatter` türü içini explicit specializationı'nı oluşturmamız gerekiyor.
- context nesnesinin begin ve end fonksiyonu var ve bu bize `:`dan sonraki konuumu döndürüyor ve bizim o iteratörü alıp onu kapanan küme parantezine kadar ilerletmemiz gerekiyor.
- diğer fonksiyon ise format_to'ya destinitation olarak geçiliyor.

```c++
class Person
{

};

template<>
std::formatter<Person>
{
public:
    //auto parse(std::format_parse_context &)
    auto parse(auto & context)
    {

    }
    auto format (const T&t, std::format_context)
    {}
};

int main()
{
    using namespace std;
    Person per;
    std::format("person = {}\n",per);
}
```

- Minimal örnek:

- `ctx.begin()` fonksiyonu açılan küme parantezinden sonraki kısmı döndürüyor.
- `ctx.end()` fonksiyonu bu yazının en son konumunu döndürüyor.
- format_to fonksiyonun 1.parametresine ctx.out pointer'ını çağıracağız. Aldığı format context'ti format_to'ya vericek

```c++
class Always40
{
public: 
    int getValue() const {return 40;}
};

template <>
struct std::formatter<Always40>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }
    auto format(cont Always40&obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out,"{}",obj.getValue());
    }
};

int main()
{
    Always40 al4;
    cout <<std::format( "|{}|"al4);
}
```

- Daha karmaşık bir örnek:

```c++
class Person
{
public:
    Person(std::string name, int id) : m_name(std::move(name)), m_id(id) {}
    std::string get_name() const {return name;}
    int get_id(){return m_id;}
private:
    std::string m_name;
    int m_id;
};

template<>
class std::formatter<Person>
{
public:
    constexpr auto parse(auto &context)
    {
        auto iter{context.begin()};
        const auto iter_end{context.end()};
        if(iter == iter_end || *iter == '}')
        {
            m_ftype = FormatType::All;
            return iter;
        }
        switch(*iter)
        {
        case 'n': m_ftype = FormatType::Name; break;       
        case 'i': m_ftype = FormatType::Id; break;
        case 'a': m_ftype = FormatType::All; break;
        default : throw std::format_error{"Person Format Errror"};
        }
        ++iter;
        if(iter != iter_end && *iter != '}')
            throw std::format_error{"Person format error!"};
        return iter;
    }
    constexpr auto format(const Person &per, auto &context)
    {
        using enum FormatType;
        switch(m_ftype)
        {
        case Name :return std::format_to(context.out(), "{}", per.get_name());
        case Id :return std::format_to(context.out(), "{}", per.get_id());
        case All :return std::format_to(context.out(), "[{} {}]", per.get_id() , per.get_name());
        }
    }
private:
    enum class FormatType {Name, Id, All};
    FormatType m_ftype;
};


int main()
{
    Person p1{"necati",1231};
    Person p1{"ali",11231};
    Person p1{"deli",31};

    std::cout << std::format("{:n}\n{:i}\n{:a}"p1,p2,p3);
}
```

- Seçenek fazlaysa bu format state'ti tutmamız gerekebilir.


```c++
struct Point
{
    int mx,my;
};

template<>
class std::formatter<Point>
{
public:
    constexpr auto parse(format_parse_context &pc)
    {
        auto iter{pc.begin()};
        for(;iter != pc.end() && *iter != '}';++iter)
        {
            if(*iter == '#')
            {
                cb_ = true;
            }
            else
                std::format_error{"Point format error"};
        }
        return iter;
    }
    typename std::format_context::iterator format(const Point &p, std::format_context fc)
    {
        return std::format_to(fc.out(),"{}{}, {}{}",(cb_ ? '{' :'('),p.mx, p.my, (cb_ ? '}' : ')'));
    }
private:
    bool cb_{};
};

int main()
{
    Point p{3,4};
    std::cout << std::format("{:#}",p);
}
```
