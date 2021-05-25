#include <stdlib.h>
#include <assert.h>

#include "dlist.h"
#include "sorted_list.h"


struct sorted_list_s
{
    dlist_t *sorted_list;
    is_before_func_t is_before;
    void *param;
};

/*******************************************************************************
* Allocates memory for SortedList.
*******************************************************************************/
sorted_list_t *SortedListCreate(is_before_func_t is_before, const void *param)
{
    sorted_list_t *slist = malloc(sizeof(sorted_list_t));

    if (NULL == slist)
    {
        return (NULL);
    }

    slist->sorted_list = DListCreate();

    if (NULL == slist->sorted_list)
    {
        free(slist);       slist = NULL;
        return (NULL);
    }

    slist->is_before = is_before;
    slist->param = (void *)param;

    return (slist);
}

/*******************************************************************************
* Releases the memory that has been allocted for the SortedList
*******************************************************************************/
void SortedListDestroy(sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    DListDestroy(sorted_list->sorted_list);

    free(sorted_list);      sorted_list = NULL;
}

/*******************************************************************************
* Counts the elements in the list.
*******************************************************************************/
size_t SortedListSize(const sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    return(DListSize(sorted_list->sorted_list));
}

/*******************************************************************************
 * SortedListIsEmpty - checks if the list is empty.  O(1)
 ******************************************************************************/
int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
    assert(NULL != sorted_list);

    return(DListIsEmpty(sorted_list->sorted_list));
}

/*******************************************************************************
* Removes the member that is in the first position in the list.
*******************************************************************************/
void *SortedListPopFront(sorted_list_t *sorted_list)
{
    void *value = NULL;

    assert(NULL != sorted_list->sorted_list);

    value = DListGetData(DListBegin(sorted_list->sorted_list));

    DListPopFront(sorted_list->sorted_list);

    return (value);
}

/*******************************************************************************
* Removes the member that is in the last position in the list.
*******************************************************************************/
void *SortedListPopBack(sorted_list_t *sorted_list)
{
    void *value = NULL;

    assert(NULL != sorted_list->sorted_list);

    value = DListGetData(DListPrev(DListEnd(sorted_list->sorted_list)));

    DListPopBack(sorted_list->sorted_list);

    return (value);
}

/*******************************************************************************
* Executes a command (cmd) given by the user with arg in given range.
*******************************************************************************/
int SortedListForEach(sorted_list_iter_t from,
                        sorted_list_iter_t to, sorted_cmd_func_t cmd, void *arg)
{
    assert(NULL != from.iter);
    assert(NULL != to.iter);
    assert(NULL != cmd);

    return(DListForEach(from.iter, to.iter, cmd, arg));
}

/* INNER func for use of SortedListFind */
static int Compare(sorted_list_t *sorted_list, const void *arg, void *arg_from_list)
{
    return ((sorted_list->is_before(arg, arg_from_list, sorted_list->param) == 0)
    && ((sorted_list->is_before(arg_from_list, arg, sorted_list->param) == 0)));
}

/* INNER func for use of SortedListFind */
static sorted_list_iter_t Move(int advance, sorted_list_iter_t iter, int move)
{
        while (move > 0)
        {
            if (advance)
            {
                iter = SortedListNext(iter);
            }
            else
            {
                iter = SortedListPrev(iter);
            }
            --move;
        }

        return (iter);
}

/*******************************************************************************
* Executes comparison (comp) to arg with inner function in given range.
*******************************************************************************/
sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
    sorted_list_iter_t from, sorted_list_iter_t to, const void *arg)
{
    size_t final = SortedListSize(sorted_list) - 1;
    size_t initial = 0;
    sorted_list_iter_t runner = from;
    size_t move = (final - initial) / 2;
    void *arg_from_list = NULL;
    int advance = 1;

    while (0 != move)
    {
        move = (final - initial) / 2;

        runner = Move(advance, runner, move);
        arg_from_list = SortedListGetData(runner);

        if (Compare(sorted_list, arg, arg_from_list))
        {
            return (runner);
        }
        else if (sorted_list->is_before(arg, SortedListGetData(runner),
                                                                    sorted_list->param) == 1)
        {
            advance = 0;
            final -= move;
        }
        else
        {
            advance = 1;
            initial += move ;
        }
    }

    return (to);
}

