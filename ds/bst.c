/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Adam Blau
Version:	Fixing
Title:		BST Source File
*******************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "bst.h"

#define NUM_OF_CHILDRENS (2)
#define LEFT (0)
#define RIGHT (1)

struct bst_node_s
{
   bst_iter_t *parent;
   bst_iter_t *child[NUM_OF_CHILDRENS];
   void *data;
};

struct bst_s
{
   bst_node_t root;
   cmp_func_t cmp;
   void *param;
};

/*******************************************************************************
                    STATIC FUNCTIONS FOR INNER USE
*******************************************************************************/

static bst_node_t *BSTCreateNode(void *data);

static int BSTHasLeftChild(bst_node_t *runner);

static int BSTHasRightChild(bst_node_t *runner);

static void RemoveBothChildren(bst_iter_t *iter, bst_iter_t *right_child, bst_iter_t *left_child, int which_child);

static void RemoveOneChild(bst_iter_t *iter, bst_iter_t *child, int which_child);

static void RemoveChildless(bst_iter_t *iter, int which_child);

/*******************************************************************************
                    FUNCTION IMPLEMANTATIONS
*******************************************************************************/
bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{
    bst_t *tree = malloc(sizeof(bst_t));

    if (NULL == tree)
    {
        return (NULL);
    }

    tree->cmp = cmp_func;
    tree->param = param;

    (tree->root).parent = NULL;
    (tree->root).child[LEFT] = NULL;
    (tree->root).child[RIGHT] = NULL;
    (tree->root).data = NULL;

    return (tree);

}

void BSTDestroy(bst_t *bst)
{
    assert (NULL != bst);

    while (!BSTIsEmpty(bst))
    {
		BSTRemove(BSTBegin(bst));
    }

    free(bst);
}

size_t BSTCount(const bst_t *bst)
{
	size_t counter = 0;
	bst_node_t *runner = NULL;

    assert(NULL != bst);

    runner = BSTBegin((bst_t *)bst);

	while (runner != BSTEnd((bst_t *)bst))
	{
		runner = BSTNext(runner);
		++counter;
	}

	return (counter);
}

int BSTIsEmpty(const bst_t *bst)
{
    assert(NULL != bst);

    return (bst->root.child[LEFT] == bst->root.child[RIGHT]);
}

bst_iter_t *BSTBegin(bst_t *bst)
{
    bst_node_t *runner = NULL;

    assert (NULL != bst);

    runner = bst->root.child[LEFT];

    if (BSTIsEmpty(bst))
    {
        return (BSTEnd(bst));
    }
    else
    {
        while (BSTHasLeftChild(runner))
        {
            runner = runner->child[LEFT];
        }
    }

    return(runner);
}

bst_iter_t *BSTEnd(bst_t *bst)
{
    assert(NULL != bst);

    return (&(bst->root));
}

bst_iter_t *BSTNext(bst_iter_t *iter)
{
	bst_node_t *next_node = NULL;

    assert(NULL != iter);

	if (BSTHasRightChild(iter))
	{
		next_node = iter->child[RIGHT];

		while (BSTHasLeftChild(next_node))
		{
			next_node = next_node->child[LEFT];
		}
	}

	if (NULL == next_node)
	{
		next_node = iter;

		while (next_node->parent != NULL)
		{
			iter = next_node;
			next_node = iter->parent;

			if (next_node->child[LEFT] == iter)
			{
				return(next_node);
			}
		}
	}

	return (next_node);
}

bst_iter_t *BSTPrev(bst_iter_t *iter)
{
	bst_node_t *prev_node = NULL;

    assert(NULL != iter);

	if (BSTHasLeftChild(iter))
	{
		prev_node = iter->child[LEFT];

		while (BSTHasRightChild(prev_node))
		{
			prev_node = prev_node->child[RIGHT];
		}
	}

	if (NULL == prev_node)
	{
		prev_node = iter;

		while (prev_node->parent != NULL)
		{
			iter = prev_node;
			prev_node = iter->parent;

			if (prev_node->child[RIGHT] == iter)
			{
				return(prev_node);
			}
		}
	}

	return (prev_node);
}

void *BSTGetData(bst_iter_t *iter)
{
	assert(NULL != iter);

    return(iter->data);
}

