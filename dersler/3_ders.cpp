#include <iostream>

int x{ 10}; 

void foo(int = 5, int, int ); // syntax hatası varsayılan argüman
//varsayılan argüman tanımda ve bildirimde olamaz!!!!

void func(int x = 10, int y = 20, int z = 30)
{
    std::cout<<x <<" "<< y <<" " << z << "\n";
}

int main() 
{
    func();
    func(2);
    func(2,4,5);
}


//wrapper function

void foo(int x, int y, int z);

void call_foo(int y, int z, int x =10)
{
    foo(x,y,z); //wrapper kullanılarak fonksiyonun ilk argümanına değer yollanılabilir.
}

void func( const char *= "hasan kaynar"); //derleyici burada çarpma işlemi olarak algılayabilir
void func( const char * = "hasan kaynar"); 

//referans semantiği
