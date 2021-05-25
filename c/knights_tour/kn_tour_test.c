#include <stdio.h>

#include "kn_tour.h"

#define INITIAL_LOCATION (0)
#define BOARD_SIZE (64)

int main()
{
	int i = 0;
	int spots[] = {0, 1, 2,3, 4, 5,6, 7, 8,9,10,11, 12,13,14, 15,16, 17,18,19,20, 21,22,23,24, 25,26,27, 28,29,30,31, 32, 33,34,35, 36,37,
                        38,39,40,41,42,43,44, 45, 46,47, 48, 49,50,51, 52, 53, 54, 55, 56, 57,58,59,60, 61, 62,63 };

	for (i = 0; i < BOARD_SIZE; ++i)
	{
	/*	int successful = KnightsTour(spots[i]);*/

		/*if (successful)
		{
			for (j = 0; j < 64; ++j)
			{
				if (j % 8 == 0)
				{
					printf("\n");
				}
				printf("%02d, ", path[j]);
			}
		}*/
		/*printf("for %d its %d\n", INITIAL_LOCATION, KnightsTour(INITIAL_LOCATION, path));*/
		printf("\n\nfor %d its %d\n\n", spots[i], KnightsTour(spots[i]));
	}
	/*printf("for %d its %d\n", INITIAL_LOCATION, KnightsTour(INITIAL_LOCATION, path));*/




	return (0);
}