bst_iter_t *BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *runner = NULL;
    bst_node_t *temp = NULL;
    bst_node_t *new_node = NULL;

    void *data_in_node = NULL;
    int bigger = 0;

    assert (NULL != bst);
    assert (NULL != data);

    runner = bst->root.child[LEFT];
    temp = &(bst->root);

    new_node = BSTCreateNode(data);

    if (NULL == new_node)
    {
        return (BSTEnd(bst));
    }

    while (NULL != runner)
    {
        temp = runner;
        data_in_node = BSTGetData(runner);

        if (bst->cmp(data, data_in_node, bst->param) > 0)
        {
            runner = runner->child[RIGHT];
            bigger = 1;
        }
        else
        {
            runner = runner->child[LEFT];
            bigger = 0;
        }
    }

    temp->child[bigger] = new_node;
    new_node->parent = temp;

    return(new_node);
}

void *BSTRemove(bst_iter_t *iter)
{
    void *data = NULL;
	bst_node_t *left_child = NULL;
	bst_node_t *right_child = NULL;
	int which_child = 0;

    assert(NULL != iter);

    data = BSTGetData(iter);

    which_child = BSTIsSameIter(iter->parent->child[RIGHT], iter);
    left_child = iter->child[LEFT];
    right_child = iter->child[RIGHT];

	if ((BSTHasLeftChild(iter)) && (BSTHasRightChild(iter)))
	{
		RemoveBothChildren(iter, right_child, left_child, which_child);
	}
	else if (BSTHasLeftChild(iter))
	{
		RemoveOneChild(iter, left_child, which_child);
	}
	else if (BSTHasRightChild(iter))
	{
		RemoveOneChild(iter, right_child, which_child);
	}
	else
	{
		RemoveChildless(iter, which_child);
	}

	free(iter);

    return (data);
}


int BSTForEach(bst_iter_t *from, bst_iter_t *to,
                     int (*action_func)(void* data, void *param), void *param)
{
	bst_node_t *runner = from;
	int result = 1;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != action_func);

	while ((!BSTIsSameIter(runner, to)) && (result == 1))
	{
		result = action_func(BSTGetData(runner), param);
		runner = BSTNext(runner);
	}

	return (result);
}

bst_iter_t *BSTFind(bst_t *bst, const void *arg)
{
	bst_node_t *runner = NULL;
    int comp_result = 0;

    assert(NULL != bst);
    assert(NULL != arg);

    runner = BSTBegin(bst);

	while (BSTEnd(bst) != runner)
	{
		comp_result = bst->cmp(BSTGetData(runner), arg, bst->param);

		if (comp_result < 0)
		{
			runner = BSTNext(runner);
		}
        else if (comp_result > 0)
        {
            runner = BSTEnd(bst);
            break;
        }

		if (comp_result == 0)
		{
			break;
		}
	}

	return (runner);
}

int BSTIsSameIter(bst_iter_t *iter1, bst_iter_t *iter2)
{
    return (iter1 == iter2);
}


/*******************************************************************************
                    STATIC FUNCTIONS FOR INNER USE
*******************************************************************************/

static bst_node_t *BSTCreateNode(void *data)
{
    bst_node_t *new_node = malloc(sizeof(bst_node_t));

    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->data = data;
    new_node->parent = NULL;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;

    return (new_node);
}

static int BSTHasLeftChild(bst_node_t *runner)
{
    return (NULL != runner->child[0]);
}

static int BSTHasRightChild(bst_node_t *runner)
{
    return (NULL != runner->child[1]);
}

static void RemoveBothChildren(bst_iter_t *iter, bst_iter_t *right_child, bst_iter_t *left_child, int which_child)
{
    bst_iter_t *runner = right_child;

    iter->parent->child[which_child] = right_child;
    right_child->parent = iter->parent;


    while (NULL != runner->child[LEFT])
    {
        runner = runner->child[LEFT];
    }

    runner->child[LEFT] = left_child;
    left_child->parent = runner;
}

static void RemoveOneChild(bst_iter_t *iter, bst_iter_t *child, int which_child)
{
    iter->parent->child[which_child] = child;
    child->parent = iter->parent;
}

static void RemoveChildless(bst_iter_t *iter, int which_child)
{
    iter->parent->child[which_child] = NULL;
}
