#ifndef Dlist_OL70 /*header guard*/
#define Dlist_OL70
/**************************************************************
* The functions in this file handle a Doubly Linked List data *
* structure. It will be denoted as Dlist.                    *
*          													  *
*      														  *
* Written by: OL-70   										  *
* Last update: 15:00 , 11.07.2019                			  *
***************************************************************/

#include <stddef.h>

typedef enum {STOP, CONTINUE} status_t;

typedef void* dlist_iter_t;

typedef struct dlist_s dlist_t;

typedef status_t (*cmd_func_t)(dlist_iter_t iter, void *arg);
typedef status_t (*comp_func_t)(void *data1, void* data2);


/***************************************************************
* Allocates the memory for Dlist                              *
* DlistDestroy must be called after the work with the            *
* Dlist is done.									               *
*														       *
* Return Value: A pointer to the New Dlist.                   *
****************************************************************/
dlist_t *DlistCreate();

/***************************************************************
* Releases the memory that has been allocted for the Dlist    *
****************************************************************/
void DlistDestroy(dlist_t *dlist);

/***************************************************************
*Counts how long is the Dlist.                                *
*                                                              *
*Return Value: the length of the list in elements              *
****************************************************************/
size_t DlistCount(const dlist_t *dlist);

/***************************************************************

****************************************************************/
int DlistIsEmpty(const dlist_t *dlist);


dlist_iter_t DlistPushFront(dlist_t *dlist, void *data);


dlist_iter_t DlistPushBack(dlist_t *dlist, void *data);


void DlistPopFront(dlist_t *dlist);


void DlistPopBack(dlist_t *dlist);


status_t DlistForEach(dlist_iter_t begin, dlist_iter_t end, cmd_func_t cmd, void *arg);


dlist_iter_t DlistFind(dlist_iter_t begin, dlist_iter_t end, comp_func_t comp, void *arg);


dlist_t *DlistSplice(dlist_iter_t begin, dlist_iter_t end, dlist_iter_t to_where);


void *DlistGetData(const dlist_iter_t iter);


dlist_iter_t DlistBegin(const dlist_t *dlist);


dlist_iter_t DlistEnd(const dlist_t *dlist);


dlist_iter_t DlistInsertBefore(dlist_t *dlist, dlist_iter_t iter, void *data);


dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data);


dlist_iter_t DlistErase(dlist_iter_t iter);


int DlistIsSame(const dlist_iter_t iter1, const dlist_iter_t iter2);

#endif  /*Dlist_OL70*/
