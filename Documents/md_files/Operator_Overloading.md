

# Operator overloading

Burada bazı operator detayları anlatılmamış olabilir onlar daha önceki derslerde anlatılmıştır. 

Örnek olarak Mint Sınıfı int türünü sarmalayan bir sınıf olarak kullanılmıştır.

Operatorler eklenmeden önce Mint sınıfı aşağıdadır.
```cpp
class Mint{
    public:
        Mint()= default;
        explicit Mint(int x): m_x{x}{}
        void set(int val)
        {
            m_x = val;
        }
    private:
        int m_x{};
};
```
## Postfix & Prefix Toplama ve Çıkartma Operatorlerinin Overload'u

### Postfix Toplama operatorü
burada postfix operatörü prefix toplama operatörünü de çağırıyor.
```cpp
   Mint operator++(int) //postfix
   {
      Mint retVal{*this}; //nesnenin değeri retVal olan değişkende tuttuk 
      ++* this;
      return retVal;
   }
```
### Prefix Toplama Operatörü
```cpp  
    Mint & operator++() //prefix
   {
      ++m_x;
      return *this;
   }
```
### Postfix Çıkartma Operatörü 
```cpp
   Mint operator--(int) //postfix
   {
      Mint retVal{*this}; 
      --* this;
      return retVal;
   }
```
### Prefix Çıkartma Operatörü
```cpp
   Mint & operator--() //prefix
   {
      --m_x;
      return *this;
   }
```
## İşaret operatörleri + ve -'nin Overload'u

Bu iki operatöründe nesneye bir etkisi yok o yüzden bu iki operatör const correctnes için const olmalılar.
### Operator+()
```cpp
   Mint operator+() const //yan etkisi yok const olmalı
   {
      return *this;
   }
```
Operator-()
```cpp
   Mint operator-() const
   {
      return Mint{ -m_x };
      //return -m_x eğer ctor explicit ise SENTAKS HATASI olur!!!!
   }
```
## Operator += Overload edilmesi

Burada +='operatörünün nesneyi değiştirmesi beklendiğinden const olmamalı
```cpp
   Mint &   operator+=(const Mint &other)
   {
      m_x += other.m_x;
      return *this;
   }
```

## Giriş & Çıkış işlemleri için kullanılan Operatorlerin Overload edilmesi

- Operator<< sınıf nesnsesini set etmediğinden const olan bir sınıf nesnesi referansı almalı.
- Fakat Operator>> sınıf nesnesini set ettiğinden const olmayan bir sınıf nesne referansı almalı.

Idiomatik olarak sentaksı: 

```cpp
   friend std::ostream& operator<<(std::ostream&, const Mint&); 
   friend std::istream& operator>>(std::istream, Mint &); 
```
```cpp
    #inlcude <ostream> //başlık dosyası include edilmeli
   inline std::ostream& operator<<(std::ostream &os, const Mint &mint)
   {
    return os << '(' << mint.m_x << ')'; //burada os ifadesi zaten
    //ostream & döndürdüğü için direkt böyle kullanılabilir.
   }
```
```cpp 
std::istream& operator>>(std::istream &is,  Mint &mint)
{
    return is>>mint.m_x;
} 
```
## Logic Operatorlerin Overload Edilmesi

  Logic operatorler overload edilirken genellikle **operator<** ve **operator==** operatorlörünün overload edilmesi, diğer logic operatorlerinin overloadlarının yazılmasını kolaylaştırıyor.
  - lhs: left hand side
  - rhs: right hand side

  ```cpp
  friend bool operator<(const Mint &lhs, const Mint &rhs) 
  {
      return lhs.m_x< rhs.m_x;
  }
  ```
  ```cpp
  friend bool operator==(const Mint &lhs, const Mint &rhs) 
  {
      return lhs.m_x==rhs.m_x;
  }
   ```

   ```cpp
  inline bool operator!=(const Mint &lhs, const Mint &rhs) 
  {
   return !(lhs == rhs); 
  }
  ```
  ```cpp
    inline bool operator>=(const Mint &lhs, const Mint &rhs) 
  {
      return !(lhs< rhs);
  }
```
```cpp
inline bool operator>(const Mint &lhs, const Mint &rhs) 
{
      return (rhs< lhs);
}
```
```cpp
inline bool operator<=(const Mint &lhs, const Mint &rhs) 
{
     return !(rhs< lhs);
}
```

## 2 Sınıf Nesnesinin Toplanması ve Çıkarma Operatorunun Overload Edilmesi

- ***1.Aşama***:
Dönüş nesne oluşturuluyor ve oluşturulan nesne için operator+=() fonksiyonu çağırılıyor. Daha sonra değer dönülüyor.
- ***2.Aşama***: Geçici nesne oluşturulup bu nesne için operator+=() fonksiyonu çağırılıyor.
- ***3.Aşama***: 2.aşama'de operator+= fonksiyonun'da işlenen geçici nesne dönülüyor.

```cpp
inline Mint operator+(const Mint &lhs, const Mint &rhs)
{
/*
1.aşama
-------
Mint retVal {lhs};
retval += rhs;
return retval;

/*
2.aşama
--------
Mint {lhs} += rhs; //geçici nesne için += operator fonksiyonu çağırılıyor
//sonucunda çıkan Mint dönülüyor
*/

//3.aşama --->
return Mint {lhs} += rhs;
}
```
## Operatorlerin Global Fonksiyonlar Olarak Overload Edilmesi

Burada friendlik verilerek fonksiyonların sınıf private bölümüne erişmesi sağlanıyor.
```cpp
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
```

## Operator []' Un overload Edilmesi 