##### Aşağıdaki kodda sentaks hatası içeren deyimleri belirtiniz ve sentaks hatalarının nedenlerini açıklayınız:

```
class Myclass {
public:
	void func();
	//...
};

int main()
{
	Myclass m;

	func();
	Myclass::func(&m);
	Myclass::func(m);
	m.func();
	m.Myclass::func();
	Myclass::func();
	&m->func();
	(&m)->Myclass::func();
}
```

[ödevin cevabı] (https://vimeo.com/368266774)
