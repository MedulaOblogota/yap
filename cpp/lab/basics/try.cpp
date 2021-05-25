#include <stdio.h>
#include <iostream>

struct X
{
	X(int a_, int b_);

	int m_a;
	int m_b;
};

X::X(int a_, int b_)
{
	m_a = a_;
	m_b = b_;
}
int main()
{
	X x1(2,4);

	std::cout << "ma, mb = " << x1.m_a << ", " << x1.m_b << std::endl;
}
