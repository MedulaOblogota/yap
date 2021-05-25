#include <stdlib.h>
#include <assert.h>

#include "heap.h"
#include "PriorityQueue.h"

struct pqueue_s
{
    heap_t *heap;
};

pqueue_t *PQCreate(pq_comp_func_t comp_func, void *param)
{
	pqueue_t *pqueue = malloc(sizeof(pqueue_t));

	assert(comp_func);

	if (NULL == pqueue)
    {
        return (NULL);
    }

	pqueue->heap = HeapCreate(comp_func, param);

	if (NULL == pqueue->heap)
	{
		free(pqueue);
		return (NULL);
	}

	return (pqueue);
}

void PQDestroy(pqueue_t *pqueue)
{
	HeapDestroy(pqueue->heap);
	free(pqueue);
}

/***************************************************************
* Returns a pointer to the element on top of the PQ            *
****************************************************************/
void *PQPeek(pqueue_t *pqueue)
{
	return (HeapPeek(pqueue->heap));
}

/***************************************************************
*Releases the first element from the start of the PQ           *
*                                                              *
* Retrun Value: pointer to the released element                *
****************************************************************/
void *PQDequeue(pqueue_t *pqueue)
{
	void *value = PQPeek(pqueue);
	HeapPop(pqueue->heap);

	return (value);
}


/**************************************************************
* Pushes data to the PQ.              			    	      *
* data is a pointer to an element                  	          *
*														      *
* Return Value: 1 if succeeded 0 if failed	       		      *
***************************************************************/
int PQEnqueue(pqueue_t *pqueue, void *data)
{
	return(HeapPush(pqueue->heap, data));
}

/**************************************************************
* Returns the number of elements in the PQ.       		      *
***************************************************************/
size_t PQSize(const pqueue_t *pqueue)
{
	return(HeapSize(pqueue->heap));
}

/**************************************************************
* Return TRUE (1) if the PQ is empty.			  	     	  *
* Return FALSE (0) otherwise.                		  		  *
***************************************************************/
int PQIsEmpty(const pqueue_t *pqueue)
{
	return(HeapIsEmpty(pqueue->heap));
}

/**************************************************************
* Clears the PQ, by emptying it from elements.      		  *
* NOTE - The PQ is not destroyed. It can be filled with New   *
* elements.                                                   *
***************************************************************/
void PQClear(pqueue_t *pqueue)
{
	while (!HeapIsEmpty(pqueue->heap))
	{
		HeapPop(pqueue->heap);
	}
}

/**************************************************************
* Erases an element in the PQ according to a certain parameter*
*                                                             *
* is_match - a function that checks whether an element meets  *
* the criteria to be erased. Subsequently, that element will  *
* be erased.                                                  *
***************************************************************/
void *PQErase(pqueue_t *pqueue,
    int (*is_match)(const void *data, const void *param), void *param)
{
	return(HeapRemove(pqueue->heap, param, is_match));
}
