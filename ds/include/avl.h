#ifndef AVL_OL70 /*header guard*/
#define AVL_OL70
/**************************************************************
* The functions in this file handle a AVL Tree ADT.			*
*  It will be denoted as AVL.                                 *
*      														  *
* Written by: OL-70   										  *
* Last update: 13:45 , 18.08.2019                			  *
***************************************************************/

#include <stddef.h>

/*
#define NUM_OF_CHILDREN (2)

struct avl_s
{
   avl_node_t root;
   cmp_func_t cmp;
   void *param;
};
struct avl_node_s
{
   void *data;
   avl_node_t *child[NUM_OF_CHILDREN];
   int height;
};
*/

typedef struct avl_s avl_t;
typedef struct avl_node_s avl_node_t;
typedef int (*cmp_func_t)(const void *data1, const void *data2,
                                                            void *param);
/*******************************************************************************
* Allocates memory for AVL.
* AVLDestroy must be called after the work with the AVL is done.
* cmp_func - compare function that the user can add. Cannot be NULL.
* param - parameter of the iter.
*
*
* Return Value: A pointer to the new AVL.
* If memory allocation failes - NULL will be returned.
*******************************************************************************/
avl_t *AVLCreate(cmp_func_t cmp_func, void *param);

/*******************************************************************************
* Releases the memory that has been allocted for the AVL. (POST ORDER)
*
* avl - a pointer to the AVL. Cannot be NULL.
*******************************************************************************/
void AVLDestroy(avl_t *avl);

/*******************************************************************************
* Counts the elements in the AVL. (PRE ORDER)
* avl - a pointer to the AVL. Cannot be NULL.
*
* Return Value: the number of nodes in the AVL.
*******************************************************************************/
size_t AVLCount(const avl_t *avl);

/*******************************************************************************
 * Checks if the AVL is empty.
 *
 * avl - a pointer to the AVL. Cannot be NULL.
 *
 * Return - TRUE if the AVL is empty and FALSE otherwise.
 ******************************************************************************/
int AVLIsEmpty(const avl_t *avl);

/*******************************************************************************
* Inserts new node to the AVL.
*
* avl - a pointer to the AVL. Cannot be NULL.
* data - pointer to the data to be saved in the new node in the AVL. Cannot be
* NULL.
*
* Return - TRUE if the AVL insetion succeded and FALSE otherwise.
*******************************************************************************/
int AVLInsert(avl_t *avl, void *data);

/*******************************************************************************
* Removes a node from the AVL.
*
* data - pointer to the node to be erased. Cannot be NULL.
*
* Return value: the data of the removed node. 
*	if the node wasn't fount, NULL will be returned
*******************************************************************************/
void *AVLRemove(avl_t *avl, const void *data);

/*******************************************************************************
* Executes a command (cmd) given by the user with arg in given range. (IN ORDER)
* cmd - command function given by the user
* from - iter that specifies from where to do the command. Cannot be NULL.
* to - iter that specifies until where to do the command. Cannot be NULL.
* Note - include
* WARNING - make sure from comes before to in the AVL, the user should not
* change the key.
*
* Return value: stop = 0, continue = 1.
*******************************************************************************/
int AVLForEach(avl_t *avl, int (*action_func)(void* data, void *param), void *param);

/*******************************************************************************
* Executes comparison with cmp_func given in CreateAVL by the user with arg
* in given range.
*
* Make sure from comes before to in the AVL.
*
* Return value: pointer to the found data. If no match was found - bad pointer
* will be returned.
*******************************************************************************/
void *AVLFind(const avl_t *avl, const void *arg);

/*******************************************************************************
* Calculates the height of the tree, which is the largest sub tree.
* 
* Return value: avl tree hight.
*******************************************************************************/
size_t AVLHeight(const avl_t *avl);

#endif  /*AVL_OL70*/
