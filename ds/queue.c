#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "queue.h"
#include "sllist.h"

struct queue_s
{
    sll_node_t *head;
    sll_node_t *tail;
};

/***************************************************************
* Allocates the memory for Queue                               *
****************************************************************/
queue_t *QueueCreate()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));

    if (NULL == queue)
    {
        return (NULL);
    }

    queue->tail = SLLCreateNode((void *)LONG_MAX, NULL);

    if (NULL == queue->tail)
    {
        free(queue);    queue = NULL;
        return (NULL);
    }

    queue->head = SLLCreateNode((void *)LONG_MAX, queue->tail);
    if (NULL == queue->tail)
    {
        free(queue->tail);  queue->tail = NULL;

        free(queue);    queue = NULL;
        return (NULL);
    }

    return (queue);
}

/**************************************************************
* Releases the memory that has been allocated for the Queue  *
***************************************************************/
void QueueDestroy(queue_t *queue)
{
    sll_node_t *temp = NULL;

    assert(NULL != queue);

    SLLFreeAll(queue->head);    queue->head = NULL;

    free(queue);    queue = NULL;
}

/**************************************************************
* Pushes pointer to the queue.          				      *
***************************************************************/
int QueueEnqueue(queue_t *queue, void *data)
{
    sll_node_t *node = SLLCreateNode(data, NULL);
    /*sll_node_t *inserted_node = NULL;*/
    assert(NULL != queue);

    if (NULL == node)
    {
        return (0);
    }

    queue->tail = SLLInsert(queue->tail, node)->next;
    /*SLLFreeAll(inserted_node);*/

    return (1);
}

/**************************************************************
* Releases the first element from the start of the queue.     *
***************************************************************/
void QueueDequeue(queue_t *queue)
{
    sll_node_t *removed_node = NULL;

    assert(NULL != queue);

    if (queue->head->next != queue->tail)
    {
        removed_node = SLLRemoveAfter(queue->head);
        SLLFreeAll(removed_node);
    }
}

/**************************************************************
* Returns the number of elements in the Queue.  		      *
***************************************************************/
size_t QueueSize(const queue_t *queue)
{
    if (!QueueIsEmpty(queue))
    {
        return (SLLCount(queue->head) - 2);
    }

    return (0);
}

/********************************************************
*-Returns a pointer to the element on top of the Queue   *
*********************************************************/
void *QueuePeek(queue_t *queue)
{
    assert(NULL != queue);

    if (!QueueIsEmpty(queue))
    {
        return (queue->head->next->data);
    }

    return (NULL);
}

/**************************************************************
* Return TRUE (1) if the Queue is empty. (0) otherwise.       *               		  		   *
***************************************************************/
int QueueIsEmpty(const queue_t *queue)
{
    assert(NULL != queue);

    return (queue->head->next == queue->tail);
}

/**************************************************************
* combine dest and src to one queue starting on dest           *
***************************************************************/
queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
    assert(NULL != dest);
    assert(NULL != src);

    if (!QueueIsEmpty(src))
    {
        dest->tail->next = src->head->next;
        src->head->next = SLLRemove(dest->tail);

        dest->tail = src->tail;
        src->tail = src->head->next;
    }

    return(dest);
}
