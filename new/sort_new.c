#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void PrintStack(stack_t *stack)
{
		while (StackSize(stack) != 0)
		{
			int num = *((int *)StackPeek(stack));
			printf("%d, ", num);
			StackPop(stack);
		}
		printf("\n");
}

int PeakAndPop(stack_t *stack)
{
	int val = *((int *)StackPeek(stack));
	StackPop(stack);

	return val;
}

void Sort(stack_t *stack, int popped)
{
	int temp = 0;
	if (StackSize(stack) == 0)
	{
		StackPush(stack, &popped);
	}
	else
	{
		temp = *((int *)StackPeek(stack));
		if (temp > popped)
		{
			StackPush(stack, &popped);
		}
		else
		{
			StackPop(stack);
			Sort(stack, popped);
			StackPush(stack, &temp);
		}
	}
}

void SortStackRec(stack_t *stack, int popped)
{
	int temp_popped = 0;

	if (StackSize(stack) != 0)
	{
		temp_popped = PeakAndPop(stack);
		SortStackRec(stack, temp_popped);
		Sort(stack, popped);
	}
	else
	{
		StackPush(stack, &popped);
	}
}

void SortStack(stack_t *stack)
{
	int popped = *((int *)StackPeek(stack));
	StackPop(stack);
	SortStackRec(stack, popped);
}

int main()
{
		stack_t *stack;

		int num1 = 3;
		int num2 = -2;
		int num3 = 0;
		int num4 = 7;
		int num5 = -5;
		int num6 = -4;
		int num7 = 9;
		int num8 = 12;
		int num9 = 20;

/*		int num1=1;
		int num2=0;
		int num3=3;*/

		stack = StackCreate(30, sizeof(int));
		StackPush(stack, &num1);
		StackPush(stack, &num2);
		StackPush(stack, &num3);
		StackPush(stack, &num4);
		StackPush(stack, &num5);
		StackPush(stack, &num6);
		StackPush(stack, &num7);
		StackPush(stack, &num8);
		StackPush(stack, &num9);

		SortStack(stack);

		PrintStack(stack);

		return 0;
}
