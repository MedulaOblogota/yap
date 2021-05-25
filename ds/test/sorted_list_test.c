#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dlist.h"
#include "sorted_list.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestSortedListCreate();
void TestSortedListSize();
void TestSortedListIsEmpty();
void TestSortedListPopFrontAndBack();
void TestSortedListForEach();
void TestSortedListFind();
void TestSortedListFindIf();
void TestSortedListMerge();
void TestSortedListGetData();
void TestSortedListBeginAndEnd();
void TestSortedListInsertAndRemove();
void TestSortedListRemove();
void TestSortedListIsSame();


int main()
{

	TestSortedListCreate();
	TestSortedListSize();
	TestSortedListIsEmpty();
	TestSortedListPopFrontAndBack();
	TestSortedListForEach();
	TestSortedListFind();
	TestSortedListFindIf();
	TestSortedListMerge();
	TestSortedListGetData();
    TestSortedListBeginAndEnd();
    TestSortedListInsertAndRemove();

    return (0);
}

static void CreateIntList(sorted_list_t *sorted_list, int *array, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        SortedListInsert(sorted_list, (void *)(array + i));
    }
}

static void PrintIntList(sorted_list_t *sorted_list)
{
    sorted_list_iter_t iter = SortedListBegin(sorted_list);

    while (!SortedListIsSame(SortedListEnd(sorted_list), iter))
    {
        printf("%d, ", *(int *)SortedListGetData(iter));
        iter = SortedListNext(iter);
    }

    printf("\n");
}

static void WrapperCompareSizet(char *func_name, size_t value, size_t expected_value)
{
    if (value == expected_value)
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!\n" RESET, func_name);
    }
}

static void WrapperCompareInt(char *func_name, int value, int expected_value)
{
	if (value == expected_value)
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!\n" RESET, func_name);
    }
}

static int CheckIfBeforeSizet(const void *data1, const void *data2, void *param)
{
    (void)param;

    return ((size_t)data1 < (size_t)data2);
}

static int CheckIfBeforeInt(const void *data1, const void *data2, void *param)
{
    (void)param;

    return (*(int *)data1 < *(int *)data2);
}

static int CompareInts(const void *data1, const void *data2, void *param)
{
    (void)param;

    return (*(int *)data1 == *(int *)data2);
}

static int IsSortedInts(sorted_list_t *list)
{
    sorted_list_iter_t iter = SortedListBegin(list);
    int temp = *(int *)SortedListGetData(iter);

    iter = SortedListNext(iter);

    while (!SortedListIsSame(iter, SortedListEnd(list)))
    {
        if (*(int *)SortedListGetData(iter) < temp)
        {
            return (0);
        }
        temp = *(int *)SortedListGetData(iter);
        iter = SortedListNext(iter);
    }

    return (1);
}

void TestSortedListCreate()
{
	sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeInt, NULL);

	if (NULL != sorted_list)
	{
		printf(GRN "SUCCESS with SortedListCreate!\n" RESET);
	}
	else
	{
		printf(RED "FAILURE with SortedListCreate!\n" RESET);
	}

	SortedListDestroy(sorted_list);
}

void TestSortedListSize()
{
	sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeSizet, NULL);

	WrapperCompareSizet("SortedListSize", SortedListSize(sorted_list), 0);

	SortedListDestroy(sorted_list);
}

void TestSortedListIsEmpty()
{
	sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeSizet, NULL);
	size_t num = 7;

    WrapperCompareSizet("SortedListIsEmpty", SortedListIsEmpty(sorted_list), 1);

	SortedListInsert(sorted_list, (void *)num);
	WrapperCompareSizet("SortedListIsEmpty", SortedListIsEmpty(sorted_list), 0);

	SortedListPopBack(sorted_list);
	WrapperCompareSizet("SortedListIsEmpty", SortedListIsEmpty(sorted_list), 1);

    SortedListDestroy(sorted_list);
}

void TestSortedListPopFrontAndBack()
{
	sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeSizet, NULL);
	size_t num = 5;
	sorted_list_iter_t pushed = SortedListInsert(sorted_list, (void *)num);

	++num;
	SortedListInsert(sorted_list, (void *)num);

	num = 4;
	SortedListInsert(sorted_list, (void *)num);

	SortedListPopFront(sorted_list);
	SortedListPopBack(sorted_list);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)SortedListGetData(pushed), 5);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)SortedListSize(sorted_list), 1);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", SortedListIsEmpty(sorted_list), 0);

	SortedListPopFront(sorted_list);
	SortedListPopBack(sorted_list);

	SortedListPopFront(sorted_list);
	SortedListPopBack(sorted_list);

	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)SortedListSize(sorted_list), 0);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", SortedListIsEmpty(sorted_list), 1);

	SortedListDestroy(sorted_list);
}

