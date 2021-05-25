#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "cbuffer.h"

struct c_buffer_s
{
    void *read;
    void *write;
    void *base;
    void *end;
    size_t size;
};

/**************************************************************
* Creates Buffer with a given capacity                        *
***************************************************************/
c_buffer_t *CBuffCreate(size_t capacity)
{
    c_buffer_t *c_buffer = NULL;

    if (capacity == 0)
    {
        return (NULL);
    }
    c_buffer = malloc(sizeof(c_buffer_t) + capacity);
    if (NULL == c_buffer)
    {
        return (NULL);
    }
    c_buffer->base = (char *)c_buffer + sizeof(c_buffer_t);
    c_buffer->end = (char *)c_buffer->base + capacity;
    c_buffer->read = c_buffer->base;
    c_buffer->write = c_buffer->base;
    c_buffer->size = 0;

    return (c_buffer);
}

/**************************************************************
* Releases the memory that has been allocated for the C_Buffer *
***************************************************************/
void CBuffDestroy(c_buffer_t *c_buffer)
{
    free(c_buffer);
	c_buffer = NULL;
}

/**************************************************************
* reads byte_num bytes from the C_buffer to dest        	  *
***************************************************************/
ssize_t CBuffRead(c_buffer_t *c_buffer, void *dest, size_t bytes_num)
{
	ssize_t new_size = 0;
	void *dest_runner = dest;

    if ((NULL == c_buffer) || (NULL == dest))
    {
        return (-1);
    }

	if (c_buffer->size < bytes_num)
	{
	    new_size = c_buffer->size;
	}
	else
	{
	    new_size = bytes_num;
	}

	if (c_buffer->size > 0)
	{
	    if ((char *)c_buffer->read + new_size - 1 < (char *)c_buffer->end)
	    {
	        memmove(dest_runner, c_buffer->read, new_size);
	        c_buffer->read = (char *)c_buffer->read + new_size;
	    }
	    else
	    {
	        memmove(dest_runner, c_buffer->read, (char *)c_buffer->end -
                                                        (char *)c_buffer->read);

	        dest_runner = (char *)dest_runner + (size_t)((char *)c_buffer->end -
                                                        (char *)c_buffer->read);
	        memmove(dest_runner, c_buffer->base, new_size -
                            (ssize_t)c_buffer->end + (ssize_t)c_buffer->read);
	        c_buffer->read = (char *)c_buffer->base + new_size -
                                (char *)c_buffer->end + (char *)c_buffer->read;
	    }
        c_buffer->size -= new_size;
	}

	return (new_size);
}

/**************************************************************
* write byte_num bytes from a source to the C_Buffer    	  *
***************************************************************/
ssize_t CBuffWrite(c_buffer_t *c_buffer, const void *src, size_t bytes_num)
{
	size_t new_size = 0;
	void *src_runner = (void *)src;

    if ((NULL == c_buffer) || (NULL == src))
    {
        return (-1);
    }

	if (CBuffFreeSpace(c_buffer) < bytes_num)
    {
        new_size = CBuffFreeSpace(c_buffer);
    }
    else
    {
        new_size = bytes_num;
    }

	if ((c_buffer->size < CBuffCapacity(c_buffer)))
	{
	    if ((char *)c_buffer->write + new_size - 1 < (char *)c_buffer->end)
	    {
	        memmove(c_buffer->write, src_runner, new_size);
	        c_buffer->write = (char *)c_buffer->write + new_size;
	    }
	    else
	    {
	        memmove(c_buffer->write, src_runner, (char *)c_buffer->end -
                                                    (char *)c_buffer->write);
	        src_runner = (char *)src_runner + (size_t)((char *)c_buffer->end -
                                                    (char *)c_buffer->write);
	        memmove(c_buffer->base, src_runner, new_size -
                        (ssize_t)c_buffer->end + (ssize_t)c_buffer->write);
	        c_buffer->write = (char *)c_buffer->base + new_size -
                            (char *)c_buffer->end + (char * )c_buffer->write;
	    }
        c_buffer->size += new_size;
    }

	return (new_size);
}




/***************************************************************
* Return TRUE (1) if the C_Buffer is empty.	(0) otherwise	   *
***************************************************************/
int CBuffIsEmpty(c_buffer_t *c_buffer)
{
    if (NULL == c_buffer)
    {
        return (-1);
    }

    if (c_buffer->size > 0)
    {
        return (0);
    }
    else
    {
        return (1);
    }
}

/**************************************************************
* Returns the free space (in bytes) in the  CBuff.            *
***************************************************************/
size_t CBuffFreeSpace(c_buffer_t *c_buffer)
{
    if (NULL == c_buffer)
    {
        return (-1);
    }

    return ((char *)c_buffer->end - (char *)c_buffer->base - c_buffer->size);
}

/**************************************************************
* Returns capacity of the C_Buffer. 	                      *
***************************************************************/
size_t CBuffCapacity(c_buffer_t *c_buffer)
{
    if (NULL == c_buffer)
    {
        return (-1);
    }

    return ((char *)c_buffer->end - (char *)c_buffer->base);
}
