#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitarray.h"

#define BOARD_SIZE (64)
#define SECONDS (20)

/*static unsigned long CheckIfValidMove(unsigned long moves, int location, int spot);*/
static void InitMovePotentialLut(unsigned long *move_potential_lut);
static int IsFirstRow(int n);
static int IsFirstOrSecondRow(int n);
static int IsFirstColumn(int n);
static int IsFirstOrSecondColumn(int n);
static int IsEighthRow(int n);
static int IsSeventhOrEighthRow(int n);
static int IsEighthColumn(int n);

static int IsSeventhOrEighthColumn(int n);

static int IndexOfFirstBitOn(unsigned long location);
int RecursiveCalcRoute(unsigned long cur_place, unsigned long visited_places, unsigned long *move_potential_lut, int *path, int *index, clock_t clock);
static unsigned long FindNewMoves(unsigned long potential_moves, unsigned long visited);
static int FindMin(unsigned long new_moves, unsigned long visited, unsigned long *move_potential_lut);

int KnightsTour(unsigned long cur_place, int *path)
{
	static unsigned long move_potential_lut[BOARD_SIZE] = {0};
	unsigned long initial_row = 0;
	unsigned long initial_column = 0;
	unsigned long visited_places = cur_place;
	int index = 1;
	int return_val = 0;
	clock_t beginning;

	srand(time(NULL));

	initial_row = rand() % 8;
	initial_column = rand() % 8;

	InitMovePotentialLut(move_potential_lut);
	beginning = clock();

	return_val = RecursiveCalcRoute(cur_place, 0, move_potential_lut, path, &index, beginning);

	printf("\ntime: %f seconds.\n", cur_place,  (double)(clock() - beginning)/CLOCKS_PER_SEC);
	/*if (return_val == 2)
	{
		return_val = 0;
	}*/



	return(return_val);
}

static int IsFirstRow(int n)
{
	return (n / 8 == 0);
}

static int IsFirstOrSecondRow(int n)
{
	return ((n / 8 == 0) || (n / 8 == 1));
}

static int IsFirstColumn(int n)
{
	return (n % 8 == 0);
}

static int IsFirstOrSecondColumn(int n)
{
	return ((n % 8 == 0) || (n % 8 == 1));
}

static int IsEighthRow(int n)
{
	return (n / 8 == 7);
}

static int IsSeventhOrEighthRow(int n)
{
	return ((n / 8 == 6) || (n / 8 == 7));
}

static int IsEighthColumn(int n)
{
	return (n % 8 == 7);
}

static int IsSeventhOrEighthColumn(int n)
{
	return ((n % 8 == 6) || (n % 8 == 7));
}

static void InitMovePotentialLut(unsigned long *move_potential_lut)
{
	size_t i = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		unsigned long move = *(move_potential_lut + i);

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

		*(move_potential_lut + i) = move;
	}
}

int RecursiveCalcRoute(unsigned long cur_place, unsigned long visited_places, unsigned long *move_potential_lut, int *path, int *index, clock_t beginning)
{
	/*unsigned long new_moves = *(move_potential_lut + cur_place) ^ visited_places;*/
	unsigned long new_moves = 0;
	unsigned long how_many_moves = 0;
	unsigned long i = 0;
	static unsigned long k = 1;
	unsigned long mask = 0x01;
	unsigned long return_val = 0;

	/*printf("cur_place=%lu\n", cur_place);*/
	if (((clock() - beginning)/CLOCKS_PER_SEC) > SECONDS)
	{
	/*	printf("failed! reached %f seconds\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);*/
		return (0);
	}

	new_moves = FindNewMoves(*(move_potential_lut + cur_place), visited_places);
	how_many_moves = BitsArrCountOn(new_moves);
	i = 0;
	mask = 0x01;
	/*printf("how_many_moves = %d\n", how_many_moves);*/
	visited_places = BitsArrSetBitOn(visited_places, cur_place);

	/*printf("cur_place=%lu\n", cur_place);*/


	if (BitsArrCountOn(visited_places) == BOARD_SIZE)
	{
		return (1);
	}

	if (how_many_moves == 0)
	{
		return (0);
	}

/*	new_moves = FindMin(new_moves, visited_places, move_potential_lut);
	return_val = RecursiveCalcRoute(i, visited_places, move_potential_lut, path, index);

	if (return_val == 1)
	{
		*(path + cur_place) = BOARD_SIZE - *(index);
		++(*(index));
	}

	return(return_val);*/

	while ((how_many_moves > 0) && (return_val != 1))
	{
		if ((new_moves & mask) == mask)
		{



			return_val = RecursiveCalcRoute(i, visited_places, move_potential_lut, path, index, beginning);
			if (return_val == 1)
			{
				*(path + cur_place) = BOARD_SIZE - *(index);
				++(*(index));
			}
			--how_many_moves;
		}

		mask = mask << 1;
		++i;
	}

	return (return_val);
}

static int IndexOfFirstBitOn(unsigned long location)
{
	unsigned long mask = 0x01;
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

	return potential_moves;
}

static int FindMin(unsigned long new_moves, unsigned long visited, unsigned long *move_potential_lut)
{
	int num_of_moves = BitsArrCountOn(new_moves);
	int i = 0;
	int num_of_moves_next_turn = 0;
	unsigned long min = 9;
	int min_index = 0;

	for (i = 0; i < num_of_moves; ++i)
	{
		int index = IndexOfFirstBitOn(new_moves);
		num_of_moves_next_turn = BitsArrCountOn(FindNewMoves(*(move_potential_lut + index), visited));

		if (num_of_moves_next_turn < min)
		{
			min = num_of_moves_next_turn;
			min_index = index;
		}

		new_moves = new_moves & (~((unsigned long)(0x01) << index));
	}

	return min_index;
}
