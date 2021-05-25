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
