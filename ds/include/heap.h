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

typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);
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
heap_t *HeapCreate(cmp_func_t cmp_func, void *param);


/**************************************************************
* Releases the memory that has been allocated for the heap    *
***************************************************************/
void HeapDestroy(heap_t *heap);


/*********************************************************************
* Pushes data to the heap.                                                             *
* *data is a pointer to void data type                               *
*                                                                                       *
* *heap - handle to the heap                                         *
*                                                                                                                             *
* Return Value: success - 1; failure - 0.                                                *
**********************************************************************/
int HeapPush(heap_t *heap, const void *data);


/**************************************************************
* Releases the element at the root of the heap.               *
* Return Value: success - 1; failure - 0.                     *
***************************************************************/
void HeapPop(heap_t *heap);

/**************************************************************
* Removes from heap the element that matches received data    *
* Return Value: pointer to removed element.                   *
***************************************************************/

void *HeapRemove(heap_t *heap, const void *data,
    int (*is_match)(const void *data1, const void *data2));

/*************************************************************************
* Returns a pointer to the element at the root of the heap.              *
**************************************************************************/
void *HeapPeek(heap_t *heap);

/**************************************************************
* Returns the number of elements in the heap.                            *
***************************************************************/
size_t HeapSize(heap_t *heap);

/**************************************************************
* Returns: 1 if heap is empty; 0 if heap is not empty.            *
***************************************************************/
int HeapIsEmpty(heap_t *heap);


#endif /*HEAP_OL70*/
