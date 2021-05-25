/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Nir Shidlansik
Version:	Approved
Title:		Singley Linked List Functions File
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sllist.h"


/***************************************************************
* Allocates the memory for a Node                              *
****************************************************************/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
    sll_node_t *sll_node = (sll_node_t *)malloc(sizeof(sll_node_t));

    if (NULL == sll_node)
    {
        return (NULL);
    }

    sll_node->data = data;
    sll_node->next = next;

    return (sll_node);
}

/***************************************************************
* Removes the current Node by unlinking it from the next Node  *
* and links the previous node with the next one                *
****************************************************************/
sll_node_t *SLLRemove(sll_node_t *node)
{
    sll_node_t *next_node = NULL;
    void *data = NULL;

    assert(NULL != node);

	next_node = node->next;
	data = node->data;

    if (NULL != next_node)
    {
        SLLRemoveAfter(node);
        node->data = next_node->data;
    }
    next_node->next = NULL;
    next_node->data = data;
    return (next_node);
}

/***************************************************************
* Removes the current Node by unlinking it from the next Node  *
* and links the previous node with the next one                *
****************************************************************/
sll_node_t *SLLRemoveAfter(sll_node_t *node)
{
    sll_node_t *next_node = NULL;

    assert(NULL != node);

    next_node = node->next;
    if (NULL == next_node)
    {
        return (NULL);
    }
    node->next = node->next->next;
    next_node->next = NULL;

    return(next_node);
}

/***************************************************************
* Releases the memory allocted to the nodes following the given*
* node, including the current one.                             *
****************************************************************/
void SLLFreeAll(sll_node_t *node)
{
    sll_node_t *temp = NULL;

    assert(NULL != node);

    if (0 == SLLHasLoop(node))
    {
        while (NULL != node)
        {
            temp = node->next;
            node->next = NULL;
            free(node);
            node = temp;
        }
    }
}

/***************************************************************
* Inserts a node before the current node and connects it to the*
* rest of the SLLink                                           *
****************************************************************/
sll_node_t *SLLInsert(sll_node_t *node, sll_node_t *new_node)
{
    void *temp_data = NULL;

    assert(NULL != node);
    assert(NULL != new_node);

    SLLInsertAfter(node, new_node);

    temp_data = node->next->data;
    node->next->data = node->data;
    node->data = temp_data;

    return(node);
}

/***************************************************************
* Inserts a node after the current node and connects it to the *
* rest of the SLLink.                                          *
****************************************************************/
sll_node_t *SLLInsertAfter(sll_node_t *node, sll_node_t *new_node)
{
    sll_node_t *temp_node = NULL;

    assert(NULL != node);
    assert(NULL != new_node);

    temp_node = node->next;
    node->next = new_node;
    new_node->next = temp_node;

    return(temp_node);
}

/***************************************************************
* Counts how many nodes there from the current node until the  *
* last node.                                                   *
****************************************************************/
size_t SLLCount(const sll_node_t *node)
{
    size_t counter = 0;

    assert(NULL != node);

    if (1 != SLLHasLoop(node))
    {
        while (NULL != node)
        {
            node = node->next;
            ++counter;
        }
    }

    return (counter);
}

/***************************************************************
* Finds a node containing the wanted element, returns a pointer*
* to said node.                                                *
****************************************************************/
sll_node_t *SLLFind(sll_node_t *node, comp_func_t comp, void *arg)
{
    assert(NULL != node);
    assert(!SLLHasLoop(node));

    while (NULL != node)
    {
        if (comp(arg, node->data) == 0)
        {
            return (node);
        }
        node = node->next;
    }

    return NULL;
}

/***************************************************************
* A boolean function. If the linked list contains a loop,      *
* SLLFind will return TRUE(1). Otherwise, it returns FALSE(0). *
****************************************************************/
int SLLHasLoop(const sll_node_t *node)
{
    sll_node_t *slow = (sll_node_t *)node;
    sll_node_t *fast = (sll_node_t *)node->next;

    assert(NULL != node);

    if (NULL == fast)
    {
        return (0);
    }

    while ((NULL != fast) && (slow != fast))
    {
        slow = slow->next;
        fast = fast->next;
        if (NULL != fast)
        {
            fast = fast->next;
        }
    }

    return (slow == fast);
}

/***************************************************************
* Travereses two lists and returns a node that is the          *
* intersection between list1 and list2. If they do not         *
* intersect, return NULL.                                      *
****************************************************************/
sll_node_t *SLLFindIntersection(sll_node_t *list1, sll_node_t *list2)
{
    size_t length1 = 0;
    size_t length2 = 0;

    assert(NULL != list1);
    assert(NULL != list2);

    length1 = SLLCount(list1);
    length2 = SLLCount(list2);

    while (length1 != length2)
    {
        if (length1 > length2)
        {
            list1 = list1->next;
            --length1;
        }
        else
        {
            list2 = list2->next;
            --length2;
        }
    }

    while (NULL != list1)
    {
        if (list1 != list2)
        {
            list1 = list1->next;
            list2 = list2->next;
        }
        else
        {
            break;
        }
    }

    return (list1);
}

/***************************************************************
* Executes a command given by the user with an argument        *
* The command will execute from the given node until the end   *
****************************************************************/
int SLLForEach(sll_node_t *node, cmd_func_t cmd, void *arg)
{
    assert(NULL != node);
    assert(!SLLHasLoop(node));

    while (NULL != node)
    {
        int status = cmd(node->data, arg);

        if ((status == 1))
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

/***************************************************************
* Flips the direction of the SLList from the end to the given  *
* node, which will mark the end of the list.                   *
****************************************************************/
sll_node_t *SLLFlip(sll_node_t *node)
{
    sll_node_t *first = NULL;
    sll_node_t *second = NULL;
    sll_node_t *third = NULL;

    assert(NULL != node);
    assert(!SLLHasLoop(node));

    first = NULL;

    if (NULL != node)
    {
        second = node;
    }
    if (NULL != node->next)
    {
        third = node->next;
    }

    while (NULL != second)
    {
        second->next = first;
        first = second;
        second = third;
        if (NULL != third)
        {
            if(NULL != third->next)
            {
                third = third->next;
            }
            else
            {
                third = NULL;
            }
        }
    }

    return (first);
}
