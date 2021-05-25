#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>

#include "heap.h"
#include "vector.h"

#define STARTING_NUM_OF_ELEMENTS (5)

struct heap_s
{
    cmp_func_t cmp_func;
    vector_t *d_vector;
	void *param;
};

/**************************************************************
				STATIC FUNCTIONS DEFINITION
***************************************************************/
static size_t GetParentIndex(size_t index);

static size_t GetLeftChildIndex(size_t index);

static size_t GetRightChildIndex(size_t index);

static void SwapData(vector_t *vector, size_t parent_index, size_t son_index);

static size_t FindSmallerChildIndex(heap_t *hash, size_t curr_item_index);

static int ItemHasChildren(vector_t *vector, size_t item_index);

static void *GetLeftChildData(vector_t *vector, size_t parent_index);

static void *GetRightChildData(vector_t *vector, size_t parent_index);

static void RemoveIndex(heap_t *heap, size_t index);

static ssize_t FindIndex(heap_t *heap, const void *data,
						int (*is_match)(const void *data1, const void *data2));

static size_t BubbleUp(heap_t *heap, size_t current_item_index);

static void PrintHeap(heap_t *heap);


/**************************************************************
* Allocates memory for the heap.                              *
***************************************************************/
heap_t *HeapCreate(cmp_func_t cmp_func, void *param)
{
	heap_t *heap = malloc(sizeof(heap_t));

	if (NULL == heap)
	{
		return (NULL);
	}

	heap->cmp_func = cmp_func;
	heap->d_vector = VectorCreate(sizeof(size_t), STARTING_NUM_OF_ELEMENTS);
	heap->param = param;

	if (NULL == heap->d_vector)
	{
		free(heap);
		return (NULL);
	}

	return (heap);
}


/**************************************************************
* Releases the memory that has been allocated for the heap    *
***************************************************************/
void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->d_vector);
	free(heap);
}


/*********************************************************************
* Pushes data to the heap. Returns 1 for success, 0 for failure.                            *
**********************************************************************/
int HeapPush(heap_t *heap, const void *data)
{
	vector_t *vector = NULL;
	void *parent_data = NULL;
	size_t child_index = 0;
	size_t parent_index = 0;

	assert(heap);
	assert(data);

	vector = heap->d_vector;

	if (0 == VectorPush(vector, &data))
	{
		return (0);
	}

	child_index = VectorSize(vector) - 1;
	parent_index = GetParentIndex(child_index);
	parent_data = VectorItemAddress(vector, parent_index);

	while (heap->cmp_func(data, (*(void **)parent_data), heap->param) < 0)
	{
		SwapData(vector, parent_index, child_index);

		child_index = parent_index;
		parent_index = GetParentIndex(child_index);
		parent_data = VectorItemAddress(vector, parent_index);
	}

	return (1);
}


/**************************************************************
* Releases element at root of heap.
***************************************************************/
void HeapPop(heap_t *heap)
{
	vector_t *vector = NULL;
	size_t last_item_index = 0;
	size_t curr_item_index = 0;

	assert(heap);

	vector = heap->d_vector;
	last_item_index = VectorSize(vector) - 1;

	if (!HeapIsEmpty(heap))
	{
		SwapData(vector, last_item_index, curr_item_index);
		VectorPop(vector);

		while (ItemHasChildren(vector, curr_item_index) && (HeapSize(heap) > 2))
		{
			curr_item_index = BubbleUp(heap, curr_item_index);
		}
	}
}

/**************************************************************
* Removes from heap the element that matches received data    *
***************************************************************/

void *HeapRemove(heap_t *heap, const void *data,
    int (*is_match)(const void *data1, const void *data2))
{
	ssize_t index_to_remove = 0;
	void **value = NULL;

	assert(heap);
	assert(data);
	assert(is_match);

	index_to_remove = FindIndex(heap, data, is_match);

	if (index_to_remove >= 0)
	{
		value = *(void **)VectorItemAddress(heap->d_vector, index_to_remove);
		RemoveIndex(heap, index_to_remove);
	}

	return (value);
}

/*************************************************************************
* Returns a pointer to the element at the root of the heap.              *
**************************************************************************/
void *HeapPeek(heap_t *heap)
{
	assert(heap);

	return (*(void **)VectorItemAddress(heap->d_vector, 0));
}

/**************************************************************
* Returns the number of elements in the heap.
***************************************************************/
size_t HeapSize(heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->d_vector));
}

