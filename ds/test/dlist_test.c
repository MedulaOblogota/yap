#include <stdio.h>
#include <string.h>

#include "dlist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestDListCreate();
void TestDListSize();
void TestDListIsEmpty();
void TestDListPushFront();
void TestDListPushBack();
void TestDListPopFront();
void TestDListPopBack();
void TestDListForEach();
void TestDListFind();
void TestDListSplice();
void TestDListGetData();
void TestDListBegin();
void TestDListEnd();
void TestDListInsert();
void TestDListInsertAfter();
void TestDListRemove();
void TestDListIsSameIter();
void TestDListNext();
void TestDListPrev();


int main()
{
    TestDListCreate();
    TestDListSize();
    TestDListIsEmpty();
    TestDListPushFront();
    TestDListPushBack();
    TestDListPopFront();
    TestDListForEach();
    TestDListFind();
    TestDListSplice();
    TestDListGetData();
    TestDListBegin();
    TestDListEnd();
    TestDListInsert();

    TestDListRemove();

    TestDListNext();
    TestDListPrev();

    return (0);
}

static void CreateList(dlist_t *dlist, size_t size)
{
		size_t item = 1;

		for (item = 1; item <= size; ++item)
		{
			DListPushBack(dlist, (void *)item);
		}
}



static void WrapperCompareIterators(char *func_name, size_t searched_item, dlist_iter_t iter)
{
		size_t extracted_value = (size_t)DListGetData(iter);

		if (extracted_value == searched_item)
		{
			printf(GRN "SUCCESS with %s!\n" RESET, func_name);
		}
		else
		{
			printf(RED "FAILURE with %s!!!\n" RESET, func_name);
		}
}

void TestDListCreate()
{
    dlist_t *dlist = DListCreate();

    if (NULL != dlist)
    {
        printf(GRN "SUCCESS with DListCreate!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListCreate!\n" RESET);
    }

    DListDestroy(dlist);
}

void WrapperCompareSizet(char *func_name, size_t value, size_t expected_value)
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

void TestDListSize()
{
    dlist_t *dlist = DListCreate();

    WrapperCompareSizet("DListSize", DListSize(dlist), 0);

    DListDestroy(dlist);
}

void TestDListIsEmpty()
{
    dlist_t *dlist = DListCreate();
	size_t num = 7;

    WrapperCompareSizet("DListIsEmpty", DListIsEmpty(dlist), 1);

	DListPushFront(dlist, (void *)num);
	WrapperCompareSizet("DListIsEmpty", DListIsEmpty(dlist), 0);

	DListPopBack(dlist);
	WrapperCompareSizet("DListIsEmpty", DListIsEmpty(dlist), 1);

    DListDestroy(dlist);
}

void TestDListPushFront()
{
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    size_t num = 5;

    iter = DListPushFront(dlist, (void *)num);

    WrapperCompareSizet("DListPushFront", DListSize(dlist), 1);
    WrapperCompareIterators("DListPushFront", num, iter);

    DListDestroy(dlist);
}

void TestDListPushBack()
{
    dlist_t *dlist = DListCreate();
    dlist_iter_t pushed = NULL;
    size_t num = 5;

    pushed = DListPushBack(dlist, (void *)num);

    WrapperCompareSizet("TestDListPushBack", DListSize(dlist), 1);
    WrapperCompareIterators("TestDListPushBack", num, pushed);
    /*printf("data in item is %lu\n", (size_t)DListGetData(pushed));*/

    DListPopFront(dlist);
    WrapperCompareSizet("DListPopFront", DListSize(dlist), 0);
    DListPopFront(dlist);
    DListPopFront(dlist);
    WrapperCompareSizet("DListPopFront", DListSize(dlist), 0);

    DListDestroy(dlist);
}

void TestDListPopFront()
{
	dlist_t *dlist = DListCreate();
	dlist_iter_t pushed = NULL;
	size_t num = 5;

	pushed = DListPushFront(dlist, (void *)num);

	++num;
	DListPushBack(dlist, (void *)num);

	num = 4;
	DListPushFront(dlist, (void *)num);

	DListPopFront(dlist);
	DListPopBack(dlist);
	WrapperCompareSizet("DListPopFront and DListPopBack", (size_t)DListGetData(pushed), 5);
	WrapperCompareSizet("DListPopFront and DListPopBack", (size_t)DListSize(dlist), 1);
	WrapperCompareSizet("DListPopFront and DListPopBack", DListIsEmpty(dlist), 0);

	DListPopFront(dlist);
	DListPopBack(dlist);

	DListPopFront(dlist);
	DListPopBack(dlist);

	WrapperCompareSizet("DListPopFront and DListPopBack", (size_t)DListSize(dlist), 0);
	WrapperCompareSizet("DListPopFront and DListPopBack", DListIsEmpty(dlist), 1);

	DListDestroy(dlist);
}

