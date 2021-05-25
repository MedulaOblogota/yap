/********************************************************************/
/*																	*/
/*	Name: 		Roy Yablonka										*/
/*	Reviewer:	Shahar Saar 										*/
/*	Version:	Sent												*/
/* 	Title:		WS9 Test File 								`		*/
/*																	*/
/********************************************************************/
#include <stdio.h>
#include <string.h>	/* to check against my functions */
#include <strings.h>
#include <stdlib.h>	
#include "ws9.h"

/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/

void TestAtoi();
void TestItoa();
void TestPrintLettersIn2Not3();
void TestIsLittleEndian();
void TestMemSet();
void TestMemCpy();
void TestMemMove();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main()
{
	TestAtoi();
	TestItoa();
	TestPrintLettersIn2Not3();
	TestIsLittleEndian();
	TestMemSet();
	TestMemCpy();
	TestMemMove();
	return 0;
}

void TestAtoi()
{
	char str1[] = "0";
	char str2[] = "100";
	char str3[] = "521526";
	char str4[] = "10010011110";
	char str5[] = "A06B8";
	char str6[] = "A1Z0";
	
	/*char shahar1[] = */
	
	int base1 = 2;
	int base3 = 7;
	int base4 = 10;
	int base5 = 17;
	int base6 = 30;
	int base7 = 36;
	
	printf("Atoi:\n");
	
	if (Atoi(str1, base1) != 0)
	{
		printf("failed with str=%s. base=%d\n", str1, base1);
	}
	if (Atoi(str1, base3) != 0)
	{
		printf("failed with str=%s. base=%d\n", str1, base3);
	}
	if (Atoi(str1, base7) != 0)
	{
		printf("failed with str=%s. base=%d\n", str1, base7);
	}
	if (Atoi(str2, base1) != 4)
	{
		printf("failed with str=%s. base=%d\n", str2, base1);
	}
	if (Atoi(str2, base4) != 100)
	{
		printf("failed with str=%s. base=%d\n", str2, base4);
	}
	if (Atoi(str2, base7) != 1296)
	{
		printf("failed with str=%s. base=%d\n", str2, base7);
	}
	if (Atoi(str3, base5) != 7272725)
	{
		printf("failed with str=%s. base=%d\n", str3, base5);
	}
	if (Atoi(str4, base1) != 1182)
	{
		printf("failed with str=%s. base=%d\n", str4, base1);
	}
	
	if (Atoi(str5, base6) != 8105738)
	{
		printf("failed with str=%s. base=%d\n", str5, base6);
	}
	if (Atoi(str6, base7) != 469116)
	{
		printf("failed with str=%s. base=%d\n", str6, base1);
	}	
	
	
}

void TestItoa()
{
	int num1 = 0; /* first 3 tests */
	int num2 = 4;
	int num3 = 100;
	int num4 = 1296;
	int num5 = 7272725;
	int num6 = 1182;
	int num7 = 8105738;
	int num8 = 469116;
	int num9 = -155;
	
	char str1[] = "0";
	char str2[] = "100";
	char str3[] = "521526";
	char str4[] = "10010011110";
	char str5[] = "A06B8";
	char str6[] = "A1Z0";
	char str7[] = "-155";
	
	char str[100];
	
	int base1 = 2;
	int base3 = 7;
	int base4 = 10;
	int base5 = 17;
	int base6 = 30;
	int base7 = 36;
	
	printf("Itoa:\n");
	
	if (strcmp(Itoa(num1, str, base1),str1) != 0)
	{
		printf("failed with num=%d. base=%d\n", num1, base1);
	}
	if (strcmp(Itoa(num1, str, base3), str1) != 0)
	{
		printf("failed with num=%d. base=%d\n", num1, base3);
	}
	if (strcmp(Itoa(num1, str, base7),str1) != 0)
	{
		printf("failed with num=%d. base=%d\n", num1, base7);
	}
	if (strcmp(Itoa(num2, str, base1),str2) != 0)
	{
		printf("failed with num=%d. base=%d\n", num2, base1);
	}
	if (strcmp(Itoa(num3, str, base4),str2) != 0)
	{
		printf("failed with num=%d. base=%d\n", num3, base4);
	}
	if (strcmp(Itoa(num4, str, base7),str2) != 0)
	{
		printf("failed with num=%d. base=%d\n", num4, base7);
	}
	
	
	if (strcmp(Itoa(num5, str, base5),str3) != 0)
	{
		printf("failed with num=%d. base=%d\n", num5, base5);
	}
	if (strcmp(Itoa(num6, str, base1),str4) != 0)
	{
		printf("failed with num=%d. base=%d\n", num6, base1);
	}
	if (strcmp(Itoa(num7, str, base6),str5) != 0)
	{
		printf("failed with num=%d. base=%d\n", num7, base6);
	}
	if (strcmp(Itoa(num8, str, base7),str6) != 0)
	{
		printf("failed with num=%d. base=%d\n", num8, base1);
	}	
	
	if (strcmp(Itoa(num9, str, base4),str7) != 0)
	{
		printf("failed with num=%d. base=%d\n", num9, base4);
	}	 
}

