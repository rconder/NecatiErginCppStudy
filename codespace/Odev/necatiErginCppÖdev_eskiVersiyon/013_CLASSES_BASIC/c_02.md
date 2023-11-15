#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:


```
class B {
	void func(int);
public:
	void func(double);
	void func(double)const;
	void func(float) = delete;
};

int main()
{
	B bx;

	bx.func(2.3);
	bx.func(10);
	bx.func(1.2f);
}
```

[odevin cevabı](https://vimeo.com/435753617)
