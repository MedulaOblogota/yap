#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "bst.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define ARRAY_SIZE (15)

int cmp_func(const void *data1, const void* data2, void *param);

void TestBSTBeginAndEnd();
void TestBSTCountAndIsEmpty();
void TestBSTNextAndPrev();
void TestBSTInsertRemove();
void TestBSTFind();
void TestBSTForEach();

int main()
{
	TestBSTBeginAndEnd();
	TestBSTCountAndIsEmpty();
	TestBSTNextAndPrev();
	TestBSTInsertRemove();
	TestBSTFind();
	TestBSTForEach();
    return (0);

}

int cmp_func(const void *data1, const void* data2, void *param)
{
    (void)param;
    return (*(int *)data1 - *(int *)data2);
}

int cmp_func_using_param(const void *data1, const void* data2, void *param)
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
}

int add_value(void* data, void *value)
{
	*(int *)data += *(int *)value;
	return 1;
}

int NumExistInArray(int *arr, size_t size, int random_num)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (arr[i] == random_num)
        {
            return (1);
        }
    }

    return (0);
}
static void CreateRandomArray(int *arr, size_t arr_size, int modulus)
{
    size_t i = 0;
    int random_num = 0;

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        random_num = rand() % modulus;

        if (!NumExistInArray(arr, i, random_num))
        {
            arr[i] = (rand() % modulus);
        }
    }

    printf("array is:\n");
    for (i = 0; i < arr_size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void WrapperCompareBSTIter(char *func_name, bst_iter_t *iter1, bst_iter_t *iter2)
{
	if (BSTIsSameIter(iter1, iter2))
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperCompareInt(char *func_name, int exiting_value, int expected_value)
{
	if (exiting_value == expected_value)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperCompareSizet(char *func_name, size_t exiting_value, size_t expected_value)
{
	if (exiting_value == expected_value)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void WrapperComparetoNULL(char *func_name, void *data)
{
	if (NULL == data)
	{
		printf(GRN"Success with %s\n"RESET, func_name);
	}
	else
	{
		printf(RED"FAILURE with %s!!\n"RESET, func_name);
	}
}

void InsertItemsToBST(bst_t *bst, int *int_arr, bst_iter_t **iter_arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		iter_arr[i] = BSTInsert(bst, (void *)&int_arr[i]);
	}
}

void MoveToArray(bst_iter_t *min_node, int *arr)
{
	size_t i = 0;

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		arr[i] = *(int *)BSTGetData(min_node);
		min_node = BSTNext(min_node);
	}
}

/* works great only when its sorted from small to large with no param */
bst_iter_t *BSTFindMin(bst_t *bst)
{
    return (BSTBegin(bst));
}

void PrintBST(bst_t *bst)
{
    bst_iter_t *runner = BSTFindMin(bst);

    while (runner != BSTEnd(bst))
    {
        printf("%d -> ", *(int *)BSTGetData(runner));
        runner = BSTNext(runner);
    }
    printf("\n");
}

void TestBSTBeginAndEnd()
{
	bst_t *bst = BSTCreate(cmp_func, NULL);
	int num1 = 5;
    int num2 = 3;

	WrapperCompareBSTIter("BSTBegin and BSTEnd", BSTBegin(bst), BSTEnd(bst));

	BSTInsert(bst, (void *)&num1);
    BSTInsert(bst, (void *)&num2);

	WrapperCompareInt("BSTBegin", *(int *)BSTGetData(BSTBegin(bst)), num2);
	WrapperComparetoNULL("BSTEnd", BSTGetData(BSTEnd(bst)));

	BSTDestroy(bst);
}


void TestBSTCountAndIsEmpty()
{
	bst_t *bst = BSTCreate(cmp_func, NULL);
	int num1 = 5;
	int num2 = 6;
	int num3 = 7;

	bst_iter_t *iter1 = NULL;
	bst_iter_t *iter2 = NULL;
	bst_iter_t *iter3 = NULL;

	WrapperCompareInt("BSTIsEmpty", BSTIsEmpty(bst), 1);

	iter1 = BSTInsert(bst, (void *)&num1);
	WrapperCompareInt("BSTIsEmpty", BSTIsEmpty(bst), 0);

	WrapperCompareSizet("BSTCount", BSTCount(bst), 1);

	iter2 = BSTInsert(bst, (void *)&num2);
	iter3 = BSTInsert(bst, (void *)&num3);

	WrapperCompareSizet("BSTCount", BSTCount(bst), 3);


	BSTRemove(iter2);
	WrapperCompareSizet("BSTCount after remove", BSTCount(bst), 2);

	BSTRemove(iter3);
	WrapperCompareSizet("BSTCount after remove", BSTCount(bst), 1);

	BSTRemove(iter1);
	WrapperCompareSizet("BSTCount after remove", BSTCount(bst), 0);
	WrapperCompareInt("BSTIsEmpty after remove", BSTIsEmpty(bst), 1);

	BSTDestroy(bst);

}
void TestBSTNextAndPrev()
{
	bst_t *bst = BSTCreate(cmp_func, NULL);
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	bst_iter_t *iter_arr[ARRAY_SIZE];
	bst_iter_t *runner = BSTBegin(bst);
	int num = 0;
	size_t counter = 0;

	InsertItemsToBST(bst, int_arr, iter_arr, ARRAY_SIZE);
	runner = iter_arr[7];
	num = *(int *)BSTGetData(runner);
	runner = BSTNext(runner);

	while (runner != BSTEnd(bst))
	{
		if (*(int *)BSTGetData(runner) < num)
		{
			++counter;
		}

		num = *(int *)BSTGetData(runner);
		runner = BSTNext(runner);
	}

	WrapperCompareSizet("BSTNext", counter, 0);

	runner = iter_arr[ARRAY_SIZE - 1];
	num = *(int *)BSTGetData(runner);
	runner = BSTPrev(runner);
	counter = 0;

	while (runner != BSTEnd(bst))
	{
		if (*(int *)BSTGetData(runner) > num)
		{
			++counter;
		}

		num = *(int *)BSTGetData(runner);
		runner = BSTPrev(runner);
	}

	WrapperCompareSizet("BSTPrev", counter, 0);

	BSTDestroy(bst);
}

void TestBSTInsertRemove()
{
	bst_t *bst = BSTCreate(cmp_func, NULL);
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	bst_iter_t *iter_arr[ARRAY_SIZE];
	bst_iter_t *runner = BSTBegin(bst);
	int num = 0;
	size_t counter = 0;
	size_t i = 0;
	void *value = 0;
    int ttlcounter = 0;

	InsertItemsToBST(bst, int_arr, iter_arr, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		value = BSTRemove(iter_arr[i]);

		counter = 0;
		if (*(int *)value != int_arr[i])
		{
			++counter;
			printf(RED"FAILURE with comparing value after removal!!\n"RESET);
		}

		runner = BSTBegin(bst);
		counter = 0;
		if (NULL != BSTGetData(runner))
		{
			num = *(int *)BSTGetData(runner);
		}

		while (runner != BSTEnd(bst))
		{
		   if (*(int *)BSTGetData(runner) < num)
		   {
			   ++counter;
		   }

		   num = *(int *)BSTGetData(runner);
		   runner = BSTNext(runner);
		}

        if (counter != 0)
        {
            printf(RED"FAILURE with BSTNext after remove!\n");
            ++ttlcounter;
        }
	/*	WrapperCompareSizet("BSTNext after remove", counter, 0);*/

		counter = 0;
		if (i != ARRAY_SIZE - 1)
		{
			runner = iter_arr[ARRAY_SIZE - 1];
			if (NULL != BSTGetData(runner))
			{
				num = *(int *)BSTGetData(runner);
			}
			runner = BSTPrev(runner);
			counter = 0;

			while (runner != BSTEnd(bst))
			{
				if (*(int *)BSTGetData(runner) > num)
				{
					++counter;
				}

				num = *(int *)BSTGetData(runner);
				runner = BSTPrev(runner);
			}
            if (counter != 0)
            {
                printf(RED"FAILURE with BSTPrev after remove!\n");
                ++ttlcounter;
            }
			/*WrapperCompareSizet("BSTPrev after remove", counter, 0);*/
		}
		/*printf("BSTCount is %lu\n", BSTCount(bst));*/

        /*WrapperCompareSizet("BSTCount after remove", BSTCount(bst), ARRAY_SIZE - i - 1);*/
        if (BSTCount(bst) != ARRAY_SIZE - i - 1)
        {
            printf(RED"FAILURE with BSTCount after remove!\n");
            ++ttlcounter;
        }
	}

    WrapperCompareInt("BSTCount, BSTNext & BSTPrev after remove", ttlcounter, 0);

	BSTDestroy(bst);

}

/*TODO not working for god knows why with param. int_arr_param array changes after call to InsertItemsToBST function */
void TestBSTFind()
{
	int param = 2;
	int none_existing_value = 3214155;

	bst_t *bst = BSTCreate(cmp_func, NULL);
	bst_t *bst_using_param = BSTCreate(cmp_func_using_param, (void *)&param);
/*
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	int int_arr_param[ARRAY_SIZE] = {623, 521, 5325, 3512, 974, 6346, 53, 436, 6423, 6, 3112, 6743, 8631, 212, 5531};
*/
    int int_arr[ARRAY_SIZE] = {0};
    int int_arr_param[ARRAY_SIZE] = {0};


	bst_iter_t *iter_arr[ARRAY_SIZE];
	bst_iter_t *iter_arr_param[ARRAY_SIZE];

	size_t counter = 0;
	int i = 0;
	void *value = 0;

    CreateRandomArray(int_arr, ARRAY_SIZE, 100);
    CreateRandomArray(int_arr_param, ARRAY_SIZE, 100);

	InsertItemsToBST(bst, int_arr, iter_arr, ARRAY_SIZE);
	InsertItemsToBST(bst_using_param, int_arr_param, iter_arr_param, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		/*WrapperCompareInt("BSTFind without param", *(int *)BSTGetData(BSTFind(bst, (void *)&int_arr[i])), int_arr[i]);*/
        if (*(int *)BSTGetData(BSTFind(bst, (void *)&int_arr[i])) != int_arr[i])
        {
            ++counter;
        }
	}

    WrapperCompareSizet("BSTFind without param", counter, 0);

    counter = 0;
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
        if (*(int *)BSTGetData(BSTFind(bst_using_param, (void *)&int_arr_param[i])) != int_arr_param[i])
        {
            ++counter;
        }
	}

    WrapperCompareSizet("BSTFind with param", counter, 0);
    PrintBST(bst);
    PrintBST(bst_using_param);


	value = BSTGetData(BSTFind(bst, (void *)&none_existing_value));

	WrapperComparetoNULL("finding non-existant value in BST", value);

	BSTDestroy(bst);
	BSTDestroy(bst_using_param);
}

void TestBSTForEach()
{
	bst_t *bst = BSTCreate(cmp_func, NULL);
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	int dest_arr[ARRAY_SIZE] = {-6, -2, 0, 4, 5, 7, 8, 9, 10, 11, 14, 14, 29, 30, 99};
	int result_arr[ARRAY_SIZE] = {0};
	bst_iter_t *iter_arr[ARRAY_SIZE];
	bst_iter_t *from =NULL;
	bst_iter_t *to = NULL;
	int value = 2;
	size_t i = 0;

	InsertItemsToBST(bst, int_arr, iter_arr, ARRAY_SIZE);

	from = BSTFind(bst, (void *)&int_arr[2]);
	to = BSTFind(bst, (void *)&int_arr[10]);

	BSTForEach(from, to, add_value, (void *)&value);

	MoveToArray(iter_arr[7], result_arr);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		if (dest_arr[i] != result_arr[i])
		{
			break;
		}
	}

	WrapperCompareInt("BSTForEach", i, ARRAY_SIZE);

    BSTDestroy(bst);
}
