#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b)
{
  int temp = *a;
  *a= *b;
  *b = temp;
}

void BubbleSort(int *arr, size_t size)
{
  int i = 0;
  int j = 1;

  for (i = 0; i < size; ++i)
  {
    for (j = 0; j < size - 1; ++j)
    {
      if (arr[j] > arr[j+1])
      {
        Swap(arr + j, arr + j + 1);
      }
    }
  }
}

void SelectionSort(int *arr, size_t size)
{
  int i = 0;
  int j = 0;
  int min = 0;

  for (i = 0; i < size - 1; ++i)
  {
    min = i;

    for (j = i+1; j < size; ++j)
    {
      if (arr[j]<arr[min])
      {
        min = j;
      }
    }

    Swap(arr + min, arr + i);
  }
}

void InsertionSort(int *arr, size_t size)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 1; i < size; ++i)
    {
      temp = arr[i];
      j = i - 1;
      while ((temp < arr[j]) && (j >= 0))
      {
        arr[j + 1] = arr[j];
        --j;
      }

      if (j != i - 1)
      {
        arr[j+1] = temp;
      }
    }
}

void PrintArray(int *arr, size_t size)
{
  int i = 0;

  for (i = 0; i < size; ++i)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}
int main()
{
  int arr[] = {2, 8, 5, 3, 9, 4, 1};

  PrintArray(arr, 7);
  InsertionSort(arr, 7);
  PrintArray(arr, 7);
}
