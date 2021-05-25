/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomo Solomont
Version:	Sent
Title:		Vector Test File
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/vector.h"

#define MAX_NUM_OF_ELEMENTS (2)

struct student
{
	int id;
	int number;
};

typedef struct student student_t;

int main()
{
    vector_t *ints_vector;
	vector_t *strings_vector;
	vector_t *structs_vector;
	
	int num = 5;
	int *p_num = &num;
	int check = 0;
	
	student_t *student = NULL;
	student_t *student_check = NULL;
		
	ints_vector = VectorCreate(sizeof(int), MAX_NUM_OF_ELEMENTS);
	strings_vector = VectorCreate(sizeof(char *), MAX_NUM_OF_ELEMENTS);
	structs_vector = VectorCreate(sizeof(student_t), MAX_NUM_OF_ELEMENTS);
	
	student = malloc(sizeof(student));
	student->id = 0;
	student->number = 1;
	
	if (NULL != VectorItemAddress(ints_vector, 0))
	{
		printf("1. error with VectorItemAddress(ints_vector, 0)\n");		
	}
	
	if (NULL != VectorItemAddress(strings_vector, 0))
	{
		printf("error with VectorItemAddress(strings_vector, 0)\n");
	}
	
	if (NULL != VectorItemAddress(structs_vector, 0))
	{
		printf("error with VectorItemAddress(structs_vector, 0)\n");
	}
	student_check = VectorItemAddress(structs_vector, 0);
	
	
	if (VectorSize(ints_vector) != 0)
	{
		printf("FAILED");
	}
	
	if (VectorSize(strings_vector) != 0)
	{
		printf("FAILED");
	}
	
	if (VectorSize(structs_vector) != 0)
	{
		printf("FAILED");
	}
	
	VectorPush(ints_vector, p_num);
	VectorPush(strings_vector, "wassudsadasfp?");
	VectorPush(structs_vector, student);
	
	VectorPush(ints_vector, p_num);
	VectorPush(strings_vector, "wassup?");
	VectorPush(structs_vector, student);

	if (VectorSize(ints_vector) != 2)
	{
		printf("FAILED");
	}
	
	if (VectorSize(strings_vector) != 2)
	{
		printf("FAILED");
	}
	
	if (VectorSize(structs_vector) != 2)
	{
		printf("FAILED");
	}
	
	VectorPop(ints_vector);
	VectorPop(strings_vector);
	VectorPop(structs_vector);
	
	VectorPop(ints_vector);
	VectorPop(strings_vector);
	VectorPop(structs_vector);
	
	VectorPop(ints_vector);
	VectorPop(strings_vector);
	VectorPop(structs_vector);
	/* should return error message */
	
	student->id = 0;
	student->number = 1;
	*p_num = 5;
	VectorPush(ints_vector, p_num);
	VectorPush(strings_vector, "wassup?");
	VectorPush(structs_vector, student);
	
	printf("%s\n", (char *)VectorItemAddress(ints_vector, 0));
	
	student->id = 1;
	student->number = 2;
	*p_num = 6;
	VectorPush(ints_vector, p_num);
	VectorPush(strings_vector, "hello?");
	VectorPush(structs_vector, student);
	
	student->id = 2;
	student->number = 3;
	*p_num = 7;
	VectorPush(ints_vector, p_num);
	VectorPush(strings_vector, "shutup?");
	VectorPush(structs_vector, student);
	
	check = *(int *)VectorItemAddress(ints_vector, 0);
	printf("*(int *)VectorItemAddress(ints_vector, 0)=%d\n", check);
	if (check != 5)
		printf("error with VectorItemAddress(ints_vector) at index 0\n");
		
	check = *(int *)VectorItemAddress(ints_vector, 1);
	printf("*(int *)VectorItemAddress(ints_vector, 1)=%d\n", check);
	if (check != 6)
		printf("error with VectorItemAddress(ints_vector) at index 1\n");
	
	check = *(int *)VectorItemAddress(ints_vector, 2);
	printf("*(int *)VectorItemAddress(ints_vector, 2)=%d\n", check);
	if (check != 7)
		printf("error with VectorItemAddress(ints_vector) at index 2\n");
	
	if (VectorItemAddress(ints_vector, 3) != NULL)
	    printf("error with addressing NULL item in ints vector at index 3\n");

	if (strcmp((char *)VectorItemAddress(strings_vector, 0), "wassup?") != 0)
	{
		printf("error with VectorItemAddress(strings_vector) at index %d\n", 0);
		printf("%s", (char *)VectorItemAddress(strings_vector, 0));
	} 

	
	if (strcmp((char *)VectorItemAddress(strings_vector, 1), "hello?") != 0)
	{
		printf("error with VectorItemAddress(strings_vector) at index %d\n", 1);
		printf("%s", (char *)VectorItemAddress(strings_vector, 1));
	}
	
	if (strcmp((char *)VectorItemAddress(strings_vector, 2), "shutup?") != 0)
	{
		printf("error with VectorItemAddress(strings_vector) at index %d\n", 2);
		printf("%s", (char *)VectorItemAddress(strings_vector, 2));
	}
	
	if (VectorItemAddress(strings_vector, 3) != NULL)
	    printf("error with addressing NULL item in strings vector\n");
	
	
	
	 student->id = 0;
	 student->number = 1;   
     student_check = VectorItemAddress(structs_vector, 0);
   /*  printf("student_check->id = %d\n*/
     if ((student_check->id != student -> id) && (student_check->number != student->number))
     {
         printf("error with VectorItemAddress(structs_vector, %d)\n", 0);
     }
     
     student->id = 1;
	 student->number = 2;   
     student_check = VectorItemAddress(structs_vector, 1);
     if ((student_check->id != student -> id) && (student_check->number != student->number))
     {
         printf("error with VectorItemAddress(structs_vector, %d)\n", 1);
     }
	     
	 student->id = 2;
	 student->number = 3;   
     student_check = VectorItemAddress(structs_vector, 2);
     if ((student_check->id != student -> id) && (student_check->number != student->number))
     {
         printf("error with VectorItemAddress(structs_vector, %d)\n", 2);
     }
	
	if (VectorItemAddress(structs_vector, 3) != NULL)
	    printf("error with addressing NULL item in structs vector\n");
	    

	
/*	if (memcmp(student_check, student) != 0)
		printf("error with VectorItemAddress(structs_vector)\n"); */
	
	/*
	TestStackSize();
	
	size_t = StackSize(ints_vector);
	TestStackSize(size_t, 
	
	VectorPush(my_ints_vector, num);
	
	int num = 5;
	int *p_num = &num;
	int *p_num2;
	my_stack = StackCreate(10, 4);
	
	VectorPush(my_stack, p_num);	*/
	/* containes:
	5
	*/
	/*
	p_num2 = (int *)VectorItemAddress(my_stack);
	
	printf("num is %d\n", *p_num2);
	*p_num = 7;
	VectorPush(my_stack, p_num);*/
	/* containes:
	7
	5
	*/
	/*
	p_num2 = (int *)VectorItemAddress(my_stack);
	
	printf("num is %d\n", *p_num2);
	
	printf("size of Stack is %lu\n", StackSize(my_stack));
	VectorPop(my_stack);*/
	/* containes:
	5
	*/
	/*
	p_num2 = (int *)VectorItemAddress(my_stack);
	
	if (p_num2 != NULL)
	{
		printf("num is %d\n", *p_num2);
	}
	printf("size of Stack is %lu\n", StackSize(my_stack));
	VectorPop(my_stack);
	printf("size of Stack is %lu\n", StackSize(my_stack));
	VectorPop(my_stack);
	
	
	printf("size of Stack is %lu\n", StackSize(my_stack));
	StackDestroy(my_stack);
*/
    printf("ints_vector: %lu\n", VectorCapacity(ints_vector));
    printf("strings_vector: %lu\n", VectorCapacity(strings_vector));
    printf("structs_vector: %lu\n", VectorCapacity(structs_vector));
    
    VectorPush(ints_vector, p_num);
    VectorPush(ints_vector, p_num);
    VectorPush(ints_vector, p_num);
     printf("ints_vector size: %lu. ints_vector capacity:%lu\n", VectorSize(ints_vector), VectorCapacity(ints_vector));
    
    if (VectorCapacity(ints_vector) != 10)
        printf("failed with VectorCapacity(ints_vector)\n");
	VectorDestroy(ints_vector);
	VectorDestroy(strings_vector);
	VectorDestroy(structs_vector);
	free(student);
	return(0);
/*
    vector_t *int_vector = VectorCreate(sizeof(int), 5);
    
    
    int num = 5;
    int result;
    VectorPush(int_vector, &num);
    printf("size is now %lu\n", VectorSize(int_vector));
    printf("capacity is now %lu\n", VectorCapacity(int_vector));
     num = 7;
    VectorPush(int_vector, &num);
    VectorPop(int_vector);
    printf("size is now %lu\n", VectorSize(int_vector));
    printf("capacity is now %lu\n", VectorCapacity(int_vector));
    VectorPop(int_vector);
    VectorPop(int_vector);
     printf("size is now %lu\n", VectorSize(int_vector));
    printf("capacity is now %lu\n", VectorCapacity(int_vector));
    
    num = 1; 
    VectorPush(int_vector, &num);
    
    num = 3;
    VectorPush(int_vector, &num);
    
    num = 5;
    VectorPush(int_vector, &num);
    
    num = 7;
    VectorPush(int_vector, &num);
    
    num = 9; 
    VectorPush(int_vector, &num);
    
    if (VectorItemAddress(int_vector, 5) != NULL)
        printf("item at index 4 is %d. should be 5\n", *(int *)VectorItemAddress(int_vector, 0));
    else
        printf("invalid index kapara\n");
    VectorDestroy(int_vector);*/
    return (0);
}
