#include <stdio.h>
#include <stdlib.h>

union numbers
{
	int i;
	float f;
	double d;
};

struct X
{
	int i;
	char c;
	double d;
	short s;
};

struct card
{
	unsigned int suit : 2;
	unsigned int face_value : 4;
};
int main()
{
	union numbers number;
	struct X x;
	struct card cardd;
	printf("FILE: %s\n", __FILE__);
	printf("LINE: %d\n", __LINE__);
	printf("DATE: %s\n", __DATE__);
	printf("TIME: %s\n", __TIME__);
	printf("sizeof(numbers)=%d\n", sizeof(number));
	printf("sizeof(X)=%d\n", sizeof(x));
	printf("sizeof(card)=%d\n", sizeof(cardd));
	return 0;
}