static int PrintItems(void *iter, void *arg)
{
    (void)arg;
	printf("%lu, ", (size_t)iter);

	return 1;
}

static int PrintIntItems(void *iter, void *arg)
{
    (void)arg;
	printf("%d, ", *(int *)iter);

	return 1;
}

static int AddArgToItems(void *iter, void *arg)
{

	*(int *)iter += *(int *)arg;


	return 1;
}

static int Compare(const void *first, const void *second)
{
	return((size_t)first == (size_t)second);
}

void TestDListForEach()
{
	dlist_t *dlist = DListCreate();
	int num = 3;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;

    int original_num = 1;

    DListPushFront(dlist, &num4);
    DListPushFront(dlist, &num3);
    DListPushFront(dlist, &num2);
    DListPushFront(dlist, &num1);

	begin = DListBegin(dlist);
	end = DListEnd(dlist);
/*
    printf("before addition:\n");
	DListForEach(begin, end, PrintIntItems, (void *)&num);*/
    end = DListFind(begin, DListEnd(dlist), Compare, (void *)&num3);
    DListForEach(begin, end, AddArgToItems, (void *)&num);

    end = DListEnd(dlist);

    WrapperCompareSizet("DListForEach", original_num + num, *(int *)DListGetData(begin));
/*    printf("after addition:\n");
    DListForEach(begin, end, PrintIntItems, (void *)&num);*/
    DListDestroy(dlist);

}


/*
static void WrapperCompareTwoIterators(char *func_name, dlist_iter_t iter1, dlist_iter_t iter2)
{
		char *extracted_value1 = (char *)DListGetData(iter1);
        char *extracted_value2 = (char *)DListGetData(iter2);

		if (strcmp((char *)extracted_value1, (char *)extracted_value2) == 0)
		{
			printf(GRN "SUCCESS with %s!\n" RESET, func_name);
		}
		else
		{
			printf(RED "FAILURE with %s!!!\n" RESET, func_name);
		}
}
*/
void TestDListFind()
{
	dlist_t *dlist = DListCreate();
	size_t amount_of_items = 6;
	size_t searched_item = 4;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;
    char *tail_data = "ThisIsTail";
    char checked[20];

	CreateList(dlist, amount_of_items);
	begin = DListBegin(dlist);
	end = DListEnd(dlist);

	WrapperCompareIterators("DListFind", searched_item, DListFind(begin, end, Compare, (void *)searched_item));

    begin = DListBegin(dlist);
	end = DListEnd(dlist);
	searched_item = 20;
/*    printf("%s\n", DListFind(begin, end, Compare, (void *)searched_item));*/
    strcpy(checked,(char *)DListGetData(DListFind(begin, end, Compare, (void *)searched_item)));
    if ( strcmp((char *)DListGetData(DListFind(begin, end, Compare, (void *)searched_item)), tail_data) == 0)
    {
        printf(GRN "SUCCESS with DListFind!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListFind!!!\n" RESET);
    }
	/*WrapperCompareIterators("DListFind", amount_of_items, DListFind(begin, end, Compare, (void *)searched_item));*/

    DListDestroy(dlist);
}

static void WrapperDListSplice(size_t items_dest_list, size_t items_src_list, size_t from, size_t to, size_t where)
{
    dlist_t *dest = DListCreate();
    dlist_t *src = DListCreate();

    dlist_iter_t from_node;
	dlist_iter_t to_node;
	dlist_iter_t where_node;

    size_t items_to_move = to - from + 1;
    CreateList(dest, items_dest_list);
    CreateList(src, items_src_list);

    from_node = DListFind(DListBegin(src), DListEnd(src), Compare, (void *)from);
	to_node = DListFind(DListBegin(src), DListEnd(src), Compare, (void *)to);
	where_node = DListFind(DListBegin(dest), DListEnd(dest), Compare, (void *)where);

    DListSplice(from_node, to_node, where_node);

    WrapperCompareSizet("DListSplice", items_to_move + items_dest_list, DListSize(dest));
    WrapperCompareSizet("DListSplice", items_src_list - items_to_move, DListSize(src));

    DListDestroy(dest);
    DListDestroy(src);
}

