#include <stddef.h>

#include "tests_adi.h"
#include "heap.h"

#define PARENT(index) ((index - 1) * 2)

void TestHeapCreate();
void TestHeapPush();
void TestHeapPush();
void TestHeapPop();
void TestHeapRemove();

int main()
{
    TestHeapCreate();
    TestHeapPush();
    TestHeapPop();
    TestHeapRemove();

    return (0);
}

static int CmpIntFunc(const void *data1, const void *data2);
static int IsMatchFunc(const void *data1, const void *data2);

void TestHeapCreate()
{
    int heap_was_created = 0;
    char *creation_msg = "HeapCreate!!";
    char *size_msg = "HeapSize!!";
    char *is_empty_msg = "HeapIsEmpty!!";
    heap_t *heap = HeapCreate(CmpIntFunc);

    puts(CYN "\n***************** Testing HeapCreate *****************\n" RESET);

    heap_was_created = Check(NULL != heap, creation_msg, 0);
    Check(ResCmp(0, HeapSize(heap)), size_msg, 1);
    Check(ResCmp(1, HeapIsEmpty(heap)), is_empty_msg, 1);

    if (heap_was_created)
    {
        HeapDestroy(heap);
    }

    puts(CYN "\n******************************************************\n" RESET);
}

void TestHeapPush()
{
    int heap_was_created = 0;
    char *creation_msg = "HeapCreate!!";
    char *push_msg = "HeapPush!!";
    char *switch_root_msg = "SwitchRoot!!";
    heap_t *heap =  HeapCreate(CmpIntFunc);
    int arr[] = {2, 3, 4, 5, 6, 7, 8, 1};
    size_t arr_size = 8;
    int insert_status = 1;

    puts(CYN "\n****************** Testing HeapPush ******************\n" RESET);

    heap_was_created = Check(NULL != heap, creation_msg, 1);

    if (heap_was_created)
    {
        size_t i = 0;

        for (; (i < arr_size) && (1 == insert_status); ++i)
        {
            insert_status = HeapPush(heap, &arr[i]);
        }

        Check(ResCmp(arr_size, HeapSize(heap)), push_msg, 0);
        Check(ResCmp(1, **(int **)HeapPeek(heap)), switch_root_msg, 1);

        HeapDestroy(heap);
    }

    puts(CYN "\n******************************************************\n" RESET);
}

void TestHeapPop()
{
    size_t arr_size = 7;
    int insert_status = 1;
    int heap_was_created = 0;
    char *pop_msg = "HeapPop!!";
    char *push_msg = "HeapPush!!";
    char *creation_msg = "HeapCreate!!";
    char *switch_root_msg = "SwitchRoot!!";
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    heap_t *heap =  HeapCreate(CmpIntFunc);

    puts(CYN "\n****************** Testing HeapPop ******************\n" RESET);

    heap_was_created = Check(NULL != heap, creation_msg, 1);

    if (heap_was_created)
    {
        size_t i = 0;

        for (; (i < arr_size) && (1 == insert_status); ++i)
        {
            insert_status = HeapPush(heap, &arr[i]);
        }

        Check(ResCmp(arr_size, HeapSize(heap)), push_msg, 1);

        HeapPop(heap);

        Check(ResCmp(arr_size - 1, HeapSize(heap)), pop_msg, 0);
        Check(ResCmp(2, **(int **)HeapPeek(heap)), switch_root_msg, 1);

        HeapDestroy(heap);
    }

    puts(CYN "\n******************************************************\n" RESET);
}

void TestHeapRemove()
{
    size_t arr_size = 7;
    int insert_status = 1;
    int heap_was_created = 0;
    char *size_msg = "HeapSize!!";
    char *push_msg = "HeapPush!!";
    char *remove_msg = "HeapRemove!!";
    char *creation_msg = "HeapCreate!!";
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    heap_t *heap =  HeapCreate(CmpIntFunc);

    puts(CYN "\n***************** Testing HeapRemove *****************\n" RESET);

    heap_was_created = Check(NULL != heap, creation_msg, 1);

    if (heap_was_created)
    {
        size_t i = 0;
        void *removed_data1 = NULL;
        void *removed_data2 = NULL;
        void *removed_data3 = NULL;

        for (; (i < arr_size) && (1 == insert_status); ++i)
        {
            insert_status = HeapPush(heap, &arr[i]);
        }

        Check(ResCmp(arr_size, HeapSize(heap)), push_msg, 1);

        removed_data1 = HeapRemove(heap, &arr[6], IsMatchFunc);
        Check(ResCmp(arr_size - 1, HeapSize(heap)), size_msg, 1);
        Check(ResCmp(arr[6], *(int *)removed_data1), remove_msg, 1);

        removed_data2 = HeapRemove(heap, &arr[1], IsMatchFunc);
        Check(ResCmp(arr_size - 2, HeapSize(heap)), size_msg, 1);
        Check(ResCmp(arr[1], *(int *)removed_data2), remove_msg, 1);

        removed_data3 = HeapRemove(heap, &arr[0], IsMatchFunc);
        Check(ResCmp(arr_size - 3, HeapSize(heap)), size_msg, 1);
        Check(ResCmp(arr[0], *(int *)removed_data3), remove_msg, 1);

        Check(ResCmp(arr[2], **(int **)HeapPeek(heap)), remove_msg, 0);

        HeapDestroy(heap);
    }

    puts(CYN "\n******************************************************\n" RESET);
}

static int CmpIntFunc(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

static int IsMatchFunc(const void *data1, const void *data2)
{
    return (*(int *)data1 == **(int **)data2);
}
