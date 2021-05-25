#include <stdlib.h>
#include <assert.h>
#include "PriorityQueue.h"
#include "sorted_list.h"

typedef struct comp_func_s comp_struct_t;

struct pqueue_s
{
    sorted_list_t *sorted_list;
    comp_struct_t *comp_struct;
};

struct comp_func_s
{
    void *param;
    pq_comp_func_t compare;
};

int IsBefore(const void *data1, const void *data2, void *compare)
{
    comp_struct_t *func = (comp_struct_t *)compare;

    return (func->compare(data1, data2, func->param) < 0);

}

/***************************************************************
* Allocates the memory for PQ                                  *
****************************************************************/
pqueue_t *PQCreate(pq_comp_func_t comp, void *param)
{
    pqueue_t *pqueue = malloc(sizeof(pqueue_t));

    assert(comp);

    if (NULL == pqueue)
    {
        return (NULL);
    }

    pqueue->comp_struct = malloc(sizeof(comp_struct_t));

    if (NULL == pqueue->comp_struct)
    {
        free(pqueue);   pqueue = NULL;
        return (NULL);
    }

    pqueue->comp_struct->param = param;
    pqueue->comp_struct->compare = comp;

    pqueue->sorted_list = SortedListCreate(IsBefore, pqueue->comp_struct);

    if (NULL == pqueue->sorted_list)
    {
        free(pqueue->comp_struct);  pqueue->comp_struct = NULL;
        free(pqueue);               pqueue = NULL;
        return NULL;
    }

    return (pqueue);

}

/***************************************************************
* Releases the memory that has been allocated to the PQ        *
****************************************************************/
void PQDestroy(pqueue_t *pqueue)
{
    assert(pqueue);

	SortedListDestroy(pqueue->sorted_list);    pqueue->sorted_list = NULL;
    free(pqueue->comp_struct);                  pqueue->comp_struct = NULL;
    free(pqueue);       pqueue = NULL;
}

/***************************************************************
* Returns a pointer to the element on top of the PQ            *
****************************************************************/
void *PQPeek(pqueue_t *pqueue)
{
    assert(pqueue);

	return(SortedListGetData(SortedListBegin(pqueue->sorted_list)));

}

/***************************************************************
*Releases the first element from the start of the PQ           *
****************************************************************/
void *PQDequeue(pqueue_t *pqueue)
{
    assert(pqueue);

	return(SortedListPopFront(pqueue->sorted_list));

}

/**************************************************************
* Pushes data to the PQ.              			    	      *
***************************************************************/
int PQEnqueue(pqueue_t *pqueue, void *data)
{
    sorted_list_iter_t end = {NULL};

    assert(pqueue);

    end = SortedListEnd(pqueue->sorted_list);

	return (!SortedListIsSame(SortedListInsert(pqueue->sorted_list, data), end));

}

/**************************************************************
* Returns the number of elements in the PQ.       		      *
***************************************************************/
size_t PQSize(const pqueue_t *pqueue)
{
    assert(pqueue);

	return(SortedListSize(pqueue->sorted_list));

}

/**************************************************************
* Return TRUE (1) if the PQ is empty. (0) otherwise.			  	     	  *
***************************************************************/
int PQIsEmpty(const pqueue_t *pqueue)
{
    assert(pqueue);

	return(SortedListIsEmpty(pqueue->sorted_list));

}

/**************************************************************
* Clears the PQ, by emptying it from elements.      		  *
***************************************************************/
void PQClear(pqueue_t *pqueue)
{
    assert(pqueue);

	while (!PQIsEmpty(pqueue))
	{
		PQDequeue(pqueue);
	}
}

/**************************************************************
* Erases an element in the PQ according to a certain parameter*
***************************************************************/
void *PQErase(pqueue_t *pqueue,
    int (*is_match)(const void *data, const void *param), void *param)
{
	sorted_list_t *list = NULL;
	sorted_list_iter_t erase = {NULL};
    void *erased_data = NULL;

    assert(pqueue);
    assert(is_match);

    list = pqueue->sorted_list;
    erase = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), is_match, param);
    erased_data = SortedListGetData(erase);

    SortedListRemove(erase);

    return(erased_data);
}
