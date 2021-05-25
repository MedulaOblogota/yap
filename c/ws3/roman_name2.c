#include <stdio.h>
#include <stdlib.h>

int roman_name(int soldiers[], int length)
{
	int knife = 0;
	int index = 0;
	int counter = length;
	
	while (counter > 1)
	{
		++index;
		index = index % length;
		while (soldiers[index] != 1)
		{
			++index;
			index = index % length;
		}
		soldiers[index] = 0;
		--counter;
		while (soldiers[index] != 1)
		{
			++index;
			index = index % length;
		}
		knife = index;
	}
	return knife;
}

int main() 
{
	int soldiers[16];
	int i=0;
	for (i = 0; i < 16; i++)
		soldiers[i] = 1;
	printf("last man standing is %d", roman_name(soldiers, 16));
	return (1);
}
