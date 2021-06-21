#include <stdio.h>
#include <stdlib.h>

void HowManyWaysRec(int *arr, int size, int amount, int *ways)
{
  int i = 0;

  if ((size == 0) || (amount < 0))
  {
    return;
  }
  else if (amount == 0)
  {
    ++(*ways);
  }
  else if (amount > arr[0])
  {
  // else
    for (i = 0; i < size; ++i)
    {
      HowManyWaysRec(arr, size, amount - arr[i], ways);
    }
  }
}

int HowManyWays(int *arr, int size, int amount)
{
  int ways = 0;

  HowManyWaysRec(arr, size, amount, &ways);

  return ways;
}

int main()
{
  int arr[] = {1, 2, 5};

  printf("%d\n", HowManyWays(arr, 3, 5));
}
