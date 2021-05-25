#include <iostream>
using namespace std;

// Normal class
template <typename T>
class A
{
public:
	A(){ cout << "A()\n"; }
	T add(T x, T y);
};

template <typename T>
T A<T>::add(T x, T y)
{
	return x+y;
}

// Specialized class
template <>
class A <char>
{
public:
	A() { cout << "Special A()\n"; }
	char add(char x, char y);
};

// template <>   <= this is not needed if defined outside of class
char A<char>::add(char x, char y)
{
	int i = x-'0';
	int j = y-'0';
	return i+j;
}

int main()
{
	A<int> intA;
	A<double> doubleA;
	A<char> charA;

	int a = 1, b = 2;
	cout << intA.add(a,b) << endl;

	double c = 3.0, d = 5.5;
	cout << doubleA.add(c,d) << endl;

	char e='e', f='f';
	cout << charA.add(e,f);

	return 0;
}
