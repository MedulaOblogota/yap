#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "avl.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define ARRAY_SIZE (15)
#define BIG_ARRAY_SIZE (5)

int cmp_func(const void *data1, const void* data2, void *param);

/*void TestAVLBeginAndEnd();*/
void TestAVLCountAndIsEmpty();
/*void TestAVLNextAndPrev();*/
void TestAVLInsertRemove();
void TestAVLFind();
void TestAVLForEach();

int main()
{
	/*TestBSTBeginAndEnd();*/
	TestAVLCountAndIsEmpty();
	/*TestBSTNextAndPrev();*/
	TestAVLInsertRemove();
	TestAVLFind();
	TestAVLForEach();
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

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        arr[i] = i;
        /*random_num = rand() % modulus;

        if (!NumExistInArray(arr, i, random_num))
        {
            arr[i] = (rand() % modulus);
        }*/
    }

/*    printf("array is:\n");
    for (i = 0; i < arr_size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");*/
}

/*
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
*/
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

void InsertItemsToAVL(avl_t *avl, int *int_arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &int_arr[i]);
	}
}

/*
void MoveToArray(bst_iter_t *min_node, int *arr)
{
	size_t i = 0;

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		arr[i] = *(int *)BSTGetData(min_node);
		min_node = BSTNext(min_node);
	}
}
*/

/* works great only when its sorted from small to large with no param */
/*
bst_iter_t *BSTFindMin(bst_t *bst)
{
    return (BSTBegin(bst));
}
*/
/*
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
*/
/*
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

*/
void TestAVLCountAndIsEmpty()
{
	avl_t *avl = AVLCreate(cmp_func, NULL);
	int num1 = 55;
	int num2 = 26;
	int num3 = 23;

	WrapperCompareInt("AVLIsEmpty", AVLIsEmpty(avl), 1);

	AVLInsert(avl, &num1);
	WrapperCompareInt("AVLIsEmpty", AVLIsEmpty(avl), 0);

	WrapperCompareSizet("AVLCount", AVLCount(avl), 1);

	AVLInsert(avl, (void *)&num2);
	AVLInsert(avl, (void *)&num3);

	WrapperCompareSizet("AVLCount", AVLCount(avl), 3);


	AVLRemove(avl, &num2);
	WrapperCompareSizet("AVLCount after remove", AVLCount(avl), 2);

	AVLRemove(avl, &num3);
	WrapperCompareSizet("AVLCount after remove", AVLCount(avl), 1);

	AVLRemove(avl, &num1);
	WrapperCompareSizet("AVLCount after remove", AVLCount(avl), 0);
	WrapperCompareInt("AVLIsEmpty after remove", AVLIsEmpty(avl), 1);

	AVLDestroy(avl);

}
/*
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
*/

void TestAVLInsertRemove()
{
	avl_t *avl = AVLCreate(cmp_func, NULL);
	avl_t *big_avl = AVLCreate(cmp_func, NULL);
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	int big_int_arr[BIG_ARRAY_SIZE] = {0};
	size_t counter = 0;
	size_t i = 0;
	void *value = 0;

    clock_t beginning = clock();

    CreateRandomArray(big_int_arr, BIG_ARRAY_SIZE, 2000000);
    beginning = clock();
	InsertItemsToAVL(big_avl, big_int_arr, BIG_ARRAY_SIZE);
	printf("time difference for Inserting Items to big_avl with %d items is %f\n", BIG_ARRAY_SIZE, (double)(clock() - beginning)/CLOCKS_PER_SEC);
	InsertItemsToAVL(avl, int_arr, ARRAY_SIZE);

	printf("Height of %d items is %ld\n", BIG_ARRAY_SIZE, AVLHeight(big_avl));
	printf("Height of %d items is %ld\n", ARRAY_SIZE, AVLHeight(avl));

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		value = AVLRemove(avl, &int_arr[i]);

		counter = 0;
		if (*(int *)value != int_arr[i])
		{
			++counter;
			printf(RED"FAILURE with comparing value after removal!!\n"RESET);
		}
	}

	counter = 0;
	beginning = clock();

	for (i = 0; i < BIG_ARRAY_SIZE; ++i)
	{
		value = AVLRemove(big_avl, &big_int_arr[i]);

		if (*(int *)value != big_int_arr[i])
		{
			++counter;

		}
	}
	printf("time difference for Removing Items from big_avl with %d items is %f\n", BIG_ARRAY_SIZE, (double)(clock() - beginning)/CLOCKS_PER_SEC);

	WrapperCompareSizet("BigAVL Remove", counter, 0);

    AVLDestroy(avl);
    AVLDestroy(big_avl);
