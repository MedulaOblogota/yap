#include <iostream>
#include <stdio.h>

struct Counter
{


	Counter &Inc();
	Counter &Dec();

	/*Counter *Inc();
	Counter *Dec();
*/
	int m_a;
	int m_b;
};

void PrintCounter(Counter x1);
void PrintCounters(Counter x1, Counter x2);



Counter &Counter::Inc()
{
	++this->m_a;
	this->m_b += 2;
}


Counter &Counter::Dec()
{
	--this->m_a;
	this->m_b /= 2;
}

void Inc(Counter *x)
{
	++x->m_a;
	x->m_b += 2;
}

void PrintCounters(Counter x1, Counter x2)
{
	std::cout << "x1.m_a=" << x1.m_a << ". x1.m_b=" << x1.m_b << std::endl;
	std::cout << "x2.m_a=" << x2.m_a << ". x2.m_b=" << x2.m_b << std::endl;
}

void PrintCounter(Counter x1)
{
	std::cout << "x1.m_a=" << x1.m_a << ". x1.m_b=" << x1.m_b << std::endl;
}

int main()
{
	Counter x1;
	Counter x2;

	PrintCounters(x1, x2);

	x1.m_a = 7;

	x2.m_a = 0;
	x2.m_b = 16;

	PrintCounters(x1, x2);

	x1.Inc();

	PrintCounters(x1, x2);

	x1.Inc();

	PrintCounters(x1, x2);

	x2.Dec();

	PrintCounters(x1, x2);

	Inc(&x1);

	PrintCounters(x1,x2);

	x1.Inc().Inc().Inc();

	PrintCounters(x1,x2);

	return 0;
}
