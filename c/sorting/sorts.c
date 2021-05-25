#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "sorting.h"

#define UNUSED(x) (void)(x)

#define NIBBLES_IN_INT (sizeof(int) *  2)
#define BITS_IN_NIBBLE (4)
#define NIBBLE_MAX (0xF)

static void SwapInt(int *num1, int *num2);
static void FillElementsNumLUT(void *arr, size_t arr_size, size_t *index_lut,
                    size_t (*find_index)(const void *element, const void *param),
                    const void *param, size_t ele_size);
static void ElementsArrToIndexLUT(size_t *index_lut, size_t index_lut_size);
int SortByIndexLut(void *arr, size_t *index_lut, size_t arr_size,
                    size_t (*find_index)(const void *element, const void *param),
                    const void *param, size_t ele_size);
static size_t FindIntArrIterNum(const void *base, size_t num_of_members);
static size_t FindNumOfDigits(int num);
static size_t FindDigit(const void *num, const void *digit_index);
/*static size_t FindRange(void *base, size_t num_of_members, size_t ele_size,
                                                            const void *param);
static int GenericRadixSort(void *base, size_t num_of_members, size_t ele_size,
                    size_t (*find_index)(const void *ele, const size_t iter_num,
                    const void *param),const void *param, size_t num_of_bytes);
static size_t RadixFindIndex(const void *ele, const void *radix_param_ptr);*/

typedef struct radix_param_s
{
    size_t (*find_index)(const void *ele, const size_t iter, const void *param);
    size_t iter_num;
    const void *param;
}radix_param_t;

void BubbleSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    int is_not_sorted = 1;

    assert(NULL != arr);

    while (is_not_sorted)
    {
        is_not_sorted = 0;
        --arr_size;

        for (i = 0; i < arr_size; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                SwapInt(arr + i, arr + i + 1);

                is_not_sorted = 1;
            }
        }
    }
}

void SelectionSort(int *arr, size_t arr_size)
{
    size_t cur_size = arr_size;
    int *min = arr;
    size_t i = 0;
    size_t k = 0;

    assert(NULL != arr);

    for (i = 0; i < arr_size; ++i, --cur_size, ++arr)
    {
        min = arr;

        for (k = 0; k < cur_size; ++k)
        {
            if (*min > arr[k])
            {
                min = arr + k;
            }
        }

        SwapInt(min, arr);
    }
}

void InsertionSort(int *arr, size_t arr_size)
{
    int runner = 0;
    size_t i = 0;
    size_t k = 0;
    size_t cur_last_index = 1;

    assert(NULL != arr);

    for (i = 1; i < arr_size; ++i, ++cur_last_index)
    {
        runner = arr[cur_last_index];

        for (k = cur_last_index; k > 0; --k)
        {
            if (runner > arr[k - 1])
            {
                break;
            }
        }
        memmove(arr + k + 1, arr + k, (cur_last_index - k) * sizeof(int));

        arr[k] = runner;
    }
}

static size_t FindDigit(const void *num, const void *digit_index)
{
    int index = (*(int*)num / *(int*)digit_index) % 10;

    if (index > 0)
    {
        return ((size_t)index);
    }

    return ((size_t)(index * -1));
}

int RadixSort(int *base, size_t num_of_members)
{
    size_t i = 0;
    size_t iter_num = FindIntArrIterNum(base, num_of_members);
    int ret = 1;
    int digit_index = 1;

    for (i = 0; (iter_num > i) && (1 == ret); ++i)
    {
        ret = CountingSort(base, sizeof(int), 10, num_of_members,
                                                    FindDigit, &digit_index);
        digit_index = digit_index * 10;
    }

    return (ret);
}

int CountingSort(void *arr, size_t ele_size, size_t range, size_t arr_size,
                    size_t (*find_index)(const void *element, const void *param),
                    const void *param)
{
    int ret = 1;
    size_t *index_lut = (size_t*)calloc(range, sizeof(size_t));
    if (NULL == index_lut)
    {
        free(index_lut);

        return (0);
    }
    FillElementsNumLUT(arr, arr_size, index_lut, find_index, param, ele_size);
    ElementsArrToIndexLUT(index_lut, range);
    ret = SortByIndexLut(arr, index_lut, arr_size, find_index, param, ele_size);

    free(index_lut);

    return (ret);
}

