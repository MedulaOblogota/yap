#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include "TEST_REPORT.h"

#include "sorting.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define USE89(x) (void)x
#define WORDSIZE sizeof(size_t)

/* tests */
REPORT *test_BubbleSort_Result		(REPORT *rprt);
REPORT *test_InsertionSort_Result	(REPORT *rprt);
REPORT *test_SelectionSort_Result	(REPORT *rprt);
REPORT *test_CountingSort_Result	(REPORT *rprt);
REPORT *test_RadixSort_Result		(REPORT *rprt);

REPORT *test_BubbleSort_Benchmarks	(REPORT *rprt);
REPORT *test_InsertionSort_Benchmarks	(REPORT *rprt);
REPORT *test_SelectionSort_Benchmarks	(REPORT *rprt);
REPORT *test_CountingSort_Benchmarks	(REPORT *rprt);
REPORT *test_RadixSort_Benchmarks	(REPORT *rprt);

/* service funcs*/
static void InitRandomIntArr(int *arr, size_t size);
static int IsEqualIntArrays(int *arr1, int *arr2, size_t size);
static int IsSortedIntArr(int *arr1, size_t size);
static void PrintIntArr(int *arr, size_t size);
static void CopyIntArr(int *dest, int *src, size_t size);

int CompareInts(const void *data1,const void *data2); /* Compare function for qsort */

size_t ReturnNum(const void* num, const void *minimum_val); /* find_f for counting sort*/


/* Test runway */
int main()
{
	/* Report Init*/
	REPORT strings_report;
	REPORT * rprt= ReportStart(&strings_report, " TEST report for SORT (VERSION 050819) functions\n");

	#ifndef NDEBUG
	printf(KRED"\n\n####################      DEBUG MODE ON   ###################### \n\n"KNRM);
	#endif

	if(NULL == rprt)
	{
		printf("Memory could not be allocated for the report.\nExiting\n");
		return 1;
	}

	/* Report runway*/
	printf(KRED"~~~~ IN-TEST PROMPTS ~~~~\n");
#if 0
#endif
	rprt = test_BubbleSort_Result		(rprt);
	rprt = test_InsertionSort_Result	(rprt);
	rprt = test_SelectionSort_Result	(rprt);
	rprt = test_CountingSort_Result		(rprt);
	rprt = test_RadixSort_Result		(rprt);

	rprt = test_BubbleSort_Benchmarks	(rprt);
	rprt = test_InsertionSort_Benchmarks	(rprt);
	rprt = test_SelectionSort_Benchmarks	(rprt);
	rprt = test_CountingSort_Benchmarks	(rprt);
	rprt = test_RadixSort_Benchmarks	(rprt);
#if 0
#endif

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"KNRM);

	/* Report Output*/
	ReportPrint(rprt);

	/* Report Process end*/
	ReportClose(rprt);

	return 0;
}
REPORT *test_BubbleSort_Result		(REPORT *rprt)
{
	int arr_source_1[]   = {9};
	int arr_expected_1[] = {9};
	size_t size_arr_1 = sizeof(arr_source_1)/sizeof(arr_source_1[0]);

	int arr_source_2[]   = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	int arr_expected_2[] = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	size_t size_arr_2 = sizeof(arr_source_2)/sizeof(arr_source_2[0]);

	int arr_source_3[]   = {10000, 8000, 600, 5, -20, -1000};
	int arr_expected_3[] = {-1000, -20, 5, 600, 8000, 10000};
	size_t size_arr_3 = sizeof(arr_source_3)/sizeof(arr_source_3[0]);

	int arr_source_4[]   = {9, 3, 65, 7, 2, 15, 8, 71, 5};
	int arr_expected_4[] = {2, 3, 5, 7, 8, 9, 15, 65, 71};
	size_t size_arr_4 = sizeof(arr_source_4)/sizeof(arr_source_4[0]);

	int *arr_source_5 = NULL;
	size_t size_arr_5 = 5000;

	int boolean_1 = 0;
	int boolean_2 = 0;
	int boolean_3 = 0;
	int boolean_4 = 0;
	int boolean_5 = 0;

	printf(">>>>>>"KNRM"test_BubbleSort_Result\n"KRED);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1 ITEM SORT */
	printf(">>>>>>>>>>>>>>> 1 item sort\n");
	BubbleSort(arr_source_1, size_arr_1);
	boolean_1 = IsEqualIntArrays(arr_source_1, arr_expected_1, size_arr_1);
	PrintIntArr(arr_source_1, size_arr_1);
	PrintIntArr(arr_expected_1, size_arr_1);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASCENDING SORT */
	printf(">>>>>>>>>>>>>>> Ascending sort\n");
	BubbleSort(arr_source_2, size_arr_2);
	boolean_2 = IsEqualIntArrays(arr_source_2, arr_expected_2, size_arr_2);
	PrintIntArr(arr_source_2, size_arr_2);
	PrintIntArr(arr_expected_2, size_arr_2);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESCENDING SORT */
	printf(">>>>>>>>>>>>>>> Descending sort\n");
	BubbleSort(arr_source_3, size_arr_3);
	boolean_3 = IsEqualIntArrays(arr_source_3, arr_expected_3, size_arr_3);
	PrintIntArr(arr_source_3, size_arr_3);
	PrintIntArr(arr_expected_3, size_arr_3);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Random sort\n");
	BubbleSort(arr_source_4, size_arr_4);
	boolean_4 = IsEqualIntArrays(arr_source_4, arr_expected_4, size_arr_4);
	PrintIntArr(arr_source_4, size_arr_4);
	PrintIntArr(arr_expected_4, size_arr_4);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Big random sort\n");
	arr_source_5   = (int *)malloc(size_arr_5 * sizeof(int));
	srand(time(0));
	InitRandomIntArr(arr_source_5, size_arr_5);

	printf("Bubble Sorting 5k\n");
	BubbleSort(arr_source_5, size_arr_5);
	boolean_5 = IsSortedIntArr(arr_source_5, size_arr_5);
	free(arr_source_5);
/*>>> TEST REPORT OUT */

	if(!boolean_1) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of 1 item after bubble sort] with [expected result array] return == false"
	"C A N T  A P P E A R  I N  R E P O R T ",
	"test_BubbleSort_Result",
	"BubbleSort [static: IsEqualIntArrays");

	if(!boolean_2) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N itemss, ascending order, after bubble sort] with [expected result array] return == false",
	"test_BubbleSort_Result",
	"BubbleSort [static: IsEqualIntArrays");

	if(!boolean_3) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, descending order, after bubble sort] with [expected result array] return == false",
	"test_BubbleSort_Result",
	"BubbleSort [static: IsEqualIntArrays");

	if(!boolean_4) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, random order, after bubble sort] with [expected result array] return == false",
	"test_BubbleSort_Result",
	"BubbleSort [static: IsEqualIntArrays");

	if(!boolean_5) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Order of items in [array of 5k items, random order] after [bubble sort] is not full ascending order",
	"test_BubbleSort_Result",
	"BubbleSort [static: IsEqualIntArrays, InitRandomIntArr, IsSortedIntArr]");

	return rprt;
}

