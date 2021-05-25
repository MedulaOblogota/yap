#include <stdio.h>

#include "avl.h"

int comp(const void *data1, const void *data2, void *param)
{
    return (*(int *)data1 - *(int *)data2);
}

int main()
{
    avl_t *avl = AVLCreate(comp, NULL);
    int num1 = 5;
    int num2 = 7;
    int num3 = 6;
    int num4 = 0;
    int num5 = 2;
    int num6 = -1;
    int num7 = 100;

    AVLInsert(avl, &num1);
    AVLInsert(avl, &num2);
    AVLInsert(avl, &num3);
    AVLInsert(avl, &num4);
    AVLInsert(avl, &num5);
    AVLInsert(avl, &num6);
    printf("find for %d is %d\n", num1, *(int *)AVLFind(avl, &num1));

    if (AVLFind(avl, &num4) == NULL)
    {
        printf("success!\n" );
    }

    printf("avl has %lu nodes\n", AVLCount(avl));

    printf("height of avl is %lu\n", AVLHeight(avl));

    printf("father of %d is %d\n", num1, *(int *)AVLRemove(avl, &num1));

    printf("avl has %lu nodes\n", AVLCount(avl));

    printf("height of avl is %lu\n", AVLHeight(avl));

    return (0);
}
