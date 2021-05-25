#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "dlist.h"

typedef struct dlist_node_s node_t;

struct dlist_s {
    node_t *head;
    node_t *tail;
};

struct dlist_node_s {
    node_t *prev;
    void *data;
    node_t *next;
};

static dlist_iter_t FindTail(dlist_iter_t iter)
{
    node_t *node = iter;

    while (NULL != node->next)
    {
        node = node->next;
    }

    return (node);
}

static dlist_iter_t CreateNode(dlist_iter_t prev, const void *data, dlist_iter_t next)
{
    dlist_iter_t node = malloc(sizeof(node_t));

    if (NULL == node)
    {
        return (NULL);
    }

    node->data = (void *)data;
    node->prev = prev;
    node->next = next;

    return (node);
}

static dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t iter, const void *data)
{
    dlist_iter_t item = iter;
    dlist_iter_t new_item = NULL;

    assert(NULL != dlist);
    assert(NULL != iter);

    if (item == dlist->tail)
    {
        return (dlist->tail);
    }

    new_item = CreateNode(item, data, item->next);

    if (NULL == new_item)
    {
        return (dlist->tail);
    }

    item->next->prev = new_item;
    item->next = new_item;

    return (new_item);
}

dlist_t *DListCreate()
{
    dlist_t *dlist = malloc(sizeof(node_t));
    char *head_data = "ThisIsHead";
    char *tail_data = "ThisIsTail";

    if (NULL == dlist)
    {
        return (NULL);
    }

    dlist->head = CreateNode(NULL, (void *)head_data, NULL);

    if (NULL == dlist->head)
    {
        free(dlist);   dlist = NULL;
        return (NULL);
    }

    dlist->tail = CreateNode(dlist->head, (void *)tail_data, NULL);

    if (NULL == dlist->tail)
    {
        free(dlist->head); dlist->head = NULL;
        free(dlist);        dlist = NULL;
        return (NULL);
    }

    dlist->head->next = dlist->tail;

    return (dlist);
}

void DListDestroy(dlist_t *dlist)
{
    dlist_iter_t runner = NULL;

    assert(NULL != dlist);

    runner = dlist->head->next;

    while (!DListIsEmpty(dlist))
    {
        runner = DListRemove(runner);

    }

    free(dlist->head);      dlist->head = NULL;
    free(dlist->tail);      dlist->tail = NULL;
    free(dlist);            dlist = NULL;
}

size_t DListSize(const dlist_t *dlist)
{
    size_t counter = 0;
    dlist_iter_t runner = NULL;

    assert(NULL != dlist);

    runner = dlist->head->next;

    while ((runner != dlist->tail))
    {
		if (runner->next == NULL)
		{
			printf("null, %s\n", (char *)runner->data);
		}
        ++counter;
        runner = runner->next;
    }

    return (counter);
}

int DListIsEmpty(const dlist_t *dlist)
{
    assert(NULL != dlist);

    return ((dlist->head->next == dlist->tail) && (dlist->tail->prev == dlist->head));
}

dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
    return (DlistInsertAfter(dlist, dlist->head, data));
}

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
    return (DListInsert(dlist, dlist->tail, data));
}

void *DListPopFront(dlist_t *dlist)
{
    void *data = NULL;

    assert(NULL != dlist);

    if (!DListIsEmpty(dlist))
    {
        data = DListGetData(DListBegin(dlist));
        DListRemove(DListBegin(dlist));
    }

    return data;
}

void *DListPopBack(dlist_t *dlist)
{
    void *data = NULL;


    assert(NULL != dlist);

    if (!DListIsEmpty(dlist))
    {
        data = DListGetData(DListPrev(DListEnd(dlist)));
        DListRemove(dlist->tail->prev);
    }

    return data;
}

int DListForEach(dlist_iter_t begin, dlist_iter_t end, cmd_func_t cmd, void *arg)
{
    dlist_iter_t begin_node = begin;
    dlist_iter_t end_node = end;

    assert(NULL != begin);
    assert(NULL != end);

    if (begin_node == end_node)
    {
        return (1);
    }

    while ((begin_node->prev != end_node) && (cmd(begin_node->data, arg) == 0))
    {
        begin_node = begin_node->next;
    }

    if (begin_node->prev == end_node)
    {
        return (0);
    }
    else
    {
        return(1);
    }
}

dlist_iter_t DListFind(dlist_iter_t begin, dlist_iter_t end, comp_func_t comp, const void *param)
{
    dlist_iter_t begin_node = begin;
    dlist_iter_t end_node = end;

    assert(NULL != begin);
    assert(NULL != end);

    while (begin_node != end_node)
    {
        if (comp(begin_node->data, param) == 1)
        {
            return (begin_node);
        }
        begin_node = begin_node->next;
    }

    return (end_node);
}

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
    dlist_iter_t begin_node = from;
    dlist_iter_t end_node = to;
    dlist_iter_t where_node = where;

    assert(NULL != where);
    assert(NULL != from);
    assert(NULL != to);
/*    assert(NULL != to->next);*/


    begin_node->prev->next = end_node->next;
    end_node->next->prev = begin_node->prev;

    end_node->next = where_node;
    begin_node->prev = where_node->prev;

    where_node->prev->next = begin_node;
    where_node->prev = end_node;

    return (end_node);
}

void *DListGetData(const dlist_iter_t iter)
{
    dlist_iter_t node = iter;
    char *head_data = "ThisIsHead";

    assert(NULL != iter);

    if (((char *)node->data != head_data))
    {
        return (node->data);
    }
    else
    {
        return (NULL);
    }
}

dlist_iter_t DListBegin(const dlist_t *dlist)
{
    assert(NULL != dlist);

    return (dlist->head->next);
}

dlist_iter_t DListEnd(const dlist_t *dlist)
{
    assert(NULL != dlist);

    return (dlist->tail);
}

dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t iter, void *data)
{
    dlist_iter_t item = iter;

    return(DlistInsertAfter(dlist, item->prev, data));
}



dlist_iter_t DListRemove(dlist_iter_t iter)
{
    dlist_iter_t node_to_erase = (node_t *)iter;
    dlist_iter_t next_node = NULL;
    dlist_iter_t tail = FindTail(iter);

    assert(NULL != iter);

    if (iter != tail)
    {
        next_node = node_to_erase->next;

        node_to_erase->prev->next = node_to_erase->next;
        node_to_erase->next->prev = node_to_erase->prev;

        node_to_erase->next = NULL;
        node_to_erase->prev = NULL;

        free(node_to_erase); node_to_erase = NULL;
    }
    else
    {
        next_node = tail;
    }

    return (next_node);
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
    dlist_iter_t current_node = iter;

    assert(NULL != iter);

    if (NULL == current_node->next)
    {
        return (current_node);
    }

    return (current_node->next);
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
    dlist_iter_t current_node = iter;

    assert(NULL != iter);

    if (NULL == current_node->prev->prev)
    {
        return (current_node);
    }

    return (current_node->prev);
}

int DListIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);

    return (iter1 == iter2);
}
