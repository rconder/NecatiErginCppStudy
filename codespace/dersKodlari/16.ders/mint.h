#pragma once 
// bunu ihmal etme yap geç %100 standard olması için aşağıdaki yapıyı kullan
/*
* 
#ifndef HEADER_FILE_NAME_H  <--> #if !defined HEADER_FILE_NAME_H
#define HEADER_FILE_NAME_H

// Contents of the header file

#endif // HEADER_FILE_NAME_H
*/

#include <iosfwd> 
// iostream de include edilebilir fakat iosfwd light bir başlık dosyasın

//using namespace std bu çok kaba bir hata bunu başlık dosyalarında kullanma!!!!!!!!!
//using std::cout -- bunun içinde geçerli

class Mint{ //duruma göre avantajı olabilir.
public:
     //default init edilse dahi 0 değeri ile başlaması sağlanabilir
    //0'a bölme tanımsız davranıştır exception throw edilebilir.
    //otomatik dönüşüm engellenebilir. 
    //Strong types konusu altında anlatıyor.
    /*
    Mint(); Olabilir
    //
    Mint(int x = 0); olabilir
    */
   Mint() = default;
   explicit Mint(int x ): m_x{x} {}

   Mint operator++(int) //postfix
   {
      Mint retVal{*this}; //nesnenin değeri retVal olan değişkende tuttuk 
      ++* this; //postfix ++ prefix ++ çağırıyor. 
      //operator++(); olarak da çağırabilirdik.
      return retVal;
   }

   Mint & operator++() //prefix
   {
      ++m_x;
      return *this;
   }
   Mint operator--(int) //postfix
   {
      Mint retVal{*this}; //nesnenin değeri retVal olan değişkende tuttuk 
      --* this; //postfix ++ prefix ++ çağırıyor. 
      //operator++(); olarak da çağırabilirdik.
      return retVal;
   }

   Mint & operator--() //prefix
   {
      --m_x;
      return *this;
   }
   Mint operator+() const //yan etkisi yok const olmalı
   {
      return *this;
   }

   Mint operator-() const //yan etkisi yok const olmalı
   {
      return Mint{ -m_x };
      //return -m_x eğer ctor explicit ise syntax hatası 
   }
   Mint &   operator+=(const Mint &other)//nesneyi değiştiriyor const olmamalı
   {
      m_x += other.m_x;
      return *this;
   }
   friend std::ostream& operator<<(std::ostream&, const Mint&); // genel idiomatik yapı bu
   friend std::istream& operator>>(std::istream, Mint &); // Sınıf nesnesini set edeceği için const olmamalı
   /*
   #include <ostream>
   std::ostream& operator<<(std::ostream &os, const Mint &mint)
   {
    return os << '(' << mint.m_x << ')'; //burada os ifadesi zaten ostream & döndürdüğü için direkt böyle kullanılabilir.
   }
   inline olarak bu şekilde yapılabilir.
   */

  friend bool operator<(const Mint &lhs, const Mint &rhs) //lhs: left hand side rhs: right hand side
  {
      return lhs.m_x< rhs.m_x;
  }
  friend bool operator==(const Mint &lhs, const Mint &rhs) 
  {
      return lhs.m_x==rhs.m_x;
  }

   void set(int val);
/*
   Mint();
   Mint( int x ): m_x{x};
   friend 
   */
private:
    int m_x{};
//şeklinde olabilir
};

/**
std::ostream& operator<<(std::ostream&, const Mint& ) ODR ihlal edilmiş olur inline keyword gerekiyor
 * 
 * 
 */
  inline bool operator!=(const Mint &lhs, const Mint &rhs) 
  {
   return !(lhs == rhs); //convetional olarak operator== fonksiyonunu çağırdık
   //operator==(lhs,rhs)
  }
    inline bool operator>=(const Mint &lhs, const Mint &rhs) //lhs: left hand side rhs: right hand side
  {
      return !(lhs< rhs);
  }

    inline bool operator>(const Mint &lhs, const Mint &rhs) //lhs: left hand side rhs: right hand side
  {
      return (rhs< lhs);
  }

inline bool operator<=(const Mint &lhs, const Mint &rhs) //lhs: left hand side rhs: right hand side
{
     return !(rhs< lhs);
}

inline Mint operator+(const Mint &lhs, const Mint &rhs)
{
/*
1.aşama
-------
Mint retVal {lhs};
retval += rhs;
return retval;

2.aşama
--------
Mint {lhs} += rhs; //geçici nesne için += operator fonksiyonu çağırılıyor
//sonucunda çıkan Mint dönülüyor
//sınıfın private

*/
//3.aşama --->
return Mint {lhs} += rhs;
}
//inline olarak başlık dosyasında tanımlanması ODR ihlal etmemek ve derleyiciye inline expantion optimizasyonu yapması

/*
friend Mint& operator--(Mint &mint)
{
   --mint.m_x;
   return mint;

}
friend Mint operator--(Mint &mint, int)
{
   Mint retval{mint};
   --mint;
   return retval;
}
*/