REPORT *test_InsertionSort_Result	(REPORT *rprt)
{
	int arr_source_1[]   = {9};
	int arr_expected_1[] = {9};
	size_t size_arr_1 = sizeof(arr_source_1)/sizeof(arr_source_1[0]);

	int arr_source_2[]   = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	int arr_expected_2[] = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	size_t size_arr_2 = sizeof(arr_source_2)/sizeof(arr_source_2[0]);

	int arr_source_3[]   = {10000, 8000, 600, 5, -20, -1000};
	int arr_expected_3[] = {-1000, -20, 5, 600, 8000, 10000};
	size_t size_arr_3 = sizeof(arr_source_3)/sizeof(arr_source_3[0]);

	int arr_source_4[]   = {9, 3, 65, 7, 2, 15, 8, 71, 5};
	int arr_expected_4[] = {2, 3, 5, 7, 8, 9, 15, 65, 71};
	size_t size_arr_4 = sizeof(arr_source_4)/sizeof(arr_source_4[0]);

	int *arr_source_5 = NULL;
	size_t size_arr_5 = 5000;

	int boolean_1 = 0;
	int boolean_2 = 0;
	int boolean_3 = 0;
	int boolean_4 = 0;
	int boolean_5 = 0;

	printf(">>>>>>"KNRM"test_InsertionSort_Result\n"KRED);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1 ITEM SORT */
	printf(">>>>>>>>>>>>>>> 1 item sort\n");
	InsertionSort(arr_source_1, size_arr_1);
	boolean_1 = IsEqualIntArrays(arr_source_1, arr_expected_1, size_arr_1);
	PrintIntArr(arr_source_1, size_arr_1);
	PrintIntArr(arr_expected_1, size_arr_1);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASCENDING SORT */
	printf(">>>>>>>>>>>>>>> Ascending sort\n");
	InsertionSort(arr_source_2, size_arr_2);
	boolean_2 = IsEqualIntArrays(arr_source_2, arr_expected_2, size_arr_2);
	PrintIntArr(arr_source_2, size_arr_2);
	PrintIntArr(arr_expected_2, size_arr_2);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESCENDING SORT */
	printf(">>>>>>>>>>>>>>> Descending sort\n");
	InsertionSort(arr_source_3, size_arr_3);
	boolean_3 = IsEqualIntArrays(arr_source_3, arr_expected_3, size_arr_3);
	PrintIntArr(arr_source_3, size_arr_3);
	PrintIntArr(arr_expected_3, size_arr_3);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Random sort\n");
	InsertionSort(arr_source_4, size_arr_4);
	boolean_4 = IsEqualIntArrays(arr_source_4, arr_expected_4, size_arr_4);
	PrintIntArr(arr_source_4, size_arr_4);
	PrintIntArr(arr_expected_4, size_arr_4);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Big random sort\n");
	arr_source_5   = (int *)malloc(size_arr_5 * sizeof(int));
	srand(time(0));
	InitRandomIntArr(arr_source_5, size_arr_5);

	printf("Insertion Sorting 5k\n");
	InsertionSort(arr_source_5, size_arr_5);
	boolean_5 = IsSortedIntArr(arr_source_5, size_arr_5);

	free(arr_source_5);
/*>>> TEST REPORT OUT */

	if(!boolean_1) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of 1 item after insertion sort] with [expected result array] return == false"
	"C A N T  A P P E A R  I N  R E P O R T ",
	"test_InsertionSort_Result",
	"InsertionSort [static: IsEqualIntArrays");

	if(!boolean_2) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N itemss, ascending order, after insertion sort] with [expected result array] return == false",
	"test_InsertionSort_Result",
	"InsertionSort [static: IsEqualIntArrays");

	if(!boolean_3) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, descending order, after insertion sort] with [expected result array] return == false",
	"test_InsertionSort_Result",
	"InsertionSort [static: IsEqualIntArrays");

	if(!boolean_4) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, random order, after insertion sort] with [expected result array] return == false",
	"test_InsertionSort_Result",
	"InsertionSort [static: IsEqualIntArrays");

	if(!boolean_5) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Order of items in [array of 5k items, random order] after [insertion sort] is not full ascending order",
	"test_InsertionSort_Result",
	"InsertionSort [static: IsEqualIntArrays, InitRandomIntArr, IsSortedIntArr]");

	return rprt;
}
REPORT *test_SelectionSort_Result	(REPORT *rprt)
{
	int arr_source_1[]   = {9};
	int arr_expected_1[] = {9};
	size_t size_arr_1 = sizeof(arr_source_1)/sizeof(arr_source_1[0]);

	int arr_source_2[]   = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	int arr_expected_2[] = {-3, -1, 1, 4, 80, 700, 9000, 10000};
	size_t size_arr_2 = sizeof(arr_source_2)/sizeof(arr_source_2[0]);

	int arr_source_3[]   = {10000, 8000, 600, 5, -20, -1000};
	int arr_expected_3[] = {-1000, -20, 5, 600, 8000, 10000};
	size_t size_arr_3 = sizeof(arr_source_3)/sizeof(arr_source_3[0]);

	int arr_source_4[]   = {9, 3, 65, 7, 2, 15, 8, 71, 5};
	int arr_expected_4[] = {2, 3, 5, 7, 8, 9, 15, 65, 71};
	size_t size_arr_4 = sizeof(arr_source_4)/sizeof(arr_source_4[0]);

	int *arr_source_5 = NULL;
	size_t size_arr_5 = 5000;

	int boolean_1 = 0;
	int boolean_2 = 0;
	int boolean_3 = 0;
	int boolean_4 = 0;
	int boolean_5 = 0;

	printf(">>>>>>"KNRM"test_SelectionSort_Result\n"KRED);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1 ITEM SORT */
	printf(">>>>>>>>>>>>>>> 1 item sort\n");
	SelectionSort(arr_source_1, size_arr_1);
	boolean_1 = IsEqualIntArrays(arr_source_1, arr_expected_1, size_arr_1);
	PrintIntArr(arr_source_1, size_arr_1);
	PrintIntArr(arr_expected_1, size_arr_1);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASCENDING SORT */
	printf(">>>>>>>>>>>>>>> Ascending sort\n");
	SelectionSort(arr_source_2, size_arr_2);
	boolean_2 = IsEqualIntArrays(arr_source_2, arr_expected_2, size_arr_2);
	PrintIntArr(arr_source_2, size_arr_2);
	PrintIntArr(arr_expected_2, size_arr_2);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESCENDING SORT */
	printf(">>>>>>>>>>>>>>> Descending sort\n");
	SelectionSort(arr_source_3, size_arr_3);
	boolean_3 = IsEqualIntArrays(arr_source_3, arr_expected_3, size_arr_3);
	PrintIntArr(arr_source_3, size_arr_3);
	PrintIntArr(arr_expected_3, size_arr_3);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Random sort\n");
	SelectionSort(arr_source_4, size_arr_4);
	boolean_4 = IsEqualIntArrays(arr_source_4, arr_expected_4, size_arr_4);
	PrintIntArr(arr_source_4, size_arr_4);
	PrintIntArr(arr_expected_4, size_arr_4);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Big random sort\n");
	arr_source_5   = (int *)malloc(size_arr_5 * sizeof(int));
	srand(time(0));
	InitRandomIntArr(arr_source_5, size_arr_5);

	printf("Selection Sorting 5k\n");
	SelectionSort(arr_source_5, size_arr_5);
	boolean_5 = IsSortedIntArr(arr_source_5, size_arr_5);

	free(arr_source_5);
/*>>> TEST REPORT OUT */

	if(!boolean_1) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of 1 item after selection sort] with [expected result array] return == false"
	"C A N T  A P P E A R  I N  R E P O R T ",
	"test_SelectionSort_Result",
	"SelectionSort [static: IsEqualIntArrays");

	if(!boolean_2) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N itemss, ascending order, after selection sort] with [expected result array] return == false",
	"test_SelectionSort_Result",
	"SelectionSort [static: IsEqualIntArrays");

	if(!boolean_3) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, descending order, after selection sort] with [expected result array] return == false",
	"test_SelectionSort_Result",
	"SelectionSort [static: IsEqualIntArrays");

	if(!boolean_4) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, random order, after selection sort] with [expected result array] return == false",
	"test_SelectionSort_Result",
	"SelectionSort [static: IsEqualIntArrays");

	if(!boolean_5) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Order of items in [array of 5k items, random order] after [selection sort] is not full ascending order",
	"test_SelectionSort_Result",
	"SelectionSort [static: IsEqualIntArrays, InitRandomIntArr, IsSortedIntArr]");

	return rprt;
}

