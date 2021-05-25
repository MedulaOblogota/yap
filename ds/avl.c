#include <stdlib.h>     /*free*/
#include <stdio.h>      /*printf*/

#include "avl.h"

#define NUM_OF_CHILDREN (2)

#define LEFT (0)
#define RIGHT (1)
#define COUNT (4)

struct avl_node_s
{
    void *data;
    avl_node_t *child[NUM_OF_CHILDREN];
    int height;
};

struct avl_s
{
   avl_node_t root;
   cmp_func_t cmp;
   void *param;
};

typedef avl_node_t *(*balance_func_t)(avl_node_t *node);

/*****************************************************************************
                        INNER FUNCTION DEFINITIONS
*****************************************************************************/

static avl_node_t *AVLCreateNode(void *data);
static int AVLHasLeftChild(avl_node_t *runner);
static int AVLHasRightChild(avl_node_t *runner);
static int GetData(avl_node_t *node);


static avl_node_t *RecursiveInsert(avl_node_t *avl_node, avl_node_t *new_node,
                                                    cmp_func_t cmp, void *param);
static size_t RecursiveCount(avl_node_t *node);
static avl_node_t *RecursiveFindFather(avl_node_t *father, avl_node_t *son,
                                cmp_func_t cmp, const void *data, void *param);
static void RecursiveDestroy(avl_node_t *node);
static int RecursiveForEach(avl_node_t *node,
                    int (*action_func)(void* data, void *param), void *param);
static void *RecursiveRemove(avl_node_t *father, avl_node_t *son,const void* data,
                                cmp_func_t cmp, void *param);

static int ReturnMaxHeight(avl_node_t *node);
static void RemoveBothChildren(avl_node_t *node_to_remove,
                        avl_node_t *father_of_node_to_remove, int which_child);
static void AddLeftChild(avl_node_t *tree, avl_node_t *added_node);
static void RemoveOneChild(avl_node_t *node_to_remove,
                        avl_node_t *father_of_node_to_remove, int which_child);
static void RemoveChildless(avl_node_t *father_of_node_to_remove,
                                                            int which_child);
static avl_node_t *ExtractSonFromFather(const avl_t *avl, avl_node_t *father,
                                                                    void *arg);

static void BalanceAVL(avl_node_t *father, avl_node_t *son);
static avl_node_t *RotateRight(avl_node_t *node);
static avl_node_t *RotateLeft(avl_node_t *node);
static avl_node_t *RightLeftBalance(avl_node_t *node);
static avl_node_t *LeftRightBalance(avl_node_t *node);

static int DetermineHeightDiff(avl_node_t *node);
static int DetermineWhichChild(avl_node_t *father, avl_node_t *son);

static int IdentifyProblem(avl_node_t *node);
static void DetermineHeights(avl_node_t *node);
static int RightChildHasLargerHeight(avl_node_t *node);
static avl_node_t *RemoveNode(avl_node_t *father, avl_node_t *son);

void print2D(avl_node_t *node);
void print2DUtil(avl_node_t *node, int space);



balance_func_t balance_func_lut[4] = {RotateRight, RotateLeft,
                                        	RightLeftBalance, LeftRightBalance};
/*******************************************************************************
* Allocates memory for AVL.
*******************************************************************************/
avl_t *AVLCreate(cmp_func_t cmp_func, void *param)
{
    avl_t *avl = malloc(sizeof(avl_t));

    if (NULL == avl)
    {
        return (NULL);
    }

    avl->cmp = cmp_func;
    avl->param = param;

    (avl->root).child[LEFT] = NULL;
    (avl->root).child[RIGHT] = NULL;
    (avl->root).data = NULL;
    (avl->root).height = 0;

    return (avl);
}

/*******************************************************************************
* Releases the memory that has been allocted for the AVL. (POST ORDER)
*******************************************************************************/
void AVLDestroy(avl_t *avl)
{
    RecursiveDestroy((avl->root.child[LEFT]));

    free(avl);
}

/*******************************************************************************
* Counts the elements in the AVL. (PRE ORDER)
*******************************************************************************/
size_t AVLCount(const avl_t *avl)
{
    return (RecursiveCount(avl->root.child[LEFT]));
}

/*******************************************************************************
 * Checks if the AVL is empty.
 ******************************************************************************/
int AVLIsEmpty(const avl_t *avl)
{
    return (avl->root.child[0] == NULL);
}

