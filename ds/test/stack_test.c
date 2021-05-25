/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Adam Blau
Version:	Sent
Title:		Stack Test File
*******************************************************************/
#define MAX_NUM_OF_ELEMENTS (2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"

void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackSize();

struct student
{
	int id;
	int number;
};

typedef struct student student_t;

stack_t *ints_stack;
stack_t *strings_stack;
stack_t *structs_stack;
	
int main()
{
	stack_t *ints_stack;
	stack_t *strings_stack;
	stack_t *structs_stack;
	
	int num = 5;
	int *p_num = &num;
	int check = 0;
	
	student_t *student = NULL;
	student_t *student_check = NULL;
		
	ints_stack = StackCreate(MAX_NUM_OF_ELEMENTS, sizeof(int));
	strings_stack = StackCreate(MAX_NUM_OF_ELEMENTS, sizeof(char *));
	structs_stack = StackCreate(MAX_NUM_OF_ELEMENTS, sizeof(student_t));
	
	student = malloc(sizeof(student));
	student->id = 0;
	student->number = 1;
	
	if (NULL != StackPeek(ints_stack))
	{
		printf("error with StackPeek(ints_stack)\n");		
	}
	
	if (NULL != StackPeek(ints_stack))
	{
		printf("error with StackPeek(strings_stack)\n");
	}
	
	if (NULL != StackPeek(structs_stack))
	{
		printf("error with StackPeek(structs_stack)\n");
	}
	student_check = StackPeek(structs_stack);
	
	
	if (StackSize(ints_stack) != 0)
	{
		printf("FAILED");
	}
	
	if (StackSize(strings_stack) != 0)
	{
		printf("FAILED");
	}
	
	if (StackSize(structs_stack) != 0)
	{
		printf("FAILED");
	}
	
	StackPush(ints_stack, p_num);
	StackPush(strings_stack, "wassup?");
	StackPush(structs_stack, student);
	
	StackPush(ints_stack, p_num);
	StackPush(strings_stack, "wassup?");
	StackPush(structs_stack, student);
	
	StackPush(ints_stack, p_num);
	StackPush(strings_stack, "wassup?");
	StackPush(structs_stack, student);
	/* should return error message */
	
	StackPop(ints_stack);
	StackPop(strings_stack);
	StackPop(structs_stack);
	
	StackPop(ints_stack);
	StackPop(strings_stack);
	StackPop(structs_stack);
	
	StackPop(ints_stack);
	StackPop(strings_stack);
	StackPop(structs_stack);
	/* should return error message */
	
	StackPush(ints_stack, p_num);
	StackPush(strings_stack, "wassup?");
	StackPush(structs_stack, student);
	
	check = *(int *)StackPeek(ints_stack);
	
	if (check != 5)
		printf("error with StackPeek(ints_stack)\n");
	
	if (strcmp((char *)StackPeek(strings_stack), "wassup?") != 0)
	{
		printf("error with StackPeek(strings_stack)\n");
		printf("%s", (char *)StackPeek(strings_stack));
	}
	printf("%s\n", (char *)StackPeek(strings_stack));
	
	student_check = StackPeek(structs_stack);
	
/*	if (memcmp(student_check, student) != 0)
		printf("error with StackPeek(structs_stack)\n"); */
	if ((student_check->id != student -> id) && (student_check->number != student->number))
	{
		printf("error with StackPeek(structs_stack)\n");
	}
	/*
	TestStackSize();
	
	size_t = StackSize(ints_stack);
	TestStackSize(size_t, 
	
	StackPush(my_ints_stack, num);
	
	int num = 5;
	int *p_num = &num;
	int *p_num2;
	my_stack = StackCreate(10, 4);
	
	StackPush(my_stack, p_num);	*/
	/* containes:
	5
	*/
	/*
	p_num2 = (int *)StackPeek(my_stack);
	
	printf("num is %d\n", *p_num2);
	*p_num = 7;
	StackPush(my_stack, p_num);*/
	/* containes:
	7
	5
	*/
	/*
	p_num2 = (int *)StackPeek(my_stack);
	
	printf("num is %d\n", *p_num2);
	
	printf("size of Stack is %lu\n", StackSize(my_stack));
	StackPop(my_stack);*/
	/* containes:
	5
	*/
	/*
	p_num2 = (int *)StackPeek(my_stack);
	
	if (p_num2 != NULL)
	{
		printf("num is %d\n", *p_num2);
	}
	printf("size of Stack is %lu\n", StackSize(my_stack));
	StackPop(my_stack);
	printf("size of Stack is %lu\n", StackSize(my_stack));
	StackPop(my_stack);
	
	
	printf("size of Stack is %lu\n", StackSize(my_stack));
	StackDestroy(my_stack);
*/
	StackDestroy(ints_stack);
	StackDestroy(strings_stack);
	StackDestroy(structs_stack);
	free(student);
	return(0);
}

/*
void TestStackSize(stack_t *stack, size_t correct_size)
{
	printf("StackSize->\n");
	if (StackSize(stack) != correct_size)
	{
		printf("FAILED\n");
	}
}
*/