REPORT *test_CountingSort_Result	(REPORT *rprt)
{
	int arr_source_1[]   = {9};
	int arr_expected_1[] = {9};
	size_t size_arr_1 = sizeof(arr_source_1)/sizeof(arr_source_1[0]);
	size_t range_1  = 10;
	int minimum_1 = 0;

	int arr_source_2[]   = {-5, -5, 2, 7, 8, 9};
	int arr_expected_2[] = {-5, -5, 2, 7, 8, 9};
	size_t size_arr_2 = sizeof(arr_source_2)/sizeof(arr_source_2[0]);
	size_t range_2 = 20;
	int minimum_2 = -10;

	int arr_source_3[]   = {-10, -11, -98, -99, -100};
	int arr_expected_3[] = {-100, -99, -98, -11, -10};
	size_t size_arr_3 = sizeof(arr_source_3)/sizeof(arr_source_3[0]);
	size_t range_3 = 91;
	int minimum_3 = -100;

	int arr_source_4[]   = {5, 0, 2, 10, 8, 0, 8, 9, 9, 6, 8};
	int arr_expected_4[] = {0, 0, 2, 5, 6, 8, 8, 8, 9, 9, 10};
	size_t size_arr_4 = sizeof(arr_source_4)/sizeof(arr_source_4[0]);
	size_t range_4 = 11;
	int minimum_4 = 0;

	int *arr_source_5 = NULL;
	size_t size_arr_5 = 5000;
	size_t range_5 = 10000;
	int minimum_5 = 0;

	int boolean_1 = 0;
	int boolean_2 = 0;
	int boolean_3 = 0;
	int boolean_4 = 0;
	int boolean_5 = 0;

	printf(">>>>>>"KNRM"test_CountingSort_Result\n"KRED);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1 ITEM SORT */
	printf(">>>>>>>>>>>>>>> 1 item sort\n");
	CountingSort(arr_source_1, sizeof(int), range_1, size_arr_1, ReturnNum, (void *)&minimum_1);
	boolean_1 = IsEqualIntArrays(arr_source_1, arr_expected_1, size_arr_1);
	PrintIntArr(arr_source_1, size_arr_1);
	PrintIntArr(arr_expected_1, size_arr_1);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASCENDING SORT */
	printf(">>>>>>>>>>>>>>> Ascending sort\n");
	CountingSort(arr_source_2, sizeof(int), range_2, size_arr_2, ReturnNum, (void *)&minimum_2);
	boolean_2 = IsEqualIntArrays(arr_source_2, arr_expected_2, size_arr_2);
	PrintIntArr(arr_source_2, size_arr_2);
	PrintIntArr(arr_expected_2, size_arr_2);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESCENDING SORT */

	printf(">>>>>>>>>>>>>>> Descending sort\n");
	CountingSort(arr_source_3, sizeof(int), range_3, size_arr_3, ReturnNum, (void *)&minimum_3);
	boolean_3 = IsEqualIntArrays(arr_source_3, arr_expected_3, size_arr_3);
	PrintIntArr(arr_source_3, size_arr_3);
	PrintIntArr(arr_expected_3, size_arr_3);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Random sort\n");
	CountingSort(arr_source_4, sizeof(int), range_4, size_arr_4, ReturnNum, (void *)&minimum_4);
	boolean_4 = IsEqualIntArrays(arr_source_4, arr_expected_4, size_arr_4);
	PrintIntArr(arr_source_4, size_arr_4);
	PrintIntArr(arr_expected_4, size_arr_4);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Big random sort\n");
	arr_source_5   = (int *)malloc(size_arr_5 * sizeof(int));
	srand(time(0));
	InitRandomIntArr(arr_source_5, size_arr_5);

	printf("Counting Sorting 5k\n");
	CountingSort(arr_source_5, sizeof(int), range_5, size_arr_5, ReturnNum, (void *)&minimum_5);
	boolean_5 = IsSortedIntArr(arr_source_5, size_arr_5);

	free(arr_source_5);
#if 0
#endif
/*>>> TEST REPORT OUT */

	if(!boolean_1) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of 1 item after counting sort] with [expected result array] return == false"
	"C A N T  A P P E A R  I N  R E P O R T ",
	"test_CountingSort_Result",
	"CountingSort [static: IsEqualIntArrays");
	if(!boolean_2) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N itemss, ascending order, after counting sort] with [expected result array] return == false",
	"test_CountingSort_Result",
	"CountingSort [static: IsEqualIntArrays");