/*******************************************************************************
* Inserts new node to the AVL.
*******************************************************************************/
int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t *new_node = AVLCreateNode(data);

    if (NULL == new_node)
    {
        return (0);
    }

    if (NULL == avl->root.child[LEFT])
    {
        avl->root.child[LEFT] = new_node;
        avl->root.height = 1;
    /*    printf("** after insert **\n");
        print2D(avl->root.child[0]);*/
        return (1);
    }

    RecursiveInsert(&(avl->root), new_node, avl->cmp, avl->param);

    /*printf("** after insert before balance **\n");
    print2D(avl->root.child[0]);*/

    avl->root.height = ReturnMaxHeight(&(avl->root)) + 1;

    printf("** after insert after balance **\n");
    print2D(avl->root.child[0]);

    return (1);
}

/*******************************************************************************
* Removes a node from the AVL.
*******************************************************************************/
void *AVLRemove(avl_t *avl, const void *data)
{
    void *removed_data = NULL;

    /*printf("** before remove of %d and before balance **\n", *(int *)data);
    print2D(avl->root.child[0]);*/
    removed_data = RecursiveRemove(&(avl->root), avl->root.child[0], data,
    											avl->cmp, avl->param);

    avl->root.height = ReturnMaxHeight(&(avl->root)) + (AVLCount(avl) > 0);

/*    printf("** after remove of %d and after balance **\n", *(int *)data);
    print2D(avl->root.child[0]);*/

    return (removed_data);
}

/*******************************************************************************
* Executes a command (cmd) given by the user with arg in given range. (IN ORDER)
*******************************************************************************/
int AVLForEach(avl_t *avl, int (*action_func)(void* data, void *param),
                                                                    void *param)
{
    return(RecursiveForEach(avl->root.child[LEFT], action_func, param));
}

/*******************************************************************************
* Executes comparison with cmp_func given in CreateAVL by the user with arg
* in given range.
*******************************************************************************/
void *AVLFind(const avl_t *avl, const void *arg)
{
    avl_node_t *father = (avl_node_t *)&(avl->root);
    avl_node_t *return_node = RecursiveFindFather(father, avl->root.child[LEFT],
                                                    avl->cmp, arg, avl->param);
    if (NULL != return_node)
    {
        return (ExtractSonFromFather(avl, return_node, (void *)arg)->data);
    }

    return NULL;
}

/*******************************************************************************
* Calculates the height of the tree, which is the largest sub tree.
*******************************************************************************/
size_t AVLHeight(const avl_t *avl)
{
    if (!AVLIsEmpty(avl))
    {
        return (avl->root.height);
    }

    return (0);
}


/*******************************************************************************
                        INNER FUNCTION IMPLEMANTATIONS
*******************************************************************************/

static avl_node_t *RecursiveInsert(avl_node_t *avl_node, avl_node_t *new_node,
                                                    cmp_func_t cmp, void *param)
{
    int value = 0;
    avl_node_t *temp_node = avl_node;

    if (avl_node->data != NULL)
    {
        value = cmp(new_node->data, avl_node->data, param);

        if (value > 0)
        {
            if (AVLHasRightChild(avl_node))
            {
                temp_node = RecursiveInsert(avl_node->child[RIGHT], new_node, cmp, param);
            }
            else
            {
                avl_node->child[RIGHT] = new_node;
            }
        }
        else if (value < 0)
        {
            if (AVLHasLeftChild(avl_node))
            {
                temp_node =RecursiveInsert(avl_node->child[LEFT], new_node, cmp, param);
            }
            else
            {
                avl_node->child[LEFT] = new_node;
            }
        }
    }
    else
    {
        temp_node =RecursiveInsert(avl_node->child[LEFT], new_node, cmp, param);
    }

    avl_node->height = ReturnMaxHeight(avl_node) + 1;
    BalanceAVL(avl_node, temp_node);
    return(avl_node);
}

static size_t RecursiveCount(avl_node_t *node)
{
    if (node != NULL)
    {
        return (1 + RecursiveCount(node->child[LEFT]) +
                                            RecursiveCount(node->child[RIGHT]));
    }

    return (0);
}

static avl_node_t *RecursiveFindFather(avl_node_t *father, avl_node_t *son,
                                cmp_func_t cmp, const void *data, void *param)
{
    int value = 0;
    if (NULL == son)
    {
        return NULL;
    }
    else
    {
        value = cmp(data, son->data, param);

        if (value < 0)
        {
            return(RecursiveFindFather(son, son->child[LEFT], cmp, data, param));
        }
        else if (value > 0)
        {
            return(RecursiveFindFather(son, son->child[RIGHT], cmp, data, param));
        }
        else
        {
            return (father);
        }
    }
}

