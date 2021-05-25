#include <iostream>

inline void Foo();

int main()
{
	Foo();
}

void Foo()
{
	std::cout << "in Foo" << std::endl;
}
