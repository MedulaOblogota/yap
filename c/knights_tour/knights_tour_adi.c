#include <stdio.h>
#include <stdlib.h>

#include "kn_tour.h"

#include "bitarray.h"

#define IDX(i, j) ((8 * i) + j)
#define U_LONG_SIZE (64)
#define BOARD_SIZE (8)

unsigned long lut[U_LONG_SIZE] = {0};

static void InitLut();
static void PrintTrack(unsigned long *path);
static void KnightsTourRec(unsigned long element_idx, unsigned long *steps_so_far,
                                                            unsigned long *path);

int KnightsTour(unsigned long cur_place)
{
    unsigned long steps = 0;
    unsigned long exp_total_steps = ~(unsigned long)0;
    unsigned long path[64] = {0};
    size_t i = 0;

    InitLut();

    for (i = 0; i < 64; ++i)
    {
        path[i] = 0;
    }

    KnightsTourRec(cur_place, &steps, path);

    if (steps == exp_total_steps)
    {
        PrintTrack(path);
    }

    return (steps == exp_total_steps);
}

static int FindMinSubStep(unsigned long steps, size_t steps_num,
                                                    unsigned long *steps_so_far)
{
    size_t i = 0;
    size_t min_steps = 9;
    size_t min_ind = -1;

    for (i = 0; (i < U_LONG_SIZE) && (steps_num > 0); ++i)
    {
        if (BitsArrIsBitOn(steps, i))
        {
            size_t steps_num = BitsArrCountOn(lut[i] & (~*steps_so_far));

            if (steps_num < min_steps)
            {
                min_ind = i;
                min_steps = steps_num;
            }
        }
    }

    return (min_ind);
}

static void KnightsTourRec(unsigned long element_idx, unsigned long *steps_so_far,
                                                            unsigned long *path)
{
    unsigned long steps = 0;
    unsigned long counter = 0;
    size_t steps_num = 0;

    *steps_so_far = BitsArrSetBitOn(*steps_so_far, element_idx);
    steps = (lut[element_idx] & (~*steps_so_far));
    steps_num = BitsArrCountOn(steps);

    path[element_idx] = (++counter);

    while (steps_num > 0)
    {
        size_t next_step = FindMinSubStep(steps, steps_num, steps_so_far);

        KnightsTourRec(next_step, steps_so_far, path);

        if ((~(unsigned long)0) == *steps_so_far)
        {
            return;
        }

        *steps_so_far = BitsArrSetBitOff(*steps_so_far, element_idx);
        steps = BitsArrSetBitOff(steps, next_step);
        path[element_idx] = 0;
        --counter;
        --steps_num;
    }
}

static void PrintTrack(unsigned long *path)
{
    size_t i = 0;
    size_t j = 0;

    puts("");

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (path[IDX(i, j)] < 10)
            {
                printf("%02lu ", path[IDX(i, j)]);
            }
            else
            {
                printf("%lu ", path[IDX(i, j)]);
            }
        }
        puts("");
    }

    puts("");
}

static void InitLut()
{
    int i = 0;
    int j = 0;
    size_t counter = 0;

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        for (j = 0; j < BOARD_SIZE; ++j)
        {
            /*up*/
            if ((i - 2) >= 0)
            {
                if ((j + 1) < BOARD_SIZE)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i - 2), (j + 1)));
                }
                if ((j - 1) >= 0)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i - 2), (j - 1)));
                }
            }
            /*down*/
            if ((i + 2) < BOARD_SIZE)
            {
                if ((j + 1) < BOARD_SIZE)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i + 2), (j + 1)));
                }
                if ((j - 1) >= 0)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i + 2), (j - 1)));
                }
            }
            /*left*/
            if ((j - 2) >= 0)
            {
                if ((i + 1) < BOARD_SIZE)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i + 1), (j - 2)));
                }
                if ((i - 1) >= 0)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i - 1), (j - 2)));
                }
            }
            /*right*/
            if ((j + 2) < BOARD_SIZE)
            {
                if ((i + 1) < BOARD_SIZE)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i + 1), (j + 2)));
                }
                if ((i - 1) >= 0)
                {
                    lut[counter] = BitsArrSetBitOn(lut[counter], IDX((i - 1), (j + 2)));
                }
            }

            ++counter;
        }
    }
}
