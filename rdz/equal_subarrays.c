#include <stdio.h>
#include <stdlib.h>

int EqualSubarrays(int *arr, int size, int *last, int *first)
{
  int i = 0;
  int j = size - 1;

  int sum1 = arr[0];
  int sum2 = arr[j];

  while ((i <= j) && (sum1 != sum2))
  {
    if (sum1 < sum2)
    {
      ++i;
      sum1 += arr[i];
    }
    // else if (sum1 == sum2)
    // {
    //   break;
    // }
    else
    {
      --j;
      sum2 += arr[j];
    }
  }

  if (sum1 == sum2)
  {
    *last = i + 1;
    *first = j;
    printf("i=%d, j=%d\n", i, j);
    return 1;
  }
  else
  {
    return 0;
  }
}

void PrintArray(int *arr, int start, int end)
{
  for (int i = start; i < end; ++i)
  {
    printf("%d, ", arr[i]);
  }

  printf("\n");
}

int main()
{
  int arr[] = {4, 3, 2, 1};
  int i, j;
  if (EqualSubarrays(arr, 4, &i, &j))
  {
    PrintArray(arr, 0, i);
    PrintArray(arr, j, 4);
  }
  else
  {
    printf("no EqualSubarrays\n");
  }

  return 0;
}
