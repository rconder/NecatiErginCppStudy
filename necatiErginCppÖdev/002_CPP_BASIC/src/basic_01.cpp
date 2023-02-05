/*
#### Aşağıdaki C++ programı derlenip çalıştırıldığında standart çıkış akımına ne yazar?

```
*/
int foo(int *p, int *q)
{
	*p = 1;
	*q = 2;
	
	return *p + *q;
}

char str[] = "0123";

#include <iostream>

int main()
{
	using namespace std;

	int a = 3;
	int b = 4;
	int c = foo(&a, &a); //c'ye verilen ilk değer 4 oldu fakat a'nın değeri 2
	cout << c; // 4 yazar
	(c == a + b ? a : b) = 5; // koşul operatörü (turnary operator'u eğer 2. ve 3. operand l value ise ifade de l value) 
	// b değerini üretecek ve b'nin değeri 5 olacak
	cout << a << b; // 25
	int i = 0;
	str[i] = i[str + 2];// *(i+str+2) ==> i[str + 2]
	//
	//2123
	cout << str; 
	
} 
/*
```
output: 4252123
[ödevin cevabı](https://youtu.be/DDYvnqgowUs)
*/