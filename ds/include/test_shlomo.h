#include <stdio.h>
#include<stdlib.h>

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestSuccess(int success)
{
    if (success)
    {
        printf(GRN "CODE PASSED ALL TESTS SUCCESSFULLY\n" RESET);
    }
    else
    {
        printf(RED "CODE FAILED\n" RESET);
    }
}

int PrintResult(char *name_of_test, int result, int line)
 {
     static int flag = 1;

    if (!result)
    {
        printf(RED "%s test fail in line %d\n" RESET, name_of_test, line);

        flag = 0;
    }

    return flag;
}

void FillArray(int *array, size_t size_array)
{
    size_t i = 0;

    for (i = 0; i < size_array; ++i)
    {
        array[i] = (rand());
    }
}

void MergeArrays(int *merged_arr, int *arr1, int *arr2, size_t first_arr1,
size_t second_arr1, size_t amount)
{
    size_t i = 0;

    for (i = 0; i < first_arr1; ++i)
    {
        *merged_arr = *arr1;
        ++merged_arr;
        ++arr1;
    }

    for (i = 0; i < amount; ++i)
    {
        *merged_arr = *arr2;
        ++arr2;
        ++merged_arr;
    }

    for (i = 0; i < second_arr1; ++i)
    {
        *merged_arr = *arr1;
        ++merged_arr;
        ++arr1;
    }
}

void ResetArray(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        *arr = 0;
        ++arr;
    }
}

void ReverseArray(int *reversed_arr, int *arr, size_t size)
{
    size_t i = 0;
    arr = arr + size - 1;

    for (i = 0; i < size; ++i)
    {
        *reversed_arr = *arr;
        ++reversed_arr;
        --arr;
    }
}

void PrintArray(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i <size; ++i)
    {
        printf("%d\n", *arr);
        ++arr;
    }
}

int MinIntArr(int *arr, size_t size)
{
    size_t i = 0;
    int min = *arr;

    for (i = 0; i < size; ++i, ++arr)
    {
        if (min > *arr)
        {
            min = *arr;
        }
    }

    return min;
}

int MaxIntArr(int *arr, size_t size)
{
    size_t i = 0;
    int max = *arr;

    for (i = 0; i < size; ++i, ++arr)
    {
        if (max < *arr)
        {
            max = *arr;
        }
    }

    return max;
}


void CopyArr(int *dest, int *src, size_t size_src)
{
    while (size_src)
    {
        *dest = *src;
        ++dest;
        ++src;
        --size_src;
    }
}

int CmpFunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int TestArr(int *arr, int *test_arr, size_t size_arr)
{
    size_t i = 0;
    int result = 0;

    for (i = 0; i < size_arr; ++i)
    {
        result = (*test_arr == *arr);
        if (result == 0)
        {
            break;
        }
        ++test_arr;
        ++arr;
    }

    return result;
}
