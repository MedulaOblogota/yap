#include <stdlib.h>
#include "fsq.h"


struct fsq_s
{
	size_t size;
	int *queue;
	size_t first_element;
	size_t elements_in_queue;
};



fsq_t *FSQCreate(size_t size)
{
	fsq_t *fsq = malloc(sizeof(fsq_t));

	if (NULL == fsq)
	{
		return NULL;
	}

	fsq->queue = malloc(sizeof(int) * size);

	if (NULL == fsq->queue)
	{
		free(fsq);
		return NULL;
	}

	fsq->size = size;
	fsq->first_element = 0;
	fsq->elements_in_queue = 0;

	return(fsq);
}

void FSQDestroy(fsq_t *fsq)
{
	free(fsq->queue);
	free(fsq);
}

int FSQEnqueue(fsq_t *fsq, int element)
{
	size_t index = 0;

	if (fsq->elements_in_queue == fsq->size)
	{
		return 1;
	}

	index = (fsq->first_element + fsq->elements_in_queue) % fsq->size;

	fsq->queue[index] = element;

	++(fsq->elements_in_queue);

	return (0);
}

int FSQDequeue(fsq_t *fsq)
{
	int return_val = fsq->queue[fsq->first_element];

	--(fsq->elements_in_queue);
	++(fsq->first_element);

	fsq->first_element = fsq->first_element % fsq->size;

	return (return_val);
}

int FSQIsEmpty(fsq_t *fsq)
{
	return (fsq->elements_in_queue == 0);
}
