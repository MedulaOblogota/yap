#include <stdio.h>

#include "tests.h"
#include "heap.h"

#define ARRAY_SIZE (10)

int cmp_func(const void *data1, const void *data2, void *param)
{
	(void)param;
	return (*(int *)data1 - *(int *)data2);
}

int is_match(const void *data1, const void *data2)
{
	return (*(int *)data1 == *(int *)data2);
}


void TestHeapPushAndPop();
void TestHeapRemove();
void TestHeapPeak();
void TestHeapSizeAndIsEmpty();

int main()
{
	TestHeapPushAndPop();
	TestHeapRemove();
	TestHeapPeak();
	TestHeapSizeAndIsEmpty();

	return (0);
}

void TestHeapPushAndPop()
{
	heap_t *heap = HeapCreate(cmp_func, NULL);
	int num1 = 5;
	int num2 = 7;
	int num3 = 4;
	int num4 = 2;
	int num5 = 1;
	int num6 = 0;
	int num7 = 9;
	int num8 = 6;
	int num9;


	HeapPush(heap, &num1);
	HeapPush(heap, &num2);
	HeapPush(heap, &num3);
	HeapPush(heap, &num4);
	HeapPush(heap, &num5);
	HeapPush(heap, &num6);
	HeapPush(heap, &num7);
	HeapPush(heap, &num8);

	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	printf("heap pop is %d\n", *(int *)HeapPeek(heap));
	printf("size is %lu\n", HeapSize(heap));
	num9 = *(int *)HeapRemove(heap, &num7, is_match);
	printf("removed data is %d\n", num9);
	HeapPop(heap);
/*	HeapPop(heap);
	HeapPop(heap);*/
	HeapPush(heap, &num3);
	HeapPush(heap, &num1);
	HeapPush(heap, &num4);
	HeapPush(heap, &num5);
	HeapPush(heap, &num2);
	HeapPush(heap, &num7);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPush(heap, &num8);
	HeapPush(heap, &num6);

	WrapperCompareSizet("HeapPush and HeapPop", 5, HeapSize(heap));


	HeapDestroy(heap);
}

void TestHeapRemove()
{
	heap_t *heap = HeapCreate(cmp_func, NULL);

	int arr[10] = {0};
	size_t i = 0;

	CreateRandomArray(arr, ARRAY_SIZE, 100);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		void *removed_data = HeapRemove(heap, &arr[i], is_match);
		if (removed_data == NULL)
		{
			printf("problem with %d\n", arr[i]);
			break;
		}

		if (*(int*)removed_data != arr[i])
		{
			printf("BAAAAD");
			break;
		}
	}

	WrapperCompareInt("HeapRemove", i, ARRAY_SIZE);

	HeapDestroy(heap);

}
void TestHeapPeak()
{
	heap_t *heap = HeapCreate(cmp_func, NULL);

	int arr[] = {7, 2, 9, -3, 20, 15, 4};
	int sorted_arr[] = {-3, 2, 4, 7, 9, 15, 20};
	size_t i = 0;

	/*CreateRandomArray(arr, ARRAY_SIZE, 100);*/

	for (i = 0; i < 7; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	for (i = 0; i < 7; ++i)
	{
		if (*(int *)HeapPeek(heap) != sorted_arr[i])
		{
			break;
		}
		HeapPop(heap);
	}

	WrapperCompareInt("HeapPeek", i, 7);
	WrapperCompareInt("HeapIsEmpty after popping and peaking", HeapIsEmpty(heap), 1);
	WrapperCompareSizet("HeapSize after popping and peaking", HeapSize(heap), 0);

	HeapDestroy(heap);
}
void TestHeapSizeAndIsEmpty()
{
	heap_t *heap = HeapCreate(cmp_func, NULL);
	int num = 3;

	WrapperCompareInt("HeapIsEmpty for empty heap", HeapIsEmpty(heap), 1);
	WrapperCompareSizet("HeapSize for empty heap", HeapSize(heap), 0);

	HeapPush(heap, &num);

	WrapperCompareInt("HeapIsEmpty for single data", HeapIsEmpty(heap), 0);
	WrapperCompareSizet("HeapSize for single data", HeapSize(heap), 1);

	HeapDestroy(heap);


}
