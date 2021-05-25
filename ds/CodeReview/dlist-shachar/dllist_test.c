#include <stdio.h>
#include <string.h>

#include "dlist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestDlistCreate();
void TestDlistCount();
void TestDlistIsEmpty();
void TestDlistPushFront();
void TestDlistPushBack();
void TestDlistPopFront();
void TestDlistPopBack();
void TestDlistForEach();
void TestDlistFind();
void TestDlistSplice();
void TestDlistGetData();
void TestDlistBegin();
void TestDlistEnd();
void TestDlistInsertBefore();
void TestDlistInsertAfter();
void TestDlistErase();
void TestDlistIsSame();
void TestDlistGetNext();
void TestDlistGetPrev();


int main()
{
    TestDlistCreate();
    TestDlistCount();
    TestDlistIsEmpty();
    TestDlistPushFront();
    TestDlistPushBack();
    TestDlistPopFront();
    TestDlistForEach();
    TestDlistFind();
    TestDlistSplice();
    TestDlistGetData();
    TestDlistBegin();
    TestDlistEnd();
    TestDlistInsertBefore();
    TestDlistInsertAfter();
    TestDlistErase();
    TestDlistIsSame();
    TestDlistGetNext();
    TestDlistGetPrev();

    return (0);
}

static void CreateList(dlist_t *dlist, size_t size)
{
		size_t item = 1;

		for (item = 1; item <= size; ++item)
		{
			DlistPushBack(dlist, (void *)item);
		}
}



static void WrapperCompareIterators(char *func_name, size_t searched_item, dlist_iter_t iter)
{
		size_t extracted_value = (size_t)DlistGetData(iter);

		if (extracted_value == searched_item)
		{
			printf(GRN "SUCCESS with %s!\n" RESET, func_name);
		}
		else
		{
			printf(RED "FAILURE with %s!!!\n" RESET, func_name);
		}
}

void TestDlistCreate()
{
    dlist_t *dlist = DlistCreate();

    if (NULL != dlist)
    {
        printf(GRN "SUCCESS with DlistCreate!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistCreate!\n" RESET);
    }

    DlistDestroy(dlist);
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

void TestDlistCount()
{
    dlist_t *dlist = DlistCreate();

    WrapperCompareSizet("DlistCount", DlistCount(dlist), 0);

    DlistDestroy(dlist);
}

void TestDlistIsEmpty()
{
    dlist_t *dlist = DlistCreate();
	size_t num = 7;

    WrapperCompareSizet("DlistIsEmpty", DlistIsEmpty(dlist), 1);

	DlistPushFront(dlist, (void *)num);
	WrapperCompareSizet("DlistIsEmpty", DlistIsEmpty(dlist), 0);

	DlistPopBack(dlist);
	WrapperCompareSizet("DlistIsEmpty", DlistIsEmpty(dlist), 1);

    DlistDestroy(dlist);
}

void TestDlistPushFront()
{
    dlist_t *dlist = DlistCreate();
    dlist_iter_t iter = NULL;
    size_t num = 5;

    iter = DlistPushFront(dlist, (void *)num);

    WrapperCompareSizet("DlistPushFront", DlistCount(dlist), 1);
    WrapperCompareIterators("DlistPushFront", num, iter);

    DlistDestroy(dlist);
}

void TestDlistPushBack()
{
    dlist_t *dlist = DlistCreate();
    dlist_iter_t pushed = NULL;
    size_t num = 5;

    pushed = DlistPushBack(dlist, (void *)num);

    WrapperCompareSizet("TestDlistPushBack", DlistCount(dlist), 1);
    WrapperCompareIterators("TestDlistPushBack", num, pushed);
    /*printf("data in item is %lu\n", (size_t)DlistGetData(pushed));*/

    DlistPopFront(dlist);
    WrapperCompareSizet("DlistPopFront", DlistCount(dlist), 0);
    DlistPopFront(dlist);
    DlistPopFront(dlist);
    WrapperCompareSizet("DlistPopFront", DlistCount(dlist), 0);

    DlistDestroy(dlist);
}

void TestDlistPopFront()
{
	dlist_t *dlist = DlistCreate();
	dlist_iter_t pushed = NULL;
	size_t num = 5;

	pushed = DlistPushFront(dlist, (void *)num);

	++num;
	DlistPushBack(dlist, (void *)num);

	num = 4;
	DlistPushFront(dlist, (void *)num);

	DlistPopFront(dlist);
	DlistPopBack(dlist);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)DlistGetData(pushed), 5);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)DlistCount(dlist), 1);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", DlistIsEmpty(dlist), 0);

	DlistPopFront(dlist);
	DlistPopBack(dlist);

	DlistPopFront(dlist);
	DlistPopBack(dlist);

	WrapperCompareSizet("DlistPopFront and DlistPopBack", (size_t)DlistCount(dlist), 0);
	WrapperCompareSizet("DlistPopFront and DlistPopBack", DlistIsEmpty(dlist), 1);

	DlistDestroy(dlist);
}

