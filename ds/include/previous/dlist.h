#ifndef Dlist_OL70 /*header guard*/
#define Dlist_OL70
/**************************************************************
* The functions in this file handle a Doubly Linked List data *
* structure. It will be denoted as Dlist.                    *
*          													  *
*      														  *
* Written by: OL-70   										  *
* Last update: 13:30 , 14.07.2019                			  *
***************************************************************/

#include <stddef.h>

typedef enum {STOP, CONTINUE} status_t;

typedef void* dlist_iter_t;

typedef struct dlist_s dlist_t;

typedef status_t (*cmd_func_t)(dlist_iter_t iter, void *arg);
typedef status_t (*comp_func_t)(void *data1, void *data2);


/*******************************************************************************
* Allocates the memory for dlist
* dlistDestroy must be called after the work with the
* dlist is done.
*
* Return Value: A pointer to the New Dlist.
*******************************************************************************/
dlist_t *DlistCreate();

/*******************************************************************************
* Releases the memory that has been allocted for the Dlist
*
* dllist - a pointer to the Doubly Link List (Not NULL).
*******************************************************************************/
void DlistDestroy(dlist_t *dlist);

/*******************************************************************************
* dllist - a pointer to the Doubly Link List (Not NULL).
*
*Return Value: the number of members in the Dlist.
*******************************************************************************/
size_t DlistCount(const dlist_t *dlist);

/*******************************************************************************
 * DlistIsEmpty - checks if the list is empty.  O(1)
 *
 * dllist - a pointer to the Doubly Link List (Not NULL).
 *
 * Return - TRUE if the Dlist is empty and FALSE otherwise.
 ******************************************************************************/
int DlistIsEmpty(const dlist_t *dlist);

/*******************************************************************************
* DlistPushFront - function receives a list and inserts a new member
* which contains data to the front location.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
*
* data - the data the new member will hold.
*
* Returns - iterator - pointing to the position of the new member.
* If failed, NULL will be returned.
*******************************************************************************/
dlist_iter_t DlistPushFront(dlist_t *dlist, void *data);

/*******************************************************************************
* DlistPushBack - function receives a list and inserts a new member
* which contains data to the last location.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
*
* data - the data the new member will hold.
*
* Returns - iterator - pointing to the position of the new member.
* If failed, NULL will be returned.
*******************************************************************************/
dlist_iter_t DlistPushBack(dlist_t *dlist, void *data);

/*******************************************************************************
* DlistPopFront - function receives a list, and removes
* the member in the front position in that list.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
*******************************************************************************/
void DlistPopFront(dlist_t *dlist);

/*******************************************************************************
* DlistPopBack - function receives a list, and removes
* the member in the last position in that list.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
*******************************************************************************/
void DlistPopBack(dlist_t *dlist);

/*******************************************************************************
* Executes a command (cmd) given by the user with arg in given range.
* cmd - command function given by the user
*
* from - iterator that specifies from where to do the command (Not NULL).
* to - iterator that specifies until where to do the command (Not NULL).
* make sure from comes before to in the List
*
* Return value: STOP, CONTINUE.
*******************************************************************************/
status_t DlistForEach(dlist_iter_t from, dlist_iter_t to,
                                cmd_func_t cmd, void *arg);

/*******************************************************************************
* Executes comparison (comp) given by the user with arg in given range.
* comp - comparison function given by the user
*
* from - iterator that specifies from where to do the comparison (Not NULL).
* to - iterator that specifies until where to do the comparison (Not NULL).
* make sure from comes before to in the List
*
* Return value: iterator to the found data. if no match is found - the tail of
* the list is returned.
*******************************************************************************/
dlist_iter_t DlistFind(dlist_iter_t from, dlist_iter_t to,
                                comp_func_t comp, void *arg);

/*******************************************************************************
* Executes splice of a given portion of list into a given place in the
* destination list, denoted by where.
*
* from - iterator that specifies from where to do the command (Not NULL).
* to - iterator that specifies until where to do the command (Not NULL).
* make sure from comes before to in the List
* where - iterator that specifies where to do tShe splice (Not NULL).
*
* Return value: iterator to the found data. if no match - NULL is returned.
*******************************************************************************/
void DlistSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);

/*******************************************************************************
* iter - iterator that specifies from where to get the data (Not NULL).
*
* Return value: the data in the given iterator.
*******************************************************************************/
void *DlistGetData(const dlist_iter_t iter);

/*******************************************************************************
* dllist - a pointer to the Doubly Link List (Not NULL).
*
* Return value: iterator to the beginning of a given list.
*******************************************************************************/
dlist_iter_t DlistBegin(const dlist_t *dlist);

/*******************************************************************************
* dllist - a pointer to the Doubly Link List (Not NULL).
*
* Return value: iterator to the end of a given list.
*******************************************************************************/
dlist_iter_t DlistEnd(const dlist_t *dlist);

/*******************************************************************************
* Inserted new member to the list before the given iterator.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
* iter - iterator that specifies before which member to insert the new member
* (Not NULL).
* data - pointer to the data to be save in the new member in the list.
* (Not NULL).
*
* Return value: iterator to the inserted member of the list. If the operation
* is failed - the tail of the list is returned.
*******************************************************************************/
dlist_iter_t DlistInsertBefore(dlist_t *dlist, dlist_iter_t iter, void *data);

/*******************************************************************************
* Inserted new member to the list after the given iterator.
*
* dllist - a pointer to the Doubly Link List (Not NULL).
* iter - iterator that specifies after which member to insert the new member
* (Not NULL).
* data - pointer to the data to be save in the new member in the list.
* (Not NULL).
*
* Return value: iterator to the inserted member of the list. If the operation
* is failed - the tail of the list is returned.
*******************************************************************************/
dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data);

/*******************************************************************************
* Erase member from the list in a given iterator.
*
* iter - iterator that specifies after which member to erase (Not NULL).
*
* Return value: iterator to the member atfer the member to erase. If the
* operation is failed - the tail of the list is returned.
*******************************************************************************/
dlist_iter_t DlistErase(dlist_iter_t iter);

/*******************************************************************************
* iter - iterator that specifies after which member to erase (Not NULL).
*
* Return value: iterator to next member of the list.
*******************************************************************************/
dlist_iter_t DlistGetNext(dlist_iter_t iter);

/*******************************************************************************
* iter - iterator that specifies after which member to erase (Not NULL).
*
* Return value: iterator to previous member of the list.
*******************************************************************************/
dlist_iter_t DlistGetPrev(dlist_iter_t iter);

/*******************************************************************************
* Checks if iter1 is the same as iter2
*
* iter1, iter2 - iterator that pointing on the position of the given
* members (Not NULL).
*
* Return value: TRUE (1) if the same, FALSE (0) otherwise.
*******************************************************************************/
int DlistIsSame(const dlist_iter_t iter1, const dlist_iter_t iter2);

#endif  /*Dlist_OL70*/
