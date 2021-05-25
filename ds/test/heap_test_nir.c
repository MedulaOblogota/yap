#include <stdio.h>

#include "heap.h"
#include "test.h"

#define TEST_SIZE (7)

static int IntCmp(const void *data1, const void *data2);
static int IsSameInt(const void *data1, const void *data2);
TestResult PushTest();
TestResult PopTest();
TestResult RemoveTest();

int main ()
{
    RUN_TEST(PushTest);
    RUN_TEST(PopTest);
    RUN_TEST(RemoveTest);

    return (0);
}

TestResult PushTest()
{
    size_t i = 0;
    heap_t *new_heap = HeapCreate(IntCmp);
    int test_data[] = {100, 50, 25, 12, 6, 3 , 1};
    int test_data2[] = {5 ,9 ,10 ,4 ,7 ,13, 3};

    for (i = 0; i < TEST_SIZE; ++i)
    {
        HeapPush(new_heap, test_data + i);
        REQUIRE(HeapPeek(new_heap) == test_data + i);
        REQUIRE(HeapSize(new_heap) == i + 1);
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
        HeapPush(new_heap, test_data2 + i);
        REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE - 1);
        REQUIRE(HeapSize(new_heap) == i + TEST_SIZE + 1);
    }

    HeapDestroy(new_heap);

    return (TEST_PASS);
}

TestResult PopTest()
{
    size_t i = 0;
    heap_t *new_heap = HeapCreate(IntCmp);
    int test_data[] = {100, 50, 25, 12, 6, 3 , 1};

    for (i = 0; i < TEST_SIZE; ++i)
    {
        HeapPush(new_heap, test_data + i);
        REQUIRE(HeapPeek(new_heap) == test_data + i);
        REQUIRE(HeapSize(new_heap) == i + 1);
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
		if (HeapPeek(new_heap) != NULL)
		{
			printf("HeapPeek(new_heap)=%d\n", *(int *)HeapPeek(new_heap));
		}
		else
		{
			printf("HeapPeek(new_heap)=NULL\n");
		}
		printf("(test_data + TEST_SIZE - i -1)=%d\n", *(test_data + TEST_SIZE - i -1));
        REQUIRE(HeapPeek(new_heap) == (test_data + TEST_SIZE - i -1));
        HeapPop(new_heap);
        REQUIRE(HeapSize(new_heap) == TEST_SIZE - i - 1);
    }

    REQUIRE(HeapIsEmpty(new_heap));

    HeapDestroy(new_heap);

    return (TEST_PASS);
}

TestResult RemoveTest()
{
    size_t i = 0;
    heap_t *new_heap = HeapCreate(IntCmp);
    int test_data[] = {100, 50, 25, 12, 6, 3 , 1};

    for (i = 0; i < TEST_SIZE; ++i)
    {
        HeapPush(new_heap, test_data + i);
        REQUIRE(HeapPeek(new_heap) == test_data + i);
        REQUIRE(HeapSize(new_heap) == i + 1);
    }

    REQUIRE(test_data == HeapRemove(new_heap ,test_data, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE -1);
    REQUIRE((test_data + 3) == HeapRemove(new_heap ,test_data + 3, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE -1);
    REQUIRE((test_data + 2) == HeapRemove(new_heap ,test_data + 2, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE -1);
    REQUIRE((test_data + TEST_SIZE -1) ==
                    HeapRemove(new_heap ,test_data + TEST_SIZE -1, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE - 2);
    REQUIRE((test_data + TEST_SIZE -2)
                == HeapRemove(new_heap ,test_data + TEST_SIZE -2, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE - 3);
    REQUIRE((test_data + 1) == HeapRemove(new_heap ,test_data + 1, IsSameInt));
    REQUIRE(HeapPeek(new_heap) == test_data + TEST_SIZE - 3);
    REQUIRE((test_data + TEST_SIZE - 3) ==
                    HeapRemove(new_heap ,test_data + TEST_SIZE - 3, IsSameInt));
    REQUIRE(NULL == HeapRemove(new_heap ,test_data + TEST_SIZE - 3, IsSameInt));

    REQUIRE(HeapIsEmpty(new_heap));

    HeapDestroy(new_heap);

    return (TEST_PASS);
}

static int IntCmp(const void *data1, const void *data2)
{
    return(*(int *)data1 - *(int *)data2);
}

static int IsSameInt(const void *data1, const void *data2)
{
    return(*(int *)data1 == *(int *)data2);
}