static status_t PrintItems(dlist_iter_t iter, void *arg)
{
    (void)arg;
	printf("%lu, ", (size_t)DlistGetData(iter));

	return CONTINUE;
}

static status_t PrintIntItems(dlist_iter_t iter, void *arg)
{
    (void)arg;
	printf("%d, ", *(int *)DlistGetData(iter));

	return CONTINUE;
}

static status_t AddArgToItems(dlist_iter_t iter, void *arg)
{

	*(int *)DlistGetData(iter) += *(int *)arg;


	return CONTINUE;
}

static status_t Compare(void *first, void *second)
{
	if ((size_t)first == (size_t)second)
	{
		return STOP;
	}
	else
	{
		return CONTINUE;
	}
}

void TestDlistForEach()
{
	dlist_t *dlist = DlistCreate();
	int num = 3;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;

    int original_num = 1;

    DlistPushFront(dlist, &num4);
    DlistPushFront(dlist, &num3);
    DlistPushFront(dlist, &num2);
    DlistPushFront(dlist, &num1);

	begin = DlistBegin(dlist);
	end = DlistEnd(dlist);
/*
    printf("before addition:\n");
	DlistForEach(begin, end, PrintIntItems, (void *)&num);*/
    end = DlistFind(begin, DlistEnd(dlist), Compare, (void *)&num3);
    DlistForEach(begin, end, AddArgToItems, (void *)&num);

    end = DlistEnd(dlist);

    WrapperCompareSizet("DlistForEach", original_num + num, *(int *)DlistGetData(begin));
/*    printf("after addition:\n");
    DlistForEach(begin, end, PrintIntItems, (void *)&num);*/
    DlistDestroy(dlist);

}


/*
static void WrapperCompareTwoIterators(char *func_name, dlist_iter_t iter1, dlist_iter_t iter2)
{
		char *extracted_value1 = (char *)DlistGetData(iter1);
        char *extracted_value2 = (char *)DlistGetData(iter2);

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
void TestDlistFind()
{
	dlist_t *dlist = DlistCreate();
	size_t amount_of_items = 6;
	size_t searched_item = 4;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;
    char *tail_data = "ThisIsTail";
    char checked[20];

	CreateList(dlist, amount_of_items);
	begin = DlistBegin(dlist);
	end = DlistEnd(dlist);

	WrapperCompareIterators("DlistFind", searched_item, DlistFind(begin, end, Compare, (void *)searched_item));

    begin = DlistBegin(dlist);
	end = DlistEnd(dlist);
	searched_item = 20;
/*    printf("%s\n", DlistFind(begin, end, Compare, (void *)searched_item));*/
    /*strcpy(checked,DlistFind(begin, end, Compare, (void *)searched_item));*/
    if ( (size_t)DlistGetData(DlistFind(begin, end, Compare, (void *)searched_item)) == 0xDEADBEEF)
    {
        printf(GRN "SUCCESS with DlistFind!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistFind!!!\n" RESET);
    }
	/*WrapperCompareIterators("DlistFind", amount_of_items, DlistFind(begin, end, Compare, (void *)searched_item));*/

    DlistDestroy(dlist);
}

