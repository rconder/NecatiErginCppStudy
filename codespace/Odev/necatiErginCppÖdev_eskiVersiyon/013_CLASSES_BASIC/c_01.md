#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:

```
void func(int);

class A {
public:
	void func()
	{
		func(1);
		A::func(2);
		func();
		::func(3);
		::func();
	}
};
```


[ödev cevabı](https://vimeo.com/435749866)
