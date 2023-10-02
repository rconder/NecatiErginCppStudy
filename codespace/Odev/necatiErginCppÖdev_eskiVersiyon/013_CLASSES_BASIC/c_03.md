#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:


```
class C {
	int mx = 0;
	mutable int my = 10;
public:
	void f();
	void cf()const;

	C *func() const
	{
		mx = 12;
		my = 23;
		f();
		cf();
		return this;
	}
};

void g()
{
	const C cx;
	cx.f();
	cx.cf();
}
```

[ödev cevabı](https://vimeo.com/435763539)
