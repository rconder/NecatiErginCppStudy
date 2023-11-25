#include "mint.h"
#include <ostream>
#include <istream>
std::ostream& operator<<(std::ostream &os, const Mint &mint)
{
    return os << '(' << mint.m_x << ')'; //burada os ifadesi zaten ostream & döndürdüğü için direkt böyle kullanılabilir.
     //friend yapmanın 2 sonucu var, 
    // 1. mint'in private bölümüne erişebiliyor.
    // 2. Class definition içinde inline verip gizli friend verilebilir.
    //bu fonksiyon veri elemanına erişsin istedik
}

std::istream& operator>>(std::istream &is,  Mint &mint)
{
    return is>>mint.m_x;
} 
