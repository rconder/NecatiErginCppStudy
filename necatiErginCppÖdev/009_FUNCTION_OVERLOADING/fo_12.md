#### Aşağıda f isimli işleve ilişkin bildirimler yer alıyor. `main` işlevi içinde f işlevine 10 ayrı çağrı yapın. İşlev çağrılarında yalnızca sabitleri `(constants/literals)` kullanın. Standart çıkış akımında `0123456789 yazısı çıkmalı.

```
#include <iostream>

void f(int, double, long) { std::cout << "0"; }
void f(int, double, float) { std::cout << "1"; }
void f(int, double, bool) { std::cout << "2"; }
void f(int, bool, char){ std::cout << "3"; }
void f(unsigned long, double, long) { std::cout << "4"; }
void f(int *, double, long) { std::cout << "5"; }
void f(int, int *, long) { std::cout << "6"; }
void f(char, int, int) { std::cout << "7"; }
void f(long long, unsigned long, int){ std::cout << "8"; }
void f(unsigned long long, float, double *){ std::cout << "9"; }
```


 
