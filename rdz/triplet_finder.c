#include <stdio.h>
#include <stdlib.h>

void PrintArray(int *arr, int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}

int FindTriplet(int *arr, int size, int *triplet)
{
  int *levels = malloc(sizeof(int) * size);
  int i = 0;
  int j = 0;

  triplet[0] = 0;
  triplet[1] = 0;
  triplet[2] = 0;

  int min = arr[0];
  int mid = 21474836;

  levels[0] = 0;

  for (i = 1; i < size; ++i)
  {
      if (arr[i] <= min)
      {
          levels[i] = 0;
          min = arr[i];
      }
      else if (arr[i] <= mid)
      {
        levels[i] = 1;
        mid = arr[i];
      }
      else // if (arr[i] > mid)
      {
        levels[i] = 2;
      }
  }

  PrintArray(levels, size);

  j = 0;

  for (i = 0; i < size; ++i)
  {
    if ((levels[i] == 0) && (j == 0))
    {
      triplet[j] = arr[i];
      ++j;
    }
    else if ((levels[i] == 1) && (j == 1))
    {
      triplet[j] = arr[i];
      ++j;
    }
    else if ((levels[i] == 2) && (j == 2))
    {
      triplet[j] = arr[i];
      break;
    }
  }

  if (triplet[2] != 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int main()
{
  int arr[] = {5, 4, 3, 7, 6, 1, 0, 10, 8, 2, 9};
  int triplet[3];
  PrintArray(arr, 11);
  if (FindTriplet(arr, 11, triplet) == 1)
  {
    PrintArray(triplet, 3);
  }
  else
  {
    printf("no success\n");
  }

  return 0;
}
