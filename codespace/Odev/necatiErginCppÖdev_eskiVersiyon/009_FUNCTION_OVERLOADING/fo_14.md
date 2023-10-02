#### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

```
#include <iostream>
#include <string>

void f(const std::string &) { std::cout << 1; }
void f(const void *) { std::cout << 2; }
void f(int = 0, ...) { std::cout << 3; }

int main() 
{
	f("necati");
	const char *pstr = "bar";
	f(pstr);
}
```

[ödevin cevabı](https://vimeo.com/436478325)
