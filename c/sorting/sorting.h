#ifndef OL70_SORTING
#define OL70_SORTING

#include <stddef.h>

/*typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);*/

void BubbleSort(int *arr, size_t arr_size);

void SelectionSort(int *arr, size_t arr_size);

void InsertionSort(int *arr, size_t arr_size);

int CountingSort(void *arr, size_t ele_size, size_t range, size_t arr_size,
                    size_t find_index(const void *element, const void *param),
                    const void *param);

int RadixSort(int *base, size_t num_of_members);

int MergeSort(void *arr, size_t num_of_members, size_t element_size, int (*cmp_func)(void *, void *));

int HeapSort(int *arr, size_t num_of_members, int (*cmp_func)(const void *, const void *, void *));

void QSort(int *arr, size_t size);

int BinarySearch(int *arr,  size_t arr_size, int element);

/*size_t BinarySearch(int *arr, size_t size);*/

#endif
