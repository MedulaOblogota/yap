#include <stdio.h>
#include <stdlib.h>


// check if a distance of x is possible b/w each cow
int chk(int *arr, int N, int x, int cows)
{
  // greedy approach, put each cow in the first place you can
  int cows_placed = 1;
  int last_pos = arr[0];
  for (int i = 1; i < N; ++i)
  {
    if ((arr[i] - last_pos) >= x)
    {
      ++cows_placed;
      if (cows_placed == cows)
      {
        printf("success. mid=%d\ncows=%d\n\n", x, cows_placed);
        return 1;
      }
      last_pos = arr[i];
    }
  }
  printf("falure. mid=%d\ncows=%d\n\n", x, cows_placed);
  return 0;
}

void solve(int *arr, int size, int cows)
{
  //cin >> N >> C;
  // for (int i = 0; i < N; i++)
  //   cin >> A[i];
  // sort(A, A + N);

  // binary search
  int low = 0, high = 30, mid, pos = 0;
  while (high >= low)
  {
    mid = (high + low) / 2;
    printf("at solve. low = %d. mid = %d. high=%d\n", low, mid, high);
    if (chk(arr, size, mid, cows))
    {
      low = mid + 1;
      pos = mid;
    }
    else
    {
      high = mid - 1;
    }
  }
  //cout << pos << endl;
  printf("%d\n", pos);
}




int FitTheCows(int *arr, int size, int cows)
{
  int loc = 0;
  int array_empty = 0;
  int i = 0;

  for (i = 0; i < 2; ++i)
  {
    if (cows > 1)
    {
      arr[loc] = 1;
      --cows;
    }
    loc = size - 1;
  }

  loc = size / 2;

  while ((cows > 0) && (!array_empty))
  {

  }
}


int main()
{
  int arr[] = {1, 4, 7, 10, 15, 30, 31};
  //int T = ;


  solve(arr,7,3);
  return 0;
}
