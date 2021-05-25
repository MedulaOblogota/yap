#include "EliavTest.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct test_s test_t;

struct test_s
{
    size_t tests_passed;
    size_t tests_failed;
};

test_t *test_control = NULL;

static test_t *BeginTest();
static void EndTest(test_t *test_control);

void RunTestFunc(test_func func)
{
    test_control = BeginTest();
    func();
    EndTest(test_control);

    return;
}

void CompareData(void *data1, void *data2, size_t size, int line)
{
    assert(NULL != data1);
    assert(NULL != data2);

    if (0 != memcmp(data1, data2, size))
    {
        printf(CYN "you have an error in line %d: \n"RESET, line);
        printf(RED"Data is not match\n"RESET);
        puts("-------------------------------------------------------------\n");
        test_control->tests_failed  += 1;

        return;
    }

    test_control->tests_passed += 1;

    return;
}

void CheckCond(int condition, int line, char *print_cond)
{
    if (!condition)
    {
        printf(CYN "you have an error in line %d: \n"RESET, line);
        printf(RED"condition faild:     %s\n"RESET, print_cond);
        puts("-------------------------------------------------------------\n");
        test_control->tests_failed  += 1;

        return;
    }

    test_control->tests_passed += 1;

    return;
}

void CompareStrings(char *data1, char *data2, int line, char *data1_name,
                                                        char *data2_name)
{
    assert(NULL != data1);
    assert(NULL != data2);

    if(0 != strcmp(data1, data2))
    {
        printf(CYN "you have an error in line %d: \n"RESET, line);
        printf(RED"%s:    %s\n"RESET, data1_name, data1);
        printf(RED"%s:    %s\n"RESET, data2_name, data2);
        puts("-------------------------------------------------------------\n");
        test_control->tests_failed  += 1;

        return;
    }

    test_control->tests_passed += 1;

    return;
}

void CompareNum(size_t data1, size_t data2, int line, char *data1_name,
                                                      char *data2_name)
{
    if(data1 != data2)
    {
        printf(CYN "you have an error in line %d: \n"RESET, line);
        printf(RED"%s:    %lu\n"RESET, data1_name, data1);
        printf(RED"%s:    %lu\n"RESET, data2_name, data2);
        puts("-------------------------------------------------------------\n");
        test_control->tests_failed  += 1;

        return;
    }

    test_control->tests_passed += 1;

    return;
}

void ComparePtr(void *data1, void *data2, int line, char *data1_name,
                                                    char *data2_name)
{
    if(data1 != data2)
    {
        printf(CYN "you have an error in line %d: \n"RESET, line);
        printf(RED"%s:    %p\n"RESET, data1_name, data1);
        printf(RED"%s:    %p\n"RESET, data2_name, data2);
        puts("-------------------------------------------------------------\n");
        test_control->tests_failed  += 1;

        return;
    }

    test_control->tests_passed += 1;

    return;
}

double GetRunTime(test_func func)
{
    clock_t before = 0;
    clock_t after = 0;

    before = clock();
    func();
    after = clock();

    printf("Time:   %g\n", (double)(after - before)/ CLOCKS_PER_SEC);

    return ((double)(after - before)/ CLOCKS_PER_SEC);
}



void PrintIntArr(int arr[], size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < (arr_size - 1); ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[i]);

    return;
}

void PrintULongArr(size_t arr[], size_t arr_size)
{
    size_t i = 0;

    for (i = 0; i < (arr_size - 1); ++i)
    {
        printf("%lu, ", arr[i]);
    }
    printf("%lu\n", arr[i]);

    return;
}

/*****************************Auxilary functions:******************************/

/*Allocate memory for the test_control and initiate struct */
static test_t *BeginTest()
{
    test_control = malloc(sizeof(test_t));
    if(NULL == test_control)
    {
		puts("Allocation has been failed. Check your computer!");

        exit (-1);
    }

    test_control->tests_passed = 0;
    test_control->tests_failed  = 0;

    return(test_control);
}

/*Print test_control results and freeing the allocated memory*/
static void EndTest(test_t *test_control)
{
    size_t tests_passed = test_control->tests_passed;
    size_t tests_fails = test_control->tests_failed;
    size_t total_tested = tests_passed + tests_fails;

    if(total_tested == tests_passed)
    {
        printf(GRN "[OK]\n" RESET);
    }
    else
    {
        puts(YLW"Errors Summery:"RESET);
        printf("Total tests:    %lu\n", total_tested);
        printf("Total Errors:   %lu\n", tests_fails);
        printf(RED"[Failed]\n\n"RESET);
    }

    free(test_control);

    return;
}

void PrintIntVal(int *ptr, char *name)
{
    if(NULL == ptr)
    {
        printf("%s is pointing to NULL!\n", name);
    }
    else
    {
        printf("%s value is:    %d\n", name, *ptr);
    }
}
