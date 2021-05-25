#define ARR_SIZE sizeof(arr) / sizeof(arr[0])

#include <stdio.h>	/* printf */
#include <stdlib.h> /* free */
#include <string.h>	/* strlen */
#include <assert.h> /* assert */


typedef struct element element_t;

/* all add funcs get an element and an int */
typedef int (*add_f_t)(element_t *element, int value); 	
/* all print funcs get an element to print */
typedef void (*print_f_t)(element_t *element);	
/* all remove funcs get an element to remove */		
typedef void (*free_memory_f_t)(element_t *element);			

struct element
{
	void *data;
	add_f_t add_func_t;
	print_f_t print_func_t;
	free_memory_f_t free_memory_func_t;
};

static element_t arr[3];

/***********************************************************************
					FUNCTION DECLARATIONS
***********************************************************************/

int InitAll(element_t *arr);
int AddAll(element_t *arr, size_t size);
void PrintAll(element_t *arr, size_t size);
void FreeAll(element_t *arr, size_t size);
	
static int IntAddFunc(element_t *element, int added_val);
static void IntPrintFunc(element_t *element);
static void IntFreeMemoryFunc(element_t *element);

static int FloatAddFunc(element_t *element, int added_val);
static void FloatPrintFunc(element_t *element);
static void FloatFreeMemoryFunc(element_t *element);

static int StringAddFunc(element_t *element, int added_val);
static void StringPrintFunc(element_t *element);
static void StringFreeMemoryFunc(element_t *element);

/***********************************************************************
								MAIN
***********************************************************************/

int main()
{
	if (0 == InitAll(arr))
	{
		printf("Failed. Try Again Please!");
		return(1);
	}
	PrintAll(arr, ARR_SIZE);
	if (0 == AddAll(arr, ARR_SIZE))
	{
		FreeAll(arr, ARR_SIZE);
	}
	PrintAll(arr, ARR_SIZE);
	FreeAll(arr, ARR_SIZE);

	return (0);
}

/***********************************************************************
					FUNCTION DEFINITIONS (IMPLEMENTATIONS)
***********************************************************************/

/* 	initiates int value of Array to 7. 
	initiates float value of Array to 2.5
	initiates string value of Array to "1"
*/
int InitAll(element_t *arr)
{

	int int_number = 7;
	float float_number = 2.5;
	char str[] = "1";
	
	int *ip = (int *)&(arr[0].data);
	float *fp = (float *)&(arr[1].data);
	char *sp = malloc(sizeof(str));
	
	if (NULL == sp)
	{
		return (0);
	}


	*ip = int_number;
	arr[0].add_func_t = IntAddFunc;
	arr[0].print_func_t = IntPrintFunc;
	arr[0].free_memory_func_t = IntFreeMemoryFunc;
	
	

	*fp = float_number;
	arr[1].add_func_t = FloatAddFunc;
	arr[1].print_func_t = FloatPrintFunc;
	arr[1].free_memory_func_t = FloatFreeMemoryFunc;
	
	sp = strcpy(sp, str);
	arr[2].data = sp;
	arr[2].add_func_t = StringAddFunc;
	arr[2].print_func_t = StringPrintFunc;
	arr[2].free_memory_func_t = StringFreeMemoryFunc;
	
	return (1);
}

/*	adds 6 to values stored in data for each element in Array */
int AddAll(element_t *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (0 == arr[i].add_func_t(&arr[i], 6))
		{
			return (0);
		}
	}
	
	return (1);
}

/*	prints values stored in data for each element in Array */
void PrintAll(element_t *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		arr[i].print_func_t( arr + i);
	}
}

/*	frees values stored in data for each element in Array. returns 1 for 
	success, 0 for failure */
void FreeAll(element_t *arr, size_t size)
{
	size_t i = 0;
	
		for (i = 0; i < size; ++i)
		{
			arr[i].free_memory_func_t(&arr[i]);
		}
}
/*****************************************************************/
/********************** STATIC FUNCTIONS *************************/
/*****************************************************************/

/* 	adds added_val value for Int */
static int IntAddFunc(element_t *element, int added_val)
{
	int *p = (int *)&(element->data);
	*p += added_val;
	
	return (1);
}

/* prints value for Int */
static void IntPrintFunc(element_t *element)
{
	int *p = (int *)&(element->data);
	printf("Int Value is %d\n", *p);
}

/* frees memory for int */
static void IntFreeMemoryFunc(element_t *element)
{
	element->data = NULL;
}

/* 	adds added_val value for Float */
static int FloatAddFunc(element_t *element, int added_val)
{
	float *fp = (float *)&(element->data);
	
	*fp +=added_val;
	
	return (1);
}

/* prints value for float */
static void FloatPrintFunc(element_t *element)
{
	float *fp = (float *)&(element->data);
	printf("Float Value is %f\n", *fp);
}

static void FloatFreeMemoryFunc(element_t *element)
{
	(*element).data = NULL;
}

/* 	concats added_val value for String */
static int StringAddFunc(element_t *element, int added_val)
{
	char added_str[11];
	char *original_string = element->data;
	char *temp_string = NULL;
	size_t added_length = 0;
	size_t original_length = strlen(original_string);
	
	assert(NULL != element->data);
	
	sprintf(added_str, "%d", added_val);
	added_length = strlen(added_str);
		
	temp_string = realloc(original_string, original_length + added_length + 1);
	/* temp_string = NULL; */ /* TO CHECK IF NULL CASE SUCCEEDS */
	if (NULL == temp_string)
	{
		return (0);

	} 
	
	original_string = strncat(temp_string, added_str, added_length);
	
	*(original_string + added_length + original_length + 1) = '\0';
	
	element->data = original_string;
	
	return (1);
}

/* prints value for string */
static void StringPrintFunc(element_t *element)
{
	char *sp = (char *)(element->data);
	printf("String Value is %s\n", sp);
}

/* frees memory for string */
static void StringFreeMemoryFunc(element_t *element)
{
	free((*element).data);
	(*element).data = NULL;
}
