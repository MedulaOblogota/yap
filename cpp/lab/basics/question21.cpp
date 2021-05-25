#include <cstdio>

// class X;
#include "inline.hpp"

class X
{
public:
	X(int a) : m_a(a) { }

	bool operator==(const X& o_) const { return m_a == o_.m_a; }

	int GetValue() const { return m_a; }


private:
	int m_a;
};

X operator+(const X& first, const X& second)
{
	return X(first.GetValue() + second.GetValue());
}

bool operator!=(const X& first, const X& second)
{
	return (first.GetValue() != second.GetValue());
}


int main()
{
	X x1(3);
	X x2(6);

	printf("x1+x2: %d\n", ((x1+x2) + x2).GetValue());
	printf("x1: %d\n", x1.GetValue());
	printf("x1==x2: %d\n", int(x1==x2));
	printf("x1!=x2: %d\n", int(x1!=x2));

	Foo();
	Boo();

	return 0;
}

void Foo()
{
	printf("abc\n");
}
