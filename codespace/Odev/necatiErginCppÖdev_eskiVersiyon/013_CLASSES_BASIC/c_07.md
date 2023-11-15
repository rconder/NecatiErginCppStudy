#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:


```
class G {
	void f(int);
	void f(double);

public:
	void f()
	{
		f();
		f(12);
		f(1.2);
		f(2.3f);
		f(4u);
	}
};

void g()
{
	f();
	G::f()
	
}

```


[ödev cevabı](https://vimeo.com/435790761)
