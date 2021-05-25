/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Ben Izakson
Version:	Sent
Title:		SORTING Source File
*******************************************************************/

#include <assert.h>     /* assert */
#include <stdlib.h>     /* malloc */
#include <stdio.h>      /* printf */
#include <string.h>     /* memcpy */

#include "sorting.h"
#include "heap.h"

/********************************************************************
                    INNER FUNCTION DECLARATIONS
********************************************************************/
static void PrintList(char *list_name, int *list, size_t size);

static void swap(int *first, int *second);

static size_t FindMin(int *arr, size_t first_index, size_t last_index);

static void InsertAndMove(int *arr, size_t curr_index, size_t dest_index);

static size_t key_to_num(const void *element, const void *param);

int FindLargestDigitNum(int *arr, size_t num_of_members);

static void CountAmountOfNumbers(int *counts, void *arr, size_t arr_size,
    size_t ele_size, const void *param,
    size_t find_index(const void *element, const void *param));

static void SumUpValues(int *counts, size_t range);

static void MoveToNewList(int *counts, void *arr, size_t arr_size,
    size_t ele_size, void *list, const void *param,
    size_t find_index(const void *element, const void *param));

void *RecursiveMergeSort(void *arr, size_t num_of_members, size_t element_size, int (*cmp_func)(void *, void *));

void MergeArrays(void *first_part, void *second_part, size_t size1, size_t size2, int (*cmp_func)(void *, void *), size_t element_size);

void RecursiveQSort(int *arr, int start, int pivot);

void PartitionQSort(int *arr, int size);



/********************************************************************
                    FUNCTION IMPLEMENTATIONS
********************************************************************/
void BubbleSort(int *arr, size_t arr_size)
{
    size_t i = 0;

    int first = 0;
    int is_sorted = 0;
    int second = 0;

    assert(NULL != arr);

    while (!is_sorted)
    {
        is_sorted = 1;
        for (i = 0; i < arr_size - 1; ++i)
        {
            first = arr[i];
            second = arr[i+1];

            if (second < first)
            {
                swap(arr + i, arr+i +1);
                is_sorted = 0;
            }
        }
        --arr_size;
    }
}

void SelectionSort(int *arr, size_t arr_size)
{
    size_t min_index = 0;
    size_t curr_first_index = 0;
    size_t curr_last_index = arr_size - 1;

    assert(NULL != arr);

    while (curr_first_index < curr_last_index)
    {
        min_index = FindMin(arr, curr_first_index, curr_last_index);

        swap(arr + curr_first_index, arr + min_index);

        ++curr_first_index;
    }
}

void InsertionSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;

    assert(NULL != arr);

    for (i = 1; i < arr_size; ++i)
    {
        j = i - 1;

        while ((arr[i] < arr[j]) && (j < i))
        {
            --j;
        }
        ++j;

        if (j != i)
        {
            InsertAndMove(arr, i, j);
        }
    }
}

int CountingSort(void *arr, size_t ele_size, size_t range, size_t arr_size,
                    size_t find_index(const void *element, const void *param),
                    const void *param)
{
	int *counts = calloc(range, sizeof(int));
	void *list = NULL;

	if (NULL == counts)
    {
        return 0;
    }

    list = calloc(arr_size, ele_size);
    if (NULL == list)
    {
        free(counts);
        return 0;
    }

    CountAmountOfNumbers(counts, arr, arr_size, ele_size, param, find_index);

    SumUpValues(counts, range);

    MoveToNewList(counts, arr, arr_size, ele_size, list, param, find_index);

	memcpy(arr, list, ele_size * arr_size);

    free(counts);
    free(list);

	return (1);
}

int RadixSort(int *base, size_t num_of_members)
 {
     int i = 0;

     int largest_digit_num = FindLargestDigitNum(base, num_of_members);

     for (i = 0; i < largest_digit_num; ++i)
     {
        if (CountingSort(base, sizeof(int), 19, num_of_members, key_to_num,
                                                            (void *)&i) == 0)
        {
            return (0);
        }
     }

     return(1);
 }

