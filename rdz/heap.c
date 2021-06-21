#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <stdio.h>

#include "heap.h"

struct heap_s
{
    int *d_arr;
    size_t free;
    size_t size;
};

static void Swap(int *first, int *sec)
{
  int temp = *first;
  *first = *sec;
  *sec = temp;
}

static int Bubble(heap_t *heap, int index) // returns -1 in case of failure
{
  if ((index >= heap->size) || (index == 0))
  {
    return -1;
  }

  while (heap->d_arr[index] < heap->d_arr[(index -1) / 2])
  {
    Swap(&(heap->d_arr[index]), &(heap->d_arr[(index -1) / 2]));
    index = (index - 1) / 2;
  }

  return 1;
}

static int ValueBiggerThanEitherChildren(int val, int first, int sec)
{
  return (val > first || val > sec);
}

static int IndexOfSmallerChild(heap_t *heap, int first, int sec)
{
  if (first < heap->size)
  {
    if (sec < heap->size)
    {
      if (heap->d_arr[first] < heap->d_arr[sec])
      {
        return first;
      }
      else
      {
        return sec;
      }
    }
    else
    {
      return first;
    }
  }
  else
  {
    if (sec < heap->size)
    {
      return sec;
    }
    else
    {
      return 0;
    }
  }
}

static int BubbleDown(heap_t *heap, int index) // returns -1 in case of failure
{
  if ((index >= heap->size))
  {
    return -1;
  }
  int left_child = index*2 + 1;
  int right_child = index*2 + 2;
  while (ValueBiggerThanEitherChildren(heap->d_arr[index], heap->d_arr[left_child], heap->d_arr[right_child]) && ((left_child < heap->size) || right_child < heap->size))
  {
    int smaller_child = IndexOfSmallerChild(heap, right_child, left_child);
    Swap(&(heap->d_arr[index]), &(heap->d_arr[smaller_child]));
    index = smaller_child;
    left_child = index*2 + 1;
    right_child = index*2 + 2;
  }

  return 1;
}

static void CopyArray(heap_t *heap, int *arr)
{
  int i = 0;

  for (i = 0; i < heap->size; ++i)
  {
    heap->d_arr[i] = arr[i];
  }
}

heap_t *MinHeapCreate(size_t size)
{
  heap_t *heap = NULL;
  void *arr = NULL;

  heap = malloc(sizeof(heap_t));

  if (NULL == heap)
  {
    return NULL;
  }

  heap->d_arr = malloc(sizeof(int)*size);
  heap->free = 0;
  heap->size = size;

  if (NULL == heap->d_arr)
  {
    free(heap);
    return NULL;
  }

  return heap;
}

void MinHeapDestroy(heap_t *heap)
{
  free(heap->d_arr);
  free(heap);
}

int MinHeapPush(heap_t *heap, const int *data)
{
  int index = heap->free;

  if (heap->free >= heap->size)
  {
    return 0;
  }

  if (heap->free == 0)
  {
    printf("(here)\n");
    heap->d_arr[0] = *data;
    ++heap->free;
    return 1;
  }

  heap->d_arr[heap->free] = *data;
  Bubble(heap, heap->free);
  ++heap->free;

  return 1;

}

int MinHeapPop(heap_t *heap)
{
  if (heap->free == 0)
  {
    return 0;
  }

  --heap->free;

  return 1;
}

int *MinHeapRemove(heap_t *heap, const int *data)
{
  int i = 0;
  int *value = NULL;
  //return 0;
  if (0 == heap->free)
  {
    return NULL;
  }

  for (i = 0; i < heap->free; ++i)
  {
    if (heap->d_arr[i] == *data)
    {
      value = &(heap->d_arr[i]);
      int j = i;

      for (j = i; j < (heap->free - 1); ++j)
      {
        heap->d_arr[j] = heap->d_arr[j+1];
        Bubble(heap, j);
      }
    }
  }
  --heap->free;

  return value;
}

int *MinHeapPeek(heap_t *heap)
{
  int *val = 0;
  if (heap->free == 0)
  {
    return NULL;
  }

  return &(heap->d_arr[heap->free - 1]);


  //return &val;
}

size_t MinHeapSize(heap_t *heap)
{
  return heap->free;
}

int MinHeapIsEmpty(heap_t *heap)
{
  return (heap->free == 0);
}

void PrintHeap(heap_t *heap)
{
  for (int i = 0; i < heap->free; ++i)
  {
    printf("%d, ", heap->d_arr[i]);
  }
  printf("\n");
}

void Heapify(int *arr, heap_t *heap)
{
  int i = 0;
  int right_child = 0;
  int left_child = 0;
  size_t size = heap->size;
  CopyArray(heap, arr);


  for (i = size - 1; i >=0; --i)
  {
    right_child = i*2+2;
    left_child = i*2+1;

    if ((right_child < size) && ((heap->d_arr[right_child] < heap->d_arr[i]) || (heap->d_arr[left_child] < heap->d_arr[i])))
    {
      BubbleDown(heap, i);
    }
  }
  heap->free = heap->size;
}
