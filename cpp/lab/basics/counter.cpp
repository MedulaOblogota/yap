#include <cstdio>

#include "counter.hpp"

void Counter::Inc()
{
	++m_a;
	m_b += 2;
}

void Counter::Dec()
{
	--m_a;
	m_b /= 2;
}

// int main()
// {
// 	Counter c;
//
// 	c.m_a = 6;
// 	c.m_b = 10;
//
// 	c.Inc();
// 	c.Dec();
// 	printf("c.ma=%d. c.mb=%d\n", c.m_a, c.m_b);
// }
