#include <stdio.h>

void FindMaxAndMin(int *arr, size_t size, int *min, int *max)
{
    size_t i = (size % 2);
    int counter = 0;
    *min = arr[0];
    *max = arr[0];

    /*i = (size % 2 != 0);

    min = arr[i];
    max = arr[i];*/

    for (; i < size - 1; i += 2)
    {
        if (arr[i] > arr[i+1])
        {
            counter += 3;
            if (*max < arr[i])
            {
                *max = arr[i];
            }
            if (*min > arr[i+1])
            {
                *min = arr[i+1];
            }
        }
        else
        {
            counter += 3;
            if (*max < arr[i+1])
            {
                *max = arr[i+1];
            }
            if (*min > arr[i])
            {
                *min = arr[i];
            }
        }
    }

    printf("compared %d times\n", counter);
    printf("min=%d. max=%d\n", *min, *max);

}

int main()
{
    int arr[] = {-3, -2, 12, -3, 15, -9, 8, 4, 12 };
    int min;
    int max;

    FindMaxAndMin(arr, 9, &min, &max);

}
