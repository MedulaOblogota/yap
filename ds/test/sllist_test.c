#include <stdio.h>
#include "sllist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"


void TestCreateAndFreeAll();
void TestRemove();
void TestRemoveAfter();
void TestInsert();
void TestInsertAfter();
void TestCount();
void TestFind();
void TestHasLoop();
void TestFindIntersection();
void TestForEach();
void TestFlip();

int main()
{
    TestCreateAndFreeAll();
    TestRemove();
    TestRemoveAfter();

    TestInsert();
    TestInsertAfter();
    TestCount();


    TestHasLoop();
    TestFindIntersection();

    TestFlip();
    TestFind();
    TestForEach();

    return (0);
}

static sll_node_t *CreateList(size_t amount_of_items)
{
    size_t value = 1;
    sll_node_t *head = SLLCreateNode((void *)value, NULL);
    sll_node_t *node = head;
    sll_node_t *new_node = NULL;

    while (amount_of_items - 1 > 0)
    {
        ++value;
        new_node = SLLCreateNode((void *)value, NULL);
        node->next = new_node;
        node = new_node;
        --amount_of_items;
    }

    return (head);
}
/*
static void PrintIntList(sll_node_t *node)
{
    while (NULL != node)
    {
        printf("current address: %lu\ncurrent data: %lu\nnext address: %lu\n\n", (size_t)node, (size_t)node->data, (size_t)node->next);
        node = node->next;
    }
}
*/

static void *ReturnValueByIndex(sll_node_t *node, size_t index)
{
    size_t i = 0;
    for (i = 0; i < index; ++i)
    {
        node = node->next;
    }

    return (node->data);
}

void TestCreateAndFreeAll()
{
    int num = 5;
    sll_node_t *intnode = SLLCreateNode(&num, NULL);

    if (NULL != intnode)
    {
        printf(GRN "SUCCESS with SLLCreateNode!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with SLLCreateNode!!!\n" RESET);
    }

    SLLFreeAll(intnode);
}

static void WrapperCompareSizet(char *func_name, size_t data_before_remove, size_t data_after_remove)
{
    if (data_after_remove == data_before_remove)
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!\n" RESET, func_name);
    }
}

void TestRemove()
{
        sll_node_t *node = CreateList(5);
        size_t data_before_remove = (size_t)ReturnValueByIndex(node, 1);
        sll_node_t *removed_node = SLLRemove(node->next);
        size_t data_after_remove = (size_t)((removed_node)->data);

        WrapperCompareSizet("SLLRemove", data_before_remove, data_after_remove);
        SLLFreeAll(removed_node);

        data_before_remove = (size_t)ReturnValueByIndex(node, 0);
        removed_node = SLLRemove(node);
        data_after_remove = (size_t)((removed_node)->data);
        WrapperCompareSizet("SLLRemove", data_before_remove, data_after_remove);

        SLLFreeAll(node);
        SLLFreeAll(removed_node);
}

void TestRemoveAfter()
{
    sll_node_t *head = CreateList(12);
    sll_node_t *node = head;
    sll_node_t *removed_node = NULL;
    size_t i = 0;
    size_t num = 5;
    size_t data_before_remove = 0;
    size_t data_after_remove = 0;

    for (i = 0; i < num; ++i)
    {
        node = node->next;
    }

    data_before_remove = (size_t)ReturnValueByIndex(head, num + 1);
    removed_node = SLLRemoveAfter(node);
    data_after_remove = (size_t)((removed_node)->data);
    WrapperCompareSizet("SLLRemoveAfter", data_before_remove, data_after_remove);
    SLLFreeAll(removed_node);

	num = 9;
    data_before_remove = (size_t)ReturnValueByIndex(head, num + 1);
    node = head;
    for (i = 0; i < num; ++i)
    {
        node = node->next;
    }

    removed_node = SLLRemoveAfter(node);
    data_after_remove = (size_t)((removed_node)->data);
    WrapperCompareSizet("SLLRemoveAfter", data_before_remove, data_after_remove);

    SLLFreeAll(head);
    SLLFreeAll(removed_node);
}

/*TODO: rearrange function with wrapping function! */
void TestInsert()
{
    sll_node_t *head = CreateList(8);
    sll_node_t *head2 = CreateList(1);
    sll_node_t *node = head;
    size_t inserted_value = 5067;
    sll_node_t *newnode = SLLCreateNode((void *)inserted_value, NULL);
    size_t i = 0;
    size_t data_after_insert = 0;

    for (i = 0; i < 2; ++i)
    {
        node = node->next;
    }

    SLLInsert(node, newnode);
    data_after_insert = (size_t)ReturnValueByIndex(head, i);
    WrapperCompareSizet("SLLInsert", data_after_insert, inserted_value);

    newnode = SLLCreateNode((void *)inserted_value, NULL);
    SLLInsert(head, newnode);
    data_after_insert = (size_t)ReturnValueByIndex(head, 0);
    WrapperCompareSizet("SLLInsert", data_after_insert, inserted_value);

    node = head;
    for (i = 0; i < 9; ++i)
    {
        node = node->next;
    }

    newnode = SLLCreateNode((void *)inserted_value, NULL);
    SLLInsert(node, newnode);
    data_after_insert = (size_t)ReturnValueByIndex(head, 9);
    WrapperCompareSizet("SLLInsert", data_after_insert, inserted_value);

    newnode = SLLCreateNode((void *)inserted_value, NULL);
    SLLInsert(head2, newnode);
    data_after_insert = (size_t)ReturnValueByIndex(head2, 0);
    WrapperCompareSizet("SLLInsert", data_after_insert, inserted_value);

    SLLFreeAll(head);
		SLLFreeAll(head2);
}