#if 0

	if(!boolean_3) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, descending order, after counting sort] with [expected result array] return == false",
	"test_CountingSort_Result",
	"CountingSort [static: IsEqualIntArrays");
#endif
	if(!boolean_4) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, random order, after counting sort] with [expected result array] return == false",
	"test_CountingSort_Result",
	"CountingSort [static: IsEqualIntArrays");

	if(!boolean_5) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Order of items in [array of 5k items, random order] after [counting sort] is not full ascending order",
	"test_CountingSort_Result",
	"CountingSort [static: IsEqualIntArrays, InitRandomIntArr, IsSortedIntArr]");
#if 0
#endif

	return rprt;
}

REPORT *test_RadixSort_Result		(REPORT *rprt)
{
		int arr_source_1[]   = {9};
	int arr_expected_1[] = {9};
	size_t size_arr_1 = sizeof(arr_source_1)/sizeof(arr_source_1[0]);

	int arr_source_2[]   = {0, 3, 1, 4, 80, 700, 9000, 10000};
	int arr_expected_2[] = {0, 1, 3, 4, 80, 700, 9000, 10000};
	size_t size_arr_2 = sizeof(arr_source_2)/sizeof(arr_source_2[0]);

	int arr_source_3[]   = {10000, 8000, 1000, 600, 20, 5};
	int arr_expected_3[] = {5, 20, 600, 1000, 8000, 10000};
	size_t size_arr_3 = sizeof(arr_source_3)/sizeof(arr_source_3[0]);

	int arr_source_4[]   = {90, 3, 65, 7, 2, 15, 8, 71, 50};
	int arr_expected_4[] = {2, 3, 7, 8, 15, 50, 65, 71, 90};
	size_t size_arr_4 = sizeof(arr_source_4)/sizeof(arr_source_4[0]);

	int *arr_source_5 = NULL;
	size_t size_arr_5 = 5000;

	int boolean_1 = 0;
	int boolean_2 = 0;
	int boolean_3 = 0;
	int boolean_4 = 0;
	int boolean_5 = 0;

	printf(">>>>>>"KNRM"test_RadixSort_Result\n"KRED);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1 ITEM SORT */
	printf(">>>>>>>>>>>>>>> 1 item sort\n");
	RadixSort(arr_source_1, size_arr_1);
	boolean_1 = IsEqualIntArrays(arr_source_1, arr_expected_1, size_arr_1);
	PrintIntArr(arr_source_1, size_arr_1);
	PrintIntArr(arr_expected_1, size_arr_1);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASCENDING SORT */
	printf(">>>>>>>>>>>>>>> Ascending sort\n");
	RadixSort(arr_source_2, size_arr_2);
	boolean_2 = IsEqualIntArrays(arr_source_2, arr_expected_2, size_arr_2);
	PrintIntArr(arr_source_2, size_arr_2);
	PrintIntArr(arr_expected_2, size_arr_2);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESCENDING SORT */
	printf(">>>>>>>>>>>>>>> Descending sort\n");
	RadixSort(arr_source_3, size_arr_3);
	boolean_3 = IsEqualIntArrays(arr_source_3, arr_expected_3, size_arr_3);
	PrintIntArr(arr_source_3, size_arr_3);
	PrintIntArr(arr_expected_3, size_arr_3);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Random sort\n");
	RadixSort(arr_source_4, size_arr_4);
	boolean_4 = IsEqualIntArrays(arr_source_4, arr_expected_4, size_arr_4);
	PrintIntArr(arr_source_4, size_arr_4);
	PrintIntArr(arr_expected_4, size_arr_4);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT */
	printf(">>>>>>>>>>>>>>> Big random sort\n");
	arr_source_5   = (int *)malloc(size_arr_5 * sizeof(int));
	srand(time(0));
	InitRandomIntArr(arr_source_5, size_arr_5);

	printf("Radix Sorting 5k\n");
	RadixSort(arr_source_5, size_arr_5);
	boolean_5 = IsSortedIntArr(arr_source_5, size_arr_5);

	free(arr_source_5);
/*>>> TEST REPORT OUT */

	if(!boolean_1) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of 1 item after selection sort] with [expected result array] return == false"
	"C A N T  A P P E A R  I N  R E P O R T ",
	"test_RadixSort_Result",
	"RadixSort [static: IsEqualIntArrays");

	if(!boolean_2) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N itemss, ascending order, after selection sort] with [expected result array] return == false",
	"test_RadixSort_Result",
	"RadixSort [static: IsEqualIntArrays");

	if(!boolean_3) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, descending order, after selection sort] with [expected result array] return == false",
	"test_RadixSort_Result",
	"RadixSort [static: IsEqualIntArrays");

	if(!boolean_4) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Comparison of [array of N items, random order, after selection sort] with [expected result array] return == false",
	"test_RadixSort_Result",
	"RadixSort [static: IsEqualIntArrays");

	if(!boolean_5) ReportWrite(rprt, TESTFAIL, __FILE__, __LINE__,
	"Order of items in [array of 5k items, random order] after [selection sort] is not full ascending order",
	"test_RadixSort_Result",
	"RadixSort [static: IsEqualIntArrays, InitRandomIntArr, IsSortedIntArr]");
