/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomo Solomont
Version:	Sent
Title:		Vector Functions File
*******************************************************************/
#define MIN_CAPACITY (5 * (vector->element_size))
#define DIVISION_FOR_REDUCING_SIZE (4)

#include <stdlib.h> /*realloc*/
#include <stdio.h>  /*printf*/
#include <string.h> /*memmove*/
#include <assert.h>
#include "vector.h"

struct vector_s
{
    size_t element_size;
    void *current_element;
    void *base;
    void *end;
};

/* INNER FUNCTION for use of VectorPop */
/**************************************************************
* reduces size of Vector if neccassary                        *
**************************************************************/
static void ReduceSize(vector_t *vector)
{
    size_t current_capacity = (size_t)vector->end - (size_t)vector->base;
    size_t current_size = (size_t)vector->current_element -
                                        (size_t)vector->base;
    if (current_capacity > MIN_CAPACITY)
    {
        if (current_size <= current_capacity/DIVISION_FOR_REDUCING_SIZE)
        {
            if (current_capacity/DIVISION_FOR_REDUCING_SIZE > MIN_CAPACITY)
            {
                vector->base = realloc(vector->base,
                        current_capacity/DIVISION_FOR_REDUCING_SIZE);

                if (NULL == vector->base)
                {
                    return;
                }
                vector->end = (char *)vector->base +
                            current_capacity/DIVISION_FOR_REDUCING_SIZE;
                vector->current_element = (char *)vector->base + current_size;
            }
            else
            {
                vector->base = realloc(vector->base, MIN_CAPACITY);
                if (NULL == vector->base)
                {
                    return;
                }
                vector->end = (char *)vector->base + MIN_CAPACITY;
                 vector->current_element = (char *)vector->base + current_size;
            }
        }
    }
    else if (current_capacity < MIN_CAPACITY)
    {
        vector->base = realloc(vector->base, MIN_CAPACITY);
        if (NULL == vector->base)
        {
            return;
        }
        vector->end = (char *)vector->base + MIN_CAPACITY;
        vector->current_element = (char *)vector->base + current_size;
    }

    return;
}

/**************************************************************
* creates vector given element_size and num_of_elements       *
**************************************************************/
vector_t *VectorCreate(size_t element_size, size_t num_of_elements)
{
    vector_t *vector = malloc(sizeof(vector_t));

    if (NULL == vector)
    {
        printf("Error creating Vector\n");
        return (NULL);
    }
    vector->element_size = element_size;
    vector->base = malloc(num_of_elements * element_size);

    if (NULL == vector->base)
    {
        free(vector);
        printf("Error creating Vector\n");
    }

    vector->current_element = vector->base;
    vector->end = (char *)vector->base + num_of_elements * element_size;

    return (vector);
}

/**************************************************************
* Releases the memory that has been allocated for the vector  *
***************************************************************/
void VectorDestroy(vector_t *vector)
{
    free(vector->base);
    vector->base = NULL;
    free(vector);
    vector = NULL;
}


/**************************************************************
* Pushes element to the top of the vector.				      *	       		          		      *
***************************************************************/
status_t VectorPush(vector_t *vector, const void *element)
{
    size_t new_size = 0;
    size_t temp_size = 0;
    void *temp_base = NULL;

    assert (NULL != vector);

    new_size = (char *)vector->end - (char *)vector->base;
    temp_size = (size_t)vector->current_element - (size_t)vector->base;
    temp_base = vector->base;

    if ((vector->current_element == vector->end) ||
                ((size_t)vector->current_element +
                                vector->element_size == (size_t)vector->end))
    {
        new_size = ((char *)vector->end - (char *)vector->base) * 2;
        temp_size = (char *)vector->current_element - (char *)vector->base;
        vector->base = realloc(vector->base, new_size);
        if (NULL == vector->base)
        {
          /*  printf("Error with pushing value\n");*/
            vector->base = temp_base;
            return (FAILED);
        }
    }

    vector->current_element = (char *)vector->base + temp_size;
    memmove(vector->current_element, element, vector->element_size);
    vector->current_element = (char *)vector->current_element +
                                                        vector->element_size;
    vector->end = (char *)vector->base + new_size;

    return (SUCCESS);
}


/**************************************************************
* Releases the last element from the top of the vector.	      *
***************************************************************/
void VectorPop(vector_t *vector)
{
    assert (NULL != vector);

    if (vector->base != vector->current_element)
    {
        vector->current_element = (char *)vector->current_element -
                                                vector->element_size;
        ReduceSize(vector);
    }
}


/*************************************************************************
* Returns a pointer to the element in index argument.                    *
**************************************************************************/
void *VectorItemAddress(vector_t *vector, size_t index)
{
    size_t index_address = 0;

    assert(NULL != vector);

    index_address = index * vector->element_size;

    if (vector->base == vector->current_element)
    {
        return (NULL);
    }
    else if (index < VectorSize(vector))
    {
        return((char *)vector->base + index_address);
    }
    else
    {
      /*  printf("index invalid for current vector state\n");*/
        return (NULL);
    }
}


/**************************************************************
* Returns the number of elements in the vector.  		      *
***************************************************************/
size_t VectorSize(vector_t *vector)
{
    assert(NULL != vector);

    return (size_t)(((size_t)vector->current_element -
                                (size_t)vector->base) / vector->element_size);
}


/**************************************************************
* Returns the current capacity of the vector.  		          *
***************************************************************/
size_t VectorCapacity(vector_t *vector)
{
    assert(NULL != vector);

    return (((size_t)vector->end -
                                (size_t)vector->base) / vector -> element_size);
}
