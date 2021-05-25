#ifndef DYNAMIC_VECTOR_OL70 /*header gaurd*/
#define DYNAMIC_VECTOR_OL70
/**************************************************************
* The functions in this file handle a dynamic vector data     *
* structure.                                                  *
*          													  *
*      														  *
* Written by: OL-70   										  *
* Last update: 10:58 , 01.07.2019                			  *
***************************************************************/

#include <stddef.h>

typedef struct vector_s vector_t;
typedef enum status {FAILED, SUCCESS} status_t;


/**************************************************************
* Allocates memory for the vector.                        *
* element_size is given in bytes.                             *
* VectorDestroy must be called after the work with the        *
* vector is done.									          *
*														      *
* Return Value: A pointer to the vector.                      *
***************************************************************/
vector_t *VectorCreate(size_t element_size, size_t num_of_elements);


/**************************************************************
* Releases the memory that has been allocated for the vector  *
***************************************************************/
void VectorDestroy(vector_t *vector);


/*********************************************************************
* Pushes element to the top of the vector.				             *
* *element is a pointer to an element of any type to be	             *
*  pushed according to vector type.						             *
* *vector_control - the vector's controller address (don't forget &) *
*														             *
* Return Value: status.		       		          		             *
**********************************************************************/
status_t VectorPush(vector_t *vector, const void *element);


/**************************************************************
* Releases the last element from the top of the vector.	      *
***************************************************************/
void VectorPop(vector_t *vector);


/*************************************************************************
* Returns a pointer to the element in index argument.                    *
*  														                 *
* Return Value: pointer to the element in index argument.                *
*                                                                        *
* WARNING: The content is valid for now but maybe subject to change.     *
**************************************************************************/
void *VectorItemAddress(vector_t *vector, size_t index);


/**************************************************************
* Returns the number of elements in the vector.  		      *
***************************************************************/
size_t VectorSize(vector_t *vector);


/**************************************************************
* Returns the current capacity of the vector.  		          *
***************************************************************/
size_t VectorCapacity(vector_t *vector);

#endif /*DYNAMIC_VECTOR_OL70*/
