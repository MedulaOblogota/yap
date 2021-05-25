#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "stack.h"
#include "dlist.h"

typedef struct simple_array_s simple_array_t;

struct simple_array_s
{
    int *arr;
    time_t *t_s_arr;

    time_t set_all_t_s;
    int init_val;
};

simple_array_t *s_a;

static int CreateSimpleArray(size_t size);
static void SetVal(int indx, int val);
static int GetVal(int indx);
static void SetAll(int val);
void Question1();

static int FindSumOfTwo(unsigned int *arr, size_t size, unsigned int sum_of_two, size_t *first_index, size_t *sec_index);
void Question2();

static int Find(char* arr, size_t size, char num_to_find);
void Question3();

void ShiftNBytes(char *arr, size_t size, size_t n);
void Question4();

static int IsOpenParentheses(char par);
static int IsClosedParentheses(char par);
static int IsParalPar(char closed, char open);
void Question7();

static int Multiply(int a, int b);
static int AddOne(int num);
static int AddOneRec(int num, int mask);
static int Divide(int a, int b);
void Question8();

void Question9();

/*************************************************************************************************************************************
 *                                                      MAIN
 * **********************************************************************************************************************************/
int main()
{
    /*Question1();
    Question2();
    Question3();
    Question4();
    Question7();
    Question8();*/
    Question9();
    return 0;
}

/*************************************************************************************************************************************
 *                                                      QUESTION 1 FUNCS
 * **********************************************************************************************************************************/
static int CreateSimpleArray(size_t size)
{
    s_a = malloc(sizeof(simple_array_t));

    if (NULL == s_a)
    {
        return 0;
    }
    s_a->arr = malloc(sizeof(int) * size);
    if (NULL == s_a->arr)
    {
        return 0;
    }
    s_a->t_s_arr = malloc(sizeof(time_t) * size);
    if (NULL == s_a->t_s_arr)
    {
        return 0;
    }

    s_a->set_all_t_s = time(NULL);

    return 1;
}

static void SetVal(int indx, int val)
{
    s_a->arr[indx] = val;
    s_a->t_s_arr[indx] = time(NULL);
}

static int GetVal(int indx)
{
    if (s_a->set_all_t_s > s_a->t_s_arr[indx])
    {
        return s_a->init_val;
    }

    return s_a->arr[indx];
}

static void SetAll(int val)
{
    s_a->set_all_t_s = time(NULL);
    s_a->init_val = val;
}

static void DestroySimpleArray()
{
    free(s_a->arr);
    free(s_a->t_s_arr);

    free(s_a);
}

void Question1()
{
    size_t i = 0;
    CreateSimpleArray(10);
    printf("initial getval (should return junk): %d\n", GetVal(3));
    sleep(2);
    SetVal(3,100);
    sleep(2);
    printf("getval (should return 100): %d\n", GetVal(3));
    sleep(2);
    SetAll(50);

    for (i = 0; i < 10; ++i)
    {
        if (GetVal(i) != 50)
        {
            printf("FAIL!\n");
            break;
        }
    }
    sleep(2);
    SetVal(3,100);
    sleep(2);
    printf("getval (should return 100): %d\n", GetVal(3));

    DestroySimpleArray();    
}

/*************************************************************************************************************************************
 *                                                      QUESTION 2 FUNCS
 * **********************************************************************************************************************************/

static int FindSumOfTwo(unsigned int *arr, size_t size, unsigned int sum_of_two, size_t *first_index, size_t *sec_index)
{
    size_t i = 0;
    size_t j = size - 1;

    for (i = 0; i < size - 1; ++i)
    {
        for (j = size - 1; j > 1; --j)
        {
            if ((arr[i] + arr[j]) == sum_of_two)
            {
                *first_index = i;
                *sec_index = j;

                return 1;
            }
        }
    }

    return 0;
}
void Question2()
{
    unsigned int arr[] = {4, 5, 1, 2, 9, 0, 3};
    size_t i, j;

    if (FindSumOfTwo(arr, 7, 122, &i, &j) == 1)
    {

        printf("first index = %lu. second index = %lu\n", i, j);
    }
    else 
    {
        printf("didnt find one buddy...\n");
    }
}

/*************************************************************************************************************************************
 *                                                      Question 3 FUNCS
 * **********************************************************************************************************************************/

static int Find(char* arr, size_t size, char num_to_find)
{
    int *lut = calloc(sizeof(int), 256);
    size_t i = 0;
    int ret_val = 0;

    if (NULL == lut)
    {
        return 0;
    }

    for (i = 0; i < size; ++i)
    {
        lut[arr[i]] = 1;
    }

    ret_val = lut[num_to_find];

    free(lut);

    return ret_val;
}

void Question3()
{
    char ch_array[] = {3, 5, 2, 8, 3, 120, 70, 15, 2, 8, 4};
    char ch_to_succ_find = 3;
    char ch_to_fail_find = 90;

    printf("did I find 3 in array? -> %d\n", Find(ch_array, sizeof(ch_array)/sizeof(*ch_array), ch_to_succ_find)); 
    printf("did I find 90 in array? -> %d\n", Find(ch_array, sizeof(ch_array)/sizeof(*ch_array), ch_to_fail_find));
}

/*************************************************************************************************************************************
 *                                                      Question 4 FUNCS
 * **********************************************************************************************************************************/