static int AddArgToItems(void* iter_arg, void *arg)
{

	*(int *)iter_arg += *(int *)arg;

	return 0;
}

static void WrapperCheckIntValuesInRange(sorted_list_iter_t begin1, sorted_list_iter_t end1, sorted_list_iter_t begin2, int addition)
{
    end1 = SortedListNext(end1);

    while (!SortedListIsSame(begin1, end1))
    {
        if (*(int *)SortedListGetData(begin1) != *(int *)SortedListGetData(begin2) + addition)
        {
            printf(RED "FAILED with SortedListForEach!!\n" RESET);
            return;
        }
        begin1 = SortedListNext(begin1);
        begin2 = SortedListNext(begin2);
    }

    printf(GRN "SUCCESS with SortedListForEach!\n" RESET);
}

void TestSortedListForEach()
{
    sorted_list_t *sorted_list1 = SortedListCreate(CheckIfBeforeInt, NULL);
    sorted_list_t *sorted_list2 = SortedListCreate(CheckIfBeforeInt, NULL);
    sorted_list_iter_t begin1 = SortedListNext(SortedListBegin(sorted_list1));
    sorted_list_iter_t end1 = SortedListEnd(sorted_list1);
    sorted_list_iter_t begin2 = SortedListNext(SortedListBegin(sorted_list2));

    int addition = 3;
    int num11 = 4;
    int num12 = 7;
    int num13 = 11;
    int num14 = 17;

    int num21 = 4;
    int num22 = 7;
    int num23 = 11;
    int num24 = 17;

    SortedListInsert(sorted_list1, (void *)&num11);
    SortedListInsert(sorted_list2, (void *)&num21);
    SortedListInsert(sorted_list1, (void *)&num12);
    SortedListInsert(sorted_list2, (void *)&num22);
    SortedListInsert(sorted_list1, (void *)&num13);
    SortedListInsert(sorted_list2, (void *)&num23);
    SortedListInsert(sorted_list1, (void *)&num14);
    SortedListInsert(sorted_list2, (void *)&num24);



    begin1 = SortedListNext(SortedListBegin(sorted_list1));
    end1 = SortedListPrev(SortedListEnd(sorted_list1));

    begin2 = SortedListNext(SortedListBegin(sorted_list2));


    printf("before:\n");
    PrintIntList(sorted_list1);

    SortedListForEach(begin1, end1, AddArgToItems, (void *)&addition);

    printf("after:\n");
    PrintIntList(sorted_list1);

    WrapperCheckIntValuesInRange(begin1, end1, begin2, addition);

    SortedListDestroy(sorted_list1);
    SortedListDestroy(sorted_list2);
}

void TestSortedListFind()
{
	sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeInt, NULL);
	int num1 = 6;
	int num2 = 9;
	int num3 = 3;
	int num4 = 1;
	int num5 = 7;
	sorted_list_iter_t begin = SortedListBegin(sorted_list);
	sorted_list_iter_t end = SortedListPrev(SortedListEnd(sorted_list));

	SortedListInsert(sorted_list, (void *)&num1);
	SortedListInsert(sorted_list, (void *)&num2);
	SortedListInsert(sorted_list, (void *)&num3);
	SortedListInsert(sorted_list, (void *)&num4);
	/*SortedListInsert(sorted_list, (void *)&num5);*/

	begin = SortedListBegin(sorted_list);
	end = SortedListPrev(SortedListEnd(sorted_list));
/*    printf("end item is %d\n", *(int *)SortedListGetData(end));*/
	WrapperCompareInt("SortedListFind", *(int *)SortedListGetData(SortedListFind(sorted_list, begin, end, (void *)&num3)), num3);
    WrapperCompareInt("SortedListFind", *(int *)SortedListGetData(SortedListFind(sorted_list, begin, end, (void *)&num5)), num2);
	SortedListDestroy(sorted_list);
}

int Compare(const void *data, const void *param)
{
        return (*(int *)data == *(int *)param);
}