static void FillElementsNumLUT(void *arr, size_t arr_size, size_t *index_lut,
                    size_t (*find_index)(const void *element, const void *param),
                    const void *param, size_t ele_size)
{
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        ++index_lut[find_index(((char*)arr) + (i * ele_size), param)];
    }

    return;
}

static void ElementsArrToIndexLUT(size_t *index_lut, size_t index_lut_size)
{
    size_t i = 0;

    for (i = 0; i < index_lut_size && 0 == index_lut[i]; ++i);
    --index_lut[i];

    for (++i; i < index_lut_size; ++i)
    {
        index_lut[i] += index_lut[i - 1];
    }
}

int SortByIndexLut(void *arr, size_t *index_lut, size_t arr_size,
                    size_t (*find_index)(const void *element, const void *param),
                    const void *param, size_t ele_size)
{
    size_t i = 0;
    void *arr_ele = NULL;
    void *tmp_arr_ele = NULL;
    void *tmp_arr = malloc(arr_size * ele_size);
    if (NULL == tmp_arr)
    {
        free(tmp_arr);

        return (0);
    }

    for (i = arr_size; i > 0; --i)
    {
        arr_ele = (char*)arr + ((i - 1) * ele_size);
        tmp_arr_ele = (char*)tmp_arr + ele_size * index_lut[find_index(arr_ele, param)];
        --index_lut[find_index(arr_ele, param)];

        memmove(tmp_arr_ele, arr_ele, ele_size);
    }
    memmove(arr, tmp_arr, ele_size * arr_size);

    free(tmp_arr);

    return (1);
}

static void SwapInt(int *num1, int *num2)
{
    int temp = 0;

    assert(NULL != num1);
    assert(NULL != num2);

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;

    return;
}

static size_t FindIntArrIterNum(const void *base, size_t num_of_members)
{
    size_t i = 0;
    const int *arr = (const int*)base;
    int max = 0;
    int min = 0;

    for (i = 0; i < num_of_members; ++i)
    {
        if (arr[i] > max || arr[i] < min)
        {
            if (arr[i] > max)
            {
                max = arr[i];
            }
            else
            {
                min = arr[i];
            }
        }
    }
    min = FindNumOfDigits(min);
    max = FindNumOfDigits(max);

    if(min > max)
    {
        return (min);
    }

    return (max);
}

static size_t FindNumOfDigits(int num)
{
    size_t i = 0;

    for (i = 1; 0 != num; ++i)
    {
        num /= 10;
    }

    return (i);
}

/*
static size_t RadixFindIndex(const void *ele, const void *radix_param_ptr)
{
    radix_param_t radix_param = *(radix_param_t*)radix_param_ptr;

    return (radix_param.find_index(ele, radix_param.iter_num, radix_param.param));
}


static int GenericRadixSort(void *base, size_t num_of_members, size_t ele_size,
                    size_t (*find_index)(const void *ele, const size_t iter_num,
                    const void *param),const void *param, size_t num_of_bytes)
{
    radix_param_t radix_param;
    size_t i = 0;
    size_t iter_num = ele_size / num_of_bytes;
    int ret = 1;
    size_t range = 0;

    radix_param.find_index = find_index;
    radix_param.param = param;

    for (i = 0; (iter_num > i) && (1 == ret); ++i)
    {
        radix_param.iter_num = i;

        range = FindRange(base, num_of_members, ele_size, &radix_param);
        if (0 != range)
        {
            ret = CountingSort(base, ele_size, range, num_of_members,
                                                RadixFindIndex, &radix_param);
        }
    }

    return (ret);
}

static size_t FindRange(void *base, size_t num_of_members, size_t ele_size,
                                                            const void *param)
{
    size_t cur_range = 0;
    size_t big_range = 0;
    size_t i = 0;

    for (i = 0; i < num_of_members; ++i)
    {
        cur_range = RadixFindIndex((char*)base + (i * ele_size), param);
        if (big_range < cur_range)
        {
            big_range = cur_range;
        }
    }

    return (big_range);
}
*/
