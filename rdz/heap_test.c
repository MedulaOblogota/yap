#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main()
{
  // heap_t *heap = MinHeapCreate(10);
  // int num = 1;
  // int num2 = 2;
  // int num3 = 3;
  // int num4 = 0;
  // int num5 = -1;
  // int num6 = 7;
  // int num7 = 4;
  // int num8 = -2;
  // int num9 = -3;
  // int num10 = -9;
  // int num11 = 13;
  // int num12 = 321;
  // printf("is empty is %d\n", MinHeapIsEmpty(heap));
  // if (MinHeapPeek(heap) != NULL)
  //   printf("peek is %d\n", *MinHeapPeek(heap));
  // MinHeapPush(heap, &num3);
  // printf("peek is %d\n", *MinHeapPeek(heap));
  // MinHeapPush(heap, &num);
  // MinHeapPush(heap, &num2);
  // MinHeapPush(heap, &num4);
  // PrintHeap(heap);
  // MinHeapPush(heap, &num5);
  // PrintHeap(heap);
  // MinHeapPush(heap, &num6);
  // MinHeapPush(heap, &num7);
  // MinHeapPush(heap, &num8);
  // MinHeapPush(heap, &num9);
  // MinHeapPush(heap, &num10);
  // MinHeapPush(heap, &num11);
  // MinHeapPush(heap, &num12);
  // PrintHeap(heap);
  // MinHeapRemove(heap, &num9);
  // PrintHeap(heap);
  //
  // printf("peek is %d\n", *MinHeapPeek(heap));
  // MinHeapRemove(heap, &num);
  // printf("peek is %d\n", *MinHeapPeek(heap));
  // PrintHeap(heap);
  // printf("size is %d\n", MinHeapSize(heap));
  //
  // MinHeapPush(heap, &num);
  // MinHeapPush(heap, &num9);
  // PrintHeap(heap);
  // printf("size is %d\n", MinHeapSize(heap));
  // printf("is empty is %d\n", MinHeapIsEmpty(heap));
  //
  // MinHeapDestroy(heap);

  int arr[] = {1, 0, -1, 13, -9, 2, 3, 321, 11, -3, -2, 4};
  heap_t *heap = MinHeapCreate(12);
  Heapify(arr, heap);
  PrintHeap(heap);
  MinHeapDestroy(heap);


}
