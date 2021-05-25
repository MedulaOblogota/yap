#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include "VSA.h"

#define SIZE_OF_WORD (8)

typedef struct block_iter_s block_iter_t;

struct block_iter_s
{
    block_iter_t *next;
    ssize_t size;
#ifndef NDEBUG
    size_t vsa_id;
#endif
};

struct vsa_s
{
    block_iter_t *next_avail_addr;
};

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

static void Defragment(vsa_t *vsa)
{
    block_iter_t *block = vsa->next_avail_addr;
    block_iter_t *temp = NULL;

    while (NULL != block)
    {
        if (block->size <= 0)
        {
            if (NULL != block->next)
            {
                if (block->next->size <= 0)
                {
                    temp = block->next;
                    block->size += temp->size - sizeof(block_iter_t);
                    block->next  = temp->next;
                    temp->next = NULL;
                    temp->size = 0;
                }
            }
        }
        /*else
        {
            block = block->next;
        }*/
        if (!((NULL != block->next) && (block->next->size < 0)) || (block->size > 0))
        {
            block = block->next;
        }
    }
}

static block_iter_t *FindSpace(vsa_t *vsa, size_t requested_size)
{
    block_iter_t *block = vsa->next_avail_addr;

    requested_size += sizeof(block_iter_t);
    requested_size = NewBlockSize(requested_size);

    while (NULL != block)
    {
        if (block->size < 0)
        {
            if (((-1) * (block->size)) >= (ssize_t)requested_size)
            {
                return (block);
            }
        }
        block = block->next;
    }

    return NULL;
}

/*******************************************************************************
* Start a VSA memory manager, from memory pool starting at address <memory>
* and ending after <size> bytes.
*******************************************************************************/
vsa_t *VSAInit(void *memory, size_t memory_size)
{
    vsa_t *vsa = memory;
    block_iter_t *block = NULL;

    memory_size = NewBlockSize(memory_size);

    block = (block_iter_t *)((char *)memory + sizeof(vsa_t));

    if ((char *)block + sizeof(block_iter_t) > (char *)memory + memory_size)
    {
        return NULL;
    }

    vsa->next_avail_addr = block;
    vsa->next_avail_addr->next = NULL;
    vsa->next_avail_addr->size = (-1) * (memory_size - sizeof(block_iter_t) - sizeof(vsa_t));
#ifndef NDEBUG
    vsa->next_avail_addr->vsa_id = 0xdeadbeef;
#endif

    return(vsa);
}

/*******************************************************************************
* Allocate <size> bytes of memory in <vsa>.
*******************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t size)
{
    block_iter_t *next_avail_space = NULL;
    block_iter_t *new_block = NULL;
    block_iter_t *prev_next = NULL;
    ssize_t prev_size = 0;

    Defragment(vsa);

    size = NewBlockSize(size);

    next_avail_space = FindSpace(vsa, size);

    if (NULL != next_avail_space)
    {
        prev_size = next_avail_space->size;
        prev_next = next_avail_space->next;


        new_block = (block_iter_t *)((char *)next_avail_space + size + sizeof(block_iter_t));
        next_avail_space->size = (ssize_t)size;
        next_avail_space->next = new_block;
#ifndef NDEBUG
        next_avail_space->vsa_id = 0xdeadbeef;
#endif
        if ((prev_size + (ssize_t)size + (ssize_t)sizeof(block_iter_t)) != 0)
        {
            new_block->size = prev_size + (ssize_t)size + (ssize_t)sizeof(block_iter_t);
            new_block->next = prev_next;
#ifndef NDEBUG
            new_block->vsa_id = 0xdeadbeef;
#endif
        }
        else
        {
            next_avail_space->next = NULL;
        }

    return ((char *)next_avail_space + sizeof(block_iter_t));

    }

    return (next_avail_space);

}

/*******************************************************************************
* Free memory starting at address <block_to_free>, and return it to
* it's associated VSA free-list.
 ******************************************************************************/
void VSAFree(void *block_to_free)
{
    block_iter_t *iter = (block_iter_t *)((char *)block_to_free - sizeof(block_iter_t));
    size_t end_of_block = 0;

    if (NULL != block_to_free)
    {

#ifndef NDEBUG
        end_of_block = *(size_t *)((char *)iter + 2 * sizeof(size_t));
        if (end_of_block != 0xdeadbeef)
        {
            return;
        }
#endif

    iter->size = -1 * (iter->size);

#ifndef NDEBUG
    iter->vsa_id = 0;
#endif

    }

}

/*******************************************************************************
* Return the size of the biggest consequent memory block in <vsa>
* available to be allocated.
*******************************************************************************/
size_t VSALargestChunkAvailable(vsa_t *vsa)
{
    block_iter_t *block = vsa->next_avail_addr;
    size_t max = 0;
    Defragment(vsa);

    while (NULL != block)
    {
        if (block->size < 0)
        {
            if ((-1) * (block->size) > (ssize_t)max)
            {
                max = (-1) * block->size;
            }
        }

        block = block->next;
    }

    return(max - sizeof(block_iter_t));

}
