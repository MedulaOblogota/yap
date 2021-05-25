#include "VSA.h"

#include <stdlib.h>
#include <stdio.h>

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestVSAInit();
void TestVSAAllocAndFree();

int main()
{
    TestVSAInit();
    TestVSAAllocAndFree();
/*
    char *malloced = malloc(120);
    vsa_t *vsa = VSAInit(malloced, 120);
    void *alloc1 = NULL;
    void *alloc2 = NULL;
    int num = 5;
    int *pnum = &num;

    alloc1 = VSAAlloc(vsa, 30);
    alloc2 = VSAAlloc(vsa, 20);

    *(char *)alloc1 = '1';
    VSAFree(alloc1);
    VSAFree(alloc2);
    VSAFree(pnum);
    VSAFree(alloc1);
    VSAAlloc(vsa, 10);
    printf("largest size is %lu\n", VSALargestChunkAvailable(vsa));*/

    return (0);
}

static void WrapperCheckIfSamePointer(char *func_name, vsa_t *value_is, vsa_t *value_should_be)
{
        if (value_is == value_should_be)
        {
            printf(GRN"SUCCESS with %s!!\n"RESET, func_name);
        }
        else
        {
            printf(RED"FAILURE with %s!!\n"RESET, func_name);
        }
}

static void WrapperCompareSizet(char *func_name, size_t current_var, size_t expected_var)
{
    if (current_var == expected_var)
    {
        printf(GRN"SUCCESS with %s!!\n"RESET, func_name);
    }
    else
    {
        printf(RED"FAILURE with %s!!\n"RESET, func_name);
    }
}

void TestVSAInit()
{
    /*HOPEFULLE BLACKBOX AS SHOULD ALWAYS SUCCEED*/
    char *malloced = malloc(500);
    vsa_t *vsa = VSAInit(malloced, 500);

    if (vsa != NULL)
    {
        printf(GRN"SUCCESS with VSAInit!!\n"RESET);
    }
    else
    {
        printf(RED"FAILURE with VSAInit!!\n"RESET);
    }

    free(malloced);

    /*MOST LIKELY BLACKBOX. SHOULD SUCCEED IN YOUR CASE*/
    malloced = malloc(10);
    vsa = VSAInit(malloced, 10);

    if (vsa == NULL)
    {
        printf(GRN"SUCCESS with VSAInit!!\n"RESET);
    }
    else
    {
        printf(RED"FAILURE with VSAInit!!\n"RESET);
    }

    free(malloced);

}


void TestVSAAllocAndFree()
{
    char *malloced = malloc(240);
    vsa_t *vsa = VSAInit(malloced, 240);
    void *alloc1 = NULL;
    void *alloc2 = NULL;
    void *alloc3 = NULL;
    int num = 5;
    int *pnum = &num;
    size_t initial_largest_chunk = VSALargestChunkAvailable(vsa);

    alloc1 = VSAAlloc(vsa, 30);
    alloc2 = VSAAlloc(vsa, 20);
    alloc3 = VSAAlloc(vsa, 200);

    if (alloc3 == NULL)
    {
        printf(GRN"SUCCESS with VSAAlloc!!\n"RESET);
    }
    else
    {
        printf(RED"FAILURE with VSAAlloc!!\n"RESET);
    }

    *(char *)alloc1 = '1';
    VSAFree(alloc1);
    VSAFree(alloc2);

    WrapperCompareSizet("VSAAlloc", initial_largest_chunk, VSALargestChunkAvailable(vsa));

    /*VSAFree(pnum);*/

    WrapperCompareSizet("VSAAlloc", initial_largest_chunk, VSALargestChunkAvailable(vsa));

    VSAFree(alloc1);

    WrapperCompareSizet("VSAAlloc", initial_largest_chunk, VSALargestChunkAvailable(vsa));

    VSAAlloc(vsa, 10);

    alloc1 = VSAAlloc(vsa, 60);

    alloc2 = VSAAlloc(vsa, 50);

    alloc3 = VSAAlloc(vsa, 50);

    VSAAlloc(vsa, 50);

    VSAFree(alloc1);
    VSAFree(alloc2);
    VSAFree(alloc3);
    VSAFree(alloc1);
    VSAFree(alloc1);
    VSAFree(alloc1);
    VSAFree(alloc1);

    printf("current largest size = %lu\n", VSALargestChunkAvailable(vsa));

    free(malloced);

}
