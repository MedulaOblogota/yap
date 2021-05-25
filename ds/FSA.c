#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "FSA.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"


#define SIZE_OF_WORD (8)
struct fsa_s
{
    fsa_t *next_avail_addr;
};

/*******************************************************************************
* Returns num of bytes requested to allocate in FSAInit.
*******************************************************************************/
static size_t NewBlockSize(size_t block_size)
{
    if ((block_size & 7) != 0)
    {
        return ((block_size & ~7) + SIZE_OF_WORD);
    }
    else
    {
        return (block_size & (~7));
    }
}


size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    assert (block_size != 0);
    assert(num_of_blocks != 0);
    block_size = NewBlockSize(block_size);

    return(sizeof(fsa_t) + block_size * num_of_blocks + num_of_blocks * sizeof(size_t));

}


/*******************************************************************************
* memory - the pointer returned from allocation done by the user.
*******************************************************************************/

fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
    fsa_t *fsa = memory;
    fsa_t *memory_runner = (fsa_t *)((char *)fsa + sizeof(fsa_t));
    fsa_t *last_block = (fsa_t *)((char *)memory + memory_size);
    size_t elements = 0;
    size_t i = 0;

    assert (block_size != 0);
    assert(memory_size != 0);
    assert(NULL != memory);

    fsa->next_avail_addr = (fsa_t *)((char *)memory + sizeof(fsa_t) + sizeof(size_t));

    block_size = NewBlockSize(block_size);
    elements = (memory_size - sizeof(fsa_t)) / (block_size + sizeof(size_t));

    for (i = 0; i < elements; ++i)
    {
        *(size_t *)memory_runner = (size_t)(memory);
        memory_runner = (void *)((char *)memory_runner + block_size + sizeof(size_t));
    }

    memory_runner = (fsa_t *)((char *)fsa + sizeof(fsa_t) + sizeof(size_t));
    for (i = 0; i < elements; ++i)
    {
        if (i != (elements - 1))
        {
            *(size_t *)memory_runner = (size_t)((char *)memory_runner + block_size + sizeof(size_t));
            memory_runner = (void *)((char *)memory_runner + block_size + sizeof(size_t));
        }
        else
        {
            memory_runner->next_avail_addr = NULL;
        }
    }

    return (fsa);

}

/*******************************************************************************
* Allocate memory in a free block, in the size of block_size.
*******************************************************************************/
void *FSAAlloc(fsa_t *fsa)
{
    fsa_t *allocated_memory = fsa->next_avail_addr;

	if (NULL != allocated_memory)
	{
    	fsa->next_avail_addr = (fsa_t *)(*(size_t *)fsa->next_avail_addr);
	}

    return(allocated_memory);

}

/*******************************************************************************
* Frees memory in an allocated block, in the size of block_size.
 ******************************************************************************/
void FSAFree(void *block_to_free)
{
    fsa_t *control = (((fsa_t *)((char *)block_to_free - SIZE_OF_WORD))->next_avail_addr);

    *(size_t *)(fsa_t *)block_to_free = (size_t)(control->next_avail_addr);

    control->next_avail_addr = block_to_free;
}

/*******************************************************************************
* Count the number of blocks that are free for allocation.
*******************************************************************************/
size_t FSACountFree(const fsa_t *fsa)
{
    fsa_t *runner = fsa->next_avail_addr;
    size_t counter = 0;

    while (NULL != runner)
    {
        ++counter;
        runner = runner->next_avail_addr;
    }

    return (counter);
}
