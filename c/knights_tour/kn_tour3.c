#include <time.h>		/* clock_t 	*/
#include <stdio.h>		/* printf 	*/

#include "bitarray.h"

#define BOARD_SIZE (64)
#define ROW_SIZE (8)
#define SECONDS (20)

int RecursiveCalcRoute(unsigned long cur_place, unsigned long visited_places, int *path, int *index, clock_t clock);
static void InitMovePotentialLut();
static int IsFirstRow(int n);
static int IsFirstOrSecondRow(int n);
static int IsFirstColumn(int n);
static int IsFirstOrSecondColumn(int n);
static int IsEighthRow(int n);
static int IsSeventhOrEighthRow(int n);
static int IsEighthColumn(int n);
static int IsSeventhOrEighthColumn(int n);
static int IndexOfFirstBitOn(unsigned long location);
static unsigned long FindNewMoves(unsigned long potential_moves, unsigned long visited);
static unsigned long FindMin(unsigned long new_moves, unsigned long visited);


static unsigned long move_potential_lut[BOARD_SIZE] = {0};
int KnightsTour(unsigned long cur_place)
{
	int index = 1;
	int return_val = 0;
	int path[BOARD_SIZE] = {0};
	clock_t beginning;
	int j = 0;

	InitMovePotentialLut();
	beginning = clock();

	return_val = RecursiveCalcRoute(cur_place, 0, path, &index, beginning);

	printf("\ntime for %lu: %f seconds.\n", cur_place,  (double)(clock() - beginning)/CLOCKS_PER_SEC);
/*
	if (return_val == 1)
	{
		printf("Path is:\n");
		for (j = 0; j < BOARD_SIZE; ++j)
		{
			if (j % ROW_SIZE == 0)
			{
				printf("\n");
			}
			printf("%02d, ", path[j]);
		}
	}
*/
	return(return_val);
}

static int IsFirstRow(int n)
{
	return (n / ROW_SIZE == 0);
}

static int IsFirstOrSecondRow(int n)
{
	return ((n / ROW_SIZE == 0) || (n / ROW_SIZE == 1));
}

static int IsFirstColumn(int n)
{
	return (n % ROW_SIZE == 0);
}

static int IsFirstOrSecondColumn(int n)
{
	return ((n % ROW_SIZE == 0) || (n % ROW_SIZE == 1));
}

static int IsEighthRow(int n)
{
	return (n / ROW_SIZE == (ROW_SIZE - 1));
}

static int IsSeventhOrEighthRow(int n)
{
	return ((n / ROW_SIZE == (ROW_SIZE - 2)) || (n / ROW_SIZE == (ROW_SIZE - 1)));
}

static int IsEighthColumn(int n)
{
	return (n % ROW_SIZE == (ROW_SIZE - 1));
}

static int IsSeventhOrEighthColumn(int n)
{
	return ((n % ROW_SIZE == (ROW_SIZE - 2)) || (n % ROW_SIZE == (ROW_SIZE - 1)));
}

static void InitMovePotentialLut()
{
	size_t i = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		unsigned long move = move_potential_lut[i];

	/*	printf("%d: ", i);
		printf("%lu\n", move); */

		if ((!IsFirstOrSecondRow(i)) && (!IsFirstColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i - 17);
		}

		if ((!IsFirstOrSecondRow(i)) && (!IsEighthColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i - 15);
		}

		if ((!IsFirstRow(i)) && (!IsSeventhOrEighthColumn(i))) /*maybe use IsFirstRow for 1st condition */
		{
			move = move | BitsArrSetBitOn(move, i - 6);
		}

		if ((!IsEighthRow(i)) && (!IsSeventhOrEighthColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i + 10);
		}

		if ((!IsSeventhOrEighthRow(i)) && (!IsEighthColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i + 17);
		}

		if ((!IsSeventhOrEighthRow(i)) && (!IsFirstColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i + 15);
		}

		if ((!IsEighthRow(i)) && (!IsFirstOrSecondColumn(i))) /*maybe use IsFirstRow for 1st condition */
		{
			move = move | BitsArrSetBitOn(move, i + 6);
		}

		if ((!IsFirstRow(i)) && (!IsFirstOrSecondColumn(i)))
		{
			move = move | BitsArrSetBitOn(move, i - 10);
		}

		move_potential_lut[i] = move;
	}
}

