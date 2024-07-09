# 34.Ders Notu

# İçerik

# Regex

Regex: regular expression, bir kural setini belirliyor ve bu kural setini kullanalarak text içinde faydalı işlemler yapıyor. Örneğin eposta adresi kodu bir yazının içinde kodu sınayabiliyor.

Bir yazı içerisinde o yazı setini sağlayan kuralları sınaya biliyor.

Arama işlemlerini *regex engine* ile yapabiliyoruz. Tokenizing araçlarını kullanılıyor.

[regex101.com](https://regex101.com) 

**literal characters**: Özel bir karakter grubundal bir şey kullanılmıyorsa bu anlama geliyor *literal* anlamda.

**Basit string operasyonlarında regex kullanma**

**meta character** herhangi bir karakteri nitelemk için (newline dışında) bu karakterleri *escape etmemiz gerekiyor.*
`[aer]` şeklinde yazdığımızda bunun anlamı 'a' 'e' ve 'r' karakterinden 1'i olabilir.

Rakam karakterleri için `[0-9]` şeklinde yazıyoruz.

`[^` karakteri: bu karakterin anlamı bu karakterlerin dışındaki karakterlerdir. 

**Quantifiers**: Nicelik gösteren grammar aracı olarak kullanılıyor. Bir tokenin arkasına geldiğinde o tokenden kaç tane olduğunu betimliyor.

'?' karakteri: 0 ya da 1 tane olabilir. 

`*` karakteri: 0 ya da daha fazla olabilir.

`+` karakteri: 1 ya da daha fazla olabilir.

`{}` karakteri: belirli bir sayıda olabilir. `{2}` şeklinde yazdığımızda 2 tane olabilir. `{2,}` şeklinde yazdığımızda 2 ya da daha fazla olabilir. `{2,4}` şeklinde yazdığımızda 2 ya da 4 tane olabilir.

`\s` whitespace karakteri. 

`\d` digit karakteri. 

`\w` word karakteri. 

`\b` word boundary karakteri.

### Parantez Atomu

hem notasyonda öncelik kazandırıyor hem de capture grup denen özelliğe sahip.

![alt text](34_ders_image1.png)

**back referans**: regex stringi içerisinde bulunan bir grubun tekrar kullanılmasını sağlayabiliyor

![alt text](image-2.png)


![alt text](34-image.png)

Ayın günlerini aramak için:

![alt text](image-1.png)

kullanılabilir.

**Positive lookahead** ? işaretinden sonra bir şey var mı diye bakıyor.
**Negative lookahead** ?= işaretinden sonra bir şey yok mu diye bakıyor.

bir quanttifier'ın sonuna ? işareti koyduğumuzda o quantifier'ın greedy olmamasını sağlıyoruz. Koşulu sağlayan ilk değeri bulduğunda durucak.

# CPP ve Regex

`#include <regex>` kütüphanesi ile regex kullanılabilir.

- regex engine'ı hazırlıyor ve bu engine ile arama işlemleri yapılıyor.
- Mutlaka ve mutlaka bir regex sınıfı türünden bir nesne tanımlanmalı
`regex rgx{"cdel"};` şeklinde tanımlanabilir.
- Dikkat etmmemiz gereken şey '\' karakteri kullanmamız durumunda escape karakteri olduğu için iki kez yazmamız gerekiyor.
- `regex rgx{"c\\del"};` şeklinde yazılmalı.

`regex_match` ile arama yapıyoruz ve en basit kullanım şekli 2 parametre ile kullanmak örneğin:

```cpp
#include <regex>
#include <iostream>

int main()
{
    std::string s = "ali";
    std::regex rgx{"ali"};
    std::cout << std::regex_match(s,rgx) << "\n";
}
```

![alt text](image-3.png)

Bu fonksiyon verilen dosya isminin içerisindeki stringleri vector'e atıyor.
