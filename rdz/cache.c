/* implementing a constant sized cache which evicts the last item when full */

#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"
#include "hash.h"

#define NUM_OF_ITEMS 10

struct cache_s
{
  hash_t *hash;
  dlist_t *list;
  size_t size;
  size_t current_size;
};

typedef struct cache_s cache_t;

cache_t *CacheCreate(size_t size, hash_func_t hash_func, comp_func_t comp_func );

void CacheInsert(cache_t *cache, void *data);

int CacheRemove(cache_t *cache);

void CacheDelete(cache_t *cache);



cache_t *CacheCreate(size_t size, hash_func_t hash_func, comp_func_t comp_func )
{
  cache_t *cache = malloc(sizeof(cache_t));

  if (NULL == cache)
  {
    return NULL;
  }

  cache->hash = HashCreate(size / 10, hash_func, comp_func);

  if (NULL == cache->hash)
  {
    free(cache);
    return NULL;
  }

  cache->list = DListCreate();

  if (NULL == cache->list)
  {
    free(cache->hash);
    free(cache);
    return NULL;
  }

  cache->size = size;
  cache->current_size = 0;

  return cache;
}


void CacheInsert(cache_t *cache, void *data)
{
  
}

int CacheRemove(cache_t *cache)
{
  return 1;
}

void CacheDelete(cache_t *cache)
{
  HashDestroy(cache->hash);
  DListDestroy(cache->list);
  free(cache);
}

size_t hash(const void *key)
{
  return 1;
}

int comp(const void *data1, const void *data2)
{
  return 0;
}

int main()
{
  cache_t *cache = CacheCreate(10, hash, comp);
  CacheDelete(cache);
}