/**************************************************************
* Returns: 1 if heap is empty; 0 otherwise.
***************************************************************/
int HeapIsEmpty(heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->d_vector) == 0);
}


/**************************************************************
				STATIC FUNCTIONS IMPLEMENTATION
***************************************************************/

static size_t GetParentIndex(size_t index)
{
	size_t parent_index = 0;

	if (index == 0)
	{
		parent_index = 0;
	}
	else
	{
		parent_index = ((index - 1) / 2);
	}

	return (parent_index);
}

static size_t GetLeftChildIndex(size_t index)
{
	return ((index * 2) + 1);
}

static size_t GetRightChildIndex(size_t index)
{
	return ((index * 2) + 2);
}

static void SwapData(vector_t *vector, size_t parent_index, size_t son_index)
{
	void **parent_data = VectorItemAddress(vector, parent_index);
	void **son_data = VectorItemAddress(vector, son_index);
	void *temp_data = *parent_data;

	*parent_data = *son_data;
	*son_data = temp_data;
}

static void *GetLeftChildData(vector_t *vector, size_t parent_index)
{
	size_t left_child_index = GetLeftChildIndex(parent_index);
	void *data = NULL;

	if (left_child_index < VectorSize(vector))
	{
		data = *(void **)VectorItemAddress(vector, left_child_index);
	}

	return (data);
}

static void *GetRightChildData(vector_t *vector, size_t parent_index)
{
	size_t right_child_index = GetRightChildIndex(parent_index);
	void *data = NULL;

	if (right_child_index < VectorSize(vector))
	{
		data = *(void **)VectorItemAddress(vector, right_child_index);
	}

	return (data);
}

static size_t FindSmallerChildIndex(heap_t *heap, size_t curr_item_index)
{
	void **right_child_data = GetRightChildData(heap->d_vector, curr_item_index);
	void **left_child_data = GetLeftChildData(heap->d_vector, curr_item_index);

	if ((right_child_data != NULL) && (left_child_data != NULL))
	{
		if (heap->cmp_func(right_child_data, left_child_data, heap->param) < 0)
		{
			return (GetRightChildIndex(curr_item_index));
		}
		else
		{
			return (GetLeftChildIndex(curr_item_index));
		}
	}
	else if (right_child_data != NULL)
	{
		return (GetRightChildIndex(curr_item_index));
	}
	else
	{
		return (GetLeftChildIndex(curr_item_index));
	}
}

static int ItemHasChildren(vector_t *vector, size_t item_index)
{
	size_t size = VectorSize(vector);

	if ((GetLeftChildIndex(item_index) > size)
									|| (GetRightChildIndex(item_index) > size))
	{
		return (0);
	}

	return (1);
}

static ssize_t FindIndex(heap_t *heap, const void *data,
						int (*is_match)(const void *data1, const void *data2))
{
	vector_t *vector = heap->d_vector;
	void *current_data = NULL;
	size_t size = VectorSize(vector);
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		current_data = VectorItemAddress(vector, i);

		if (is_match(*(void **)current_data, data))
		{
			return (i);
		}
	}

	return (-1);
}

static void RemoveIndex(heap_t *heap, size_t index)
{
	vector_t *vector = heap->d_vector;
	size_t last_item_index = VectorSize(vector) - 1;
	size_t curr_item_index = index;

	SwapData(vector, last_item_index, curr_item_index);
	VectorPop(vector);

	while (ItemHasChildren(vector, curr_item_index))
	{
		curr_item_index = BubbleUp(heap, curr_item_index);
	}
}

static size_t BubbleUp(heap_t *heap, size_t current_item_index)
{
	size_t smaller_child_index = FindSmallerChildIndex(heap, current_item_index);
	vector_t *vector = heap->d_vector;

	void *smaller_child_data = VectorItemAddress(heap->d_vector,
															smaller_child_index);
	void *item_data = VectorItemAddress(heap->d_vector, current_item_index);

	if (heap->cmp_func(*(void **)smaller_child_data, *(void **)item_data, heap->param) < 0)
	{
		SwapData(vector, current_item_index, smaller_child_index);
	}
	return (smaller_child_index);
}

static void PrintHeap(heap_t *heap)
{
	size_t i = 0;

	for (i = 0; i < HeapSize(heap); ++i)
	{
		printf("%d. %d\n", (i+1), **(int **)VectorItemAddress(heap->d_vector, i));
	}
}