void TestInsertAfter()
{
    sll_node_t *head = CreateList(8);
    sll_node_t *node = head;
    size_t inserted_value = 5067;
    sll_node_t *newnode = SLLCreateNode((void *)inserted_value, NULL);
    size_t i = 0;
    size_t data_after_insert = 0;

    for (i = 0; i < 2; ++i)
    {
        node = node->next;
    }

    SLLInsertAfter(node, newnode);
    data_after_insert = (size_t)ReturnValueByIndex(head, i+1);
    WrapperCompareSizet("SLLInsertAfter", data_after_insert, inserted_value);

    SLLFreeAll(head);
}

void TestCount()
{
    size_t length = 8;
    sll_node_t *head = CreateList(length);

    WrapperCompareSizet("SLLCount", length, SLLCount(head));

    SLLFreeAll(head);
}

static int CompareSizet(void *node, void *data)
{
    if ((size_t)node == (size_t)data)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void TestFind()
{
    sll_node_t *head = CreateList(9);
    size_t num = 5;

    if (SLLFind(head, CompareSizet, (void *)num) == (head->next->next->next->next))
    {
        printf(GRN "SUCCESS with SLLFind!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with SLLFind\n" RESET);
    }

    num = 17;
    if (SLLFind(head, CompareSizet, (void *)num) == NULL)
    {
        printf(GRN "SUCCESS with SLLFind!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with SLLFind\n" RESET);
    }

    SLLFreeAll(head);
}

void TestHasLoop()
{
    sll_node_t *head = CreateList(3);
    sll_node_t *node = head->next->next;
    sll_node_t *head2 = CreateList(6);
    node->next = head->next;         /*creates vlgrind error */

    WrapperCompareSizet("SLLHasLoop", 1, SLLHasLoop(head));
    WrapperCompareSizet("SLLHasLoop", 0, SLLHasLoop(head2));

    node->next = NULL;

    SLLFreeAll(head);
    SLLFreeAll(head2);
}

static sll_node_t *FindPointerToIntersection(sll_node_t *head2, sll_node_t *new_node)
{
    while ((head2->next != new_node) && (NULL != head2))
    {
        head2 = head2->next;
    }

    return (head2);
}

void TestFindIntersection()
{
    sll_node_t *head1 = CreateList(2);
    sll_node_t *head2 = CreateList(2);
    sll_node_t *node1 = head1->next;
    sll_node_t *node2 = head2->next;
    sll_node_t *intersection = NULL;
    size_t value = 4512;
    sll_node_t *new_node = SLLCreateNode((void *)value, NULL);
    sll_node_t *new_node2 = SLLCreateNode((void *)value, NULL);

    node1->next = new_node;
    node2->next = new_node;
    new_node->next = new_node2;

    if (SLLFindIntersection(head1, head2) == new_node)
    {
        printf(GRN "SUCCESS with SLLFindIntersection\n" RESET);
    }
    else
    {
        printf(RED "FAIL with SLLFindIntersection\n" RESET);
    }

    SLLFreeAll(head2);

    intersection = FindPointerToIntersection(head1, new_node);

    if (NULL != intersection)
    {
      /*  printf("entered\n");*/
        intersection->next = NULL;
        /*printf("after\n");*/
    }

    SLLFreeAll(head1);

    head2 = CreateList(4);
    head1 = CreateList(3);

    if (SLLFindIntersection(head1, head2) == NULL)
    {
        printf(GRN "SUCCESS with SLLFindIntersection\n" RESET);
    }
    else
    {
        printf(RED "FAIL with SLLFindIntersection\n" RESET);
    }

    SLLFreeAll(head1);
    SLLFreeAll(head2);
}

static int ReachValue(void *node, void *data)
{
    static size_t sum = 0;

    if (sum >= (size_t)data)
    {
        sum = 0;
    }

    sum += (size_t)(node);

    if (sum >= (size_t)data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void TestForEach()
{
    sll_node_t *node = CreateList(15);
    size_t value = 20;

    if (SLLForEach(node, ReachValue, (void *)value) == 1)
    {
        printf(GRN "SUCCESS with SLLForEach\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with SLLForEach\n" RESET);
    }

    value = 200;

    if (SLLForEach(node, ReachValue, (void *)value) == 0)
    {
        printf(GRN "SUCCESS with SLLForEach\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with SLLForEach\n" RESET);
    }

    SLLFreeAll(node);
}

void TestFlip()
{
    sll_node_t *original_node = CreateList(4);
    sll_node_t *node_runner = original_node;
    size_t arr[4] = {0};
    size_t i = 0;

    for (i = 0; i < 4; ++i)
    {
        arr[i] = (size_t)node_runner;
        node_runner = node_runner->next;
    }

  /*  for (i = 0; i < 4; ++i)
    {
        printf("%lu, ", arr[i]);
    }*/

  /*  printf("original:\n");
    PrintIntList(original_node);*/

    original_node = SLLFlip(original_node);
    node_runner = original_node;
/*
    printf("flip:\n");
    PrintIntList(original_node);*/

    for (i = 4; i >0; --i)
    {
        if ((size_t)node_runner != arr[i - 1])
        {
            printf(RED "FAILED with SLLFlip!\n" RESET);
            break;
        }
        node_runner = node_runner->next;
    }
    if (i == 0)
    {
        printf(GRN "SUCCESS with SLLFlip!\n" RESET);
    }
  /*  printf("\n");*/

    SLLFreeAll(original_node);
}
