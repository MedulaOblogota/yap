#include <stdio.h>
#include <string.h>

#include "ws9.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"
#define CHAR_AS_INT_SIZE (sizeof(int) * 8) + 1

void TestAtoi();

void TestItoa();

void TestPrintLettersIn2Not3();

void TestMemSet();

void TestMemCpy();

void TestMemMove();

int main()
{
	unsigned int y = 0x012345;

	TestItoa();

	TestAtoi();

	/*puts("Testing IsLittleEndian function...");
	printf("Is little endian? %s\n", IsLittleEndian(&y) ? "True\n" : "False\n");

	printf("----------------------------------------------------------\n");

	TestPrintLettersIn2Not3();*/

	TestMemSet();

	TestMemCpy();

	TestMemMove();

	return (0);
}

void TestAtoi()
{
	char num_s1[] = "5361";
	char num_s2[] = "0";
	char num_s3[] = "1111000";
	char num_s4[] = "FF";
	char num_s5[] = "D65E";
	char num_s6[] = "-19";

	puts("Testing Atoi function...\n");

	puts("Test 1: ");
	if (5361 != Atoi(num_s1, 10))
	{
		puts("The function failed with the input str = 5361");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	puts("Test 2: ");
	if (0 != Atoi(num_s2, 10))
	{
		puts("The function failed with the input str = 0");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	puts("Test 3: ");
	if (120 != Atoi(num_s3, 2))
	{
		puts("The function failed with the input str = 1111000");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	puts("Test 4: ");
	if (255 != Atoi(num_s4, 16))
	{
		puts("The function failed with the input str = FF");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	puts("Test 5: ");
	if (54878 != Atoi(num_s5, 16))
	{
		puts("The function failed with the input str = D65E");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	puts("Test 5: ");
	if (-19 != Atoi(num_s6, 10))
	{
		puts("The function failed with the input str = -19");
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}

	printf("----------------------------------------------------------\n\n");
}


void TestItoa()
{
	char str[CHAR_AS_INT_SIZE];
	char *str_p = str;
	char *p = NULL;

	int num1 = 6;
	int num2 = 54325;
	int num3 = 0;

	char res1[] = "110";
	char res2[] = "1101010000110101";
	char res3[] = "0";
	char res4[] = "6";
	char res5[] = "54325";
	char res6[] = "0";
	char res7[] = "6";
	char res8[] = "D435";

	puts("Testing Itoa function...\n");

	puts("Test 1:");
	p = Itoa(num1, str_p, 2);
	if (0 != strcmp(p, res1))
	{
		puts(RED "The function failed with the input num = 6, base 2" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 2:");
	p = Itoa(num2, str_p, 2);
	if (0 != strcmp(p, res2))
	{
		puts(RED "The function failed with the input num = 54325, base 2" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 3:");
	p = Itoa(num3, str_p, 2);
	if (0 != strcmp(p, res3))
	{
		printf("%d", (int)*p);
		puts(RED "The function failed with the input num = 0, base 2" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 4:");
	p = Itoa(num1, str_p, 10);
	if (0 != strcmp(p, res4))
	{
		puts(RED "The function failed with the input num = 6, base 10" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 5:");
	p = Itoa(num2, str_p, 10);
	if (0 != strcmp(p, res5))
	{
		puts(RED "The function failed with the input num = 54325, base 10" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 6:");
	p = Itoa(num3, str_p, 10);
	if (0 != strcmp(p, res6))
	{
		puts(RED "The function failed with the input num = 0, base 10" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 7:");
	p = Itoa(num1, str_p, 16);
	if (0 != strcmp(p, res7))
	{
		puts(RED "The function failed with the input num = 6, base 16" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 8:");
	p = Itoa(num2, str_p, 16);
	if (0 != strcmp(p, res8))
	{
		puts(RED "The function failed with the input num = 54325, base 16" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	puts("Test 9:");
	p = Itoa(num3, str_p, 16);
	if (0 != strcmp(p, res3))
	{
		puts(RED "The function failed with the input num = 0, base 16" RESET);
	}
	else
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	p = NULL;

	printf("----------------------------------------------------------\n\n");
}


void TestPrintLettersIn2Not3()
{
	char s1[] = {'c', 'g', 'h', 'g', 't', 's'};
	char s2[] = {'a', 'b', 'i', 'n', 'g', 'e'};
	char s3[] = {'s', 'm', 'p', 'w', 'b', 't'};
	char s4[] = {'s', 'm', 'g', 'w', 'b', 't'};
	char s5[] = {'s', 'm', 'g', 'w', 'b', 't'};
	char s6[] = {'a', 'b', 'c', 'd', 'e', 'f'};


	puts("\nTesting PrintLetters function...");

	/*2 similar letters in the 1st and 2nd*/
	puts("\nTest 1 should print g:");
/*	PrintLettersIn2Not3(s1, s2, s3);*/

	/*3 similar letters in each of the arrays*/
	puts("\nTest 2 should print nothing");
/*	PrintLettersIn2Not3(s1, s2, s4);*/

	/*2 similar arrays, 3rd array different*/
	puts("\nTest 3 should print s, m, g, w, t:");
/*	PrintLettersIn2Not3(s4, s5, s6);*/

	printf("----------------------------------------------------------\n\n");
}

static void TestMemSetWrapper(void *s, int c, size_t n, void *s_test)
{
	static size_t i = 1;

	if (0 == strcmp(memset(s_test, c, n), MemSet(s, c, n)))
	{
		printf(GRN "Test %lu result: SUCCESS!!!\n" RESET, i);
	}
	else
	{
		printf(RED "Test %lu result: FAILED\n" RESET, i);
	}
	++i;
}

void TestMemSet()
{
	char s1[] = "Hello everybody! How are you feelin' today??";
	char s1_test[] = "Hello everybody! How are you feelin' today??";
	char s2[] = "Cause you're a sky, cause you're a sky full of stars";
	char s2_test[] = "Cause you're a sky, cause you're a sky full of stars";
	char s3[] = "I need a dollar dollar, a dollar is what I need";
	char s3_test[] = "I need a dollar dollar, a dollar is what I need";
	char s4[] = "Shtrudel is my favorite cake in the whole world!!!";
	char s4_test[] = "Shtrudel is my favorite cake in the whole world!!!";

	int c1 = '.';
	int c2 = '*';
	int c3 = '$';
	int c4 = '@';

	size_t n1 = 15;
	size_t n2 = 5;
	size_t n3 = 6;
	size_t n4 = 50;

	size_t offset1 = 6; /* = s1 + 6*/
	size_t offset2 = 47;
	size_t offset3 = 26;
	size_t offset4 = 0;

	puts("Testing MemSet function...");

	printf("\nTest 1\n");
	printf("Before: %s\n", s1);
	TestMemSetWrapper(s1 + offset1, c1, n1, s1_test + offset1);
	printf("Result: %s\n", s1);

	printf("\nTest 2\n");
	printf("Before: %s\n", s2);
	TestMemSetWrapper(s2 + offset2, c2, n2, s2_test + offset2);
	printf("Result: %s\n", s2);

	printf("\nTest 3\n");
	printf("Before: %s\n", s3);
	TestMemSetWrapper(s3 + offset3, c3, n3, s3_test + offset3);
	printf("Result: %s\n", s3);

	printf("\nTest 4\n");
	printf("Before: %s\n", s4);
	TestMemSetWrapper(s4 + offset4, c4, n4, s4_test + offset4);
	printf("Result: %s\n", s4);

	printf("----------------------------------------------------------\n\n");
}


static void TestMemCpyWrapper(void *dest, const void *src, size_t n,
									void *dest_test, const void *src_test)
{
	static size_t i = 1;

	if (0 == strcmp(memcpy(dest_test, src_test, n), MemCpy(dest, src, n)))
	{
		printf(GRN "Test %lu result: SUCCESS!!!\n" RESET, i);
	}
	else
	{
		printf(RED "Test %lu result: FAILED\n" RESET, i);
	}
	++i;
}


void TestMemCpy()
{
	const char src1[] = "Hello everybody! How are you feelin' today??";
	const char src1_test[] = "Hello everybody! How are you feelin' today??";
	const char src2[] = "Cause you're a sky, cause you're a sky full of stars";
	const char src2_test[] = "Cause you're a sky, cause you're a sky full of stars";
	const char src3[] = "I need a dollar dollar, a dollar is what I need";
	const char src3_test[] = "I need a dollar dollar, a dollar is what I need";
	const char src4[] = "Shtrudel is my favorite cake in the whole world!!!";
	const char src4_test[] = "Shtrudel is my favorite cake in the whole world!!!";

	size_t n1 = strlen(src1) + 1;
	size_t n2 = strlen(src2) + 1;
	size_t n3 = strlen(src3) + 1;
	size_t n4 = strlen(src4) + 1;

	char dest[100] = {'\0'};
	char dest_test[100] = {'\0'};

	puts("Testing MemCpy function...");

	printf("\nTest 1\n");
	TestMemCpyWrapper(dest, src1, n1, dest_test, src1_test);

	printf("\nTest 2\n");
	TestMemCpyWrapper(dest, src2, n2, dest_test, src2_test);

	printf("\nTest 3\n");
	TestMemCpyWrapper(dest, src3, n3, dest_test, src3_test);

	printf("\nTest 4\n");
	TestMemCpyWrapper(dest, src4, n4, dest_test, src4_test);

	printf("----------------------------------------------------------\n\n");
}


void TestMemMove()
{
	char src1[100] = "Hello everybody! How are you feelin' today??";
	char src2[100] = "Cause you're a sky, cause you're a sky full of stars";
	char src3[100] = "I need a dollar dollar, a dollar is what I need";
	char src4[200] = "Shtrudel is my favorite cake in the whole world!!!";
	char dest[100] = {'\0'};

	size_t n1 = strlen(src1) + 1;
 	size_t n2 = strlen(src2) + 1;
 	size_t n3 = strlen(src3) + 1;
 	size_t n4 = strlen(src4) + 1;

	puts("Testing MemMove function...");

	/*dest is ahead of src*/
	puts("\nTest 1:");
	if (0 == memcmp(memmove(src1 + 16, src1, n1), MemMove(src1 + 16, src1, n1), n1))
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	else
	{
		printf(RED "FAILED\n" RESET);
	}

	/*src is ahead of dest*/
	puts("\nTest 2:");
	if (0 == memcmp(memmove(src2, src2 + 8, n2), MemMove(src2, src2 + 8, n2), n2))
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	else
	{
		printf(RED "FAILED\n" RESET);
	}

	/*dest and src fully aligned*/
	puts("\nTest 3:");
	if (0 == memcmp(memmove(src3, src3, n2), MemMove(src3, src3, n3), n3))
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	else
	{
		printf(RED "FAILED\n" RESET);
	}

	/*dest and src are far away from each other*/
	puts("\nTest 4:");
	if (0 == memcmp(memmove(dest, src4, n4),
							MemMove(dest, src4, n4), n4))
	{
		printf(GRN "SUCCESS!!!\n" RESET);
	}
	else
	{
		printf(RED "FAILED\n" RESET);
	}

}

/*mrm*/
