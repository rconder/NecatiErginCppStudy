class Myclass
{
public:
    operator bool() const;
};

int main()
{
    Myclass m1, m2;

    // auto x = m1 + m2;
    // x değişkeninin türü int
    // nomrmalde operator bool() fonksiyonu ile implicit conversion yapılıyor
    // aslında bu kod
    auto x = m1.operator bool() + m2.operator bool(); // int altı tür olduğundan bool türden
    // olan operandlar integral promotion ile bool türünden int türüne yükseltilmiş oluyor.
}