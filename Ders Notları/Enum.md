# Enum
- C++'da enum türlerinden standart türlere implicit dönüşüm yok static_cast operatörü kullanılmalı. ( Dikkatli bir biçimde kullanılmalı.) 
- C'de underline type int olmak zorundayken, C++'da zorunlu değil derleyici kendi seçebilir.
- Türün scope'u neyse numaralandırma türünün scope'u o.
- C++'da isim çakışması engellmek için namespace ya da Scoped enum kullanılabilir.

# Name Lookup 
Derleyicininin isim arama sürecine deniyor.

Name lookup -> Context control -> Acces control

Bir isim aranıp, bulunamaması sentaks hatası. İsim aramanın kuralları var, belirli sıra ile aranıyor ve bu kurallar sayesinde name hiding yapılabilir.

## Scope resolution operator (::)

Binary kullanımı: <code>alan_adi::degisken/fonksiyon_adi</code>

Unary kullanımı: <code> ::degisken/fonksiyon_adi</code> Operandı olan isim bu ismin kullanıldığı isim alanında aranıyor.

**unnamed namespace**: C'deki static davranışı gibi.