int MergeSort(void *arr, size_t num_of_members, size_t element_size, int (*cmp_func)(void *, void *))
{
	RecursiveMergeSort(arr, num_of_members, element_size, cmp_func);

	return 1;
}

int HeapSort(int *arr, size_t num_of_members, int (*cmp_func)(const void *, const void *, void *))
{
	size_t i = 0;

	heap_t *heap = HeapCreate(cmp_func, NULL);

	if (NULL == heap)
	{
		return 0;
	}

	for (i = 0; i < num_of_members; ++i)
	{
		HeapPush(heap, arr + i);
	}

	for (i = 0; i < num_of_members; ++i)
	{
		arr[i] = *(int *)HeapPeek(heap);
		HeapPop(heap);
	}

	return 1;
}

void QSort(int *arr, size_t size)
{
	if (size < 2)
	{
		return;
	}

	if (size == 2)
	{
		if (arr[0] > arr[1])
		{
			swap(arr, arr  + 1);
		}
	}
	else
	{
		PartitionQSort(arr, size);
	}
}

int BinarySearch(int *arr,  size_t arr_size, int element)
{
	int is_found = 0;
	size_t index = arr_size / 2;
	size_t begin = 0;
	size_t end = arr_size - 1;
	while (!is_found)
	{
		index = begin + (end - begin) / 2;
		if (arr[index] < element)
		{
			begin = index + 1;
		}
		else  if (arr[index] > element)
		{
			end = index - 1;
		}
		else
		{
			return (index);
		}

		if ((begin == end) || (begin > end))
		{
			return -1;
		}
	}

	return -1;
}

/*
int BinarySearch(int *arr,  size_t arr_size, int element)
{
	size_t index = arr_size / 2;
	int first_return;
	int second_return;

	if (arr_size == 1)
	{
		if (arr[arr_size - 1] != element)
		{
			return -1;
		}
		else
		{
			return arr[arr_size - 1];
		}
	}



	first_return = BinarySearch(arr + index + 1, arr_size - index - 1, element);
	second_return = BinarySearch(arr, arr_size - index - 1, element);

	return (first_return > second_return ? first_return : second_return);
}*/

/********************************************************************
                    INNER FUNCTION DEFINITIONS
********************************************************************/
static void PrintList(char *list_name, int *list, size_t size)
{
	size_t i = 0;

	printf("%s is: \n", list_name);

	for (i = 0; i < size; ++i)
	{
		printf("%lu. %d\n", i, *(list + i));
	}
}

static void swap(int *first, int *second)
{
    int temp = *first;

    if (first != second)
    {
        *first = *second;
        *second = temp;
    }
}

static size_t FindMin(int *arr, size_t first_index, size_t last_index)
{
    size_t i = first_index;
    size_t index = first_index;
    int min = arr[i];

    for (i = first_index; i <= last_index; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            index = i;
        }
    }

    return index;
}

static void InsertAndMove(int *arr, size_t curr_index, size_t dest_index)
{
    while (dest_index < curr_index)
    {
        swap(arr + curr_index, arr + dest_index);
        ++dest_index;
    }
}

static size_t key_to_num(const void *element, const void *param)
{
    int num = *(int *)element;
    int power = *(int *)param;
    int i = 0;
    int index = 0;

    for (i = 0; i < power; ++i)
    {
        num = num / 10;
    }

    index = num % 10;

    return (index + 9);
}

int FindLargestDigitNum(int *arr, size_t num_of_members)
{
    size_t i = 0;
    int max_digs = 0;
    int digs = 0;
    int num = 0;

    for (i = 0; i < num_of_members; ++i)
    {
        num = arr[i];

        digs = 0;
        while (0 != num)
        {
            num = num / 10;
            ++digs;
        }

        if (digs > max_digs)
        {
            max_digs = digs;
        }
    }

    return (max_digs);
}

static void CountAmountOfNumbers(int *counts, void *arr, size_t arr_size,
    size_t ele_size, const void *param,
    size_t find_index(const void *element, const void *param))
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
	{
		++(*(counts + find_index(((char *)arr + ele_size * i), param)));
	}
}

