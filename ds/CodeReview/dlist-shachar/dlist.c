#include <stdlib.h> /* size_t, malloc, free */
#include <assert.h>

#include "dlist.h"

#define DUMMY_DATA ((void*)(0xDEADBEEF))

typedef struct dlist_node_s dlist_node_t;

struct dlist_node_s
{
	dlist_node_t *next;
	dlist_node_t *prev;
	void *data;
};

struct dlist_s
{
	dlist_node_t *head;
	dlist_node_t *tail;
};

static dlist_node_t *DlistCreateNodeConv(dlist_node_t *next, dlist_node_t *prev, void *data)
{
	dlist_node_t *new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return(NULL);
	}

	new_node->next = next;
	new_node->prev = prev;
	new_node->data = data;

	return(new_node);
}

dlist_t *DlistCreate()
{
	dlist_t *new_dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == new_dlist)
	{
		return(NULL);
	}

	new_dlist->tail = DlistCreateNodeConv(NULL, NULL, DUMMY_DATA);
	if (NULL == new_dlist->tail)
	{
		free(new_dlist);
		new_dlist = NULL;

		return(NULL);
	}

	new_dlist->head = DlistCreateNodeConv(NULL, NULL, DUMMY_DATA);
	if (NULL == new_dlist->head)
	{
		free(new_dlist);
		new_dlist = NULL;
		free(new_dlist->tail);
		new_dlist->tail = NULL;

		return(NULL);
	}

	new_dlist->head->next = new_dlist->tail;
	new_dlist->tail->prev = new_dlist->head;

	return(new_dlist);
}

dlist_iter_t DlistErase(dlist_iter_t iter)
{
	dlist_iter_t return_iter = NULL;
	dlist_node_t *removed_node = NULL;

	assert(NULL != iter);

	removed_node = (dlist_node_t *)iter;
	return_iter = (dlist_iter_t)removed_node->next;

	removed_node->prev->next = removed_node->next;
	removed_node->next->prev = removed_node->prev;

	removed_node->prev = NULL;
	removed_node->next = NULL;
	free(removed_node);
	removed_node = NULL;

	return(return_iter);
}

int DlistIsEmpty(const dlist_t *dlist)
{
	assert(NULL != dlist);
/*TODO: please follow conventions */
	return (dlist->head->next == dlist->tail && dlist->tail->prev == dlist->head);
}

void DlistDestroy(dlist_t *dlist)
{
	dlist_iter_t current_node = NULL;

	assert(NULL != dlist);

/*TODO: when you have such a name I would just use the function name instead of comparing it to 0
I understand the conventions are this way */
	if(0 == DlistIsEmpty(dlist))
	{
		current_node = (dlist_iter_t)(dlist->head->next);

		while (current_node != (dlist_iter_t)(dlist->tail))
		{
			current_node = DlistErase(current_node);
		}
	}

	free(dlist->head);
	dlist->head = NULL;
	free(dlist->tail);
	dlist->tail = NULL;
	free(dlist);
	dlist = NULL;

	return;
}

size_t DlistCount(const dlist_t *dlist)
{
	dlist_node_t *current_node = NULL;
	size_t cnt = 0;

	assert (NULL != dlist);

	current_node = dlist->head->next;

	while(current_node != dlist->tail)
	{
		++cnt;
		current_node = current_node->next;
	}

	return(cnt);
}

/*TODO: instead of duplicating code, you can use DlistInsertAfter for the previous item */
dlist_iter_t DlistInsertBefore(dlist_t *dlist, dlist_iter_t iter, void *data)
{
	dlist_node_t *new_node = NULL;

	assert(NULL != dlist);

	new_node = DlistCreateNodeConv((dlist_node_t*)iter, ((dlist_node_t*)iter)->prev, data);
	if(NULL == new_node)
	{
		return((dlist_iter_t)dlist->tail);
	}

	((dlist_node_t*)iter)->prev->next = new_node;
	((dlist_node_t*)iter)->prev = new_node;

	return(new_node);
}

dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data)
{
	dlist_node_t *new_node = NULL;

	assert(NULL != dlist);

	if(iter == DlistEnd(dlist))
	{
		return(DlistEnd(dlist));
	}

	new_node = DlistCreateNodeConv(((dlist_node_t*)iter)->next, ((dlist_node_t*)iter), data);
	if(NULL == new_node)
	{
		return((dlist_iter_t)dlist->tail);
	}

	((dlist_node_t*)iter)->next->prev = new_node;
	((dlist_node_t*)iter)->next = new_node;

	return(new_node);
}

dlist_iter_t DlistPushFront(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);

	return(DlistInsertAfter(dlist, (dlist_iter_t)dlist->head, data));
}

dlist_iter_t DlistPushBack(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);

	return(DlistInsertBefore(dlist, (dlist_iter_t)dlist->tail, data));
}

void DlistPopFront(dlist_t *dlist)
{
	assert(NULL != dlist);

/*TODO again, I would just use the function name, your decision */
	if(0 == DlistIsEmpty(dlist))
	{
		DlistErase((dlist_iter_t)dlist->head->next);
	}

	return;
}

void DlistPopBack(dlist_t *dlist)
{
	assert(NULL != dlist);

	if(0 == DlistIsEmpty(dlist))
	{
		DlistErase((dlist_iter_t)dlist->tail->prev);
	}

	return;
}

void *DlistGetData(const dlist_iter_t iter)
{
	return(((dlist_node_t *)iter)->data);
}

dlist_iter_t DlistBegin(const dlist_t *dlist)
{
	assert(NULL != dlist);

	return((dlist_iter_t)dlist->head->next);
}

dlist_iter_t DlistEnd(const dlist_t *dlist)
{
	assert(NULL != dlist);

	return((dlist_iter_t)dlist->tail);
}

int DlistIsSame(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	return(iter1 == iter2);
}

dlist_iter_t DlistGetNext(const dlist_iter_t iter)
{
	return((dlist_iter_t)((dlist_node_t *)iter)->next);
}

dlist_iter_t DlistGetPrev(const dlist_iter_t iter)
{
	return((dlist_iter_t)((dlist_node_t *)iter)->prev);
}

status_t DlistForEach(dlist_iter_t from, dlist_iter_t to, cmd_func_t cmd, void *arg)
{
	dlist_node_t *current_node = (dlist_node_t *)from;
	status_t func_status = CONTINUE;
/*TODO why do you check if current_node->next is NULL? */
	while((current_node != ((dlist_node_t *)to)->next) &&
			(current_node->next != NULL) &&
			(func_status != STOP))
	{
		func_status = cmd((dlist_iter_t)current_node, arg);
		current_node = current_node->next;
	}

	return(func_status);
}

dlist_iter_t DlistFind(dlist_iter_t from, dlist_iter_t to, comp_func_t comp, void *arg)
{
	dlist_node_t *current_node = (dlist_node_t *)from;

	assert(NULL != from);
	assert(NULL != to);

	while((current_node != ((dlist_node_t *)to)/*->next*/) &&
			(current_node->next != NULL) &&/*TODO why do you check if current_node->next is NULL? */
			(comp(current_node->data, arg) != STOP))
	{
		current_node = current_node->next;
	}

	return((dlist_iter_t)current_node);
}


void DlistSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_node_t *from_node = NULL;
    dlist_node_t *to_node = NULL;
    dlist_node_t *where_node = NULL;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);

	from_node = (dlist_node_t *)from;
	to_node = (dlist_node_t *)to;
	where_node = (dlist_node_t *)where;

    from_node->prev->next = to_node->next;
    to_node->next->prev = from_node->prev;

    from_node->prev = where_node->prev;
    to_node->next = where_node;

    where_node->prev->next = from_node;
    where_node->prev = to_node;

    return;

}
