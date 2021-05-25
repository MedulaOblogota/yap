#ifndef VSA_OL70 /*header guard*/
#define VSA_OL70
/*******************************************************************************
* The functions in this file handle a Variable size memory allocator, will
* be denoted as VSA.
*
* Written by: OL-70
* Last update: 15:00 , 28.07.2019
*******************************************************************************/

#include <stddef.h>

typedef struct vsa_s vsa_t;

/*******************************************************************************
* Start a VSA memory manager, from memory pool starting at address <memory>
* and ending after <size> bytes.
*
* Return value - pointer to vsa_t.
*
* Complexity O(1).
*******************************************************************************/
vsa_t *VSAInit(void *memory, size_t memory_size);

/*******************************************************************************
* Allocate <size> bytes of memory in <vsa>.
*
* Return value - Pointer to allocated memory if enough
* consequent memory was found ,NULL otherwise.
*
* Complexity O(n).
*******************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t size);

/*******************************************************************************
* Free memory starting at address <block_to_free>, and return it to
* it's associated VSA free-list.
*
* Return Value - None.
* Complexity O(1).
 ******************************************************************************/
void VSAFree(void *block_to_free);

/*******************************************************************************
* Return the size of the biggest consequent memory block in <vsa> 
* available to be allocated.
*
* Return Value - size of block in bytes.
* Complexity O(n).
*******************************************************************************/
size_t VSALargestChunkAvailable(vsa_t *vsa);

#endif  /*VSA_OL70*/