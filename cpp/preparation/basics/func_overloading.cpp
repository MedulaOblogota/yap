#include <iostream>

void Foo()
{
 	std::cout << "no args" << std::endl;
}
void Foo(int i)
{
	std::cout << "int as arg" << std::endl;
};
void Foo(char c)
{
	std::cout << "char as arg" << std::endl;
};

int main()
{
	int int_num = 3;
	char c = 'a';
	float float_num = 1.1;
	char *str = "hello";
	Foo(float_num);

	return 0;
}
