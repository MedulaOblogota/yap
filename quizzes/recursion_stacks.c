#include "stack.h"

void StackInsert(stack_t *stack, int data)
{
    int peeked_item = 0;

    if (StackSize(stack) > 0)
    {
        peeked_item = *(int *)StackPeek(stack);
    }

    if ((peeked_item < data) || (StackSize(stack) == 0))
    {
        StackPush(stack, &data);
    }
    else
    {
        StackPop(stack);
        StackInsert(stack, data);
        StackPush(stack, &peeked_item);
    }
}

void StackSort(stack_t *stack)
{
    int num = 0;

    if (StackSize(stack) > 1)
    {
        num = *(int *)StackPeek(stack);
        StackPop(stack);
        StackSort(stack);
        StackInsert(stack, num);
    }
}

void PrintStack(stack_t *stack)
{
    while (StackSize(stack) > 0)
    {
        printf("%d, ", *(int *)StackPeek(stack));
        StackPop(stack);
    }
}

int main()
{
    stack_t *stack = StackCreate(10, sizeof(int));
    int num1 = 6;
    int num2 = 2;
    int num3 = -4;
    int num4 = 9;
    int num5 = 14;
    int num6 = 11;

    StackPush(stack, &num1);
    StackPush(stack, &num2);
    StackPush(stack, &num3);
    StackPush(stack, &num4);
    StackPush(stack, &num5);
    StackPush(stack, &num6);

    StackSort(stack);

    PrintStack(stack);

    return (0);
}