#if 0
#endif
	return rprt;
}


/********************//********************//********************/
		      /* Benchmark tests */
/********************//********************//********************/

REPORT *test_BubbleSort_Benchmarks	(REPORT *rprt)
{
	int *arr_1_tested = NULL;
	int *arr_1_qsort  = NULL;

	size_t size_arr_1 = 50000;

	clock_t start_1_tested = 0;
	clock_t end_1_tested = 0;

	clock_t start_1_qsort = 0;
	clock_t end_1_qsort = 0;

	printf(">>>>>>"KNRM"test_BubbleSort_Benchmarks\n"KRED);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT - BENCHMARK */
	arr_1_tested = (int *)malloc(size_arr_1 * sizeof(int));
	arr_1_qsort  = (int *)malloc(size_arr_1 * sizeof(int));

	srand(time(0));	/*init */
	printf("INITING RANDOM 50k...\n");
	InitRandomIntArr(arr_1_tested, size_arr_1);
	printf("COPYING 50k...\n");
	CopyIntArr(arr_1_qsort, arr_1_tested, size_arr_1);

	printf("BUBBLE SORTING 50k...\n");
	start_1_tested = clock();
	BubbleSort(arr_1_tested, size_arr_1); /* run tested */
	end_1_tested = clock();

	printf("QUICK SORTING 50k...\n");
	start_1_qsort = clock();
	qsort(arr_1_qsort, size_arr_1, sizeof(int), CompareInts);
	end_1_qsort = clock();

	printf("Tested Bubble Sort on [50k int arr] : [%f]\n", ((double)end_1_tested - start_1_tested)/CLOCKS_PER_SEC);
	printf("System QSort       on [50k int arr] : [%f]\n", ((double)end_1_qsort - start_1_qsort)/CLOCKS_PER_SEC);

	free(arr_1_tested);
	free(arr_1_qsort);

	return rprt;
}
REPORT *test_InsertionSort_Benchmarks	(REPORT *rprt)
{
	int *arr_1_tested = NULL;
	int *arr_1_qsort  = NULL;

	size_t size_arr_1 = 50000;

	clock_t start_1_tested = 0;
	clock_t end_1_tested = 0;

	clock_t start_1_qsort = 0;
	clock_t end_1_qsort = 0;

	printf(">>>>>>"KNRM"test_InsertionSort_Benchmarks\n"KRED);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT - BENCHMARK */
	arr_1_tested = (int *)malloc(size_arr_1 * sizeof(int));
	arr_1_qsort  = (int *)malloc(size_arr_1 * sizeof(int));

	srand(time(0));	/*init */
	printf("INITING RANDOM 50k...\n");
	InitRandomIntArr(arr_1_tested, size_arr_1);
	printf("COPYING 50k...\n");
	CopyIntArr(arr_1_qsort, arr_1_tested, size_arr_1);

	printf("Insertion SORTING 50k...\n");
	start_1_tested = clock();
	InsertionSort(arr_1_tested, size_arr_1); /* run tested */
	end_1_tested = clock();

	printf("QUICK SORTING 50k...\n");
	start_1_qsort = clock();
	qsort(arr_1_qsort, size_arr_1, sizeof(int), CompareInts);
	end_1_qsort = clock();

	printf("Tested Insertion Sort on [50k int arr] : [%f]\n", ((double)end_1_tested - start_1_tested)/CLOCKS_PER_SEC);
	printf("System QSort          on [50k int arr] : [%f]\n", ((double)end_1_qsort - start_1_qsort)/CLOCKS_PER_SEC);

	free(arr_1_tested);
	free(arr_1_qsort);

	return rprt;
}
REPORT *test_SelectionSort_Benchmarks	(REPORT *rprt)
{
	int *arr_1_tested = NULL;
	int *arr_1_qsort  = NULL;

	size_t size_arr_1 = 50000;

	clock_t start_1_tested = 0;
	clock_t end_1_tested = 0;

	clock_t start_1_qsort = 0;
	clock_t end_1_qsort = 0;

	printf(">>>>>>"KNRM"test_SelectionSort_Benchmarks\n"KRED);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT - BENCHMARK */
	arr_1_tested = (int *)malloc(size_arr_1 * sizeof(int));
	arr_1_qsort  = (int *)malloc(size_arr_1 * sizeof(int));

	srand(time(0));	/*init */
	printf("INITING RANDOM 50k...\n");
	InitRandomIntArr(arr_1_tested, size_arr_1);
	printf("COPYING 50k...\n");
	CopyIntArr(arr_1_qsort, arr_1_tested, size_arr_1);

	printf("Selection SORTING 50k...\n");
	start_1_tested = clock();
	SelectionSort(arr_1_tested, size_arr_1); /* run tested */
	end_1_tested = clock();

	printf("QUICK SORTING 50k...\n");
	start_1_qsort = clock();
	qsort(arr_1_qsort, size_arr_1, sizeof(int), CompareInts);
	end_1_qsort = clock();

	printf("Tested Selection Sort on [50k int arr] : [%f]\n", ((double)end_1_tested - start_1_tested)/CLOCKS_PER_SEC);
	printf("System QSort          on [50k int arr] : [%f]\n", ((double)end_1_qsort - start_1_qsort)/CLOCKS_PER_SEC);

	free(arr_1_tested);
	free(arr_1_qsort);

	return rprt;
}

