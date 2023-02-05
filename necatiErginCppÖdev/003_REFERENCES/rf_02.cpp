/*
#### Sentaks hatası olan satırları belirtiniz:

```
*/
//auto a; //initialize edilmesi zorunlu
int &b;
auto c = 10;
int &d = c;
const auto &e = 20;
int &f = ++c;
//int &g = c + 5; // lvalue referansaa r value ataması yapılmış
int &&h = c % 2;
int func(); int &&j = func();
//int &foo(); int &&m = foo(); //rval referansa lval ref değeri ile ilk deeğer verilmiş
int ival = 10; int &&rval = ival + 10; int &p = rval;

/*
```


[ödev cevabı](https://vimeo.com/433277804)
*/