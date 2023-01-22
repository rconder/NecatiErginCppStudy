#### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

```
#include <iostream>

int main() 
{
	void *vp = &vp;
	std::cout << (vp &&& vp);
}

```
