#include <stdio.h>

int FindDuplications(int arr[], size_t arr_size, int result[])
{
	size_t i = 0;
	size_t j = arr_size - 1;
	int num1 = 0;
	int num2 = 0;
	int k = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		num1 = arr[i];
		for (j = arr_size - 1; j > i; --j)
		{
			num2 = arr[j];
			
			if (num1 == num2)
			{
				result[k] = num1;
				++k;
				break;
			}
		}
	
	}
	
	return (k);
}

int main()
{
	int arr[] = {9, 5, 2, 7, 9, 33, 2, 6};
	int result[10];
	int k = 0;
	int i = 0;
	k =	FindDuplications(arr, 8, result);
	for (i = 0; i < k; ++i)
	{
		printf("%d, ", result[i]);
	}
	
	return 0;		
}
