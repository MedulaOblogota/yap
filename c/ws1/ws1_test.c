#include <stdio.h>
#include <stdlib.h>
#include "ws1.h"

void Test_Swap();
void Test_Flip();
void Test_Power();

int main() 
{
/*	int x = 20, y = 35;
	int num = 42152;
	int num2 = 3;
	printf("before swap x=%d, y=%d\n", x, y);
	Swap(&x,&y);
	printf("after swap x=%d, y=%d\n", x, y);
	
	printf("%d flipped is %f\n", num, Flip(num));

    printf("10^%d is %d", num, Power(num2));

	printf("string is: %s", HelloWorld()); */
	Test_Swap();
	Test_Flip();
	Test_Power();

}

void Test_Swap() 
{
	int num1 = 5;
	int num2 = 9;
	printf("before swap a=%d and b=%d", &num1, &num2);
	swap(&num1, &num2);
	printf("after swap a=%d and b=%d", &num1, &num2);
}

void Test_Flip() 
{
	int num1 = 421550;
	int	num2 = -4215;
	int num3 = 3;
	int num4 = 0;
	if (flip(num1) != 55124)
		printf("%d unsuccesfull", num1);
	if (flip(num2) != -5124)
		printf("%d unsuccesfull", num2);
	if (flip(num3) != 3)
		printf("%d unsuccesfull", num3);
	if (flip(num4) != 0)
		printf("%d unsuccesfull", num4);
}

void Test_Power()
{
	int num1 = 3;
	int	num2 = 0;
	int num3 = 1;
	int	num4 = -4;
	if (Power(num1) != 1000.0)
		printf("%d unsuccesful", num1);
	if (Power(num2) != 1.0)
		printf("%d unsuccesful", num1);
	if (Power(num3) != 10.0)
		printf("%d unsuccesful", num1);
	if (Power(num4) != 1.0/10000)
		printf("%d unsuccesful", num1);
}

