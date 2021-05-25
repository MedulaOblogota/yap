#include <stdio.h>
#include <stdlib.h> /*EXIT_SUCCESS*/
#include <string.h> /* strlen */

#include "ws9.h"

#define IS_LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define ARR_SIZE(array) (sizeof((array)) / sizeof(array[0]))


static void TestLittleEndian();
static void TestPrintLettersIn2Not3();
static void TestIntToStringAnyBase();
static void TestStringToIntAnyBase();

static void TestMemset();
static void TestMemcpy();
static void TestMemmove();


int main()
{
	puts("Test Little Endian:\n");
	TestLittleEndian();

	puts("\nTest Print Letters In str1 and str2 and NOT in str3:\n");
	TestPrintLettersIn2Not3();

	puts("\nTest Int To String Any Base:\n");
	TestIntToStringAnyBase();

	puts("\nTest String To Int Any Base:\n");
	TestStringToIntAnyBase();

	puts("\nTest MemSet:\n");
	TestMemset();
	
	puts("\nTest MemCpy:\n");
	TestMemcpy();

	puts("\nTest MemMove:\n");
	TestMemmove();


	return (EXIT_SUCCESS);
}

static void TestLittleEndian()
{
	int to_check = IsLittleEndian();

	if(IS_LITTLE_ENDIAN == to_check)
	{
		puts ("Little Endian");
	}
	else
	{
		puts ("Big Endian");
	}
	
	return;
}

static void TestPrintLettersIn2Not3()
{
	char *str1 = "Hello World";
	char *str2 = "Best String";
	char *str3 = "shachar";
	size_t size1 = strlen(str1) - 1;
	size_t size2 = strlen(str2) - 1;
	size_t size3 = strlen(str2) - 1;
	
	PrintLettersIn2Not3(str1, str2, str3, size1, size2, size3);

	return;
}

static void TestIntToStringAnyBase()
{
	char string_for_conversion[30];

	int value_array10[] = {155, -155, 0, 10000, 1234567890};
	char *ans_array10[] = {"155", "-155", "0", "10000", "1234567890"}; 
	int lenght_array10 = ARR_SIZE(value_array10);

	int value_array16[] = {0x10, 15, 0x0};
	char *ans_array16[] = {"10", "F", "0"};
	int lenght_array16 = ARR_SIZE(value_array16);

	int value_array2[] = {2, 3, 8, 0xffff};
	char *ans_array2[] = {"10", "11", "1000", "1111111111111111"};
	int lenght_array2 = ARR_SIZE(value_array2);
	
	int base = 0; 

	int i = 0;
	
	/* test base 10 using Itoa*/
	base = 10;
	for (i = 0; i < lenght_array10; ++i)
	{
		if (0 == strcmp(Itoa(value_array10[i], string_for_conversion, base), ans_array10[i]))
		{	
			printf("Int %d, using base %d is String: %s\t (using Itoa)\n", value_array10[i], base, string_for_conversion);
		}
	}

	/*test base 16*/
	base = 16;
	for (i = 0; i < lenght_array16; ++i)
	{
		if (0 == strcmp(Itoa(value_array10[i], string_for_conversion, base), ans_array16[i]))
		{	
				printf("Int %d, using base %d is String: %s\n", value_array16[i], base, string_for_conversion);
		}
	}

	/*test base 2*/
	base = 2;
	for (i = 0; i < lenght_array2; ++i)
	{
		if (0 == strcmp(Itoa(value_array10[i], string_for_conversion, base), ans_array2[i]))
		{	
			printf("Int %d, using base %d is String: %s\n", value_array2[i], base, string_for_conversion);
		}
	}

	return;		
}

static void TestStringToIntAnyBase()
{
	int base = 0; 

	char *string_array10[] = {"155", "-155", "0", "10000", "2147483647"};
	int ans_array10[] = {155, -155, 0, 10000, 2147483647};
	int lenght_array10 = ARR_SIZE(string_array10); 

	int ans_array16[] = {0x10, 15, 0x0};
	char *string_array16[] = {"10", "F", "0"};
	int lenght_array16 = ARR_SIZE(string_array16);

	int ans_array2[] = {2, 3, 8, 0xffff};
	char *string_array2[] = {"10", "11", "1000", "1111111111111111"};
	int lenght_array2 = ARR_SIZE(string_array2);

	int i = 0; 
	
	/* test base 10 using Atoi*/
	base = 10;
	for (i = 0; i < lenght_array10; ++i)
	{
		if ((Atoi(string_array10[i], base)) == (ans_array10[i]))
		{	
			printf("String: %s is Int %d ,using base %d\t (using Atoi)\n", string_array10[i], Atoi(string_array10[i], base), base);
		}
	}

	/*test base 16*/
	base = 16; 
	for (i = 0; i < lenght_array16; ++i)
	{
		if ((Atoi(string_array10[i], base)) == ans_array16[i])
		{	
			printf("String: %s is Int %d ,using base %d\n", string_array16[i], Atoi(string_array10[i], base), base);
		}
	}

	/*test base 2*/
	base = 2; 
	for (i = 0; i < lenght_array2; ++i)
	{
		if ((Atoi(string_array10[i], base) == ans_array2[i]))
		{	
			printf("String: %s is Int %d ,using base %d\n", string_array2[i], Atoi(string_array10[i], base), base);
		}
	}

	return;
}


