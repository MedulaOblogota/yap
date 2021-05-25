#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sorting.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

#define ARRAY_SIZE (10)
#define QSORT_SIZE (6)

void TestCountingSort();
void TestRadixSort();

int cmp_func(const void *data1, const void *data2, void *param)
{
	(void)param;
	return (*(int *)data1 - *(int *)data2);
}

static void PrintArray(int *arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {

            printf("%lu. %d\n ", i, arr[i]);


    }
}

static void PrintVoidIntArray(void *arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {

            printf("%lu. %d\n ", i, *((int *)(arr) + i));


    }
}

static void CreateRandomArray(int *arr, size_t arr_size, int modulus, int addition)
{
    size_t i = 0;

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        arr[i] = (rand() % modulus) + addition;
    }
}

static void CheckIfSorted(char *func_name, int *arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size - 1; ++i)
    {
        if (arr[i+1] < arr[i])
        {
            printf(RED"%s FAILED!!!\n"RESET, func_name);
            return;
        }
    }
    printf(GRN"SUCCESS with %s!\n"RESET, func_name);
}

static size_t find_index(const void *element, const void *param)
{
    return (*(int *)element - *(int *)param);
}

static void CopyArray(int *dest_arr, int *src_arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        dest_arr[i] = src_arr[i];
    }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int int_cmp_func(void * num1, void *num2)
{
	if (num1 == NULL)
	{
		return (1);
	}
	else if (num2 == NULL)
	{
		return (-1);
	}

	return (*(int *)num1 - *(int *)num2);
}

void CheckIfEqualToQsort (int *qsort_arr, int *arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        if (qsort_arr[i] != arr[i])
        {
            printf(RED"FAILED!!!!\n"RESET);
            break;
        }
    }
}

