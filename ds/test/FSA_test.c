#include <stdio.h>
#include <stdlib.h>

#include "FSA.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define SIZE_OF_WORD (8)

void TestFSAInitAndFree();
void TestFSAAlloc();

int main()
{
    TestFSAInitAndFree();
    TestFSAAlloc();


    return(0);
}

static void WrapperCompareSizet(char *func_name, size_t size, size_t expected_size)
{
    if (size == expected_size)
    {
        printf(GRN"SUCCESS with %s!!\n"RESET, func_name);
    }
    else
    {
        printf(RED"FAILURE with %s!!!!\n"RESET, func_name);
    }
}

void TestFSAInitAndFree()
{
    size_t fsa_size = FSASuggestSize(12, 3);    /* 12 Bytes, 3 blocks */
    char *malloced = malloc(fsa_size);
    fsa_t *fsa = FSAInit(malloced, fsa_size, 12);

    WrapperCompareSizet("alignment of size",fsa_size % SIZE_OF_WORD, 0);
    WrapperCompareSizet("free size of FSA", FSACountFree(fsa), 3);

    free(malloced);
}

static void WrapperFSAAlloc(size_t size_of_block, size_t num_of_blocks)
{
    size_t fsa_size = FSASuggestSize(size_of_block, num_of_blocks);
    char *malloced = malloc(fsa_size);
    fsa_t *fsa = FSAInit(malloced, fsa_size, size_of_block);
    void *entry = NULL;

    entry = FSAAlloc(fsa);

    if (NULL != entry)
    {
        printf(GRN"SUCCESS with receiving NULL for allocating in full list!!\n"RESET);
    }
    else
    {
        printf(RED"FAILURE with receiving NULL for allocating in full list!!!!\n"RESET);
    }

    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);
    entry = FSAAlloc(fsa);

    if (NULL == entry)
    {
        printf(GRN"SUCCESS with receiving NULL for allocating in full list!!\n"RESET);
    }
    else
    {
        printf(RED"FAILURE with receiving NULL for allocating in full list!!!!\n"RESET);
    }

    free(malloced);

}

static void WrapperFSAFree()
{
    fsa_t *fsa = NULL;
    size_t fsa_size = FSASuggestSize(12, 3); /* 8 BYTES, 3 ITEMS */
    char *malloced = malloc(fsa_size);
    int num = 5;
    void *entry1;
    void *entry2;
    void *entry3;

    printf("fsa_size=%lu\n", fsa_size);
    fsa = FSAInit(malloced, fsa_size, 12);

    printf("size of fsa is %lu\n", FSACountFree(fsa));
    entry1 = FSAAlloc(fsa);
    printf("size of fsa is %lu\n", FSACountFree(fsa));
    entry2 = FSAAlloc(fsa);
    printf("size of fsa is %lu\n", FSACountFree(fsa));
    entry3 = FSAAlloc(fsa);
    printf("size of fsa is %lu\n", FSACountFree(fsa));
    /*entry4 = FSAAlloc(fsa);
    printf("size of fsa is %lu\n", FSACountFree(fsa));*/

    *(int *)entry1 = num;
    FSAFree(entry3);
    printf("size of fsa is %lu\n", FSACountFree(fsa));
    FSAFree(entry1);
    printf("size of fsa is %lu\n", FSACountFree(fsa));
    FSAFree(entry2);
    printf("size of fsa is %lu\n", FSACountFree(fsa));

    free(malloced);
}

void TestFSAAlloc()
{

    WrapperFSAAlloc(12, 3);
    WrapperFSAAlloc(3, 4);
    WrapperFSAAlloc(16, 2);
    WrapperFSAAlloc(29, 4);

    WrapperFSAFree();

}