void ShiftNBytes(char *arr, size_t size, size_t n)
{
    char *first_n_bytes;    
    size_t i = 0;

    n = n % size;
    first_n_bytes = malloc(sizeof(char) * n);

    for (i = 0; i < n; ++i)
    {
        first_n_bytes[i] = arr[i];
    }

    for (i = n; i < size; ++i)
    {
        arr[i-n] = arr[i];
    }

    for (i = 0; i < n; ++i)
    {
        arr[size-n+i] = first_n_bytes[i];
    }

    free(first_n_bytes);
}
void Question4()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    size_t i = 0;

    ShiftNBytes(arr, 7, 3);

    for (i = 0; i < 7; ++i)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

static int IsOpenParentheses(char par)
{
    return (par == '(' || par == '[' || par == '{' || par == '<');
}

static int IsClosedParentheses(char par)
{
    return (par == ')' || par == ']' || par == '}' || par == '>');
}

static int IsParalPar(char closed, char open)
{
    switch (open)
    {
        case '(':
            return (closed == ')');
            break;
        
        case '[':
            return (closed == ']');
            break;

        case '{':
            return (closed == '}');
            break;
        
        case '<':
            return (closed == '>');
            break;
        
        default:
            return 0;
            break;
    }
}

void Question7()
{
    char str[] = "(x+3*[4*6])<";
    size_t length = strlen(str);
    size_t i = 0;
    char zero = 0;
    stack_t *stack = StackCreate(length, sizeof(char));

    StackPush(stack, &zero);

    for (i = 0; i < length; ++i)
    {
        if (IsClosedParentheses(str[i]))
        {
            char open_par = 0;
            if (*(char *)StackPeek(stack) != zero)
            {
                open_par = *(char *)StackPeek(stack);
            }
            else 
            {
                printf("0\n");
                break;
            }

            if (!IsParalPar(str[i], open_par))
            {
                printf("0\n");
                break;
            }

            StackPop(stack);
        }
        else if (IsOpenParentheses(str[i]))
        {
            StackPush(stack, &str[i]);
        }
    }

    printf("%d\n", (*(char *)StackPeek(stack) == zero));
}

static int Multiply(int a, int b)
{
    if (b == 1)
    {
        return a;
    }

    return (a+Multiply(a, b-1));
}

static int AddOneRec(int num, int mask)
{
    if ((num & mask) != mask)
    {
        return (num | mask);
    }

    return (AddOneRec(num^mask, mask << 1));
}

static int AddOne(int num)
{
    int mask = 0x01;
    return (AddOneRec(num, mask));
}

static int Divide(int a, int b)
{
    if (a < b)
    {
        return 0;
    }

    return (1 + Divide(a-b, b));
}

void Question8()
{
    printf("8*3=%d\n", Multiply(8,3));
    printf("8/3=%d\n", Divide(8,3));
    printf("8/4=%d\n", Divide(8,4));
    printf("6+1 = %d\n", AddOne(6));

}

static dlist_t *CreateList()
{
    int num1 = 6;
    int num2 = 2;
    int num3 = 0;
    int num4 = 4;
    int num5 = 5;
    int num6 = 3;
    int num7 = 7;
    int num8 = 1;
    
    dlist_t* dlist = DListCreate();

    DListPushFront(dlist, &num8);
    DListPushFront(dlist, &num7);
    DListPushFront(dlist, &num6);
    DListPushFront(dlist, &num5);
    DListPushFront(dlist, &num4);
    DListPushFront(dlist, &num3);
    DListPushFront(dlist, &num2);
    DListPushFront(dlist, &num1);

    return dlist;

}

int comp_int(const void *data1, const void *data2)
{
    return (*(int *)data1 == *(int *)data2);
}

void ArrangeLinkedList(dlist_t *dlist, dlist_iter_t pivot)
{
    dlist_iter_t runner = DListBegin(dlist);
    dlist_iter_t end = DListEnd(dlist);

    int x = *(int *)DListGetData(pivot);
    int is_x_found = 0;

    while (runner != end)
    {
        if (runner != pivot)
        {
            if (*(int *)DListGetData(runner) > x)
            {   
                int removed_data = *(int *)DListGetData(runner);
                runner = DListRemove(runner);
                DListPushBack(dlist, &removed_data);
            }
            else 
            {
                int removed_data = *(int *)DListGetData(runner);
                runner = DListRemove(runner);
                DListPushFront(dlist, &removed_data);
            }
        }
        runner = DListNext(runner);
    }
    
}

void Question9()
{
    dlist_t *dlist = CreateList();
    int pivot = 4;
    dlist_iter_t begin = DListBegin(dlist);
    dlist_iter_t end = DListEnd(dlist);
    dlist_iter_t pivot_iter = DListFind(DListBegin(dlist), DListEnd(dlist), comp_int,  &pivot);

    dlist_iter_t runner = begin;

    while (runner != end)
    {
        printf("%d -> ", *(int *)DListGetData(runner));
        runner = DListNext(runner);
    }
    printf("\n");


    printf("pivot is %d\n", *(int *)DListGetData(pivot_iter));

    ArrangeLinkedList(dlist, pivot_iter);

    runner = DListBegin(dlist);
    while (runner != end)
    {
        printf("%d -> ", *(int *)DListGetData(runner));
        runner = DListNext(runner);
    }
    printf("\n");

}