int main()
{
    int bubble_sort_arr[ARRAY_SIZE] = {0};
    int selection_sort_arr[ARRAY_SIZE] = {0};
    int insertion_sort_arr[ARRAY_SIZE] = {0};
    int merge_sort_arr[ARRAY_SIZE] = {0};
    int qsort_arr[ARRAY_SIZE] = {0};
	int heap_arr[ARRAY_SIZE] = {0};
	int my_qsort_arr[ARRAY_SIZE] = {0};
	int binary_search_arr[10] = {1, 5, 7, 8, 12, 14, 20, 29, 31, 35};

    clock_t beginning = clock();
    int modulus = 1000;
    int min = 0;

    TestCountingSort();
    TestRadixSort();

    CreateRandomArray(bubble_sort_arr, ARRAY_SIZE, modulus, min);
    CopyArray(selection_sort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(insertion_sort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(qsort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(merge_sort_arr, bubble_sort_arr, ARRAY_SIZE);
	CopyArray(heap_arr, bubble_sort_arr, ARRAY_SIZE);
	CopyArray(my_qsort_arr, bubble_sort_arr, ARRAY_SIZE);

    beginning = clock();
    BubbleSort(bubble_sort_arr, ARRAY_SIZE);
    printf("time difference for BubbleSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    SelectionSort(selection_sort_arr, ARRAY_SIZE);
    printf("time difference for SelectionSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    InsertionSort(insertion_sort_arr, ARRAY_SIZE);
    printf("time difference for InsertionSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	beginning = clock();
	PrintArray(merge_sort_arr, ARRAY_SIZE);
	MergeSort((void *)merge_sort_arr, ARRAY_SIZE, sizeof(int), int_cmp_func);
	printf("time difference for MergeSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	PrintVoidIntArray(merge_sort_arr, ARRAY_SIZE);

	beginning = clock();
	HeapSort(heap_arr, ARRAY_SIZE, cmp_func);
	printf("time difference for HeapSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	beginning = clock();
	QSort(my_qsort_arr, ARRAY_SIZE);
	printf("time difference for MyQueueSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    qsort(qsort_arr, ARRAY_SIZE, sizeof(int), cmpfunc);
    printf("time difference for QSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	printf("%d\n", BinarySearch(binary_search_arr, 10, 5));
	if (BinarySearch(binary_search_arr, 10, 5) == 1)
	{
		printf(GRN"success with binary search for finding existing value!\n"RESET);
	}
	else
	{
		printf(RED"failure with binary search for finding existing value!!!\n"RESET);
	}

	printf("%d\n", BinarySearch(binary_search_arr, 10, 50));
	if (BinarySearch(binary_search_arr, 10, 50) == -1)
	{
		printf(GRN"success with binary search for finding none-existing value!!\n"RESET);
	}
	else
	{
		printf(RED"failure with binary search for finding none-existing value!!!\n"RESET);
	}



    CheckIfSorted("BubbleSort", bubble_sort_arr, ARRAY_SIZE);
    CheckIfSorted("SelectionSort", selection_sort_arr, ARRAY_SIZE);
    CheckIfSorted("InsertionSort", insertion_sort_arr, ARRAY_SIZE);
	CheckIfSorted("MergeSort", merge_sort_arr, ARRAY_SIZE);
	CheckIfSorted("MyQueueSort", my_qsort_arr, ARRAY_SIZE);
	/*CheckIfSorted("HeapSort", heap_arr, ARRAY_SIZE);*/

    CheckIfEqualToQsort(qsort_arr, bubble_sort_arr, ARRAY_SIZE);
    CheckIfEqualToQsort(qsort_arr, selection_sort_arr, ARRAY_SIZE);
    CheckIfEqualToQsort(qsort_arr, insertion_sort_arr, ARRAY_SIZE);
	CheckIfEqualToQsort(my_qsort_arr, insertion_sort_arr, ARRAY_SIZE);

    return (0);
}

void TestCountingSort()
{
    int arr[ARRAY_SIZE] = {0};
    int min = 0;

    int modulus = 1000;

    clock_t beginning = clock();

    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);

    beginning = clock();
    CountingSort(arr, sizeof(int), modulus, ARRAY_SIZE, find_index, (void *)&min);
    printf("time difference for CountingSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("CountingSort with random values between 0->999", arr, ARRAY_SIZE);

    min = 500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    CountingSort(arr, sizeof(int), modulus, ARRAY_SIZE, find_index, (void *)&min);
    printf("time difference for CountingSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("CountingSort with random values between 500->1499", arr, ARRAY_SIZE);

    min = -500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    CountingSort(arr, sizeof(int), modulus, ARRAY_SIZE, find_index, (void *)&min);
    printf("time difference for CountingSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("CountingSort with random values between -500->499", arr, ARRAY_SIZE);

    min = -1500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    CountingSort(arr, sizeof(int), modulus, ARRAY_SIZE, find_index, (void *)&min);
    printf("time difference for CountingSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("CountingSort with random values between -1500->-501", arr, ARRAY_SIZE);

}

void TestRadixSort()
{
    int arr[ARRAY_SIZE] = {0};
    int min = 0;

    int modulus = 900000000;

    clock_t beginning = clock();

    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);

    beginning = clock();
    RadixSort(arr, ARRAY_SIZE);
    printf("time difference for RadixSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("RadixSort with random values between 0->999", arr, ARRAY_SIZE);

    min = 500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    RadixSort(arr, ARRAY_SIZE);
    printf("time difference for RadixSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("RadixSort with random values between 500->1499", arr, ARRAY_SIZE);

    min = -500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    RadixSort(arr, ARRAY_SIZE);
    printf("time difference for RadixSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("RadixSort with random values between -500->499", arr, ARRAY_SIZE);

    min = -1500;
    CreateRandomArray(arr, ARRAY_SIZE, modulus, min);
    beginning = clock();
    RadixSort(arr, ARRAY_SIZE);
    printf("time difference for RadixSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    CheckIfSorted("RadixSort with random values between -1500->-501", arr, ARRAY_SIZE);
}