REPORT *test_CountingSort_Benchmarks	(REPORT *rprt)
{
	int *arr_1_tested = NULL;
	int *arr_1_qsort  = NULL;

	size_t size_arr_1 = 50000;

	int range_1 = 10000;
	int minimum_1 = 0;

	clock_t start_1_tested = 0;
	clock_t end_1_tested = 0;

	clock_t start_1_qsort = 0;
	clock_t end_1_qsort = 0;

	printf(">>>>>>"KNRM"test_CountingSort_Benchmarks\n"KRED);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT - BENCHMARK */
	arr_1_tested = (int *)malloc(size_arr_1 * sizeof(int));
	arr_1_qsort  = (int *)malloc(size_arr_1 * sizeof(int));

	srand(time(0));	/*init */
	printf("INITING RANDOM 50k...\n");
	InitRandomIntArr(arr_1_tested, size_arr_1);
	printf("COPYING 50k...\n");
	CopyIntArr(arr_1_qsort, arr_1_tested, size_arr_1);

	printf("Counting SORTING 50k...\n");
	start_1_tested = clock();
CountingSort(arr_1_tested, sizeof(int), range_1, size_arr_1, ReturnNum, (void *)&minimum_1); /* run tested */
	end_1_tested = clock();

	printf("QUICK SORTING 50k...\n");
	start_1_qsort = clock();
	qsort(arr_1_qsort, size_arr_1, sizeof(int), CompareInts);
	end_1_qsort = clock();

	printf("Tested Counting Sort  on [50k int arr] : [%f]\n", ((double)end_1_tested - start_1_tested)/CLOCKS_PER_SEC);
	printf("System QSort          on [50k int arr] : [%f]\n", ((double)end_1_qsort - start_1_qsort)/CLOCKS_PER_SEC);

	free(arr_1_tested);
	free(arr_1_qsort);

	return rprt;
}

