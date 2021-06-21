#include <stdio.h>
#include <stdlib.h>

int MultiplicationRec(int num, int times)
{
  if (times == 1)
  {
    return num;
  }

  return num + MultiplicationRec(num, times - 1);
}

int DivisionRec(int num, int times)
{
  if (num >= times)
  {
    return 1 + DivisionRec(num - times, times);
  }
  else
  {
    return 0;
  }
}
int main()
{
  int first = 3;
  int sec = 10;
  printf("%d*%d=%d\n", first, sec, MultiplicationRec(first,sec));
  printf("%d/%d=%d\n", sec, first, DivisionRec(sec, first));
  return 0;
}
