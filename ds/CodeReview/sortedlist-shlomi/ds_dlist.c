#include <stdlib.h>
#include <assert.h>

#include "dlist.h"

typedef struct dlnode dlnode_t;

static dlist_iter_t DListLastNode(const dlist_t *dlist);
static dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data);

struct dlnode
{
    dlnode_t *prev;
    dlnode_t *next;
    void *data;
};

struct dlist_s
{
    dlnode_t *head;
    dlnode_t *tail;
};

dlist_t *DListCreate()
{
    dlist_t *list_ptr = malloc(sizeof(dlist_t));
    if (NULL == list_ptr)
    {
        return (NULL);
    }

    list_ptr->head = malloc(sizeof(dlnode_t));
    if (NULL == list_ptr->head)
    {
        free(list_ptr);
        return (NULL);
    }

    list_ptr->tail = malloc(sizeof(dlnode_t));
    if (NULL == list_ptr->head)
    {
        free(list_ptr->head);
        free(list_ptr);
        return (NULL);
    }

    list_ptr->head->next = list_ptr->tail;
    list_ptr->tail->prev = list_ptr->head;

    list_ptr->tail->data = (dlist_iter_t)0xdeadbeef;
    list_ptr->head->data = (dlist_iter_t)0xdeadbeef;

    return (list_ptr);
}


void DListDestroy(dlist_t *dlist)
{
    dlnode_t *node_destroy = NULL;

    assert(NULL != dlist);

    while (dlist->head != dlist->tail)
    {
        node_destroy = dlist->head;
        dlist->head = dlist->head->next;
        free(node_destroy);
    }

    free(dlist->tail);
    free(dlist);

    return;
}


size_t DListSize(const dlist_t *dlist)
{
    size_t counter = 0;
    dlnode_t *cur_node = NULL;

    assert(NULL != dlist);

    cur_node = dlist->head->next;

    while (dlist->tail != cur_node)
    {
        ++counter;
        cur_node = cur_node->next;
    }

    return (counter);
}


int DListIsEmpty(const dlist_t *dlist)
{
    assert(NULL != dlist);

    return ((size_t)dlist->head->next == (size_t)dlist->tail);
}


dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
    assert(NULL != dlist);

    return (DListInsert(dlist, (dlist_iter_t)DListBegin(dlist), data));
}


dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
    dlist_iter_t end = DListLastNode(dlist);
    if ((dlnode_t*)end == dlist->tail)
    {
        end = (dlist_iter_t)dlist->head;
    }

    return (DListInsertAfter(dlist, end, data));
}

void *DListPopFront(dlist_t *dlist)
{
    void *ret = dlist->head->next->data;

    if (DListIsEmpty(dlist))
    {
        return (NULL);
    }

    assert(NULL != dlist);

    DListRemove((dlist_iter_t)dlist->head->next);

    return (ret);
}

void *DListPopBack(dlist_t *dlist)
{
    void *ret = dlist->tail->prev->data;

    if (DListIsEmpty(dlist))
    {
        return (NULL);
    }

    assert(NULL != dlist);

    DListRemove((dlist_iter_t)dlist->tail->prev);

    return (ret);
}

int DListForEach(dlist_iter_t begin, dlist_iter_t end,
                 int (*do_func)(void *list_data, void *param),
                 void *param)
{
    dlnode_t *runner_node = (dlnode_t*)begin;
    dlnode_t *end_node = ((dlnode_t*)end);
    int status = 0;

    assert(NULL != begin);
    assert(NULL != end);

    if (runner_node != end_node)
    {
        status = do_func(runner_node->data, param);
    }

    while ((runner_node != end_node) && (0 == status))
    {
        runner_node = runner_node->next;
        status = do_func(runner_node->data, param);
    }

    return (status);
}

dlist_iter_t DListFind(dlist_iter_t begin, dlist_iter_t end,
                       int(*is_match)(const void *list_data, const void *param),
                       const void *param)
{
    dlnode_t *runner_node = (dlnode_t*)begin;
    dlnode_t *end_node = (dlnode_t*)end;
    int status = 1;

    assert(NULL != begin);
    assert(NULL != end);
    assert(NULL != is_match);

    if (runner_node != end_node)
    {
        status = is_match(runner_node->data, param);
    }

    while ((runner_node != end_node) && (0 == status))
    {
        runner_node = runner_node->next;
        status = is_match(runner_node->data, param);
    }

    if (1 == status)
    {
        return ((dlist_iter_t)(runner_node));
    }

    return ((dlist_iter_t)end);
}

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != where);

    ((dlnode_t *)from)->prev->next = ((dlnode_t *)to)->next;
    ((dlnode_t *)to)->next->prev = ((dlnode_t *)from)->prev;

    ((dlnode_t *)from)->prev = ((dlnode_t *)where)->prev;
    ((dlnode_t *)to)->next = (dlnode_t *)where;

    ((dlnode_t *)where)->prev->next = (dlnode_t *)from;
    ((dlnode_t *)where)->prev = (dlnode_t *)to;

    return (to);
}

void *DListGetData(const dlist_iter_t iter)
{
    assert(NULL != iter);

    return ((dlist_iter_t)((dlnode_t*)iter)->data);
}

dlist_iter_t DListBegin(const dlist_t *dlist)
{
    assert(NULL != dlist);

    return ((dlist_iter_t)(dlist->head->next));
}

dlist_iter_t DListEnd(const dlist_t *dlist)
{
    return ((dlist_iter_t)dlist->tail);
}

dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t iter, void *data)
{
    dlnode_t *new_node = malloc(sizeof(dlnode_t));
    if (NULL == new_node)
    {
        return ((dlist_iter_t)dlist->tail);
    }

    assert(NULL != iter);
    assert(NULL != dlist);

    new_node->data = data;
    new_node->next = (dlnode_t*)iter;
    new_node->prev = ((dlnode_t*)iter)->prev;

    ((dlnode_t*)iter)->prev->next = new_node;
    ((dlnode_t*)iter)->prev = new_node;

    return ((dlist_iter_t)new_node);
}

static dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data)
{
    assert(NULL != iter);
    assert(NULL != dlist);

    return (DListInsert(dlist, (dlist_iter_t)((dlnode_t*)iter)->next, data));
}

dlist_iter_t DListRemove(dlist_iter_t iter)
{
    dlnode_t *to_free = (dlnode_t*)iter;
    dlnode_t *ret = NULL;

    assert(NULL != iter);

    ret = to_free->next;
    if (ret == NULL)
    {
        return ((dlist_iter_t)to_free);
    }

    ret->prev = to_free->prev;
    to_free->prev->next = ret;

    free(to_free);

    return ((dlist_iter_t)ret);
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
    if (NULL == (dlist_iter_t)((dlnode_t*)iter)->next)
    {
        return (iter);
    }

    return ((dlist_iter_t)((dlnode_t*)iter)->next);
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
    if (NULL == ((dlnode_t*)iter)->prev)
    {
        return ((dlist_iter_t)((dlnode_t*)iter)->next);
    }

    return ((dlist_iter_t)((dlnode_t*)iter)->prev);
}

int DListIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);

    return ((size_t)iter1 == (size_t)iter2);
}

static dlist_iter_t DListLastNode(const dlist_t *dlist)
{
    if (DListIsEmpty(dlist))
    {
        return ((dlist_iter_t)dlist->tail);
    }

    return ((dlist_iter_t)(dlist->tail->prev));
}