static void TestMemset()
{
	int c = '#';
	
	size_t i = 0; 
	int status = 0;
	size_t test_array[] = {0, 3, 8, 10, 25};

	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str1 = (char *)malloc(200 * sizeof(char));
		char *str2 = (char *)malloc(200 * sizeof(char));
		char *str_cpy1 = str1;
		char *str_cpy2 = str2;
		
		MemSet(str1, c, test_array[i]);
		memset(str2, c, test_array[i]);
	
		status = memcmp(str1, str2, test_array[i]);
		if (0 == status)
		{
			printf("Memset works for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed for  %lu \n", test_array[i]);
		}
		free(str_cpy1);
		free(str_cpy2);
		str1 = NULL;
		str2 = NULL;
	}

	/* test with offset */
	
	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str3 = (char *)malloc(200 * sizeof(char));
		char *str4 = (char *)malloc(200 * sizeof(char));
		char *str_cpy3 = str3;
		char *str_cpy4 = str4;
		
		++str3;
		++str4;
		
		MemSet(str3, c, test_array[i]);
		memset(str4, c, test_array[i]);
	
		status = memcmp(str3, str4, test_array[i]);
		if (0 == status)
		{
			printf("Memset with offset works for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed offset for  %lu \n", test_array[i]);
		}
		
		free(str_cpy3);
		free(str_cpy4);
		str3 = NULL;
		str4 = NULL;
	}

	return;
}

static void TestMemcpy()
{
	size_t i = 0; 
	int status = 0;
	size_t test_array[] = {0, 3, 8, 10, 25};
	char src[] = "1234567890abcdefghij1234567890";

	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str1 = (char *)malloc(200 * sizeof(char));
		char *str2 = (char *)malloc(200 * sizeof(char));
		char *str_cpy1 = str1;
		char *str_cpy2 = str2;

		++str1; /* creating an offset */
		++str2;
		
		MemCpy(str1, (void *)src, test_array[i]);
		memcpy(str2, (void *)src, test_array[i]);
		

		status = memcmp(str1, str2, test_array[i]);
		if (0 == status)
		{
			printf("Memcpy works for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed for  %lu \n", test_array[i]);
		}
		free(str_cpy1);
		free(str_cpy2);
		
		str_cpy1 = NULL;
		str_cpy2= NULL;
	}

	return;
}

static void TestMemmove()
{
	size_t i = 0; 
	int status = 0;
	size_t test_array[] = {0, 3, 8, 10, 25};
	char * string = {"1234567890abcdefghij1234567890"};
		
	
	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str1 = (char *)malloc(200 * sizeof(char));
		char *str2 = (char *)malloc(200 * sizeof(char));
		
		void *dest1 = (str1 + 8);
		void *dest2 = (str2 + 8);
		
		strcpy(str1, string);
		strcpy(str2, string);
		
		MemMove(dest1, str1, test_array[i]);
		memmove(dest2, str2, test_array[i]);
	
		status = memcmp(dest1, dest2, test_array[i]);
		if (0 == status)
		{
			printf("Memmove works for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed for  %lu \n", test_array[i]);
		}
		free(str1);
		free(str2);
		
		str1 = NULL;
		str2= NULL;
	}

	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str1 = (char *)malloc(200 * sizeof(char));
		char *str2 = (char *)malloc(200 * sizeof(char));
		
		void *dest1 = (str1);
		void *dest2 = (str2);
		
		strcpy(str1, string);
		strcpy(str2, string);
		
		MemMove(dest1, str1, test_array[i]);
		memmove(dest2, str2, test_array[i]);
		

		status = memcmp(dest1, dest2, test_array[i]);
		if (0 == status)
		{
			printf("Memmove with no offset works for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed for  %lu \n", test_array[i]);
		}
		free(str1);
		free(str2);
		
		str1 = NULL;
		str2= NULL;
	}

	for (i = 0; i < ARR_SIZE(test_array); ++i)
	{	
		char *str1 = (char *)malloc(200 * sizeof(char));
		char *str2 = (char *)malloc(200 * sizeof(char));
		
		void *dest1 = (str1);
		void *dest2 = (str2);

		str2 = (str2 + 8);
		str1 = (str1 + 8);
		
		strcpy(str1, string);
		strcpy(str2, string);
		
		MemMove(dest1, str1, test_array[i]);
		memmove(dest2, str2, test_array[i]);
		

		status = memcmp(dest1, dest2, test_array[i]);
		if (0 == status)
		{
			printf("Memmove works neg offset for %lu \n", test_array[i]);
		}
		else 
		{
			printf("failed for  %lu \n", test_array[i]);
		}
		free(dest1);
		free(dest2);
		
		dest1 = NULL;
		dest2= NULL;
	}

	return;
}