void TestDListSplice()
{
	/*dlist_t *dest1 = DListCreate();
	dlist_t *src1 = DListCreate();
	dlist_iter_t from_node;
	dlist_iter_t to_node;
	dlist_iter_t where_node;
	dlist_iter_t begin;
	dlist_iter_t end;
	size_t from = 2;
	size_t to = 4;
	size_t where = 3;
    size_t initial_dest_size = 0;
    size_t initial_src_size = 0;

	dlist_t *dest2 = DListCreate();
	dlist_t *src2 = DListCreate();
	dlist_iter_t from2;
	dlist_iter_t to2;

	dlist_t *dest3 = DListCreate();
	dlist_t *src3 = DListCreate();
	dlist_iter_t from3;
	dlist_iter_t to3;*/

	WrapperDListSplice(8, 6, 2, 4, 3);

    WrapperDListSplice(1, 1, 1, 1, 1);

    WrapperDListSplice(1, 2, 1, 2, 1);
    /*
	CreateList(dest1, 8);
    initial_dest_size = 8;
	CreateList(src1, 6);
    initial_src_size = 3;

	from_node = DListFind(DListBegin(src1), DListEnd(src1), Compare, (void *)from);
	to_node = DListFind(DListBegin(src1), DListEnd(src1), Compare, (void *)to);
	where_node = DListFind(DListBegin(dest1), DListEnd(dest1), Compare, (void *)where);

	DListSpliceBefore(where_node, from_node, to_node);

    printf("dest1 length = %lu\n", DListSize(dest1));
    printf("src1 length = %lu\n", DListSize(src1));

	WrapperCompareSizet("DListSplice", initial_dest_size + initial_src_size, DListSize(dest1));
    WrapperCompareSizet("DListSplice", 3, DListSize(src1));


	CreateList(dest2, 1);
	CreateList(src2, 1);
    initial_dest_size = 1;
    initial_src_size = 1;

	from = 1;
	to = 1;
	where = 1;

	begin = DListBegin(src2);
	end = DListEnd(src2);

	from_node = DListFind(begin, end, Compare, (void *)from);
	to_node = DListFind(begin, end, Compare, (void *)to);

	begin = DListBegin(dest2);
	end = DListEnd(dest2);

	where_node = DListFind(begin, end, Compare, (void *)where);

	DListSpliceBefore(where_node, from_node, to_node);

    WrapperCompareSizet("DListSplice", initial_dest_size + initial_src_size, DListSize(dest2));
    WrapperCompareSizet("DListSplice", 0, DListSize(src2));

	CreateList(dest3, 1);
	CreateList(src3, 2);
    initial_dest_size = 1;
    initial_src_size = 1;

    from = 2;
	to = 2;
	where = 1;

    begin = DListBegin(src3);
	end = DListEnd(src3);

	from_node = DListFind(begin, end, Compare, (void *)from);
	to_node = DListFind(begin, end, Compare, (void *)to);

	begin = DListBegin(dest3);
	end = DListEnd(dest3);

	where_node = DListFind(begin, end, Compare, (void *)where);

	DListSpliceBefore(where_node, from_node, to_node);

    WrapperCompareSizet("DListSplice", initial_dest_size + initial_src_size, DListSize(dest3));
    WrapperCompareSizet("DListSplice", 1, DListSize(src3));*/
}


void TestDListGetData()
{
	dlist_t *dlist = DListCreate();
	dlist_iter_t iter = DListBegin(dlist);
    size_t num1 = 3;
    size_t num2 = 7;
    size_t num3 = 29;
    char *tail_data = "ThisIsTail";

	if (strcmp((char *)DListGetData(iter), tail_data) != 0)
    {
        printf(RED "FAILURE with DListGetData!!!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with DListGetData!!\n" RESET);
    }

    DListPushBack(dlist, (void *)num1);
    iter = DListPushBack(dlist, (void *)num2);
    DListPushBack(dlist, (void *)num3);

    if (7 != (size_t)DListGetData(iter))
    {
        printf(RED "FAILURE with DListGetData!!!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with DListGetData!!\n" RESET);
    }

    DListDestroy(dlist);
}

/* returns head if empty list */
void TestDListBegin()
{
    dlist_t *dlist = DListCreate();
    char *tail_data = "ThisIsTail";

    if (strcmp((char *)DListGetData(DListBegin(dlist)), tail_data ) == 0)
    {
        printf(GRN "SUCCESS with DListBegin!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListBegin!\n" RESET);
    }

    DListDestroy(dlist);
}

/* returns tail if empty list */
void TestDListEnd()
{
    dlist_t *dlist = DListCreate();
    char *tail_data = "ThisIsTail";

    if (strcmp((char *)DListGetData(DListEnd(dlist)), tail_data ) == 0)
    {
        printf(GRN "SUCCESS with DListBegin!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListBegin!\n" RESET);
    }

    DListDestroy(dlist);
}

