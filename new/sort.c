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

void SortStackRec(stack_t *stack, int popped)
{
	stack_t *temp_stack = NULL;
	int temp_popped = 0;
	int temp_num = -999999;

	if (StackSize(stack) != 0)
	{
		temp_stack = StackCreate(30, sizeof(int));
		temp_popped = PeakAndPop(stack);
		SortStackRec(stack, temp_popped);

		while ((StackSize(stack) != 0) && (temp_num < temp_popped))
		{
			temp_num = *((int *)StackPeek(stack));
			StackPop(stack);
			StackPush(temp_stack, &temp_num);
		}

		StackPush(stack, &temp_popped);

		while (StackSize(temp_stack) != 0)
		{
			temp_num = PeakAndPop(temp_stack);
			StackPush(stack, &temp_num);
		}
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

	/*	int num1 = 3;
		int num2 = -2;
		int num3 = 0;
		int num4 = 7;
		int num5 = -5;
		int num6 = -4;
		int num7 = 9;
		int num8 = 20;
		int num9 = 12;
*/
		int num1=1;
		int num2=0;
		int num3=3;

		stack = StackCreate(30, sizeof(int));
		StackPush(stack, &num1);
		StackPush(stack, &num2);
		StackPush(stack, &num3);
		/*StackPush(stack, &num4);
		StackPush(stack, &num5);
		StackPush(stack, &num6);
		StackPush(stack, &num7);
		StackPush(stack, &num8);
		StackPush(stack, &num9);*/

		SortStack(stack);

		PrintStack(stack);
}