/*    avl = AVLCreate(cmp_func, NULL);

    InsertItemsToAVL(avl, int_arr, ARRAY_SIZE);
    num = 1290;

    if (AVLRemove(avl, &num) == NULL)
    {
        printf(GRN"success with trying to remove a value that isnt there!\n"RESET);
    }
    else
    {
        printf(RED"failure with trying to remove a value that isnt there!\n"RESET);
    }


    AVLDestroy(avl);*/
}

/*TODO not working for god knows why with param. int_arr_param array changes after call to InsertItemsToBST function */
void TestAVLFind()
{
	int none_existing_value = 3214155;

	avl_t *avl = AVLCreate(cmp_func, NULL);
	avl_t *big_avl = AVLCreate(cmp_func, NULL);
/*
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	int int_arr_param[ARRAY_SIZE] = {623, 521, 5325, 3512, 974, 6346, 53, 436, 6423, 6, 3112, 6743, 8631, 212, 5531};
*/
    int int_arr[ARRAY_SIZE] = {0};
    int big_int_arr[BIG_ARRAY_SIZE] = {0};


	/*bst_iter_t *iter_arr[ARRAY_SIZE];
	bst_iter_t *iter_arr_param[ARRAY_SIZE];
*/
	size_t counter = 0;
	int i = 0;
	void *value = 0;
	clock_t beginning = clock();


    CreateRandomArray(int_arr, ARRAY_SIZE, 100);
    CreateRandomArray(big_int_arr, BIG_ARRAY_SIZE, 2000000);


	InsertItemsToAVL(avl, int_arr, ARRAY_SIZE);
	InsertItemsToAVL(big_avl, big_int_arr, BIG_ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		/*WrapperCompareInt("BSTFind without param", *(int *)BSTGetData(BSTFind(bst, (void *)&int_arr[i])), int_arr[i]);*/
        if (*(int *)AVLFind(avl, (void *)&int_arr[i]) != int_arr[i])
        {
            ++counter;
        }
	}

    WrapperCompareSizet("AVLFind without param", counter, 0);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		value = AVLRemove(avl, &int_arr[i]);

		counter = 0;
		if (*(int *)value != int_arr[i])
		{
			++counter;
			/*printf(RED"FAILURE with comparing value after removal!!\n"RESET);*/
		}
	}

	WrapperCompareSizet("AVLRemove for consecutive numbered avl", counter, 0);

    counter = 0;
    beginning = clock();
	for (i = 0; i < BIG_ARRAY_SIZE; ++i)
	{
        if (*(int *)AVLFind(big_avl, (void *)&big_int_arr[i]) != big_int_arr[i])
        {
            ++counter;
        }
	}
printf("time difference for Finding all Items from big_avl with %d items is %f\n", BIG_ARRAY_SIZE, (double)(clock() - beginning)/CLOCKS_PER_SEC);
    WrapperCompareSizet("BigAVL Find", counter, 0);

    /*PrintBST(bst);
    PrintBST(bst_using_param);*/


	value = AVLFind(avl, (void *)&none_existing_value);

	WrapperComparetoNULL("finding non-existant value in AVL", value);

    printf("avl size is %lu\n", AVLCount(avl));
/*    printf("avl_with_param size is %lu\n", AVLCount(avl_using_param));*/

	/*BSTDestroy(bst);
	BSTDestroy(bst_using_param);*/
    AVLDestroy(avl);
    AVLDestroy(big_avl);
}


void TestAVLForEach()
{
	avl_t *avl = AVLCreate(cmp_func, NULL);
	int int_arr[ARRAY_SIZE] = {7, 3, 2, 9, 12, 5, -2, -6, 30, 29, 14, 8, 0, 6, 99};
	int dest_arr[ARRAY_SIZE] = {9, 5, 4, 11, 14, 7, 0, -4, 32, 31, 16, 10, 2, 8, 101};
	int value = 2;
	size_t i = 0;

	InsertItemsToAVL(avl, int_arr, ARRAY_SIZE);

	AVLForEach(avl, add_value, &value);

	/*MoveToArray(iter_arr[7], result_arr);*/

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		if (dest_arr[i] != *(int *)AVLFind(avl, &dest_arr[i]))
		{
			break;
		}
	}

	WrapperCompareInt("AVLForEach", i, ARRAY_SIZE);

    AVLDestroy(avl);
}