void TestDListInsert()
{
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = DListEnd(dlist);
    size_t num = 5;
    WrapperCompareIterators("DListInsert", num, DListInsert(dlist, iter, (void *)num));
    DListDestroy(dlist);

    dlist = DListCreate();
    iter = DListBegin(dlist);
    WrapperCompareIterators("DListInsert", num, DListInsert(dlist, iter, (void *)num));
    DListDestroy(dlist);

    dlist = DListCreate();
    CreateList(dlist, 6);
    num = 3;
    iter = DListFind(DListBegin(dlist), DListEnd(dlist), Compare, (void *)num);
    WrapperCompareIterators("DListInsert", num, DListInsert(dlist, iter, (void *)num));
    DListDestroy(dlist);
}
/*
static void WrapperInsert(char * func_name, dlist_t *dlist, dlist_iter_t iter, void *num)
{
    if (DListInsertAfter(dlist, iter, (void *)num) == DListEnd(dlist))
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!!!\n" RESET, func_name);
    }
}*/
/*
void TestDListInsertAfter()
{
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = DListEnd(dlist);
    size_t num = 5;


    if (DListInsertAfter(dlist, iter, (void *)num) == DListEnd(dlist))
    {
        printf(GRN "SUCCESS with DListInsertAfter!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListInsertAfter!!!\n" RESET);
    }


    iter = DListBegin(dlist);

    WrapperInsert("DListInsertAfter", dlist, iter, (void *)num);
    DListDestroy(dlist);

    dlist = DListCreate();
    CreateList(dlist, 6);
    num = 3;
    iter = DListFind(DListBegin(dlist), DListEnd(dlist), Compare, (void *)num);
    WrapperCompareIterators("DListInsertAfter", num, DListInsertAfter(dlist, iter, (void *)num));
    DListDestroy(dlist);
}*/

void TestDListRemove()
{
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter;
    size_t num = 3;

    CreateList(dlist, 5);

    iter = DListFind(DListBegin(dlist), DListEnd(dlist), Compare, (void *)num);
    iter = DListRemove(iter);

    if ((DListSize(dlist) == 4) && ((size_t)DListGetData(iter) == 4))
    {
        printf(GRN "SUCCESS with DListRemove!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListRemove!!!\n" RESET);
    }

    DListDestroy(dlist);
}
/*
void TestDListIsSameIter()
{
    dlist_t *dlist1 = DListCreate();
    dlist_t *dlist2 = DListCreate();
    dlist_iter_t iter1;
    dlist_iter_t iter2;
    size_t num1 = 3;
    size_t num2 = 3;

    CreateList(dlist1, 7);
    CreateList(dlist2, 4);

    iter1 = DListFind(DListBegin(dlist1), DListEnd(dlist1), Compare, (void *)num1);
    iter2 = DListFind(DListBegin(dlist2), DListEnd(dlist2), Compare, (void *)num2);

    if (DListIsSameIter(iter1, iter2) == 1)
    {
        printf(GRN "SUCCESS with DListIsSameIter!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListIsSameIter!!!\n" RESET);
    }

    num1 = 20;
    iter1 = DListFind(DListBegin(dlist1), DListEnd(dlist1), Compare, (void *)num1);

    if (DListIsSameIter(iter1, iter2) == 0)
    {
        printf(GRN "SUCCESS with DListIsSameIter!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DListIsSameIter!!!\n" RESET);
    }

    DListDestroy(dlist1);
    DListDestroy(dlist2);

}*/

void TestDListNext()
{
    dlist_t *dlist = DListCreate();
    size_t num = 2;
    CreateList(dlist, 5);

    /*printf("(size_t)DListGetData(DListNext(DListBegin(dlist)))=%lu\n", (size_t)DListGetData(DListNext(DListBegin(dlist))));*/
    WrapperCompareSizet("DListNext", (size_t)DListGetData(DListNext(DListBegin(dlist))), num);

    DListDestroy(dlist);

}

void TestDListPrev()
{
    dlist_t *dlist = DListCreate();
    size_t num = 5;
    CreateList(dlist, 5);

    /*printf("(size_t)DListGetData(DListNext(DListBegin(dlist)))=%lu\n", (size_t)DListGetData(DListNext(DListBegin(dlist))));*/
    WrapperCompareSizet("DListPrev", (size_t)DListGetData(DListPrev(DListEnd(dlist))), num);

    DListDestroy(dlist);
}
