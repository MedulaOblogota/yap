#ifndef HEAP_OL70   /*header gaurd*/
#define HEAP_OL70
/**************************************************************
* The functions in this file handle Heap data structure.
*
*                                                                                                                        *
* Written by: OL-70                                                                                     *
* Last update: 11:10 , 26.08.2019                                          *
***************************************************************/

#include <stddef.h>     /*  size_t  */

typedef struct heap_s heap_t;

/*
struct heap_s
{
    cmp_func_t cmp_func;
    vector_t *d_vector;
};
*/

/**************************************************************
* Allocates memory for the heap.                              *
* element_size is given in bytes.                             *
* HeapDestroy must be called after the work with the          *
* heap is done.                                                                                      *
*                                                                                                                      *
* Return Value: success - pointer to the heap; failure - NULL *
***************************************************************/
heap_t *MinHeapCreate(size_t size);


/**************************************************************
* Releases the memory that has been allocated for the heap    *
***************************************************************/
void MinHeapDestroy(heap_t *heap);


/*********************************************************************
* Pushes data to the heap.                                                             *
* *data is a pointer to void data type                               *
*                                                                                       *
* *heap - handle to the heap                                         *
*                                                                                                                             *
* Return Value: success - 1; failure - 0.                                                *
**********************************************************************/
int MinHeapPush(heap_t *heap, const int *data);


/**************************************************************
* Releases the element at the root of the heap.               *
* Return Value: success - 1; failure - 0.                     *
***************************************************************/
int MinHeapPop(heap_t *heap);

/**************************************************************
* Removes from heap the element that matches received data    *
* Return Value: pointer to removed element.                   *
***************************************************************/

int *MinHeapRemove(heap_t *heap, const int *data);

/*************************************************************************
* Returns a pointer to the element at the root of the heap.              *
**************************************************************************/
int *MinHeapPeek(heap_t *heap);

/**************************************************************
* Returns the number of elements in the heap.                            *
***************************************************************/
size_t MinHeapSize(heap_t *heap);

/**************************************************************
* Returns: 1 if heap is empty; 0 if heap is not empty.            *
***************************************************************/
int MinHeapIsEmpty(heap_t *heap);

void PrintHeap(heap_t *heap);

void Heapify(int *arr, heap_t *heap);

#endif /*HEAP_OL70*/