void TestSortedListFindIf()
{
    sorted_list_t *sorted_list = SortedListCreate(CompareInts, NULL);
	int num1 = 6;
	int num2 = 9;
	int num3 = 3;
	int num4 = 1;
	int num5 = 3;
	sorted_list_iter_t begin = SortedListBegin(sorted_list);
	sorted_list_iter_t end = SortedListPrev(SortedListEnd(sorted_list));

	SortedListInsert(sorted_list, (void *)&num1);
	SortedListInsert(sorted_list, (void *)&num2);
	SortedListInsert(sorted_list, (void *)&num3);
	SortedListInsert(sorted_list, (void *)&num4);
	SortedListInsert(sorted_list, (void *)&num5);

	begin = SortedListBegin(sorted_list);
	end = SortedListPrev(SortedListEnd(sorted_list));
	WrapperCompareInt("SortedListFindIf", *(int *)SortedListGetData(SortedListFindIf(begin, end, Compare, (void *)&num5)), num5);

	SortedListDestroy(sorted_list);
}

static void WrapperSortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
    sorted_list_iter_t iter = SortedListBegin(dest);

    iter = SortedListNext(iter);

    if (SortedListSize(src) != 0)
    {
        printf(RED "FAILED with SortedListMerge!!\n" RESET);
        return;
    }

    if (IsSortedInts(dest))
    {
        printf(GRN "SUCCESS with SortedListMerge!\n" RESET);
    }
    else
    {
        printf(RED "FAILED with SortedListMerge!!\n" RESET);
    }
    /*while (!SortedListIsSame(iter, SortedListEnd(dest)))
    {
        if (*(int *)SortedListGetData(iter) < temp)
        {
            printf(RED "FAILED with SortedListMerge!!\n" RESET);
            break;
            temp = *(int *)SortedListGetData(iter);
        }
        iter = SortedListNext(iter);
    }

    printf(GRN "SUCCESS with SortedListMerge!\n" RESET);*/

}

void TestSortedListMerge()
{
    sorted_list_t *dest = SortedListCreate(CheckIfBeforeInt, NULL);
    sorted_list_t *src = SortedListCreate(CheckIfBeforeInt, NULL);
	int i = 0;
    int array1[3] = {0};
    int array2[5] = {0};

    srand(time(NULL));
    for (i = 0; i < 3; ++i)
    {
        array1[i] = rand();
    }

   CreateIntList(dest, array1, 3);

    printf("dest:\n");
    PrintIntList(dest);

    for (i = 0; i < 5; ++i)
    {
        array2[i] = rand();
    }
    CreateIntList(src, array2, 5);

   printf("src:\n");
    PrintIntList(src);

    printf("dest:\n");
    PrintIntList(dest);

    SortedListMerge(dest, src);

    PrintIntList(dest);
    printf("src:\n");
    PrintIntList(src);
    WrapperSortedListMerge(dest, src);

    SortedListDestroy(src);
    SortedListDestroy(dest);
}

void TestSortedListGetData()
{
    sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeInt, NULL);

    /*printf("SortedListGetData(SortedListBegin(sorted_list))=%s\n", (char *)SortedListGetData(SortedListBegin(sorted_list)));*/
    if (SortedListGetData(SortedListBegin(sorted_list)) != SortedListGetData(SortedListEnd(sorted_list)))
    {
        printf(RED "FAILURE with SortedListGetData!!\n" RESET);
        return;
    }
    else
    {
        printf(GRN "SUCCESS with SortedListGetData!!\n" RESET);
    }

    SortedListDestroy(sorted_list);
}

void TestSortedListBeginAndEnd()
{
    sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeInt, NULL);

    if (!SortedListIsSame(SortedListEnd(sorted_list), SortedListBegin(sorted_list)))
    {
        printf(RED "FAILURE with SortedListBegin or SortedListEnd!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with SortedListBegin and SortedListEnd!!\n" RESET);
    }

    SortedListDestroy(sorted_list);
}

void TestSortedListInsertAndRemove()
{
    sorted_list_t *sorted_list = SortedListCreate(CheckIfBeforeInt, NULL);
    int num1 = 4;
    int num2 = 70;
    int num3 = -1;
    int num4 = 2;
    int num5 = 0;

    SortedListInsert(sorted_list, (void *)&num1);
    SortedListInsert(sorted_list, (void *)&num2);
    SortedListInsert(sorted_list, (void *)&num3);
    SortedListInsert(sorted_list, (void *)&num4);
    SortedListInsert(sorted_list, (void *)&num5);

    if (!IsSortedInts(sorted_list))
    {
        printf(RED "FAILURE with SortedListInsert!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with SortedListInsert!!\n" RESET);
    }

    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListBegin(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));
    SortedListRemove(SortedListEnd(sorted_list));

    /*PrintIntList(sorted_list);*/
    if (!SortedListIsEmpty(sorted_list))
    {
        printf(RED "FAILURE with SortedListRemove!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with SortedListRemove!!\n" RESET);
    }

    SortedListDestroy(sorted_list);
}
