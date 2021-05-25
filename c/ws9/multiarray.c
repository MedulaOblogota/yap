#include <stdio.h>
#include <stdlib.h>

int Addition1(int arr[][3], int row, int col)
{
	return arr[0][1] + arr[1][0];
}

int Addition(int *arr, int row, int col)
{
	return arr[0 * 3 + 1] + arr[1 * 3 + 0];
}

int main() 
{
	int arr[][3] = {{1, 2, 3}, {4, 5, 6}};
	
	printf("arr[0][1] + arr[1][0] = %d\n", Addition(arr[0], 2, 1));
	
	printf("arr[0][1] + arr[1][0] = %d\n", Addition1(arr, 2, 1));
	
	return 0;
}