static void SumUpValues(int *counts, size_t range)
{
    int temp = 0;
    int counter = 0;
    size_t i = 0;

    for (i = 0; i < range; ++i)
	{

		temp = *(counts + i);
		*(counts + i) = counter + *(counts + i);
        counter += temp;
	}
}

static void MoveToNewList(int *counts, void *arr, size_t arr_size,
    size_t ele_size, void *list, const void *param,
    size_t find_index(const void *element, const void *param))
{
    int j = 0;
    int index = 0;

    for (j = arr_size - 1; j >= 0; --j)
	{

		--(*(counts + find_index(((char *)arr + ele_size * j), param)));
		index = *(counts + find_index(((char *)arr + ele_size * j), param));
        memcpy((void *)((char *)list + ele_size * index),
                                (void *)((char *)arr + ele_size * j), ele_size);
	}
}

void MergeArrays(void *first_part, void *second_part, size_t size1, size_t size2, int (*cmp_func)(void *, void *), size_t element_size)
{
	void *temp_arr = malloc((size1 +size2)*element_size);
	size_t i = 0;
	size_t j = 0;

	void *first_val = NULL;
	void *second_val = NULL;

	while ((i < size1) || (j < size2))
	{
		if (i == size1)
		{
			first_val = NULL;
		}
		else
		{
			first_val = ((char *)first_part + i * element_size);
		}

		if (j == size2)
		{
			second_val = NULL;
		}
		else
		{
			second_val = ((char *)second_part + j * element_size);
		}

		if (cmp_func(first_val, second_val) < 0)
		{
			memcpy((char *)temp_arr + i * element_size + j * element_size, first_val, element_size);
			/*((char *)temp_arr + i * element_size + j * element_size) = first_val;*/
			++i;
		}
		else
		{
			memcpy((char *)temp_arr + i * element_size + j * element_size, second_val, element_size);
		/*	((char *)temp_arr + i * element_size + j * element_size) = second_val;*/
			++j;
		}
	}

	for (i = 0; i < size1 + size2; ++i)
	{
		memcpy((char *)first_part + i * element_size, (char *)temp_arr + i * element_size, element_size);
		/*((char *)first_part + i * element_size) = ((char *)temp_arr + i * element_size);*/
	}

	free(temp_arr);
}

void *RecursiveMergeSort(void *arr, size_t num_of_members, size_t element_size, int (*cmp_func)(void *, void *))
{
	/*int *first_part = malloc(num_of_members * sizeof(int));
	int *second_part = malloc(num_of_members * sizeof(int));*/
	void *first_part = NULL;
	void *second_part = NULL;
	int index = 0;

	if (num_of_members == 1)
	{
		return arr;
	}

	index = num_of_members / 2;

	first_part = RecursiveMergeSort(arr, index, element_size, cmp_func);
	second_part = RecursiveMergeSort((char *)arr + index*element_size, num_of_members - index, element_size, cmp_func);
	MergeArrays(first_part, second_part, index, num_of_members - index, cmp_func, element_size);

	return(arr);
}

/*
void RecursiveQSort(int *arr, int start, int pivot)
{
	int new_pivot = PartitionQSort(arr, start, pivot);

	if (new_pivot != pivot)
	{
		RecursiveQSort(arr, new_pivot + 1, pivot);
	}

	if (new_pivot != start)
	{
		RecursiveQSort(arr, start, new_pivot - 1);
	}
}
*/

void PartitionQSort(int *arr, int size)
{
	int left_index = 0;
	int pivot = size - 1;
	int right_index = pivot - 1;

	while (left_index < right_index)
	{
		while (arr[left_index] < arr[pivot])
		{
			++left_index;
		}
		while (arr[right_index] >= arr[pivot])
		{
			--right_index;
			if (right_index == 0)
			{
				break;
			}
		}

		if (left_index < right_index)
		{
			swap(arr + left_index, arr + right_index);
		}

		swap(arr + left_index, arr + pivot);
		QSort(arr, left_index);
		QSort(arr + left_index, size - left_index);
	}
}
