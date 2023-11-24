/*
#### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?


```
*/
#include <iostream>
 
size_t getSize_1(int* a)
{
	return sizeof a; //sizeof int* döner
}	
 
size_t getSize_2(int a[])
{
	return sizeof a; //
}
 
size_t getSize_3(int(&a)[10]) //diziye referans olduğu için dizinin boyutu döner 
{
	return sizeof a;
} 
 
int main()
{
	int a[10] = { 0 };
 
	std::cout << (sizeof(a) == getSize_1(a)); // false because it returns sizeof int pointer
	std::cout << (sizeof(a) == getSize_2(a)); // false because it returns sizeof int pointer
	std::cout << (sizeof(a) == getSize_3(a)); //true because it uses reference semantics to argument variable
}
/*
```

__Sorunun yanıtı şu seçeneklerden biri de olabilir:__

+ Sentaks hatası *(syntax error)*
+ Tanımsız davranış *(undefined behavior)*
+ Derleyiciye göre değişir *(implementation defined)*
*/