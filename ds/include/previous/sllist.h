#ifndef SLLIST_OL70 /*header guard*/
#define SLLIST_OL70
/**************************************************************
* The functions in this file handle a Singly Linked List data *
* structure, and will be denoted as SLList.                   *
* The SLList a Node-based, each Node has data and a pointer   *
* to the next Node. The last Node points to NULL, marking the *
* end of the SLList.                                          *
*                    										  *
* Written by: OL-70   										  *
* Last update: 11:25 08.07.2019                    			  *
***************************************************************/
#include <stddef.h>


typedef enum {STOP, CONTINUE} status_t;
typedef struct sll_node_s sll_node_t;
typedef status_t (*cmd_func_t)(sll_node_t *node, void *data);
typedef status_t (*comp_func_t)(void *data1, void* data2);

struct sll_node_s
{
    void *data;
    sll_node_t *next;
};

/***************************************************************
* Allocates the memory for a Node                              *
* SLLFreeAll must be called after the work with the            *
* SLList is done.									           *
*														       *
* data is the data to be inserted inside the new Node          *
* Return Value: A pointer to the New Node                      *
****************************************************************/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/***************************************************************
* Removes the current Node by unlinking it from the next Node  *
* and links the previous node with the next one                *
*          ***UNABLE TO EXECUTE ON THE LAST NODE***            *
* Return value: pointer to the next node after the removed node*
****************************************************************/
sll_node_t *SLLRemove(sll_node_t *node);

/***************************************************************
* Removes the Next Node by unlinking it from the current Node  *
* and links the current node with the one after the node that  *
* is being removed.                                            *
* Return value: a pointer to the next node                     *
****************************************************************/
sll_node_t *SLLRemoveAfter(sll_node_t *node);

/***************************************************************
* Releases the memory allocted to the nodes following the given*
* node, including the current one.                             *
****************************************************************/
void SLLFreeAll(sll_node_t *node);

/***************************************************************
* Inserts a node before the current node and connects it to the*
* rest of the SLLink                                           *
* Return value: pointer to the newly inserted nodes            *
****************************************************************/
sll_node_t *SLLInsert(sll_node_t *node, sll_node_t *new_node);

/***************************************************************
* Inserts a node after the current node and connects it to the *
* rest of the SLLink.                                          *
* Return value: pointer to the newly inserted nodes            *
****************************************************************/
sll_node_t *SLLInsertAfter(sll_node_t *node, sll_node_t *new_node);

/***************************************************************
* Counts how many nodes there from the current node until the  *
* last node.                                                   *
* Return value: The number of nodes counted                    *
****************************************************************/
size_t SLLCount(const sll_node_t *node);

/***************************************************************
* Finds a node containing the wanted element, returns a pointer*
* to said node.                                                *
* cmp is the compare function given by the user.               *
* *node is the node we check from and on until the end         *
* Return value: a pointer to the node containing the argument  *
****************************************************************/
sll_node_t *SLLFind(sll_node_t *node, comp_func_t comp, void *arg);

/***************************************************************
* A boolean function. If the linked list contains a loop,      *
* SLLFind will return TRUE(1). Otherwise, it returns FALSE(0). *
****************************************************************/
int SLLHasLoop(const sll_node_t *node);

/***************************************************************
* Travereses two lists and returns a node that is the          *
* intersection between list1 and list2. If they do not         *
* intersect, return NULL.                                      *
****************************************************************/
sll_node_t *SLLFindIntersection(sll_node_t *list1, sll_node_t *list2);

/***************************************************************
* Executes a command given by the user with an argument        *
* The command will execute from the given node until the end   *
* *cmd is the command function given by the user               *
* num is the number of nodes to go over                        *
*                                                              *
* Return value: STOP(1), CONTINUE(2)                             *
****************************************************************/
status_t SLLForEach(sll_node_t *node, cmd_func_t cmd, void *arg, size_t num);

/***************************************************************
* Flips the direction of the SLList from the end to the given  *
* node, which will mark the end of the list.                   *
* Return value: A pointer to the beginning of the newly flipped*
* SLList                                                       *
****************************************************************/
sll_node_t *SLLFlip(sll_node_t *node);


#endif  /*SLLIST_OL70*/
