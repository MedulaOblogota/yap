#include <stdio.h>
#include "UID.h"

#define ARRAY_SIZE (50)
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

int main()
{
    UID_t uid_array[ARRAY_SIZE];
    size_t i = 0;
    size_t j = 0;
    size_t counter = 0;

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        uid_array[i] = UIDCreate();
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (UIDISBad(uid_array[i]))
        {
            ++counter;
        }
        for (j = 0; j < ARRAY_SIZE; ++j)
        {
            if (i != j)
            {
                if (UIDIsSame(uid_array[i], uid_array[j]))
                {
                    ++counter;
                }
            }
        }
    }

    if (counter != 0)
    {
        printf(GRN"GREAT SUCCESS!!!!\n"RESET);
    }
    else
        {
            printf(RED"GREAT FAILURE!!!!!!!!!!!!\n"RESET);
        }
    /*TestCreateUID();
    TestUIDIsSame();
    TestUIDIsBad();*/
    return (0);
}
