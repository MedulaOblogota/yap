#include <stdio.h>
#include <string.h>
#include "PriorityQueue.h"
#include "sorted_list.h"
/*#include "dlist.h"*/

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define TAIL_DATA ("ThisIsTail")

void TestPQCreate();
void TestPQPeek();
void TestPQDequeue();
void TestPQEnqueue();
void TestPQSize();
void TestPQIsEmpty();
void TestPQClear();
void TestPQErase();
void TestAll();

int main()
{
    TestPQCreate();
    TestPQPeek();
    TestPQDequeue();
    TestPQEnqueue();
    TestPQSize();
    TestPQIsEmpty();
    TestPQClear();
    TestPQErase();
    TestAll();
	return (0);
}

static void PrintQueue(pqueue_t *pqueue)
{
    while (PQSize(pqueue) != 0)
    {
        printf("%d, ", *(int *)PQDequeue(pqueue));
    }
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

int Comp(const void *data1, const void *data2, void *param)
{
    (void)param;
	return (*(int *)data1 - *(int *)data2);
}

int CompDividedByNum(const void *data1, const void *data2, void *param)
{

    if ((*(int *)data2 % *(int *)param) == 0)
    {
        if ((*(int *)data1 % *(int *)param) == 0)
        {
            return (*(int *)data1 - *(int *)data2);
        }
        else
        {
            return (1);
        }
    }
    else
    {
        if ((*(int *)data1 % *(int *)param) == 0)
        {
            return (-1);
        }
        else
        {
            return (*(int *)data1 - *(int *)data2);
        }
    }
    /*return (((*(int *)data2 % *(int *)param) == 0) && (*(int *)data1 - *(int *)data2));*/

}

void TestPQCreate()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);

    if (NULL != pqueue)
	{
		printf(GRN "SUCCESS with PQCreate!\n" RESET);
	}
	else
	{
		printf(RED "FAILURE with PQCreate!\n" RESET);
	}

	PQDestroy(pqueue);
}

void TestPQPeek()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    /*if (0 == strcmp((char *)PQPeek(pqueue), TAIL_DATA))
    {
        printf(GRN "SUCCESS with PQPeek!\n" RESET);
	}
	else
	{
		printf(RED "FAILURE with PQPeek!\n" RESET);
	}*/

    PQEnqueue(pqueue, (void *)&num1);
    PQEnqueue(pqueue, (void *)&num2);
    PQEnqueue(pqueue, (void *)&num3);

    WrapperCompareInt("PQPeek", *(int *)PQPeek(pqueue), num3);

    PQDestroy(pqueue);
}

void TestPQDequeue()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    PQEnqueue(pqueue, (void *)&num1);
    PQEnqueue(pqueue, (void *)&num2);
    PQEnqueue(pqueue, (void *)&num3);

    WrapperCompareInt("PQDequeue", *(int *)PQDequeue(pqueue), num3);
    WrapperCompareInt("PQDequeue", *(int *)PQDequeue(pqueue), num1);
    WrapperCompareInt("PQDequeue", *(int *)PQDequeue(pqueue), num2);

/*    PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);*/

    PQDestroy(pqueue);
}

void TestPQEnqueue()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);

    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    WrapperCompareInt("PQEnqueue", PQEnqueue(pqueue, (void *)&num1), 1);
    WrapperCompareInt("PQEnqueue", PQEnqueue(pqueue, (void *)&num2), 1);
    WrapperCompareInt("PQEnqueue", PQEnqueue(pqueue, (void *)&num3), 1);


    PQDestroy(pqueue);
}

void TestPQSize()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    WrapperCompareInt("PQSize", PQSize(pqueue), 0);

    PQEnqueue(pqueue, (void *)&num1);
    WrapperCompareInt("PQSize", PQSize(pqueue), 1);

    PQEnqueue(pqueue, (void *)&num2);
    WrapperCompareInt("PQSize", PQSize(pqueue), 2);

    PQEnqueue(pqueue, (void *)&num3);
    WrapperCompareInt("PQSize", PQSize(pqueue), 3);

    PQDestroy(pqueue);

}
void TestPQIsEmpty()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 1);

    PQEnqueue(pqueue, (void *)&num1);
    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 0);

    PQEnqueue(pqueue, (void *)&num2);
    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 0);

    PQEnqueue(pqueue, (void *)&num3);
    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 0);

    PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);
    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 1);

    /*PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);
    PQDequeue(pqueue);
    WrapperCompareInt("PQIsEmpty", PQIsEmpty(pqueue), 1);*/


    PQDestroy(pqueue);
}

void TestPQClear()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;

    PQEnqueue(pqueue, (void *)&num1);
    PQEnqueue(pqueue, (void *)&num2);
    PQEnqueue(pqueue, (void *)&num3);

    PQClear(pqueue);

    if ((0 == PQSize(pqueue)))
    {
        printf(GRN "SUCCESS with PQClear!\n" RESET);
	}
	else
	{
		printf(RED "FAILURE with PQClear!\n" RESET);
	}

    PQDestroy(pqueue);
}

int IsMatch(const void *data, const void *param)
{
    return (*(int *)data == *(int *)param);
}

void TestPQErase()
{
    pqueue_t *pqueue = PQCreate(Comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 2;
    int counter = 0;

    PQEnqueue(pqueue, (void *)&num1);
    PQEnqueue(pqueue, (void *)&num2);
    PQEnqueue(pqueue, (void *)&num3);

    PQErase(pqueue, IsMatch, (void *)&num1);


    while (0 != PQSize(pqueue))
    {
            ++counter;
            if (5 == *(int *)PQDequeue(pqueue))
            {
                counter = -1;
                break;
            }
    }

    if (2 == counter)
    {
        printf(GRN "SUCCESS with PQErase!\n" RESET);
	}
	else
	{
		printf(RED "FAILURE with PQErase!\n" RESET);
	}

    PQDestroy(pqueue);
}

void TestAll()
{
        int num1 = 1;
        int num2 = 6;
        int num3 = 2;
        int num4 = 0;
        int num5 = 3;
        int num = 2;
        pqueue_t *pqueue = PQCreate(CompDividedByNum, (void *)&num);

        PQEnqueue(pqueue, (void *)&num1);
        PQEnqueue(pqueue, (void *)&num2);
        PQEnqueue(pqueue, (void *)&num3);
        PQEnqueue(pqueue, (void *)&num4);
        PQEnqueue(pqueue, (void *)&num5);

        if (*(int *)PQPeek(pqueue) == num4)
        {
            printf(GRN "SUCCESS with Testing Several Things!\n" RESET);
    	}
    	else
    	{
    		printf(RED "FAILURE with Testing Several Things!\n" RESET);
    	}

        PrintQueue(pqueue);
        PQDestroy(pqueue);
}
