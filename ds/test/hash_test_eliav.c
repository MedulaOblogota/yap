#include "EliavTest.h"
#include "hash.h"
#include "dlist.h"

#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)(x)

typedef struct fake_hash_s fake_hash_t;

struct fake_hash_s
{
    hash_func_t hash_func;
    comp_func_t comp_func_t;
    dlist_t **containers;
    size_t num_of_buckets;
};


/************************Static Functions Declerations*************************/

static size_t NumModTen(const void *data);
static int IsMatch(const void *data1, const void *data2);
static int PrintAllHash(void *data, void *param);

static size_t HashDictionary(const void *data);
static int IsMatchStr(const void *data1, const void *data2);
static int PrintHashSizes(void *data, void *param);

/*************************TEST Functions Declerations**************************/

void TestFlow();
void TestDictionary();

/*************************************main*************************************/

int main()
{

    RunTest(TestFlow);
    RunTest(TestDictionary);



    return (0);
}

/*******************************TEST Functions*********************************/

void TestFlow()
{
    size_t i = 0;
    size_t num_of_buckets = 10;
    size_t *data = malloc(2 * num_of_buckets * sizeof(size_t));
    size_t *check = malloc(2 * num_of_buckets * sizeof(size_t));
    hash_t *hash = HashCreate(num_of_buckets, NumModTen, IsMatch);
    void *fake_hash = hash;
    size_t *a = data;
    size_t *b = check;

    CheckCondition(NULL != data);
    CheckCondition(NULL != check);

    CheckCondition(NULL != hash);
    CmpNum(HashSize(hash), 0);
    CheckCondition(HashIsEmpty(hash));

    for (i = 0; i < (num_of_buckets * 2); ++i)
    {
        a[i] = i;
        b[i] = a[i];
        CheckCondition(HashInsert(hash, &a[i]));
        CmpNum(HashSize(hash), (i + 1));
        CheckCondition(!HashIsEmpty(hash));
    }

    for (i = 0; i < (num_of_buckets * 2); ++i)
    {
        b[i] = i;
        CmpPtr(HashFind(hash, &b[i]), &a[i]);
    }

    CmpPtr(HashRemove(hash, &b[1]), &a[1]);

    /*CheckCondition(0 == HashForEach(hash, PrintAllHash, fake_hash));*/

    HashDestroy(hash);

    free(data);
    free(check);

    return;
}

void TestDictionary()
{
    size_t i = 0;
    size_t num_of_buckets = 100;
    hash_t *hash = HashCreate(num_of_buckets, HashDictionary, IsMatchStr);
    char *dictionary[105000];
    char buf[100];
    void *fake_hash = hash;

    FILE *ptr = fopen("words","r");
    if (ptr == NULL)
    {
        printf("no such file.");
        return;
    }

    while(EOF != fscanf(ptr,"%s", buf))
    {
        dictionary[i] = malloc(1 + strlen(buf));
        strcpy(dictionary[i], buf);
        CheckCondition(HashInsert(hash, dictionary[i]));
        ++i;
        CmpNum(i, HashSize(hash));
    }

    PrintAddress(HashFind(hash, "sassasas"));
    GET_RUN_TIME(HashFind(hash, "kill"));

    /*CheckCondition(1 == HashForEach(hash, PrintHashSizes, fake_hash));*/

    for ( ; i > 0; --i)
    {
        free(dictionary[i-1]);
    }

    HashDestroy(hash);

    return;
}

/*******************************Static Functions*******************************/

static size_t NumModTen(const void *data)
{
    size_t returned_index = *(size_t *)data;

    return(returned_index % 10);
}

static int IsMatch(const void *data1, const void *data2)
{
    return((*(size_t *)data1) == (*(size_t *)data2));
}

static int PrintAllHash(void *data, void *param)
{
    fake_hash_t *hash = (fake_hash_t *)param;
    size_t container_index = ((hash->hash_func(data)) % (hash->num_of_buckets));

    printf("container No.:      %lu\n", container_index);
    PrintInt(data);
    puts("-------------------------------------------------------------\n");

    return (0);
}


static size_t HashDictionary(const void *data)
{
    size_t hash = 0;
    size_t i = 0;
    char *word = (char *)data;

    while ('\0' != *word)
    {
        hash <<= i;
        hash += *word;
        ++word;
        i += 3;
    }

    return (hash);
}

static int IsMatchStr(const void *data1, const void *data2)
{
    return(0 == strcmp(data1, data2));
}

static int PrintHashSizes(void *data, void *param)
{
    size_t i = 0;
    fake_hash_t *hash = (fake_hash_t *)param;
    (void)data;
    for(i = 0; i < hash->num_of_buckets; ++i)
    {
        dlist_t *dlist = hash->containers[i];
        printf("container No.:      %lu\n", i);
        printf("container size:      %lu\n", DListSize(dlist));
        puts("-------------------------------------------------------------\n");
    }

    return (1);
}
