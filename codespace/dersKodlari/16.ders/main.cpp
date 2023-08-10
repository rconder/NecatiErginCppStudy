#include "mint.hpp"
#include <iostream>
#include <fstream>
int main_giris_cikis_operator_overloading_ornek()
{
    Mint m1{25}, m2{457};
    Mint m3{}, m4{};
    std::cout << m1 << " " << m2 << "\n";
    std::cin >> m3;
    std::cin >> m4;
    std::ofstream ofs{"out.txt"};

    if (!ofs)
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        exit(EXIT_FAILURE);
    }
    ofs << m1 << " " << m2 << '\n';

    return 0;
}

//////////////
int g{};

class Nec
{
public:
    int &operator[](int i)
    {
        std::cout << "Nec::operator[]() i = " << i << "\n";
        return 
    }
};

int main2()
{
    using namespace std;

    vector<int> ivec(12);
    ivec[3] = 45;

    Nec mynec;
    mynec[5]; // mynec.operator[](5);

    string name{"cansin onder"};
    for (size_t i{}; i < name.size(); ++i)
    {
        cout << name[i] << " "; //[] overload edildiği için kullanabiliriz.
    }

    int a[10]; // kullanmak yerine bu diziyi sarmalayan bir
    // sınıf kullanabiliri. (wrapper class)
    // stl'e daha uyumlu daha kullanıcı dostu, daha güvenli
    array<int, 10> ar;
    for (int i = 0; i < 10; ++i)
    {
        ar[i] = i;
        // ar.operator[](i) = i;
    }
    vector<int> ivec{1, 4, 6, 78, 2, 1};
    // const vector<int> ivec {1, 4, 6, 78, 2,1};
    auto val = ivec[3];
    ivec[4] = 999;
    // ivec[4] yorum satırındaki kod için bu hatalı bir sentaks
    // const overloading var.
}

/**

 class ivector{
    public:
    int& operator[](std::size_t idx);
    const int& operator[](std::size_t idx)const;

 };
    conts ivector myvec;

    autoval = myvec[2];
    myvec[2] = 4; bu sentaks hatası çünkü const bir nesneye atama yapılıyor

 *
 */

// 17.ders ek
int main3()
{
    Mint mx(872334);
    int x(76234);

    if (x)
    {
    }
    // if(mx) eger operator bool fonksiyyonu yoksa sentaks hatası olabilir.
}