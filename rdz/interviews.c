#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void PrintArray(int *arr, int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void Swap()
{
  int a = 3;
  int b = 10;

  printf("before swap. a=%d. b=%d\n", a, b);
  a = a + b;
  b = a - b;
  a = a - b;
  printf("after swap. a=%d. b=%d\n", a, b);
}

int DiagonalVictory(char board[3][3])
{
  char c = board[1][1];

  if (c == 0)
  {
    return 0;
  }

  return (((c == board[0][0]) && (c == board[2][2])) || ((c == board[0,2]) && (c == board[2][0])));
}

int RowVictory(char board[3][3], int row, char c)
{
  return ((board[row][0] == c) && (board[row][1] == c) && (board[row][2] == c));
}

int ColVictory(char board[3][3], int col, char c)
{
  return ((board[0][col] == c) && (board[1][col] == c) && (board[2][col] == c));
}

int TicTacToeVictory(char board[3][3])
{
  int i = 0;
  int j = 0;

  char c = 0;

  if (DiagonalVictory(board))
  {
    return 1;
  }

  for (i = 0; i < 3; ++i)
  {
    c = board[i][0];
    if (RowVictory(board, i, c))
    {
      return 1;
    }
  }

  for (i = 0; i < 3; ++i)
  {
    c = board[0][i];
    if (ColVictory(board, i, c))
    {
      return 1;
    }
  }

  // for (i = 0; i < 3; ++i)
  // {
  //   for (j = 0; j < 3; ++j)
  //   {
  //     if (board[i][j] != 0)
  //     {
  //       c = board[i][j];
  //       if (RowVictory(board, i, c))
  //       {
  //         return 1;
  //       }
  //       if (ColVictory(board, j, c))
  //       {
  //         return 1;
  //       }
  //     }
  //   }
  // }
  return 0;
}

void LinesIntersection()
{
  struct point_s
  {
    int x;
    int y;
  };

  typedef struct point_s point_t;

  struct line_s
  {
    point_t p1;
    point_t p2;
  };

  typedef struct line_s line_t;

  line_t l1;
  line_t l2;

  l1.p1.x = 0;
  l1.p1.y = 0;
  l1.p2.x = 5;
  l1.p2.y = 5;

  l2.p1.x = 1;
  l2.p1.y = 3;
  l2.p2.x = 3;
  l2.p2.y = 3;

  float m1, m2, n1, n2, xc, yc;

  m1 = (l1.p1.y-l1.p2.y)/(l1.p1.x-l1.p2.x);
  m2 = (l2.p1.y-l2.p2.y)/(l2.p1.x-l2.p2.x);

  n1 = l1.p1.y-m1*l1.p1.x;
  n2 = l2.p1.y-m2*l2.p1.x;

  xc = (n2-n1)/(m1-m2);
  yc = m1*xc+n1;

  if ((xc > l1.p1.x) && (xc < l1.p2.x))
  {
    printf("X = %f. Y = %f\n", xc, yc);
  }
  else
  {
    printf("no intersection!\n");
  }

}

void WrapperTicTacToe()
{
  char board[3][3] = {{'x', 0, 'o'}, {'x', 'x', 'o'}, {'o', 0, 0}};

  printf("%d\n", TicTacToeVictory(board));
}

int Factorial(int num)
{
  int i = 0;
  int val = 1;
  for (i = 1; i <= num; ++i)
  {
    val = val * i;
  }
  return val;
}
void ComputeTrailingZeros()
{
  printf("ComputeTrailingZeros\n");
  int num = Factorial(10);
  printf("factorial is %d\n", num);
  int counter = 0;
  while (num % 10 == 0)
  {
    num /= 10;
    ++counter;
  }

  printf("%d\n", counter);
}

int FindMinDifference(int *arr1, int *arr2, int size1, int size2)
{
  int i1 = 0;
  int i2 = 0;

  int min = abs(arr1[i1]-arr2[i2]);
  qsort(arr1, size1, sizeof(int), cmpfunc);
  qsort(arr2, size2, sizeof(int), cmpfunc);

  PrintArray(arr1, size1);
  PrintArray(arr2, size2);

  while ((i1 < size1) && (i2 < size2))
  {
    int curr = abs(arr1[i1] - arr2[i2]);
    if (curr < min)
    {
      min = curr;
    }

    if (arr1[i1] < arr2[i2])
    {
      ++i1;
    }
    else
    {
      ++i2;
    }
  }

  return min;
}

void WrapperFindMinDifference()
{
  int arr1[] = {1, 2, 11, 15};
  int arr2[] = {4, 12, 19, 23, 127, 235};

  printf("min difference is %d\n", FindMinDifference(arr1, arr2, 4, 6));
}

// void DescribeNumber(int num)
// {
//   stack_t *stack = StackCreate(20, sizeof(int));
//   int i = 19;
//   int val = num;
//   int *dig = malloc(20*sizeof(int));
//
//   while (val != 0)
//   {
//     dig[i] = val % 10;
//     val = val / 10;
//     --i;
//   }
//
//   ++i;
//   for (i;i<20;++i)
//   {
//     case
//     if (i % 3 == 0)
//     {
//       printf(" thirty ");
//       if (i == 15)
//       {
//         printf(" thousand ");
//       }
//       if (i == 12)
//       {
//         printf(" million ");
//       }
//       if (i == 9)
//       {
//         printf(" billion ");
//       }
//     }
//     else
//     {
//       printf(" ")
//     }
//
//   }
// }

void PrintPairs()
{
  int arr[] = {1, 7, 4, 2, 9, 8, 5, 6};
  int i = 0;
  int j = 7;

  int val = 9;

  qsort(arr, 8, sizeof(int), cmpfunc);

  while (j > i)
  {
    int sum = arr[i]+ arr[j];

    if (sum  > val)
    {
      --j;
    }
    if (sum < val)
    {
      ++i;
    }
    if (sum == val)
    {
      printf("(%d, %d); ", arr[i], arr[j]);
      ++i;
      ++j;
    }
  }

}
int main()
{
  Swap();
  LinesIntersection();
  WrapperTicTacToe();
  ComputeTrailingZeros();
  WrapperFindMinDifference();
  PrintPairs();
}
