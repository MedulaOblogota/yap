#include <stdio.h>
#include <stdlib.h>

struct meeting_s
{
  int val[2];
};

typedef struct meeting_s meeting_t;

void FindFreeTime(meeting_t *meetings1, meeting_t *meetings2, meeting_t *meetings3, int size)
{



}
int main()
{
  meeting_t meetings1[] = { {2, 4}, {6, 8}, {10, 12}, {12, 15}};
  meeting_t meetings2[] = { {1, 3}, {4, 5}, {11, 16}, {17, 19}};
  meeting_t meetings3[4];

  FindFreeTime(meetings1, meetings2, meetings3, 4);

}
