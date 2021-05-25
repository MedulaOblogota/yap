#ifndef BST_OL70 /*header guard*/
#define BST_OL70
/**************************************************************
* The functions in this file handle a Binary Search Tree ADT. *
*  It will be denoted as BST.                                 *
*      														  *
* Written by: OL-70   										  *
* Last update: 12:45 , 08.08.2019                			  *
***************************************************************/

#include <stddef.h>

/*
#define NUM_OF_CHILDRENS (2)

struct bst_s
{
   bst_iter_t root;
   cmp_func_t cmp;
   void *param;
};
struct bst_node_s
{
   bst_iter_t *parent;
   bst_iter_t *child[NUM_OF_CHILDRENS];
   void *data;
};
*/

typedef struct bst_s bst_t;
typedef struct bst_node_s bst_node_t;
typedef bst_node_t bst_iter_t;

typedef int (*cmp_func_t)(const void *data1, const void *data2,
                                                            void *param);
/*******************************************************************************
* Allocates memory for BST.
* BSTDestroy must be called after the work with the BST is done.
* cmp_func - compare function that the user can add. Cannot be NULL.
* param - parameter of the iter.
*
*
* Return Value: A pointer to the new BST.
* If memory allocation failes - NULL will be returned.
*******************************************************************************/
bst_t *BSTCreate(cmp_func_t cmp_func, void *param);

/*******************************************************************************
* Releases the memory that has been allocted for the BST.
*
* bst - a pointer to the BST. Cannot be NULL.
*******************************************************************************/
void BSTDestroy(bst_t *bst);

/*******************************************************************************
* Counts the elements in the BST.
* bst - a pointer to the BST. Cannot be NULL.
*
* Return Value: the number of iters in the BST.
*******************************************************************************/
size_t BSTCount(const bst_t *bst);

/*******************************************************************************
 * Checks if the BST is empty.
 *
 * bst - a pointer to the BST. Cannot be NULL.
 *
 * Return - TRUE if the BST is empty and FALSE otherwise.
 ******************************************************************************/
int BSTIsEmpty(const bst_t *bst);

/*******************************************************************************
* bst - a pointer to the BST. Cannot be NULL.
*
* Return value: pointer to the begining of a given BST.
* If the BST is empty - bad pointer is returned.
*******************************************************************************/
bst_iter_t *BSTBegin(bst_t *bst);

/*******************************************************************************
* bst - a pointer to the BST. Cannot be NULL.
*
* Return value: bad pointer which indicates the end.
* If the BST is empty - bad pointer is returned.
*******************************************************************************/
bst_iter_t *BSTEnd(bst_t *bst);

/*******************************************************************************
* iter - pointer to the current iter in the tree.
*
* Return value: pointer to the next iter (according to its data) of the BST.
*******************************************************************************/
bst_iter_t *BSTNext(bst_iter_t *iter);

/*******************************************************************************
* iter - pointer to the current iter in the tree. Cannot be NULL.
*
* Return value: pointer to the previous iter (according to its data) of the BST.
*******************************************************************************/
bst_iter_t *BSTPrev(bst_iter_t *iter);

/*******************************************************************************
* iter - pointer to the iter to get the data from. Cannot be NULL.
*
* Return value: the data in the given tree iter.
*******************************************************************************/
void *BSTGetData(bst_iter_t *iter);

/*******************************************************************************
* Inserts new iter to the BST.
*
* bst - a pointer to the BST. Cannot be NULL.
* data - pointer to the data to be saved in the new iter in the BST. Cannot be
* NULL.
*
* Return value: pointer to the inserted iter in the BST. If the operation
* failes - bad pointer will be returned.
*******************************************************************************/
bst_iter_t *BSTInsert(bst_t *bst, void *data);

/*******************************************************************************
* Removes a iter from the BST.
*
* iter - pointer to the iter to be erased. Cannot be NULL.
*
* Return value: the data of the removed iter.
*******************************************************************************/
void *BSTRemove(bst_iter_t *iter);


/*******************************************************************************
* Executes a command (cmd) given by the user with arg in given range.
* cmd - command function given by the user
*
* from - iter that specifies from where to do the command. Cannot be NULL.
* to - iter that specifies until where to do the command. Cannot be NULL.
* Note - include
* WARNING - make sure from comes before to in the BST, the user should not
* change the key.
*
* Return value: stop = 0, continue = 1.
*******************************************************************************/
int BSTForEach(bst_iter_t *from, bst_iter_t *to,
                     int (*action_func)(void* data, void *param), void *param);

/*******************************************************************************
* Executes comparison with cmp_func given in CreateBST by the user with arg
* in given range.
*
* Make sure from comes before to in the BST.
*
* Return value: pointer to the found data. If no match was found - bad pointer
* will be returned.
*******************************************************************************/
bst_iter_t *BSTFind(bst_t *bst, const void *arg);

/*******************************************************************************
* Checks if iter1 is the same as iter2
*
* iter1, iter2 - iterator that pointing on the position of the given
* members (Not NULL).
*
* Return value: TRUE (1) if the same, FALSE (0) otherwise.
*******************************************************************************/
int BSTIsSameIter(bst_iter_t *iter1, bst_iter_t *iter2);

#endif  /*BST_OL70*/