void TestPrintLettersIn2Not3()
{
	const char str1[] = "hello buddy";
	const char str2[] = "lobba dude";
	const char str3[] = "yeah";

	char result[50];
	
	printf("PrintLettersIn2Not3:\n");
	
	PrintLettersIn2Not3(str1, str2, str3, result);
}

void TestIsLittleEndian()
{
	printf("IsLittleEndian:\n");
	if (IsLittleEndian())
	{
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}	
}

void TestMemSet()
{
	char str1[] = "hello my good man, how are you? I am very very well buddy";
	char str2[] = "hello my good man, how are you? I am very very well buddy";
	char str3[] = "hello my good man, how are you? I am very very well buddy";
	char str4[] = "hello my good man, how are you? I am very very well buddy";

	
	int c = 36;
	int i = 0;
	int num = 17;
	
	printf("MemSet:\n");
	
	MemSet(str1, c, num);
	
	for (i = 0; i < num; ++i)
	{
		str2[i] = c;
	}	
	
	if (0 != strcmp(str2, str1))
	{
		printf("failed at %s with %c %d times\n", str1, c, num);
	}
	
	num = 0;
	MemSet(str3, c, num);
	
	if (0 != strcmp(str4, str3))
	{
		printf("failed at %s with %c %d times\n", str3, c, num);
	}
	
	num = 0;
	MemSet(str3 + 5, c, num);
	
	if (0 != strcmp(str4, str3))
	{
		printf("failed at %s with %c %d times\n", str3, c, num);
	}
	
}

void TestMemCpy()
{
	char dest1[] = "hello good buddy, how are you?";
	char src1[] = "shalom my best friend";
	char dest2[] = "hello good buddy, how are you?";
	char src2[] = "shalom my best friend";
	
	size_t num = 18;
	
	
	printf("MemCpy:\n");
	
	MemCpy(dest1, src1, num);
	memcpy(dest2, src2, num);
	
	if (0 != strcmp(dest1, dest2)) 
	{
		printf("failed with %lu and %s\n", num, dest1);
	}
	
	num = 0;
	MemCpy(dest1, src1, num);
	memcpy(dest2, src2, num);
	
	if (0 != strcmp(dest1, dest2)) 
	{
		printf("failed with %lu and %s\n", num, dest1);
	}
	
	/*printf("MY VERSION: %s\n", (char *)MemCpy(dest1, src1, num));
	printf("THEIR VERSION: %s\n", (char *)memcpy(dest1, src1, num));*/
}

void TestMemMove()
{
	char my_dest0[] = "hello my good friend, how are you buddy?";
	char their_dest0[] = "hello my good friend, how are you buddy?"; 
	
	char my_dest1[] = "hey there good buddy good pal! All going perfect with ya?";
	char their_dest1[] = "hey there good buddy good pal! All going perfect with ya?";
	
	char my_dest2[] = "This is ground control to major Tom";
	char their_dest2[] = "This is ground control to major Tom";
	/*char result_should_be = "abcdeh";*/
/*	result is = */                 

	size_t n1 = 16;
	size_t n2 = 8;
	size_t n3 = 0;
	/*int i = 0;*/

	printf("MemMove:\n");

	MemMove(my_dest0, my_dest0 + n1, 13);
	memmove(their_dest0, their_dest0 + n1, 13);
	
	if (0 != strcmp(my_dest0, their_dest0))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n1, their_dest0, my_dest0);
	}

	MemMove(my_dest1 + n1, my_dest1, 6);
	memmove(their_dest1 + n1, their_dest1, 6);
	
	if (0 != strcmp(my_dest1, their_dest1))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n1, their_dest1, my_dest1);
	}
	
	MemMove(my_dest1 + n3, my_dest1, 9);
	memmove(their_dest1 + n3, their_dest1, 9);
	
	if (0 != strcmp(my_dest1, their_dest1))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n3, their_dest1, my_dest1);
	}
	
	MemMove(my_dest1 + n3, my_dest1, 0);
	memmove(their_dest1 + n3, their_dest1, 0);
	
	if (0 != strcmp(my_dest1, their_dest1))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n3, their_dest1, my_dest1);
	}
	
	MemMove(my_dest2 + n2, my_dest2, 5);
	memmove(their_dest2 + n2, their_dest2, 5);
	
	if (0 != strcmp(my_dest2, their_dest2))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n2, their_dest2, my_dest2);
	}
	
	MemMove(my_dest2, my_dest2 + n2, 5);
	memmove(their_dest2, their_dest2 + n2, 5);
	
	if (0 != strcmp(my_dest2, their_dest2))
	{
		printf("failed with n=%lu!\nTheir memmove=%s\nYour MemMove=%s\n", n2, their_dest2, my_dest2);
	}
	
	/*if (my_dest1 + n1, my_dest1, 6)
	printf("MY VERSION: %s\n", (char *)MemMove(my_dest1+5, my_dest1, n));
	printf("THEIR VERSION: %s\n", (char *)memmove(their_dest1+5, their_dest1, n));*/
}
