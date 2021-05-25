#include <stdlib.h>
#include <assert.h>

#include "sorted_list.h"
#include "dlist.h"

static size_t LenBetweenIter(sorted_list_iter_t from, sorted_list_iter_t to);
static int CompIterArg(sorted_list_iter_t iter, const void *arg,
            is_before_func_t is_before, const void* param);
static sorted_list_iter_t SortedListFindIsBefore(sorted_list_iter_t from,
            sorted_list_iter_t to, is_before_func_t is_before, const void *arg);
/*static int CompArgArg(void *data, void *arg, is_before_func_t is_before);*/
static int CmpIterData(const sorted_list_iter_t iter1,
                                            const sorted_list_iter_t iter2);

struct sorted_list
{
    dlist_t *dlist;
    is_before_func_t is_before;
};

sorted_list_t *SortedListCreate(is_before_func_t is_before)
{
    sorted_list_t *list_ptr = (sorted_list_t*)malloc(sizeof(sorted_list_t));

    assert(NULL != is_before);

    if (NULL == list_ptr)
    {
        return (NULL);
    }

    list_ptr->dlist = DListCreate();
    if (NULL == list_ptr->dlist)
    {
        free(list_ptr);

        return (NULL);
    }

    list_ptr->is_before = is_before;

    return (list_ptr);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    DListDestroy(sorted_list->dlist);
    free(sorted_list);

    return;
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    return (DListSize(sorted_list->dlist));
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    return (DListIsEmpty(sorted_list->dlist));
}

sorted_list_iter_t SortedListBegin(sorted_list_t *sorted_list)
{
    sorted_list_iter_t begin = {NULL};

    assert(NULL != sorted_list);

    begin.iter = (dlist_iter_t)DListBegin(sorted_list->dlist);

    return (begin);
}

sorted_list_iter_t SortedListEnd(sorted_list_t *sorted_list)
{
    sorted_list_iter_t end = {NULL};

    assert(NULL != sorted_list);

    end.iter = (dlist_iter_t)DListEnd(sorted_list->dlist);

    return (end);
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
    assert(NULL != iter.iter);

    iter.iter = DListNext(iter.iter);

    return (iter);
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
    assert(NULL != iter.iter);

    iter.iter = DListPrev(iter.iter);

    return (iter);
}

int SortedListIsSame(const sorted_list_iter_t iter1,
    const sorted_list_iter_t iter2)
{
    assert(NULL != iter1.iter);
    assert(NULL != iter2.iter);

    return (DListIsSameIter(iter1.iter, iter2.iter));
}

void *SortedListGetData(sorted_list_iter_t iter)
{
    assert(NULL != iter.iter);

    return (DListGetData(iter.iter));
}

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
    sorted_list_iter_t runner = SortedListBegin(sorted_list);
    sorted_list_iter_t end = SortedListEnd(sorted_list);

    while ((runner.iter != end.iter) &&
    (0 != (sorted_list->is_before(SortedListGetData(runner), data, NULL))))
    {
        runner = SortedListNext(runner);
    }

    runner.iter = DListInsert(sorted_list->dlist, runner.iter, data);

    return (runner);
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
    assert(NULL != iter.iter);

    iter.iter = DListRemove(iter.iter);

    return (iter);
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
    void *ret = NULL;

    assert(NULL != sorted_list);

    ret = DListGetData(DListBegin(sorted_list->dlist));
    DListPopFront(sorted_list->dlist);

    return (ret);
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
    void *ret = NULL;

    assert(NULL != sorted_list);

    ret = DListGetData(DListPrev(DListEnd(sorted_list->dlist)));

    DListPopBack(sorted_list->dlist);

    return (ret);
}

