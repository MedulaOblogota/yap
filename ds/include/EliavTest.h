#ifndef ELIAV_TEST
#define ELIAV_TEST

#include <stdio.h>
#include <time.h>

#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YLW "\033[1;33m"
#define BLU "\033[0;34m"
#define CYN "\033[0;36m"
#define RESET "\033[0m"

#define ELEM_IN_ARR(input) (sizeof(input[0]))
#define SIZEOFARR(input) (sizeof(input)/ELEM_IN_ARR(input))

#define RunTest(test) \
do { \
	fprintf(stderr, RESET"Running "#test"... \n"); \
	RunTestFunc(test); \
} while(0)

#define CmpStrings(data1, data2) \
do { \
	CompareStrings(data1, data2, __LINE__, #data1, #data2); \
} while(0)

#define CmpNum(data1, data2) \
do { \
	CompareNum(data1, data2, __LINE__, #data1, #data2); \
} while(0)

#define CmpPtr(data1, data2) \
do { \
	ComparePtr(data1, data2, __LINE__, #data1, #data2); \
} while(0)

#define CmpData(data1, data2, size) \
do { \
	CompareData(data1, data2, size, __LINE__); \
} while(0)

#define CheckCondition(condition) \
do { \
	CheckCond(condition, __LINE__, #condition); \
} while(0)

#define Stab() \
do { \
	printf("Stab in FILE: %s		LINE: %d\n", __FILE__, __LINE__);; \
} while(0)

#define PrintAddress(ptr) \
do { \
	printf(""#ptr" Address is:		%p\n", (void *)ptr); \
} while(0)

#define PrintInt(ptr) \
do { \
	PrintIntVal(ptr, #ptr); \
} while(0)

#define END_OF_RUN(i) \
do { \
	printf("----------------------End_Of_Run_%lu----------------------\n", i); \
} while(0)

#define GET_RUN_TIME(func) \
do { \
    double after = clock(); \
    double before = clock(); \
	func; \
    after = clock(); \
    printf("RunTime of %s:     %f\n", #func, (after - before)/ CLOCKS_PER_SEC);\
} while(0)

typedef void (*test_func)();

/*******************************************************************************
* Allocate memory for the test, running the function pointed by test_func, and
* finally, freeing the allocated memory.
* In case Allocation has been failed - a meesege will be printed, and test will
* not perform.
*
* test_func - Test function to check conditions, using Compersion functions
* below.
*
* Function prints [OK] in case Test passed, [Failed] otherwise and Error Summery
* with total number of errors and tests will be shown.
*
* Function should be called with macro RunTest(test_func).
*******************************************************************************/
void RunTestFunc(test_func test_func);

/*******************************************************************************
* Compares the first size bytes of the memory areas tested_data and
* expected_data.
*
* data1, data2 - data to compare.
* size - num of bytes to compare.
* line - num of line test function has been called.
*
* Function should be called with macro:
* CompareData(tested_data, expected_data, size).
*******************************************************************************/
void CompareData(void *data1, void *data2, size_t size, int line);

/*******************************************************************************
* Compares the first size bytes of the memory areas tested_data and
* expected_data.
*
* data1, data2 - data to compare.
* size - num of bytes to compare.
* line - num of line test function has been called.
*
* If the two given strings are not equal, an error messege with the two
* strings will be printed, and number of errors in the test will increase by 1.
*
* Function should be called with the following macro:
* CompareStrings(data_to_test, expected_result).
*******************************************************************************/
void CompareStrings(char *data1, char *data2, int line, char *data1_name,
                                                        char *data2_name);

/*******************************************************************************
* Compares between two numbers.
*
* data1, data2 - data to compare.
* line - num of line test function has been called.
*
* If the two given numbers are not equal, an error messege with the two numbers
* will be printed, and number of errors in the test will increase by 1.
*
* Function should be called with the following macro:
* CompareNum(num_to_test, expected_result).
*******************************************************************************/
void CompareNum(size_t data1, size_t data2, int line, char *data1_name,
                                                      char *data2_name);

/*******************************************************************************
* Compares between two pointers.
*
* data1, data2 - data to compare.
* line - num of line test function has been called.
*
* If the two given numbers are not equal, an error messege with the two numbers
* will be printed, and number of errors in the test will increase by 1.
*
* Function should be called with the following macro:
* ComparePtr(ptr_to_test, expected_address).
*******************************************************************************/
void ComparePtr(void *data1, void *data2, int line, char *data1_name,
                                                    char *data2_name);

/*******************************************************************************
* Check if condition is TRUE.
*
* condition - condition to test.
* line - num of line test function has been called.
*
* Function should be called with macro:
* CheckCondition(condition).
*******************************************************************************/
void CheckCond(int condition, int line, char *print_cond);

/*******************************************************************************
* Calculate test runtime.
*
* func - Test function.
*
* Return value - test runtime.
*******************************************************************************/
double GetRunTime(test_func func);

/*******************************************************************************
* Print array of ints.
*
* arr - array of ints.
* arr_size - array size.
*******************************************************************************/
void PrintIntArr(int arr[], size_t arr_size);

/*******************************************************************************
* Print array of ints.
*
* arr - array of ints.
* arr_size - array size.
*******************************************************************************/
void PrintULongArr(size_t arr[], size_t arr_size);


void PrintIntVal(int *ptr, char *name);
#endif /* ELIAV_TEST */
