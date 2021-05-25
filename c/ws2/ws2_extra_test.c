/********************************************************************/
/*																	*/
/*	Name: 		Roy Yablonka										*/
/*	Reviewer:	Eliav 												*/
/*	Version:	Sent												*/
/* 	Title:		WS2_EXTRA Test File 								*/
/*																	*/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws2_extra.h"

/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/

void TestIsPalindrome();
void TestSevenBoom();
void TestSwapPointer();
void TestAddition();
void TestRmSpaces();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main() 
{
	
	TestIsPalindrome();
	TestSevenBoom();
	TestSwapPointer();
	TestAddition();
	TestRmSpaces();
	return (1);
}

/********************************************************************/
/*	 																*/
/*				Function Definitions								*/
/* 																	*/
/********************************************************************/

void TestIsPalindrome()
{
	printf("IsPalindrome -> ");
	if (IsPalindrome("abBba") != 1)
		printf("DOESNT WORK FOR abBba\n");
	else 
		printf("works");
	if (IsPalindrome("abba") != 1)
		printf("DOESNT WORK FOR abba\n");
	if (IsPalindrome("a") != 1)
		printf("DOESNT WORK FOR a\n");
	if (IsPalindrome("") != 1)
		printf("DOESNT WORK FOR ''\n");
	if (IsPalindrome("agBba") != 0)
		printf("DOESNT WORK FOR agBba\n");
	if (IsPalindrome("^bBb^") != 1)
		printf("DOESNT WORK FOR ^bBb^\n");
	if (IsPalindrome("a^Bba") != 0)
		printf("DOESNT WORK FOR a^Bba\n");
	printf("\n");
}
void TestSevenBoom()
{
	printf("SevenBoom -> ");
	SevenBoom(-20, 20);
	printf("\n");
	SevenBoom(20, -20);
	printf("\n");
	SevenBoom(3, 3);
	printf("\n");
	SevenBoom(0, 0);
	printf("\n");
}

void TestSwapPointer()
{
	int num1 = 3;
	int num2 = 5;
	int *p_num1 = &num1;
	int *p_num2 = &num2;
	SwapPointer(&p_num1, &p_num2);
	if (p_num1 != &num2 || p_num2 != &num1)
		printf("Swap DIDNT WORK\n");
/*	printf("before swap: p_num1 = %p. p_num2 = %p\n", p_num1, p_num2);
	SwapPointer(&p_num1, &p_num2);
	printf("after swap: p_num1 = %p. p_num2 = %p\n", p_num1, p_num2); */
}

void TestAddition()
{
	char num1[] = "627583499";
	char num2[] = "76543";
	char num3[] = "4531266235312611245";
	char num4[] = "5123667999999";
	char num5[] = "9888";
	char num6[] = "53122";
	printf("%s + %s is %s\n", num1, num2, Addition(num1, num2));
	printf("%s + %s is %s\n", num3, num4, Addition(num3, num4));
	printf("%s + %s is %s\n", num5, num6, Addition(num5, num6));
	printf("%s + %s is %s\n", num5, num5, Addition(num5, num5));
}

void TestRmSpaces()
{
	char str1[] = " 	hello	man 	how 	 are 	you";
	char str2[] = "     a   ";
	char str3[] = "    ";
	char str4[] = "";
	RmSpaces(str1);
	printf("str1 is now .%s.\n", str1);
	RmSpaces(str2);
	printf("str2 is now .%s.\n", str2);
	RmSpaces(str3);
	printf("str3 is now .%s.\n", str3);
	RmSpaces(str4);
	printf("str4 is now .%s.\n", str4); 
}
