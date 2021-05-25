#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sorting.h"

#define ARRAY_SIZE (10000)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

static void PrintArray(int *arr, size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        printf("%lu. %d\n", i, arr[i]);

        if (i == (arr_size - 1))
        {
            printf("\n");
        }
    }
}

static void CreateRandomArray(int *arr, size_t arr_size)
{
    size_t i = 0;

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        arr[i] = (rand() % 1000);
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
    int counting_sort_arr[ARRAY_SIZE] = {0};
    int qsort_arr[ARRAY_SIZE] = {0};

    clock_t beginning = clock();

/*    int arr[7] = {1, 8, 6, 9, 20, 13, 2};*/

    CreateRandomArray(bubble_sort_arr, ARRAY_SIZE);
    CopyArray(selection_sort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(insertion_sort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(counting_sort_arr, bubble_sort_arr, ARRAY_SIZE);
    CopyArray(qsort_arr, bubble_sort_arr, ARRAY_SIZE);

    /*PrintArray(counting_sort_arr, ARRAY_SIZE);*/

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
    CountingSort(counting_sort_arr, sizeof(int), 1000, ARRAY_SIZE, find_index, (void *)&min);
    printf("time difference for CountingSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    m

    PrintArray(counting_sort_arr, ARRAY_SIZE);

    beginning = clock();
    qsort(qsort_arr, ARRAY_SIZE, sizeof(int), cmpfunc);
    printf("time difference for QSort is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    CheckIfSorted("BubbleSort", bubble_sort_arr, ARRAY_SIZE);
    CheckIfSorted("SelectionSort", selection_sort_arr, ARRAY_SIZE);
    CheckIfSorted("InsertionSort", insertion_sort_arr, ARRAY_SIZE);
    CheckIfSorted("CountingSort", counting_sort_arr, ARRAY_SIZE);

    CheckIfEqualToQsort(qsort_arr, bubble_sort_arr, ARRAY_SIZE);
    CheckIfEqualToQsort(qsort_arr, selection_sort_arr, ARRAY_SIZE);
    CheckIfEqualToQsort(qsort_arr, insertion_sort_arr, ARRAY_SIZE);
    /*CheckIfEqualToQsort(qsort_arr, counting_sort_arr, ARRAY_SIZE);*/

    return (0);
}
