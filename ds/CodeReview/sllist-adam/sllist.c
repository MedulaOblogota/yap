/******************************************************************
* Author: Adam Blau                                               *
*                                                                 *
* Reviewer: Mr. Roy Yablonka                                      *
*                                                                 *
* Version: S                                                      *
*                                                                 *
* Description: sllist                                             *
******************************************************************/

#include "sllist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/************************************************************************/

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
    sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));
    if (NULL == node)
    {
        return (NULL);
    }

    assert(NULL != data);

    node->data = data;
    node->next = next;

    return (node);
}

/************************************************************************/

void SLLFreeAll(sll_node_t *node)
{
    sll_node_t *ptr = NULL;

    if (0 == SLLHasLoop(node))
    {
        while (NULL != node)
        {
            ptr = node->next;
            node->next = NULL;
            free(node);
            node = ptr;
        }
    }

    return;
}

/************************************************************************/

sll_node_t *SLLInsert(sll_node_t *node, sll_node_t *new_node)
{
    void *temp = NULL;

    assert(NULL != node);
    assert(NULL != new_node);

    new_node->next = node->next;
    node->next = new_node;

    temp = node->data;
    node->data = new_node->data;
    new_node->data = temp;

    return (node);
}

/************************************************************************/

sll_node_t *SLLInsertAfter(sll_node_t *node, sll_node_t *new_node)
{
    assert(NULL != node);
    assert(NULL != new_node);

    new_node->next = node->next;
    node->next = new_node;

    return(new_node);
}

/************************************************************************/

sll_node_t *SLLRemove(sll_node_t *node)
{
    void *temp = NULL;

    sll_node_t *removed_node = NULL;

    assert(NULL != node);
    assert(NULL != node->next);

    removed_node = node->next;
    temp = node->data;
    node->data = (node->next)->data;
    (node->next)->data = temp;
    node->next = (node->next)->next;
    removed_node->next = NULL;

    return (removed_node);
}

/************************************************************************/

sll_node_t *SLLRemoveAfter(sll_node_t *node)
{
    sll_node_t *ptr = NULL;

    assert(NULL != node);
    assert(NULL != node->next);

    ptr = node->next;
    node->next = (node->next)->next;
    ptr->next = NULL;

    return (ptr);
}

/************************************************************************/

size_t SLLCount(const sll_node_t *node)
{
    size_t counter = 0;

    assert(NULL != node);

    if (0 != SLLHasLoop(node))
    {
        return (counter);
    }

    while ( NULL != node)
    {
        ++counter;
        node = node->next;
    }

    return(counter);
}

/************************************************************************/

sll_node_t *SLLFind(sll_node_t *node, comp_func_t comp, void *arg)
{
    while ((NULL != node) && ((CONTINUE) == comp(arg, node->data)))
    {
        node = node->next;
    }

    return (node);
}

/************************************************************************/

int SLLHasLoop(const sll_node_t *node)
{
    sll_node_t *slow_ptr = (sll_node_t *)node;
    sll_node_t *fast_ptr = (sll_node_t *)node;

    assert(NULL != node);

    fast_ptr = node->next;

    while ((NULL != fast_ptr) && (NULL != fast_ptr->next) && (fast_ptr != slow_ptr))
    {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next;
        if (NULL == fast_ptr->next)
        {
            break;
        }

        fast_ptr = fast_ptr->next;
    }

    return (fast_ptr == slow_ptr);
}

/************************************************************************/

sll_node_t *SLLFindIntersection(sll_node_t *list1, sll_node_t *list2)
{
    sll_node_t *longer = list1;
    sll_node_t *shorter = list2;
    long list_len1 = 0;
    long list_len2 = 0;
    long diff = 0;

    assert(NULL != list1);
    assert(NULL != list2);

    list_len1 = SLLCount(list1);
    list_len2 = SLLCount(list2);

    if ((0 != SLLHasLoop(list1)) && (0 != SLLHasLoop(list2)))
    {
        return (NULL);
    }

    if (list_len2 > list_len1)
    {
        longer = list2;
        shorter = list1;
    }

    diff = ((list_len2 - list_len1) > 0 ? list_len2 - list_len1 :
                                                list_len1 - list_len2);
    while (diff > 0)
    {
        longer = longer->next;
        --diff;
    }

    while ((NULL != longer) && (longer != shorter))
    {
        longer = longer->next;
        shorter = shorter->next;
    }

    return (longer);
}

/************************************************************************/

sll_node_t *SLLFlip(sll_node_t *node)
{
    sll_node_t *prev = NULL;
    sll_node_t *curr = NULL;

    sll_node_t *next = NULL;

    assert(NULL != node);

    prev = node;
    curr = node;
    next = node->next;

    if (0 != SLLHasLoop(node))
    {
        return (NULL);
    }

    curr->next = NULL;

    while (NULL != next)
    {
        curr = next;
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }

    return (prev);
}

/************************************************************************/

status_t SLLForEach(sll_node_t *node, cmd_func_t cmd, void *arg, size_t num)
{
    assert(NULL != node);
    assert(NULL != node);
    assert(NULL != arg);

    if (0 != SLLHasLoop(node))
    {
        return (STOP);
    }

    while ((0 != num) && (NULL != node))
    {
        if (STOP == cmd(node, arg))
        {
            return (STOP);
        }

        else
        {
            --num;
            node = node->next;
        }
    }

    return (CONTINUE);
}

/************************************************************************/
