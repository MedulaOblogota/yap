#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "tests.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

int NumExistInArray(int *arr, size_t size, int random_num)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (arr[i] == random_num)
        {
            return (1);
        }
    }

    return (0);
}

void CreateRandomArray(int *arr, size_t arr_size, int modulus)
{
    size_t i = 0;
    int random_num = 0;

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        random_num = rand() % modulus;

        if (!NumExistInArray(arr, i, random_num))
        {
            arr[i] = (rand() % modulus);
        }
    }

    printf("array is:\n");
    for (i = 0; i < arr_size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void WrapperCompareInt(char *func_name, int exiting_value, int expected_value)
{
	if (exiting_value == expected_value)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperCompareSizet(char *func_name, size_t exiting_value, size_t expected_value)
{
	if (exiting_value == expected_value)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperComparetoNULL(char *func_name, void *data)
{
	if (NULL == data)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperCompareStringsWithStrLen(char *func_name, char *str1, char *str2)
{
    size_t i = 0;
    size_t length1 = 0;
    size_t length2 = 0;

	if ((str1 == str2) && (str1 == NULL))
	{
		printf(GRN"SUCCESS with %s as both are NULL!\n"RESET, func_name);
		return;
	}
	else if ((str1 == NULL ) || (str2 == NULL))
	{
		printf(RED"FAILURE with %s as only one is NULL!!!\n"RESET, func_name);
		return;
	}

	length1 = strlen(str1);
	length2 = strlen(str2);

    if (length1 != length2)
    {
        printf(RED"FAILURE with %s due to size!\n length of first string is %ld. length of second string is %ld"RESET,func_name, length1, length2);
        return;
    }
    for (i = 0; i < strlen(str1); ++i)
    {
        if (*(str1 + i) != *(str2 + i))
        {
            printf(RED"FAILURE with %s.\n char of first string is %c. char of second string is %c!"RESET, func_name, *str1, *str2);
            return;
        }
    }
    printf(GRN"SUCCESS with %s!!\n"RESET, func_name);
}
