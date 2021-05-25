#include <stdio.h>
#include <stdlib.h>


int MaxSubArray(int *arr, size_t size, int *solution, size_t solution_size)
{
	size_t i = 0;
	size_t beg = 0;
	size_t end = 0;
	int sum = 0;
	int maxsum = 0;
	int success = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] > sum)
		{
			if (sum > 0)
			{
				sum += arr[i];
			}
			else
			{
				beg = i;
				sum = arr[i];
			}
		} 
		else 
		{
			sum += arr[i];
		}
		if (sum > maxsum)
		{
			end = i;
			maxsum = sum;
			success = 1;
		}
/*		sum += arr[i];*/
	}
	
	solution[0] = maxsum;
	solution[1] = beg;
	solution[2] = end;
	return success;
}

int main() 
{
	int arr[] = {0};
	int solution[3] = {0};
	
	int i = 0;
	/*printf("MaxSubArray is %d\n", MaxSubArray(arr, 9));*/
	if (MaxSubArray(arr, 9, solution, 3))
	{
		for (i = 0; i < 3; ++i)
		{
			printf("%d\n", solution[i]);
		}
	}
	else
		printf("failure");
	
	
	return 0;
}
