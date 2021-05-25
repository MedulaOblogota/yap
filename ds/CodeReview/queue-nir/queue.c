/**********************************************
*Name: Nir                                    *
*Reviewer: Roy                                *
*OL70 --Queue                                 *
*Version: Review                              *
*Last Update 10/7/19                          *
*                                             *
**********************************************/
#include "queue.h"
#include "sllist.h"
#include <stdlib.h>
#include <assert.h>

struct queue_s
{
    sll_node_t *head;
    sll_node_t *tail;
};

queue_t *QueueCreate()
{
    char *head_data = "ThisIsTheHead";
    char *tail_data = "ThisIsTheTail";
    queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));

    if(NULL == new_queue)
    {
        return (NULL);
    }

    new_queue->tail = SLLCreateNode((void *)tail_data, NULL);

    if(NULL == new_queue->tail)
    {
        free(new_queue);

        return (NULL);
    }

    new_queue->head = SLLCreateNode((void *)head_data, new_queue->tail);
    if(NULL == new_queue->head)
    {
        SLLFreeAll(new_queue->tail);
        free(new_queue);

        return (NULL);
    }

    return (new_queue);
}

void QueueDestroy(queue_t *queue)
{
    assert(NULL != queue);

    SLLFreeAll(queue->head);

    free(queue);

    return;
}

int QueueEnqueue(queue_t *queue, void *data)
{
    sll_node_t *new_node = NULL;
    new_node = SLLCreateNode(data, NULL);

    if (NULL == new_node)
    {
        return (0);
    }

    new_node = SLLInsert(queue->tail, new_node);
    queue->tail = (queue->tail)->next;

    return (1);
}

void QueueDequeue(queue_t *queue)
{
    sll_node_t *node_to_remove = NULL;

    assert(NULL != queue);

    if (1 != QueueIsEmpty(queue))
    {
        node_to_remove = SLLRemoveAfter(queue->head);
        SLLFreeAll(node_to_remove);
    }

    return;
}

size_t QueueSize(const queue_t *queue)
{
    size_t size = 0;
    sll_node_t *queue_runner = NULL;

    assert(NULL != queue);

    queue_runner = queue->head;

    while (queue->tail != (queue_runner->next))
    {
        queue_runner = queue_runner->next;
        ++size;
    }

    return (size);
}

void *QueuePeek(queue_t *queue)
{
    void *peeking_tom = NULL;

    assert(NULL != queue);

    peeking_tom = ((queue->head)->next)->data;

    if ((queue->tail)->data == peeking_tom)
    {
        peeking_tom = NULL;
    }

    return (peeking_tom);
}

int QueueIsEmpty(const queue_t *queue)
{
    int status = 0;

    assert(NULL != queue);

    if((queue->head)->next == queue->tail)
    {
        status = 1;
    }

    return (status);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
    sll_node_t *saved_dest_tail = NULL;

    assert(NULL != dest);
    assert(NULL != src);

    if(QueueIsEmpty(src))
    {
        return (dest);
    }

    (dest->tail)->next = (src->head)->next;
    saved_dest_tail = SLLRemove(dest->tail);

    dest->tail = src->tail;
    src->tail = saved_dest_tail;
    (src->head)->next = src->tail;

    return (dest);
}
