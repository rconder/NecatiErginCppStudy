##### Aşağıdaki C++ programında sınıfın *non-const* olan *func* isimli üye işlevinin yine sınıfın *const* olan üye işlevini çağırmasını istiyoruz. Bunu nasıl sağlayabiliriz? 

```
#include <iostream>

class A {
public:
	void func()const
	{
		std::cout << "A::func() const\n";
	}

	void func()
	{
		std::cout << "A::func()\n";
		//burada sınıfın const üye işlevi olan func cagrilacak
	}
};

int main()
{
	A ax;

	ax.func();
}

```

[ödevin cevabı](https://vimeo.com/368235967)
