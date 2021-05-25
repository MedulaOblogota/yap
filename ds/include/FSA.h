#ifndef FSA_OL70 /*header guard*/
#define FSA_OL70
/*******************************************************************************
* The functions in this file handle a fixed size memory allocator, will
* be denoted as FSA.
*
* Written by: OL-70
* Last update: 11:30 , 25.07.2019
*******************************************************************************/

#include <stddef.h>

typedef struct fsa_s fsa_t;

/*******************************************************************************
* block_size - num of bytes in a block.
* num_of_blocks - total num of blocks possible to allocate.
*
* WARNING - Not using this function to calculate the required size may result
* in undefined behavior.
*
* Return value - num of bytes requested to allocate in FSAInit.
*
* Complexity O(1).
*******************************************************************************/
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks);


/*******************************************************************************
* memory - the pointer returned from allocation done by the user.
* block_size - num of bytes in a block.
* memory_size - return size of FSASuggestSize.
*
* WARNING - When allocated memory for the FSA, use FSARequiredSize to
* calculate the amount of bytes to allocate.
*
* Return value - num of bytes requested to allocate in Init.
*
* Complexity O(1).
*******************************************************************************/
fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size);

/*******************************************************************************
* Allocate memory in a free block, in the size of block_size.
* Return value - pointer to allocated memory.
*
* Complexity O(1).
*******************************************************************************/
void *FSAAlloc(fsa_t *fsa);

/*******************************************************************************
* Frees memory in an allocated block, in the size of block_size.
*
* Complexity O(1).
 ******************************************************************************/
void FSAFree(void *block_to_free);

/*******************************************************************************
* Count the number of blocks that are free for allocation.
* Return value - number of free blocks.
*
* Complexity O(n).
*******************************************************************************/
size_t FSACountFree(const fsa_t *fsa);

#endif  /*FSA_OL70*/
