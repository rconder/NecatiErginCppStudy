#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:

```
class E {
	int x(int) { return 1; }
public:
	void foo();
};

int x = 20;


void E::foo()
{
	if (auto x = ::x + 5; x  > 10)
		x = this->x(x);
	
	++x;
	auto val = x(::x);
	E::x(::x);

}
```

[ödev cevabı](https://vimeo.com/435771459)
