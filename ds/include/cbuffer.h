#ifndef CBuff_OL70 /*header gaurd*/
#define CBuff_OL70
/**************************************************************
* The functions in this file handle a Circular Buffer data    *
* structure. The Circular Buffer will be denoted as CBuff. *
* The CBuff is First-in-First-out based Data structure     *
*      														  *
* Written by: OL-70   										  *
* Last update: 07:50 , 03.07.2019                			  *
***************************************************************/

#include <stddef.h>

typedef struct c_buffer_s c_buffer_t;

/**************************************************************
* Allocates the memory for the CBuff according to capacity.    *
* CBuffDestroy must be called after the work with the          *
* CBuff is done.									           *
*														       *
* Return Value: A pointer to the CBuff.                        *
***************************************************************/
c_buffer_t *CBuffCreate(size_t capacity);

/**************************************************************
* Releases the memory that has been allocated for the CBuff *
***************************************************************/
void CBuffDestroy(c_buffer_t *c_buffer);

/**************************************************************
* reads byte_num bytes from the C_buffer to dest        	  *
* return value - non-negative: the number of bytes read       *
*              - (-1) on failure                              *
***************************************************************/
ssize_t CBuffRead(c_buffer_t *c_buffer, void *dest, size_t bytes_num);

/**************************************************************
* write byte_num bytes from a source to the CBuff    	      *
* return value - non-negative: the number of bytes written    *
*              - (-1) on failure                              *
***************************************************************/
ssize_t CBuffWrite(c_buffer_t *c_buffer, const void *src, size_t bytes_num);

/**************************************************************
* Return TRUE (1) if the CBuff is empty.			  		   *
* Return FALSE (0) otherwise.                		  		   *
***************************************************************/
int CBuffIsEmpty(c_buffer_t *c_buffer);

/**************************************************************
* Returns the free space (in bytes) in the  CBuff.            *
***************************************************************/
size_t CBuffFreeSpace(c_buffer_t *c_buffer);

/**************************************************************
* Returns the capacity of the CBuff. 	                       *
***************************************************************/
size_t CBuffCapacity(c_buffer_t *c_buffer);


#endif /*CBuff_OL70*/