static void *RecursiveRemove(avl_node_t *father, avl_node_t *son,
                                const void* data, cmp_func_t cmp, void *param)
{
    int value = 0;
    avl_node_t *removed_node = NULL;
    int which_child = DetermineWhichChild(father, son);

    if (NULL == son)
    {
        return NULL;
    }
    else
    {
        value = cmp(data, son->data, param);

        if (value < 0)
        {
            removed_node = RecursiveRemove(son, son->child[LEFT], data, cmp, param);
        }
        else if (value > 0)
        {
            removed_node = RecursiveRemove(son, son->child[RIGHT], data, cmp, param);
        }
        else
        {
            removed_node = RemoveNode(father, son);
        }
    }

	/*if (NULL != removed_node)
	{*/
	    DetermineHeights(father);
	/*    print2D(father->child[which_child]);*/
	    BalanceAVL(father, father->child[which_child]);

		if (NULL != father->child[which_child])
		{
			BalanceAVL(father->child[which_child], father->child[which_child]->child[LEFT]);
			BalanceAVL(father->child[which_child], father->child[which_child]->child[RIGHT]);
		}
	/*}*/
    return (removed_node);
}

static avl_node_t *AVLCreateNode(void *data)
{
    avl_node_t *new_node = malloc(sizeof(avl_node_t));

    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->data = data;
    new_node->height = 0;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;

    return (new_node);
}

static int AVLHasLeftChild(avl_node_t *runner)
{
    return (NULL != runner->child[LEFT]);
}

static int AVLHasRightChild(avl_node_t *runner)
{
    return (NULL != runner->child[RIGHT]);
}

static int ReturnMaxHeight(avl_node_t *node)
{
    int max = 0;

    if (AVLHasLeftChild(node))
    {
        max = node->child[LEFT]->height;
    }

    if (AVLHasRightChild(node))
    {
        if (node->child[RIGHT]->height > max)
        {
            max = node->child[RIGHT]->height;
        }
    }

    return (max);
}

static void RemoveBothChildren(avl_node_t *node_to_remove,
                        avl_node_t *father_of_node_to_remove, int which_child)
{
    father_of_node_to_remove->child[which_child] = node_to_remove->child[RIGHT];

    AddLeftChild(node_to_remove->child[RIGHT], node_to_remove->child[LEFT]);
}

static void AddLeftChild(avl_node_t *tree, avl_node_t *added_node)
{
    if (NULL == tree->child[LEFT])
    {
        tree->child[LEFT] = added_node;
    }
    else
    {
        AddLeftChild(tree->child[LEFT], added_node);
    }
    tree->height = ReturnMaxHeight(tree) + 1;
}

static void RemoveOneChild(avl_node_t *node_to_remove,
                        avl_node_t *father_of_node_to_remove, int which_child)
{
    int which_child_to_append = (node_to_remove->child[RIGHT] != NULL);

    father_of_node_to_remove->child[which_child] =
                        node_to_remove->child[which_child_to_append];

    father_of_node_to_remove->child[which_child]->height =
                ReturnMaxHeight(father_of_node_to_remove);
}

static void RemoveChildless(avl_node_t *father_of_node_to_remove,
                                                                int which_child)
{
    father_of_node_to_remove->child[which_child] = NULL;

    father_of_node_to_remove->height = 0;
}

static void RecursiveDestroy(avl_node_t *node)
{
    if (NULL != node)
    {
        RecursiveDestroy(node->child[LEFT]);
        RecursiveDestroy(node->child[RIGHT]);

        node->child[LEFT] = NULL;
        node->child[RIGHT] = NULL;

        if ((!AVLHasLeftChild(node)) && (!AVLHasRightChild(node)))
        {
            free(node);
        }
    }
}

static avl_node_t *ExtractSonFromFather(const avl_t *avl, avl_node_t *father,
                                                                    void *arg)
{
    avl_node_t *node = NULL;

    if (father == &(avl->root))
    {
        node = father->child[LEFT];
    }
    else if (avl->cmp(arg, father->data, avl->param) > 0)
    {
        node = father->child[RIGHT];
    }
    else
    {
        node = father->child[LEFT];
    }

    return (node);
}

static int RecursiveForEach(avl_node_t *node,
                        int (*action_func)(void* data, void *param), void *param)
{
    if (node == NULL)
    {
        return(1);
    }
    else
    {
        return(RecursiveForEach(node->child[LEFT], action_func, param) &&
                action_func(node->data, param) &&
                        RecursiveForEach(node->child[RIGHT], action_func, param));
    }
}

static void BalanceAVL( avl_node_t *father, avl_node_t *son)
{
    int problem = 0;

    if (NULL != son)
    {
		int which_child = DetermineWhichChild(father, son);
        /*BalanceAVL(son, son->child[LEFT]);
        BalanceAVL(son, son->child[RIGHT]);*/

        if (((DetermineHeightDiff(son) > 1) || (DetermineHeightDiff(son) < -1)))
        {
            problem = IdentifyProblem(son);
            if (problem >= 0)
            {
                father->child[which_child] = balance_func_lut[problem](son);
				BalanceAVL(father, father->child[which_child]);
            }
        }
		DetermineHeights(father);
    }

    /*print2D(son);*/
}

