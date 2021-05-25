#include <stdio.h>
#include <clock.h>

#include "kn_tour.h"

#define INITIAL_LOCATION (0)

int main()
{
	int path[63];
	int i = 0;
	int j = 0;
	int success[] = {0,1,4,6,7,11,14,16,20,24,27,31,32,35,44,45,48,52,54,56,61};
	int failures[] = {2,3,5,8,9,10,12,13,15,17,18,19,21,22,23,25,26,28,29,30,33,34,36,37,
                        38,39,40,41,42,43,46,47,49,50,51,53,55,57,58,59,60,62,63};

	int arr_size = sizeof(success) / sizeof(int);

	int failure_arr_size = sizeof(failures)/ sizeof(int);

	clock_t endwait;

	for (i = 0; i < arr_size; ++i)
	{
		printf("\n\nfor %d its %d\n\n", success[i], KnightsTour(success[i], path));
		for (j = 0; j < 64; ++j)
		{
			if (j % 8 == 0)
			{
				printf("\n");
			}
			printf("%02d, ", path[j]);
		}
		/*printf("for %d its %d\n", INITIAL_LOCATION, KnightsTour(INITIAL_LOCATION, path));*/
	}

	i = 0;
	endwait = clock () + seconds * CLOCKS_PER_SEC ;

	for (i = 0; i < failure_arr_size; ++i)
	{
		printf("\n\nfor %d its %d\n\n", success[i], KnightsTour(success[i], path));
		/*printf("for %d its %d\n", INITIAL_LOCATION, KnightsTour(INITIAL_LOCATION, path));*/
	}

	/*printf("for %d its %d\n", INITIAL_LOCATION, KnightsTour(INITIAL_LOCATION, path));*/




	return (0);
}
