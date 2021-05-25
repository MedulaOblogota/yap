#include <iostream>

struct Counter
{
	void Inc();
	void Dec();
	void Mult();

	int m_a;
	int m_b;
};

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

void Counter::Mult()
{
	m_a *= 2;
	m_b *= 3;
}

using namespace std;
int main()
{
	Counter x1;
	Counter x2;

	x1.m_a = 7;

	x2.m_a = 0;
	x2.m_b = 16;

	cout << "x1.m_a = " << x1.m_a << ". x1.m_b = " << x1.m_b << "\n";
	cout << "x2.m_a = " << x2.m_a << ". x2.m_b = " << x2.m_b << "\n";

	x1.Inc();

	cout << "x1.m_a = " << x1.m_a << ". x1.m_b = " << x1.m_b << "\n";
	cout << "x2.m_a = " << x2.m_a << ". x2.m_b = " << x2.m_b << "\n";

	x1.Inc();

	cout << "x1.m_a = " << x1.m_a << ". x1.m_b = " << x1.m_b << "\n";
	cout << "x2.m_a = " << x2.m_a << ". x2.m_b = " << x2.m_b << "\n";

	x2.Dec();

	cout << "x1.m_a = " << x1.m_a << ". x1.m_b = " << x1.m_b << "\n";
	cout << "x2.m_a = " << x2.m_a << ". x2.m_b = " << x2.m_b << "\n";

	return 0;
}
