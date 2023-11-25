#### Aşağıdaki kodda sentaks hatası içeren deyimleri işaretleyiniz ve her bir sentaks hatasının nedenini açıklayınız:

```
class A {
public:
	A &f1();
	A *f2();
	const A &f3();
	void f4() const;
};

int main()
{
	A ax;
	const A c;
	auto p{ &ax };
	ax.f2()->f1().f4();
	ax.f2()->f3().f4();
	ax.f3().f1();
	p->f2()->f3().f4();
	c.f4();
	c.f3().f4();
}

```

[ödevin cevabı](https://vimeo.com/368262675)
