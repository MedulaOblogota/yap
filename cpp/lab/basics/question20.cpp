#include <cstdio>

class X
{
	int m_a;
public:
	explicit X();
	explicit X(int a_);
	void Foo();
	void SetM_A(int m_a_);
	const int GetM_A() const;

// private:
};

X::X()
	: m_a(0)
{

}

X::X(int a_)
	: m_a(a_)
{

}

void X::SetM_A(int m_a_)
{
	m_a = m_a_;
}

const int X::GetM_A() const
{
	return m_a;
}

void X::Foo()
{
	printf("%d\n", m_a);
}

void Foo(const X &x1)
{
	printf("%d\n", x1.GetM_A());
}

int main()
{
	X x1;

	x1.Foo();
	printf("%d\n", x1.m_a);
	Foo(x1);

	return 0;
}