REPORT *test_RadixSort_Benchmarks	(REPORT *rprt)
{
	int *arr_1_tested = NULL;
	int *arr_1_qsort  = NULL;

	size_t size_arr_1 = 50000;

	clock_t start_1_tested = 0;
	clock_t end_1_tested = 0;

	clock_t start_1_qsort = 0;
	clock_t end_1_qsort = 0;

	printf(">>>>>>"KNRM"test_RadixSort_Benchmarks\n"KRED);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BIG RANDOM SORT - BENCHMARK */
	arr_1_tested = (int *)malloc(size_arr_1 * sizeof(int));
	arr_1_qsort  = (int *)malloc(size_arr_1 * sizeof(int));

	srand(time(0));	/*init */
	printf("INITING RANDOM 50k...\n");
	InitRandomIntArr(arr_1_tested, size_arr_1);
	printf("COPYING 50k...\n");
	CopyIntArr(arr_1_qsort, arr_1_tested, size_arr_1);

	printf("Radix SORTING 50k...\n");
	start_1_tested = clock();
	RadixSort(arr_1_tested, size_arr_1); /* run tested */
	end_1_tested = clock();

	printf("QUICK SORTING 50k...\n");
	start_1_qsort = clock();
	qsort(arr_1_qsort, size_arr_1, sizeof(int), CompareInts);
	end_1_qsort = clock();

	printf("Tested Radix Sort on [50k int arr] : [%f]\n", ((double)end_1_tested - start_1_tested)/CLOCKS_PER_SEC);
	printf("System QSort      on [50k int arr] : [%f]\n", ((double)end_1_qsort - start_1_qsort)/CLOCKS_PER_SEC);

	free(arr_1_tested);
	free(arr_1_qsort);

	return rprt;
}
/* SERVICE FUNCTIONS */
static void InitRandomIntArr(int *arr, size_t size)
{
	size_t i = 0;

	for(; size > i ;++i)
	{
		arr[i] = rand()%10000;
		/*printf("inserted %d\n", arr[i]);*/
	}
}
static int IsEqualIntArrays(int *arr1, int *arr2, size_t size)
{
	size_t i = 0;
	size_t is_equal = 1;

	for(; size > i && is_equal; ++i)
	{
		is_equal = (arr1[i] == arr2[i]);
	}

	return is_equal;
}

static int IsSortedIntArr(int *arr, size_t size)
{
	size_t i = 1;
	size_t is_sorted = 1;

	if(size > 1)
	{
		for(; size - 1> i && is_sorted; ++i)
		{
			is_sorted = (arr[i] <= arr[i + 1]);
		}
	}

	if(!is_sorted)
	{
		printf("not sorted at : [%d] [%d] [%d]\n", arr[i-1], arr[i], arr[i+1]);
	}

	return is_sorted;
}

static void PrintIntArr(int *arr, size_t size)
{
	size_t i = 0;

	printf("Int Array [%p]\n", arr);

	for(; size > i; ++i)
	{
		printf(" [%d] ",arr[i]);
	}

	printf("\n\n");
}

static void CopyIntArr(int *dest, int *src, size_t size)
{
	size_t i = 0;

	for(; size > i; ++i)
	{
		dest[i] = src[i];
	}
}

int CompareInts(const void *data1,const  void *data2)
{
/*	assert(data1);
	assert(data2);*/

	return *(int *)data1 - *(int *)data2;
}

size_t ReturnNum(const void* num, const void *minimum_val)
{
	return (*(int *)num - *(int *)minimum_val);
}
