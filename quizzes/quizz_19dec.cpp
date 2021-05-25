#include <iostream>
using namespace std;

class A
{
public:
    A() {cout << "1"; }
    virtual ~A() {cout << "2"; }
};

class B: public A
{
public:
    B() {cout << "3"; }
    ~B() {cout << "4"; }
};

class Test
{
public:
    Test() {}
    Test(const Test &)
    {
        static int i = 0;
        i++;
        cout << i;
    }
};

Test func(Test A1, Test &A2)
{
    return A2;
}

int main()
{
    // B *b = new B();
    Test A1, A2;
    func(A1, A2);
    return 0;
}