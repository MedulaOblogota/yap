#include <iostream>

void Foo()
{
 	std::cout << "no args" << std::endl;
}
void Foo(int i)
{
	std::cout << "int as arg" << std::endl;
}
void Foo(char c)
{
	std::cout << "char as arg" << std::endl;
}
