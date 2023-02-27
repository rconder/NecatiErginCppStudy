#### Aşağıdaki kodda (varsa) sentaks hatalarını (gecersiz kodları) saptayın. Her bir sentaks hatasının nedenini açıklayın:

```
class F {
	int mx = 10;
public:
	void func(F& rf)const;
};


F fg;

void F::func(F& rf)const
{
	F local_f;

	fg.mx = 45;
	rf.mx = 55;
	local_f.mx = 65;
	F::mx = 75;
}

```

[ödev cevabı](https://vimeo.com/435779773)
