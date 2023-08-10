# Yararlı Notlar Kısmı

Necati erginin derste bahsettiği kullanışlı methodlar ya da açıklamalar

- ## Sarmalayan Sınıfın Yararları

Burada öreniğin [Mint](./Operator_Overloading.md) sınıfını baz alalım. 

- Bu sınıf için defualt initialize edilse dahi 0 değeri ile başlaması garanti edilebilir. `mint(int x = 0):m_x{x}{}`
- 0'a bölme tanımsız davranışında exception throw edilebilir.
- Otamatik tür dönüşümü engellenebilir. 

Bu konu daha detaylı olarak **Strong Types** konusunda anlatılıyor
<!---
TODO: Strong Type'ın linklenmesi gerekicek!!!
-->