/*******************************************************************************
* Executes comparison (comp) given by the user with arg in given range.
*******************************************************************************/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to,
    int (*is_match)(const void *data, const void *param), const void *arg)
{
    to.iter = DListFind(from.iter, to.iter, is_match, arg);

    return (to);
}

/*******************************************************************************
* Executes merge of a given range of list into a given place in the
* destination list, denoted by dest.
*******************************************************************************/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
    sorted_list_iter_t dest_runner = SortedListBegin(dest);
    sorted_list_iter_t src_runner = SortedListBegin(src);

    sorted_list_iter_t dest_end = SortedListEnd(dest);
    sorted_list_iter_t src_end = SortedListEnd(src);

    sorted_list_iter_t src_begin = src_runner;
    int is_dest_empty = 0;

    while (src_runner.iter != src_end.iter)
    {
        void *src_item = SortedListGetData(src_runner);
        void *dest_item = SortedListGetData(dest_runner);

        if (SortedListIsSame(dest_runner, dest_end))
        {
            is_dest_empty = 1;
        }

        src_begin = src_runner;
        if ((dest->is_before(dest_item, src_item, dest->param) == 0) || (is_dest_empty))
        {
            while ((dest->is_before(dest_item, src_item, dest->param) == 0) || (is_dest_empty))
            {
                src_runner = SortedListNext(src_runner);
                src_item = SortedListGetData(src_runner);

                if (SortedListIsSame(src_runner, src_end))
                {
                    is_dest_empty = 1;
                    break;
                }
            }
            DListSplice(src_begin.iter, SortedListPrev(src_runner).iter,
                                                            dest_runner.iter);
        }
        dest_runner = SortedListNext(dest_runner);
    }
}


/*******************************************************************************
* iter - iterator that specifies from where to get the data (Not NULL).
*******************************************************************************/
void *SortedListGetData(const sorted_list_iter_t iter)
{
    return (DListGetData(iter.iter));
}

/*******************************************************************************
* returns an iterator to the end of a given list. If the list is empty
* - bad iterator is returned.
*******************************************************************************/
sorted_list_iter_t SortedListBegin(sorted_list_t *sorted_list)
{
    sorted_list_iter_t begin;

    assert(NULL != sorted_list);

    begin.iter = DListBegin(sorted_list->sorted_list);

    return (begin);
}

/*******************************************************************************
* returns an iterator to the end of a given list. If the list is empty
* - bad iterator is returned.
*******************************************************************************/
sorted_list_iter_t SortedListEnd(sorted_list_t *sorted_list)
{
    sorted_list_iter_t end;

    assert(NULL != sorted_list);

    end.iter = DListEnd(sorted_list->sorted_list);

    return (end);
}

/*******************************************************************************
* Inserts new member to the list before the given iterator.
*******************************************************************************/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
    sorted_list_iter_t runner = SortedListBegin(sorted_list);
    sorted_list_iter_t end = SortedListEnd(sorted_list);

    while (runner.iter != end.iter)
    {
        void *data_in_list = SortedListGetData(runner);
        if (sorted_list->is_before(data_in_list, data, sorted_list->param) == 0)
        {
            runner.iter = DListInsert(sorted_list->sorted_list,
                                                            runner.iter, data);

            return (runner);
        }
        runner = SortedListNext(runner);
    }

    runner.iter = DListInsert(sorted_list->sorted_list, end.iter, data);
    return(runner);
}

/*******************************************************************************
* Erase member from the list in a given iterator.
*******************************************************************************/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
    sorted_list_iter_t removed;

    removed.iter = DListRemove(iter.iter);

    return(removed);
}

/*******************************************************************************
* returns an iterator to next member of the list.
*******************************************************************************/
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
    iter.iter = DListNext(iter.iter);

    return(iter);
}

/*******************************************************************************
* returns an iterator to previous member of the list.
*******************************************************************************/
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
    iter.iter = DListPrev(iter.iter);

    return(iter);
}

/*******************************************************************************
* Checks if iter1 is the same as iter2
*******************************************************************************/
int SortedListIsSame(const sorted_list_iter_t iter1,
                                                const sorted_list_iter_t iter2)
{
    return (DListIsSameIter(iter1.iter, iter2.iter));
}
