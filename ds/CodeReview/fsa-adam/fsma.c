/******************************************************************
* Author: Adam Blau                                               *
*                                                                 *
* Reviewer: Roy Yablonka                                          *
*                                                                 *
* Version: S                                                      *
*                                                                 *
* Description: fsma                                               *
******************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include "FSA.h"

struct fsa_s
{
    size_t offset_next_free;
    size_t free_blocks_counter;
    void *base;
};



size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    assert(0 != block_size);
    assert(0 != num_of_blocks);

    if (0 != block_size % 8)
    {
        block_size = (block_size - (block_size % 8)) + 8;
    }

    return (sizeof(fsa_t) + ((block_size + sizeof(size_t)) * num_of_blocks));
}



fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
    void *end_ptr = NULL;
    void *runner = NULL;
    fsa_t *fsa = memory;
    size_t i = 1;

    assert(NULL != memory);

    end_ptr = (char *)memory + memory_size;
    runner = (char *)memory + sizeof(fsa_t);
    if (0 != block_size % 8)
    {
        block_size = (block_size - (block_size % 8)) + 8;
    }

    while (runner < end_ptr)
    {
        *(size_t *)runner = i * (block_size + sizeof(size_t));
        runner = (char *)runner + (block_size + sizeof(size_t));
        ++i;
    }

    fsa->offset_next_free = 0;
    fsa->free_blocks_counter = i - 1;
    fsa->base = (char *)memory + sizeof(fsa_t);

    return (fsa);
}



void *FSAAlloc(fsa_t *fsa)
{
    size_t backup = 0;
    void *runner_ptr = NULL;

    assert (NULL != fsa);

    if (fsa->free_blocks_counter == 0)
    {
        return (NULL);
    }

    backup = fsa->offset_next_free;
    runner_ptr = (char *)fsa->base + backup;
    fsa->offset_next_free = *(size_t *)runner_ptr;
    *(size_t *)runner_ptr = backup;
    fsa->free_blocks_counter -= 1;

    return ((size_t *)runner_ptr + 1);
}



void FSAFree(void *block_to_free)
{
    size_t backup = 0;
    fsa_t *runner_ptr = NULL;
    void *controler = NULL;
    void *convert_to_fsa = NULL;

    assert(NULL != block_to_free);

    controler = (char *)block_to_free - sizeof(size_t);
    backup =  *(size_t *)controler;
    convert_to_fsa = (char *)controler - (backup + sizeof(fsa_t));
    runner_ptr = (fsa_t *)convert_to_fsa;
    *(size_t *)controler = runner_ptr->offset_next_free;
    runner_ptr->offset_next_free = backup;
    runner_ptr->free_blocks_counter += 1;

    return;
}



size_t FSACountFree(const fsa_t *fsa)
{
    assert (NULL != fsa);

    return (fsa->free_blocks_counter);
}







































/*xxx*/