int RecursiveCalcRoute(unsigned long cur_place, unsigned long visited_places, int *path, int *index, clock_t beginning)
{
	unsigned long new_moves = 0;
	unsigned long return_val = 0;
	long next_moves = 0;
	int how_many_moves = 0;
	int next_move = 0;

	if (((clock() - beginning)/CLOCKS_PER_SEC) > SECONDS)
	{
		return (0);
	}

	new_moves = FindNewMoves(move_potential_lut[cur_place], visited_places);
	next_moves = FindMin(new_moves, visited_places);
	how_many_moves = BitsArrCountOn(next_moves);
	visited_places = BitsArrSetBitOn(visited_places, cur_place);

	while (how_many_moves > 0)
	{
		next_move = IndexOfFirstBitOn(next_moves);
		next_moves = BitsArrSetBitOff(next_moves, next_move);
		--how_many_moves;
		return_val = RecursiveCalcRoute(next_move, visited_places, path, index, beginning);
	}


	if (BitsArrCountOn(visited_places) == BOARD_SIZE)
	{
		return (1);
	}

	/*
	if (next_move < 0)
	{
		return (0);
	}
*/

	if (return_val == 1)
	{
		*(path + cur_place) = BOARD_SIZE - *(index);
		++(*(index));
	}

	return(return_val);
}

static int IndexOfFirstBitOn(unsigned long location)
{
	unsigned long i = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		if (BitsArrIsBitOn(location, i))
		{
			break;
		}
	}

	return (i);
}

static unsigned long FindNewMoves(unsigned long potential_moves, unsigned long visited)
{
	unsigned long i = 0;
	unsigned long mask = 0x01;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		if (((mask << i) & potential_moves) == (mask << i))
		{
			if (((mask << i) & visited) == (mask << i))
			{
				potential_moves = BitsArrSetBitOff(potential_moves, i);
			}
		}
	}

	return (potential_moves);
}

static unsigned long FindMin(unsigned long new_moves, unsigned long visited)
{
	int num_of_moves = BitsArrCountOn(new_moves);
	int i = 0;
	int num_of_moves_next_turn = 0;
	int min = 9;
	int min_index = -1;
	unsigned long next_new_moves = new_moves;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		if (BitsArrIsBitOn(new_moves, i))
		{
			num_of_moves_next_turn = BitsArrCountOn(FindNewMoves(move_potential_lut[i], visited));
			if (num_of_moves_next_turn < min)
			{
				min = num_of_moves_next_turn;
			}
		}
	}

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		if (BitsArrIsBitOn(new_moves, i))
		{
			num_of_moves_next_turn = BitsArrCountOn(FindNewMoves(move_potential_lut[i], visited));
			if (num_of_moves_next_turn > min)
			{
				/*new_moves = new_moves & (~((unsigned long)(0x01) << i));*/
				new_moves = BitsArrSetBitOff(new_moves, i);
			}
		}
	}

	/*
	for (i = 0; i < num_of_moves; ++i)
	{
		int index = IndexOfFirstBitOn(new_moves);
		num_of_moves_next_turn = BitsArrCountOn(FindNewMoves(move_potential_lut[index], visited));

		if (num_of_moves_next_turn < min)
		{
			min = num_of_moves_next_turn;
			min_index = index;
			new_moves = new_moves & (~((unsigned long)(0x01) << index));
		}
	}

	new_moves = next_new_moves;

	for (i = 0; i < num_of_moves; ++i)
	{
		int index = IndexOfFirstBitOn(new_moves);
		num_of_moves_next_turn = BitsArrCountOn(FindNewMoves(move_potential_lut[index], visited));
		new_moves = new_moves & (~((unsigned long)(0x01) << index));

		if (num_of_moves_next_turn > min)
		{
			new_moves = new_moves & (~((unsigned long)(0x01) << index));
		}
	}*/

	return (new_moves);
}