static void WrapperDlistSplice(size_t items_dest_list, size_t items_src_list, size_t from, size_t to, size_t where)
{
    dlist_t *dest = DlistCreate();
    dlist_t *src = DlistCreate();

    dlist_iter_t from_node;
	dlist_iter_t to_node;
	dlist_iter_t where_node;

    size_t items_to_move = to - from + 1;
    CreateList(dest, items_dest_list);
    CreateList(src, items_src_list);

    from_node = DlistFind(DlistBegin(src), DlistEnd(src), Compare, (void *)from);
	to_node = DlistFind(DlistBegin(src), DlistEnd(src), Compare, (void *)to);
	where_node = DlistFind(DlistBegin(dest), DlistEnd(dest), Compare, (void *)where);

    DlistSplice(from_node, to_node, where_node);

    WrapperCompareSizet("DlistSplice", items_to_move + items_dest_list, DlistCount(dest));
    WrapperCompareSizet("DlistSplice", items_src_list - items_to_move, DlistCount(src));

    DlistDestroy(dest);
    DlistDestroy(src);
}

void TestDlistSplice()
{

	WrapperDlistSplice(8, 6, 2, 4, 3);

    WrapperDlistSplice(1, 1, 1, 1, 1);

    WrapperDlistSplice(1, 2, 1, 2, 1);

}


void TestDlistGetData()
{
	dlist_t *dlist = DlistCreate();
	dlist_iter_t iter = DlistBegin(dlist);
    size_t num1 = 3;
    size_t num2 = 7;
    size_t num3 = 29;
    char *tail_data = "ThisIsTail";

	if ((size_t)DlistGetData(iter) != 0xDEADBEEF)
    {
        printf(RED "FAILURE with DlistGetData!!!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with DlistGetData!!\n" RESET);
    }

    DlistPushBack(dlist, (void *)num1);
    iter = DlistPushBack(dlist, (void *)num2);
    DlistPushBack(dlist, (void *)num3);

    if (7 != (size_t)DlistGetData(iter))
    {
        printf(RED "FAILURE with DlistGetData!!!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with DlistGetData!!\n" RESET);
    }

    DlistDestroy(dlist);
}

/* returns head if empty list */
void TestDlistBegin()
{
    dlist_t *dlist = DlistCreate();
    char *tail_data = "ThisIsTail";

    if ((size_t)DlistGetData(DlistBegin(dlist)) == 0xDEADBEEF)
    {
        printf(GRN "SUCCESS with DlistBegin!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistBegin!\n" RESET);
    }

    DlistDestroy(dlist);
}

/* returns tail if empty list */
void TestDlistEnd()
{
    dlist_t *dlist = DlistCreate();
    char *tail_data = "ThisIsTail";

    if ((size_t)DlistGetData(DlistEnd(dlist)) == 0xDEADBEEF)
    {
        printf(GRN "SUCCESS with DlistEnd!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistEnd!\n" RESET);
    }

    DlistDestroy(dlist);
}

void TestDlistInsertBefore()
{
    dlist_t *dlist = DlistCreate();
    dlist_iter_t iter = DlistEnd(dlist);
    size_t num = 5;
    WrapperCompareIterators("DlistInsertBefore", num, DlistInsertBefore(dlist, iter, (void *)num));
    DlistDestroy(dlist);

    dlist = DlistCreate();
    iter = DlistBegin(dlist);
    WrapperCompareIterators("DlistInsertBefore", num, DlistInsertBefore(dlist, iter, (void *)num));
    DlistDestroy(dlist);

    dlist = DlistCreate();
    CreateList(dlist, 6);
    num = 3;
    iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), Compare, (void *)num);
    WrapperCompareIterators("DlistInsertBefore", num, DlistInsertBefore(dlist, iter, (void *)num));
    DlistDestroy(dlist);
}