static int DetermineHeightDiff(avl_node_t *node)
{
    if (AVLHasRightChild(node) && AVLHasLeftChild(node))
    {
        return (node->child[LEFT]->height - node->child[RIGHT]->height);
    }
    else if (AVLHasLeftChild(node))
    {
        return (node->child[LEFT]->height + 1);
    }
    else if (AVLHasRightChild(node))
    {
        return (-1 - node->child[RIGHT]->height);
    }
    else
    {
        return 0;
    }
}

static avl_node_t *RotateRight(avl_node_t *node)
{
    avl_node_t *root = node->child[LEFT];

    node->child[LEFT] = root->child[RIGHT];
    root->child[RIGHT] = node;

    root->child[RIGHT]->child[RIGHT] = node->child[RIGHT];

    DetermineHeights(root);
    return(root);
}

static avl_node_t *RotateLeft(avl_node_t *node)
{
    avl_node_t *root = node->child[RIGHT];

    node->child[RIGHT] = root->child[LEFT];
    root->child[LEFT] = node;

    root->child[LEFT]->child[LEFT] = node->child[LEFT];

    DetermineHeights(root);
    return(root);
}

static avl_node_t *RightLeftBalance(avl_node_t *node)
{
    avl_node_t *right_left_rotation = NULL;

    node->child[LEFT] = RotateLeft(node->child[LEFT]);
    right_left_rotation = RotateRight(node);
    DetermineHeights(node);

    return (right_left_rotation);
}

static avl_node_t *LeftRightBalance(avl_node_t *node)
{
    avl_node_t *left_right_rotation = NULL;

    node->child[RIGHT] = RotateRight(node->child[RIGHT]);
    left_right_rotation = RotateLeft(node);
    DetermineHeights(node);

    return (left_right_rotation);
}

static int DetermineWhichChild(avl_node_t *father, avl_node_t *son)
{
    return (father->child[RIGHT] == son);
}

void print2D(avl_node_t *node)
{
    printf("***************************\n");
    print2DUtil(node, 0);
    printf("***************************\n");
}

void print2DUtil(avl_node_t *node, int space)
{
   size_t i = 0;
   if (node == NULL)
       return;
   space += COUNT;
   print2DUtil(node->child[1], space);
   printf("\n");
   for (i = COUNT; i < (size_t)space; i++)
   printf(" ");
   printf("%d (h=%d)\n", *(int *)node->data, node->height);
   print2DUtil(node->child[0], space);
}

static int IdentifyProblem(avl_node_t *node)
{
    if (DetermineHeightDiff(node) > 0)
    {
        if (AVLHasLeftChild(node->child[LEFT]))
        {
            if (RightChildHasLargerHeight(node->child[LEFT]))
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if (AVLHasRightChild(node->child[RIGHT]))
        {
            if (RightChildHasLargerHeight(node->child[RIGHT]))
            {
                return 1;
            }
            else
            {
                return 3;
            }
        }
    }

    return -1;
}

static void DetermineHeights(avl_node_t *node)
{
    if (NULL != node)
    {
        DetermineHeights(node->child[LEFT]);
        DetermineHeights(node->child[RIGHT]);

        if ((!AVLHasLeftChild(node)) && (!AVLHasRightChild(node)))
        {
            node->height = 0;
        }
        else
        {
            node->height = ReturnMaxHeight(node) + 1;
        }
    }
}

static int RightChildHasLargerHeight(avl_node_t *node)
{
    int right_height = 0;
    int left_height = 0;

    if (AVLHasRightChild(node) && AVLHasLeftChild(node))
    {
        right_height = node->child[RIGHT]->height;
        left_height = node->child[LEFT]->height;
    }
    else if (AVLHasRightChild(node))
    {
        right_height = node->child[RIGHT]->height;
        left_height = -1;
    }
    else if (AVLHasLeftChild(node))
    {
        right_height = -1;
        left_height = node->child[LEFT]->height;
    }

    return (right_height >= left_height);
}

static avl_node_t *RemoveNode(avl_node_t *father, avl_node_t *son)
{
    void *removed_data = NULL;

    int which_child = 0;

    if (NULL != father)
    {
        which_child = (son == father->child[RIGHT]);

        if ((AVLHasLeftChild(son)) && (AVLHasRightChild(son)))
    	{
    		RemoveBothChildren(son, father, which_child);
    	}
    	else if (AVLHasLeftChild(son) || AVLHasRightChild(son))
    	{
    		RemoveOneChild(son, father, which_child);
    	}
    	else
    	{
    		RemoveChildless(father, which_child);
    	}

        removed_data = son->data;

        free(son);

        return (removed_data);
    }

    return NULL;
}

static int GetData(avl_node_t *node)
{
	return (*(int *)node->data);
}
