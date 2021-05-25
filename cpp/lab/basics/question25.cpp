#include <cstddef>
#include <cstdio>
#include <iostream>
#include <typeinfo>

namespace math
{
long Fibo(int n) { printf("in math::Fibo\n" ); }
double Sin(double d) { printf("in math::Sin\n" ); };
double Cos(double d) { printf("in math::Cos\n" ); };
}//namespace math

namespace fibonaci
{
long lookupTable[256];
long Fibo(int n) { printf("in fibonaci::Fibo\n" ); };

namespace altversion
{
long Fibo(size_t n) { printf("in altversion::Fibo\n" ); };
}//namespace altversion

}//namespace fibonaci

namespace math
{
double Tang(double d) { printf("in math::Tang\n" ); };
}

namespace C
{
	char x;
}

namespace D
{
	using namespace C;
	int x;
}

void A()
{
	int n = 3;
	fibonaci::Fibo(n);
	using math::Fibo;
	Fibo(n);

	math::Sin(3.14);
	math::Tang(3.14);
}

long Fibo(size_t n)
{
	printf("in Global Fibo\n");
}

using namespace math;
using namespace fibonaci;
namespace alt=fibonaci::altversion;

void B()
{
	size_t n = 3;
	alt::Fibo(n);
	//Fibo(n);
	Cos(n);
}

int main()
{
	::Fibo(3);
	alt::Fibo(3);
	A();
	B();
	math::Fibo(3);

	std::cout << "typeid(C::x).name() " << typeid(C::x).name() << std::endl;
	std::cout << "typeid(D::x).name() " << typeid(D::x).name() << std::endl;
	// std::cout << "typeid(D::C::x).name() " << typeid(D::C::x).name() << std::endl;
	return 0;
}
