#include <iostream>
class Nec
{

public:
    // operator bool( )const
    explicit operator bool() const
    {
        std::cout << "Nec operator bool()\n";
        return true;
    }
}

int main()
{
    double x;
    Nec mynec;
    // x= mynec;//bu durumda user defined + standart conversiondan dolayı x'in değeri 1 oldu
    //  bunu önlemek için fonksiyon explicit yapılmalı
    std::cout << "x= "<< x << "\n";
    if (mynec)
    {
        std::cout << "YAPARIM DOGRU\n";
    }
    return 0;
}