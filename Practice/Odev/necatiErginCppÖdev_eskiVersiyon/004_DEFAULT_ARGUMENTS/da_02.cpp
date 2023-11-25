/* <h3>Aşağıdaki programın çıktısı ne olur? Açıklayınız:</h3>

``` */
#include <iostream>

int foo()
{
	static int x{};
	//
	
	return ++x;
}

void func(int i = foo()) //parametre değişkeni varsayılan argüman olarak foo ya yapılan çağrının dönüş değerini almış
//yapılan her çağrı da tekrar ele alınacak
{
	std::cout << i;
}

int main()
{
	func(); // 1
	func(); // 2 
	func(); // 3
}



/* ```

[Ödevin cevabı](https://vimeo.com/551901741)
 */