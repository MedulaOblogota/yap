#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

static int IsOpening(char c)
{
  return (c == '(' || c == '[' || c == '{' || c == '<');
}

static int IsClosing(char c)
{
  return (c == ')' || c == ']' || c == '}' || c == '>');
}

static int IsCouple(char c1, char c2)
{
  return ( ((c1 == '(') && (c2 == ')')) || ((c1 == '[') && (c2 == ']')) || ((c1 == '{') && (c2 == '}')) || ((c1 == '<') && (c2 == '>')) );
}
int IsValidParentheses(char *str)
{
  stack_t *stack = StackCreate(100, sizeof(char));
  char *runner = str;
  char parentheses = '\0';

  while (*runner)
  {
    if (IsOpening(*runner))
    {
      StackPush(stack, runner);
    }
    else if (IsClosing(*runner))
    {
      parentheses = *(char *)StackPeek(stack);
      if (!IsCouple(parentheses, *runner))
      {
        return 0;
      }
      StackPop(stack);


    }
    runner += 1;
  }

  if (StackSize(stack) == 0)
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
  char str[] = "5a{2+(p[(3+1)]-5)<* } - ()";
//  printf("%d\n", IsCouple('(', ']'));
  printf("str is %d\n", IsValidParentheses(str));
}
