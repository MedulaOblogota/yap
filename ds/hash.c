#include <stdlib.h> 	/* malloc */
#include <assert.h>		/* assert */

#include "hash.h"
#include "dlist.h"

struct hash_s
{
    hash_func_t hash_func;
    comp_func_t cmp_func;
    dlist_t **containers;
    size_t num_of_buckets;
};

static dlist_iter_t FindIterator(hash_t *hash, const void* data);
static void CacheData(dlist_t *dlist, dlist_iter_t iterator, void *data);

/********************************************************************
* Allocates memory for the Hash Table.
 *******************************************************************/
 hash_t *HashCreate(size_t num_of_buckets, hash_func_t hash_func,
                           int (*cmp_func)(const void *data1, const void *data2))
{
	hash_t *hash = NULL;
	size_t i = 0;

	assert(NULL != hash_func);
	assert(NULL != cmp_func);

	hash = malloc(sizeof(hash_t));

	if (NULL == hash)
	{
		return (NULL);
	}

	hash->hash_func = hash_func;
	hash->cmp_func = cmp_func;
	hash->num_of_buckets = num_of_buckets;
	hash->containers = malloc(num_of_buckets * sizeof(dlist_t *));

	if (NULL == hash->containers)
	{
		return (NULL);
	}
	
	for (i = 0; i < num_of_buckets; ++i)
	{
		hash->containers[i] = DListCreate();

		if (NULL == hash->containers[i])
		{
			size_t j = 0;

			for (j = 0; j < i; ++j)
			{
				DListDestroy(hash->containers[j]);
			}

			free(hash->containers);
			free(hash);

			return (NULL);
		}
	}

	return (hash);
}

/*******************************************************************************
* Releases the memory that has been allocted for the Hash Table.
*******************************************************************************/
void HashDestroy(hash_t *hash)
{
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < hash->num_of_buckets; ++i)
	{
		DListDestroy(hash->containers[i]);
	}

	free(hash->containers);
	free(hash);
}


/*******************************************************************************
* Inserts a given data into the Hash Table.
*******************************************************************************/
int HashInsert(hash_t *hash, const void *data)
{
	size_t place_in_hash = 0;

	dlist_iter_t end = NULL;
	dlist_iter_t item = NULL;

	assert(NULL != hash);
	assert(NULL != data);

	place_in_hash = hash->hash_func(data) % hash->num_of_buckets;
	end = DListEnd(hash->containers[place_in_hash]);

	if (NULL != HashFind(hash, data))
	{
		HashRemove(hash, data);
	}

	item = DListPushFront(hash->containers[place_in_hash], (void *)data);

	return (!DListIsSameIter(end, item));
}


/*******************************************************************************
* Removes a given data from the Hash Table.
*******************************************************************************/
void *HashRemove(hash_t *hash, const void *data)
{
	size_t place_in_hash = 0;
	dlist_iter_t found_iterator = NULL;
	void *removed_data = NULL;

	assert(NULL != hash);
	assert(NULL != data);

	place_in_hash = hash->hash_func(data) % hash->num_of_buckets;
	found_iterator = FindIterator(hash, data);

	if (!DListIsSameIter(found_iterator,DListEnd(hash->containers[place_in_hash])))
	{
		removed_data = DListGetData(found_iterator);
		DListRemove(found_iterator);
	}

	return (removed_data);
}

/*******************************************************************************
* Finds a given data into the Hash Table.
*******************************************************************************/
void *HashFind(hash_t *hash, const void *data)
{
	dlist_iter_t found_iterator = NULL;
	size_t place_in_hash = 0;
	void *found_data = NULL;
	dlist_t *dlist = NULL;

	assert(NULL != hash);
	assert(NULL != data);

	found_iterator = FindIterator(hash, data);
	place_in_hash = hash->hash_func(data) % hash->num_of_buckets;
	dlist = hash->containers[place_in_hash];

	if (DListIsSameIter(found_iterator, DListEnd(dlist)))
	{

		return (NULL);
	}
	else
	{
		found_data = DListGetData(found_iterator);
		CacheData(dlist, found_iterator, found_data);

		return (found_data);
	}
}

/*******************************************************************************
* Calculates the amount of elements in the hash table.
*******************************************************************************/
size_t HashSize(const hash_t *hash)
{
	size_t size = 0;
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < (hash->num_of_buckets); ++i)
	{
		size += DListSize(hash->containers[i]);
	}

	return (size);
}


/*******************************************************************************
* Traverses the Hash Table, executing a function on each element.
*******************************************************************************/
int HashForEach(hash_t *hash, int (*action_func)(void *data, void *param), void *param)
{
	size_t i = 0;

	assert(NULL != hash);
	assert(NULL != action_func);

	for (i = 0; i < (hash->num_of_buckets); ++i)
	{
		dlist_iter_t begin = DListBegin(hash->containers[i]);
		dlist_iter_t end = DListEnd(hash->containers[i]);

		if (DListForEach(begin, end, action_func, param) == 1)
		{
			return (0);
		}
	}

	return (1);

}

/*******************************************************************************
* Boolean Function - whether the hash table is empty or not.
*******************************************************************************/
int HashIsEmpty(const hash_t *hash)
{
	return(HashSize(hash) == 0);
}

static dlist_iter_t FindIterator(hash_t *hash, const void* data)
{
	size_t place_in_hash = hash->hash_func(data) % hash->num_of_buckets;

	dlist_t *dlist = hash->containers[place_in_hash];

	dlist_iter_t begin = DListBegin(dlist);
	dlist_iter_t end = DListEnd(dlist);

	return(DListFind(begin, end, hash->cmp_func, data));
}

static void CacheData(dlist_t *dlist, dlist_iter_t iterator, void *data)
{
	DListRemove(iterator);
	DListPushFront(dlist, data);
}