int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                                sorted_cmd_func_t cmd, void *arg)
{
    return (DListForEach(from.iter, to.iter, cmd, arg));

/*    int status = 0;

    assert(NULL != cmd);

    if (CmpIterData(from, SortedListNext(from)))
    {
        return (0);
    }

    while ((from.iter != to.iter) && (0 == status))
    {
        status = cmd(SortedListGetData(from), arg);
        from = SortedListNext(from);
    }
    status = (0 != status) ? status : cmd(SortedListGetData(from), arg);

    return (status);*/
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
    sorted_list_iter_t src_runner = SortedListBegin(src);
    sorted_list_iter_t dest_runner = SortedListBegin(dest);

    sorted_list_iter_t src_end = SortedListPrev(SortedListEnd(src));

    assert(dest->is_before == src->is_before);

    while ((0 == CmpIterData(src_runner, SortedListEnd(src))) &&
                            (0 == CmpIterData(dest_runner, SortedListEnd(dest))))
    {
        if (0 == (dest->is_before(SortedListGetData(dest_runner),
                                        SortedListGetData(src_runner), NULL)))
        {
            src_runner = SortedListNext(src_runner);
            DListSplice(SortedListBegin(src).iter,
                        SortedListPrev(src_runner).iter, dest_runner.iter);
        }
        else
        {
            dest_runner = SortedListNext(dest_runner);
        }
    }

    DListSplice(SortedListBegin(src).iter, src_end.iter, dest_runner.iter);

    return;
}

sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
            sorted_list_iter_t from, sorted_list_iter_t to, const void *arg)
{
    assert(NULL != sorted_list);

    return (SortedListFindIsBefore(from, to, sorted_list->is_before, arg));
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to,
    int (*is_match)(const void *data, const void *param),
    const void *arg)
{
    assert(NULL != is_match);

    from.iter = DListFind(from.iter, to.iter, is_match, arg);

    return (from);
}


static sorted_list_iter_t SortedListFindIsBefore(sorted_list_iter_t from,
            sorted_list_iter_t to, is_before_func_t is_before, const void *arg)
{
    int cmp = 1;
    size_t i = 0;
    size_t len = 0;

    assert(NULL != is_before);

    len = LenBetweenIter(from, to);

    while ((0 < len) && (0 != cmp))
    {
        len = len / 2 + ((1 != len) * len) % 2;
        for(i = 0; (i < len) && (1 == cmp); ++i, from = SortedListNext(from));
        for(i = 0; (i < len) && (-1 == cmp); ++i, from = SortedListPrev(from));

        cmp = CompIterArg(from, arg, is_before, arg);
    }

    return ((0 == cmp) ? from : to);
/*  -------------------------------------
    ~ ~ Solution with Nested Function ~ ~
    -------------------------------------

    int CompFunc(void *data1, void *data2)
    {
        int status = 1;
        if (0 == CompArgArg(data1, data2, is_before))
        {
            status = 0;
        }

        return (status);
    }

    from.iter = DListFind(from.iter, to.iter, CompFunc, arg);

    return (from);
*/
}

static size_t LenBetweenIter(sorted_list_iter_t from, sorted_list_iter_t to)
{
    size_t counter = 0;

    while (0 == CmpIterData(from, to))
    {
        ++counter;
        from = SortedListNext(from);
    }

    return (counter);
}

static int CompIterArg(sorted_list_iter_t iter, const void *arg,
    is_before_func_t is_before, const void* param)
{
    int ret = 0;
    assert(NULL != is_before);

    if (0 == is_before(SortedListGetData(iter), arg, param))
    {
        ret = -1;

        if (0 == is_before(arg, SortedListGetData(iter), param))
        {
            ret = 0;
        }
    }
    else
    {
        ret = 1;
    }

    return (ret);
}

/*static int CompArgArg(void *data, void *arg, is_before_func_t is_before)
{
    int ret = 0;

    if (0 == is_before(data, arg, NULL))
    {
        ret = 1;

        if (0 == is_before(arg, data, NULL))
        {
            ret = 0;
        }
    }
    else
    {
        ret = -1;
    }

    return (ret);
}*/

static int CmpIterData(const sorted_list_iter_t iter1,
                                            const sorted_list_iter_t iter2)
{
    return ((size_t)SortedListGetData(iter1) == (size_t)SortedListGetData(iter2));
}

