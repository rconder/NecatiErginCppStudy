#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:


```
class D {
public:
	void func();
	void foo()
	{
		func();
		foo();
		D::func();
		this->func();
		(*this).func();
		this->D::func();
	}
};

void g(D dx)
{
	dx.func();
	dx.D::func();
}
```

[ödev cevabı](https://vimeo.com/435767306)
