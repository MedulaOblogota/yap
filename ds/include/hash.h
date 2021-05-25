#ifndef HASH_OL70 /*header guard*/
#define HASH_OL70
/**************************************************************
* The functions in this file handle a Hash Table                   *
*  It will be denoted as Hash.                                 *
*                                                                                                                        *
* Written by: OL-70                                                                                     *
* Last update: 15:30 , 22.08.2019                                          *
***************************************************************/
#include <stddef.h>

typedef struct hash_s hash_t;
typedef size_t (*hash_func_t)(const void *data_key);


/********************************************************************
* Allocates memory for the Hash Table.
* HashDestroy must be called after the work with the Hash Table is done.
* cmp_func - compare function that the user adds. Cannot be NULL.
* param - parameter for the compare function.
* size - the capacity of the hash table.
*
* Return Value: A pointer to the created Hash Table.
* If memory allocation fails - NULL will be returned.
 *******************************************************************/
hash_t *HashCreate(size_t num_of_buckets, hash_func_t hash_func,
                          int (*cmp_func)(const void *data1, const void *data2));

/*******************************************************************************
* Releases the memory that has been allocted for the Hash Table.
*
* hash - a pointer to the hash table. Cannot be NULL.
*******************************************************************************/
void HashDestroy(hash_t *hash);


/*******************************************************************************
* Inserts a given data into the Hash Table.
*
* hash - a pointer to the hash table. Cannot be NULL.
*
* data_key - the data to be inserted into the hash table.
*
* Return Value - 1 for succeeded to insert and 0 otherwise.
*******************************************************************************/
int HashInsert(hash_t *hash, const void *data);


/*******************************************************************************
* Removes a given data from the Hash Table.
*
* hash - a pointer to the hash table. Cannot be NULL.
* data - an identifier for the removed data.
* data_key - the unique data key
*
* Return Value - returns a pointer to the removed data or NULL otherwise.
*******************************************************************************/
void *HashRemove(hash_t *hash, const void *data);

/*******************************************************************************
* Finds a given data into the Hash Table.
*
* hash - a pointer to the hash table. Cannot be NULL.
*
* data - an identifier for the searched data.
*
* Return Value - returns a pointer to the found data or NULL otherwise.
*******************************************************************************/
void *HashFind(hash_t *hash, const void *data);

/*******************************************************************************
* Calculates the amount of elements in the hash table.
*
* hash - a pointer to the hash table. Cannot be NULL.
*
*
* Return Value - The amount of elements in the hash table
*******************************************************************************/
size_t HashSize(const hash_t *hash);


/*******************************************************************************
* Traverses the Hash Table, executing a function on each element.
*
* hash - a pointer to the hash table. Cannot be NULL.
*
* action_func - a pointer to an action function provided by the user.
* param - a parameter for the action function.
*
* Return Value - 1 for continue and 0 for stop
*******************************************************************************/
int HashForEach(hash_t *hash, int (*action_func)(void *data, void *param), void *param);


/*******************************************************************************
* Boolean Function - whether the hash table is empty or not.
*
* hash - a pointer to the hash table. Cannot be NULL.
*
*
* Return Value - 1 for TRUE and 0 for FALSE
*******************************************************************************/
int HashIsEmpty(const hash_t *hash);

#endif  /*HASH_OL70*/
