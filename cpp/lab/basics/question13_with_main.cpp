#include <stdio.h>
#include <iostream>

#include "question13.hpp"

X::X()
	: m_a(3), m_b(4)
{
	printf("Default Ctor: %p, %d, %d\n", this, m_a, m_b);
	m_a = 9;

}

Y::Y()
	: m_x(), m_i(2)
{
	printf("Ctor Y(int, int): %p, %d, %d, %d\n", this, m_x.m_a, m_x.m_b, m_i);
}
Y::Y(int a_, int b_, int i_)
	: m_x(a_, b_), m_i(i_)
{
	printf("Ctor Y(int, int): %p, %d, %d, %d\n", this, m_x.m_a, m_x.m_b, m_i);
}

X::X(int a_, int b_)
	: m_a(a_), m_b(b_)
{
	printf("Ctor(int, int): %p, %d, %d\n", this, m_a, m_b);
}

X::X(const X& other_)
	: m_a(other_.m_a), m_b(other_.m_b)
{
	printf("Copy Ctor: %p, %d, %d\n", this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
	m_a = other_.m_a;

	printf("Copy Assignment: %p, %d, %d\n", this, m_a, m_b);

	return *this;
}

X::~X()
{
	printf("Dtor: %p, %d, %d\n", this, m_a, m_b);
}

int main()
{
	X x1;
	X x2(7, 1);
	X x3(9, 10);
	X x4(x1);


	Y y1(2,4,5);

	// std::cout << "sizeof(X) = " << sizeof(X) << std::endl;

	x1 = x3;

	std::cout << std::endl;
	std::cout << std::endl;

	// y1.m_x.m_a = 250;
	//y1.m_x.m_b = 750;
	std::cout << std::endl;
	Y y2(y1);
	Y y3;
	y3 = y1;

	std::cout << "y1.m_x.m_a=" << y1.m_x.m_a << ". y1.m_x.m_b=" << y1.m_x.m_b << ". y1.m_i=" << y1.m_i << std::endl;
	std::cout << "y2.m_x.m_a=" << y2.m_x.m_a << ". y2.m_x.m_b=" << y2.m_x.m_b << ". y2.m_i=" << y2.m_i << std::endl;
	std::cout << "y3.m_x.m_a=" << y3.m_x.m_a << ". y3.m_x.m_b=" << y3.m_x.m_b << ". y3.m_i=" << y3.m_i << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}
