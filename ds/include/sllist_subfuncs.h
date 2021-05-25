#ifndef SUB_FUNCS
#define SUB_FUNCS

#include <stdio.h>
#include "sllist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

sll_node_t *InitList(sll_node_t *node, void *array,
size_t size_of_array, size_t size_of_element)
{
    int i = 0;
    array = (char *)array + (size_of_array-1) * size_of_element;

    node = SLLCreateNode(array, NULL);
    array = (char *)array - size_of_element;

    for (i = size_of_array - 2; i >= 0; --i)
    {
        node = SLLCreateNode(array, node);
        array = (char *)array - size_of_element;
    }
    return node;
}

sll_node_t *MoveNode(sll_node_t *node, size_t num)
{
    while (NULL != node && num > 0)
    {
        node = node->next;
    }
    --num;

    return node;
}

void PrintList(sll_node_t *node)
{
    assert (NULL != node);
    while (NULL != node)
    {
        printf("%d\n", *(int *)node->data);
        node = node->next;
    }
}

void PrintResult(char *name_of_test, int *index_test, int result)
 {
    if (result)
    {
        printf(GRN "%s test %d success\n" RESET, name_of_test, *index_test);
    }
    else
    {
        printf(RED "%s test %d fail\n" RESET, name_of_test, *index_test);
    }
    ++*index_test;
}

status_t CompIntFunc(void *data1, void *data2)
{
    if (*(int *)data1 == *(int *)data2)
    {
        return  STOP;
    }
    else
    {
        return CONTINUE;
    }
}

status_t CmdIntFunc(sll_node_t *node, void *data)
{
    (void)data;

    printf("%d\n", *(int *)node->data);

    return  CONTINUE;

}

#endif
