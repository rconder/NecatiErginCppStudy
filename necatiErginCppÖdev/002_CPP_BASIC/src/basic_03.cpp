/*
#### Aşağıdaki C++ programı hakkında yorum yapınız:

+ sentaks hatası
+ tanımsız davranış
+ derleyiciye göre değişir
+ ekrana şunu yazar: 

```
*/
#include <iostream>

int main() 
{
	void *vp = &vp;
	std::cout << (vp &&& vp); //burada Maximal munch kuralı ile (vp && &vp) olucaktı ve çıktısıı her zaman true olan bir ifade olduğu için ekrana 
	//true bastırılcaktı
}

//```
