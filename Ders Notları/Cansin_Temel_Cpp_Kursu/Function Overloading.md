# Function Overloading
- C dilinde yok.
- İsimleri aynı fonksiyonların bir arada bulunmasına deniyor. 
- Programın çalışma zamanıyla değil **compile time** ile alakalı bir mekanizma.
> **Binding**: Eğer fonskiyona yapılan çağrının hangi fonksiyona ilişkin olduğu compile time da biliniyorsa *early binding* eğer bu runtime'da biliniyorsa *late binding* deniyor.
- Function overloading olması için belirli koşulların sağlanması lazım: 
- - Aynı scope içinde bildirilmeli 
- - İmzaları (Signature) farklı olmalı.

NOT: Parametrelerinin **const** olması function **re-declaration** yaratıyor. Overloading değil!!!! Redeclation'da fonksyion tanımları aynı olursa sentaks hatası olyr.

- Bazı durumlarda function overloading işletim sistemine bağlı

## Function Overloading Resolution

Derleyicinin aynı isimli fonksiyonlara yapılan çağrının hangisine yapıldığına karar vermesine deniyor. Function overloading yapılmış olması her zaman fonksiyona yapılan çağrının legal olacağı anlamına gelmiyor.
- Fonksiyon çağırısı hiçbir fonksiyon için uygun değildir.
- **Ambiguity**: Birden fazla fonksiyon var ve bunlardan sadece 1 tane olsaydı seçim yapılabilirdi.

Resolution adımları:
1. Visible olan fonksiyon listesi çıkarılıyor.
2. Fonksiyona gönderilen argümanlar, hangi fonksiyona çağrı yapabilir(legal fonksiyonlar) çıkarılıyor.
3. Ya bunlardın 1'i seçilebilir ya da sentaks hatası oluşucak.

### Dönüşüm seçenekleri
**Variyatik** Dönüşüm: Eğer bir fonksiyonun parametreleri (...) ile tanımlanıyorsa bu fonksiyona variyatik fonksiyon denir. Fonksiyon deklarasyonunda belirtilen tüm parametrelere argüman gitmek zorundayken (...) ile belirtilen paramterelere argüman gönderilmek zorunda değil.

**User defined Conversion**

**Standart Conversion**

> C++ sabit türleri.  
int | long | unsigned int | double | float | bool | char 

Resolution sırasında tür dönüşümlerinin güçleri 
Exact Match (Array dikey, const conversion, function to pointer) > Promotion (int altı argümanların int'e | float'tan double ) > Normal conversion.

> nullptr yerine 0 kullanma, C++ için kötü bir alışkanlık.

- Birden fazla argümanlı fonksiyon overload için, En az 1 argümanda diğerlerinden üstün olacak ve kalan argümanlarda diğerlerinden( diğer overload'lardan ) kötü olmayacak.

- Sağ taraf referansların sol taraf referanslarına üstünlü var.

~~~cpp
void func(int , double, int);
void func(double, long, int);
void func(char, float, double);
~~~

## Fonksyionların Delete edilmesi

Bir fonksiyon default edilebilir veya delete edilebilir. 
~~~cpp
void func(int)=delete
~~~

Bu fonksiyon object dosyalarında var fakat derleyici bu fonksiyona çağrı yapıldığında sentaks hatası oluşturuyor. Eper bu fonksiyon function resolution sonunda seçilirse kullanılması engelleniyor. Generic programlama ve sınıflar ile alakalı bir kavram.

