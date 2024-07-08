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

