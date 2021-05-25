#ifndef QUEUE_OL70 /*header guard*/
#define QUEUE_OL70
/**************************************************************
* The functions in this file handle a Queue data              *
* structure, and will be denoted as Queue.                    *
*                    										  *
* Written by: OL-70   										  *
* Last update: 18:00 08.07.2019                    			  *
***************************************************************/
#include <stddef.h>

typedef struct queue_s queue_t;

/***************************************************************
* Allocates the memory for Queue                               *
* QueueDestroy must be called after the work with the          *
* Queue is done.									           *
*														       *
* Return Value: A pointer to the New Queue                     *
****************************************************************/
queue_t *QueueCreate();

/**************************************************************
* Releases the memory that has been allocated for the Queue  *
***************************************************************/
void QueueDestroy(queue_t *queue);

/**************************************************************
* Pushes pointer to the queue.          				      *
* data is a pointer to an element                  	          *
* queue - the queue's address                                 *
*														      *
* Return Value: 1 if success 0 if fail.	          		      *
***************************************************************/
int QueueEnqueue(queue_t *queue, void *data);

/**************************************************************
* Releases the first element from the start of the queue.     *
***************************************************************/
void QueueDequeue(queue_t *queue);

/**************************************************************
* Returns the number of elements in the Queue.  		      *
***************************************************************/
size_t QueueSize(const queue_t *queue);

/********************************************************
*-Returns a pointer to the element on top of the Queue   *
*********************************************************/
void *QueuePeek(queue_t *queue);

/**************************************************************
* Return TRUE (1) if the Queue is empty.			  		   *
* Return FALSE (0) otherwise.                		  		   *
***************************************************************/
int QueueIsEmpty(const queue_t *queue);

/**************************************************************
* combine dest and src to one queue starting on dest           *
* after appending src is empty queue					      *
* Return pointer to the start of the new queue (dest)	       *
***************************************************************/
queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /*QUEUE_OL70*/