static void WrapperInsert(char * func_name, dlist_t *dlist, dlist_iter_t iter, void *num)
{
    if (DlistInsertAfter(dlist, iter, (void *)num) == DlistEnd(dlist))
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!!!\n" RESET, func_name);
    }
}
void TestDlistInsertAfter()
{
    dlist_t *dlist = DlistCreate();
    dlist_iter_t iter = DlistEnd(dlist);
    size_t num = 5;

    /*WrapperInsert("DlistInsertAfter", dlist, iter, (void *)num);*/
    /*if (DlistInsertAfter(dlist, iter, (void *)num) == DlistEnd(dlist))
    {
        printf(GRN "SUCCESS with DlistInsertAfter!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistInsertAfter!!!\n" RESET);
    }*/

    /*DlistDestroy(dlist);

    dlist = DlistCreate();*/
/*    iter = DlistBegin(dlist);

    WrapperInsert("DlistInsertAfter", dlist, iter, (void *)num);
    DlistDestroy(dlist);

    dlist = DlistCreate();*/
    CreateList(dlist, 6);
    num = 3;
    iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), Compare, (void *)num);
    WrapperCompareIterators("DlistInsertAfter", num, DlistInsertAfter(dlist, iter, (void *)num));
    DlistDestroy(dlist);
}

void TestDlistErase()
{
    dlist_t *dlist = DlistCreate();
    dlist_iter_t iter;
    size_t num = 3;

    CreateList(dlist, 5);

    iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), Compare, (void *)num);
    iter = DlistErase(iter);

    if ((DlistCount(dlist) == 4) && ((size_t)DlistGetData(iter) == 4))
    {
        printf(GRN "SUCCESS with DlistErase!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistErase!!!\n" RESET);
    }

    DlistDestroy(dlist);
}

void TestDlistIsSame()
{
    dlist_t *dlist1 = DlistCreate();
    dlist_t *dlist2 = DlistCreate();
    dlist_iter_t iter1;
    dlist_iter_t iter2;
    size_t num1 = 3;
    size_t num2 = 3;

    CreateList(dlist1, 7);
    CreateList(dlist2, 4);

    iter1 = DlistFind(DlistBegin(dlist1), DlistEnd(dlist1), Compare, (void *)num1);
    iter2 = DlistFind(DlistBegin(dlist2), DlistEnd(dlist2), Compare, (void *)num2);

    if (DlistIsSame(iter1, iter2) == 1)
    {
        printf(GRN "SUCCESS with DlistIsSame!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistIsSame!!!\n" RESET);
    }

    num1 = 20;
    iter1 = DlistFind(DlistBegin(dlist1), DlistEnd(dlist1), Compare, (void *)num1);

    if (DlistIsSame(iter1, iter2) == 0)
    {
        printf(GRN "SUCCESS with DlistIsSame!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with DlistIsSame!!!\n" RESET);
    }

    DlistDestroy(dlist1);
    DlistDestroy(dlist2);

}

void TestDlistGetNext()
{
    dlist_t *dlist = DlistCreate();
    size_t num = 2;
    CreateList(dlist, 5);

    /*printf("(size_t)DlistGetData(DlistGetNext(DlistBegin(dlist)))=%lu\n", (size_t)DlistGetData(DlistGetNext(DlistBegin(dlist))));*/
    WrapperCompareSizet("DlistGetNext", (size_t)DlistGetData(DlistGetNext(DlistBegin(dlist))), num);

    DlistDestroy(dlist);

}

void TestDlistGetPrev()
{
    dlist_t *dlist = DlistCreate();
    size_t num = 5;
    CreateList(dlist, 5);

    /*printf("(size_t)DlistGetData(DlistGetNext(DlistBegin(dlist)))=%lu\n", (size_t)DlistGetData(DlistGetNext(DlistBegin(dlist))));*/
    WrapperCompareSizet("DlistGetPrev", (size_t)DlistGetData(DlistGetPrev(DlistEnd(dlist))), num);

    DlistDestroy(dlist);
}
