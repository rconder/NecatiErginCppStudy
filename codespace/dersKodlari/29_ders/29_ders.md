# 29.ders

```cpp
namespace ders_29
{

    /* Yorum Baslik:Generic programlama   
        template deniyor 
        Belirli programlamlama dilinde farklı amaçlara denk geliyor olabilir.
        C++ ile olan o anlamla ele alma!!!

        Derleyiciye kod yazdıran kod  => metacode / code formula
        Türden bağımsız ( generi programlama aracı ) derleyiciye kod yazdırmak.
        Dilden bağımsız olarak bir kodun bir den fazla tür için kullanılabilirsin 
        
        Mesela C' de swap(int,int) fonksiyonu int türden iki nesneyi takas edebilir.
        onun için swap(double, double) ayrı fonksiyon yazılmış olmalı

        Orneğin öyle bir fonksiyon olsunki aynı türden iki değişkeni takas edebilsin 
        Yaklaşımlardan biri parametrenin türünün void * olabilir
        C - kodu
        void gswap(void *vp1, void *vp2, size_t n )
        {
            char *p1 = (char*) vp1;
            char *p2 = (char*) vp2;
            whie(n--)
            {
                char temp = *p1;
                *p1++ = *p2;
                *p2++ = temp;
            }
        }
        int main()
        {
            int x = 214, y = 4282;

            gswap(&x, &y, sizeof(int));
        }

        ----------
        İkinci generic yapı 
        Örneeğin java'da her şey bir object onun içinden de ilerliyor.
        -----------
        Üçüncü olarak 
        C'de ön işlemci programına kod yazdırılabilir. Kısıtlı da olsa yaptırılabilir.

        Fakat C++'da bunun çok çok çok gelişmiş hali

        Burada her tür için ayrı bir kod oluşturuluyor ve bu kodu biz değil derleyici yazıyor.
        İnt türü için parametresi ona göre ayrılmış fonksyionlar yazılıyor.

        Bundan sonra derleyicinin de kod yazabilmesini sağlayan kodları da yazabiliyor.

        Şablon <==> Template

        Çok sayıda kural ve alt araç barındırıyor. STL => Standart Template Library anlamı dışında 
        standart kütüphane anlamında da kullanılıyor.

        Bazı durumlarda bu template'leri kullanıyoruz. Fakat bazı durumlarda da bizim de yazmamız gerekiyor.
        İlk ilişkimiz kullanıcı olmamız fakat 
        İkinci ilişkimiz direkt yazıcı olmamaız.

        Her yeni C++ standartları ile generic programlama araçları artıyor/yeni öğeler ekleniyor ve standart kütüphane
        de bu yönde büyüme yönünde 

        C++20 iile concepts aracı eklendi. Bu konuda en iyi kaynak C++ templates kitabını oku  Davivd Vandervoode 
        Nicolai Josuttis

        Dilin temel kısmını çok iyi öğrenmeliyiz 

        template code : bu kodun varlık nedeni derleyiciye kod yazdırmak

        ==========
        Temel 4 Kategori var
        1.Function template : fonksiyon şablonu amaç derleyiciye fonksiyon kodu yazdırmak. 
        2.Class template: Sınıf şablonu derleyici bizim için bizim sağladığımız template koddan faydalanarak 
        sınıf kodu yazıyor. std::vector sınıfı örenğin
        Bunlar modern C++'dan önce vardı fakat bunlara modern c++ ile çok fazla ekleme yapıldı.
        ==============
        Modern c++ ile
        3. Variable templata: Öyle bir meta kod ki derleyici bu koddan yararlanarak farklı farklı değişkenlerin 
        tanımını yapıyor.
        4. Alias template: Tür eş isim şablonu derleyici yapıyor.
        5. C++20 ile gelen concept kısım
        variadic template'ler fonksiyon ve class şablonları bu template türünden de olabiliyor.


        Ortak olan bir özellik 
        Meta kod oluşturuyoruz ve bu anahtar sözcüyü ile oluşturuyoruz
        template parameters: Fonksiyon parametresini birbirine karıştırma açısal parantezler içinde belirtilen p
        paremtere 
        a) type parameter: tür parametresi olabilir.: Derleyiciye buraya kullandığım isim yerine
        sen burada tür isim kullanabilirsin Öyle bir isimki bu bir türe karşılık geliyor 
        template <class T>
        Başlangıçta class anahtar sözcüğü vardı ve burada bu anahtar sözcük illa bir sınıf olması gerekiyormuş gibi
        bir anlam çıkıyordu. T'nin sınıf türü olma zorunluluğu yok ve zaman içinde typename anahtar sözcüğü eklendi 

        template <typename T> 
        Artık burada ikisinin bir farkı derleyiciye T kullandığım yerde sen burada bir tür kullanacaksın
        T burada bir identifier fakat burada T konvesyonel olarak kullanılıyor.

        template<typename T, class U>' bile kullanılabilir.
        template<typename T, typename U >'
        typename'in ilave kullanıldığı yerlerde class'I kullanamıyoruz sadece burada kullanabiliyoruz.

        T türünün ne olduğuna template parmetresi oluyor örneğin 
        T'nin int olduğu yerde int parametresi olarak isimlendiriyoruz.


        b) non-tyoe parameter: template sabit parametresi
        c) template parameter: template parametresi : bu daha sonra
        template< template parameters >
    */

} // namespace ders_29
```
