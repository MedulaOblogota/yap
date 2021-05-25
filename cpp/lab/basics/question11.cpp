#include <stdio.h>

void Foo(int arg1, int arg2, float arg3);

int main()
{
	bool b1 = true;
	bool b2;
	int i = b1;

	printf("%d", b1);
	printf("%d", b2);

	i = 7;
	b2 = i;
	printf("%d", b2);
	printf("sizeof(b1)=%d\n", sizeof(b1));

	Foo(3);
	Foo(6, 5);
	Foo(4, 7, 8.7);
}

void Foo(int arg1, int arg2, float arg3)
{
	arg2 = 3;
	arg3 = 4;
	printf("arg1=%d. arg2=%d. arg3=%f\n", arg1, arg2, arg3);
}
