#include <stdio.h>


#define ROWS (5)
#define BITS_IN_BYTE (8)

int IsValidMove(char *accessed, int c, int r)
{
    int first_condition = ((c < (sizeof(char) * BITS_IN_BYTE)) && (c >= 0) && (r < ROWS) && (r >= 0));
    int second_condition = ((accessed[r] & (0x01 << c)) != (0x01 << c));

    return (first_condition && second_condition);
}

int IsOne (char num, int index)
{
	if (num & (0x01 << index)) printf("%d and %d is one\n", num, index);
	return (num & (0x01 << index));
}
int CheckIsland(char *islands, char *accessed, int row_ind, int col_ind)
{
    int row[] = 		{0, 0, 	1, -1, 1, -1, 	-1, 1};
    int column[] = 	{1, -1, 0, 	0, 1, -1, 	1, -1};
		size_t k = 0;
		int ret = 0;

		int is_one = ((islands[row_ind] & (0x01 << col_ind)) == (0x01 << col_ind));
		int is_accessed = accessed[row_ind] & (0x01 << col_ind);
		int sum = 0;

		if ((is_accessed) || !(is_one))
		{
			return 0;
		}

		accessed[row_ind] = (accessed[row_ind] | (0x01 << col_ind));
		for (k = 0; k < 8; ++k)
		{
			if ((IsValidMove(accessed, col_ind + column[k], row_ind + row[k])) && (IsOne(islands[row_ind + row[k]], col_ind + column[k])))
			{
				sum += (1 + CheckIsland(islands, accessed, row_ind + row[k], col_ind + column[k]));
			}
		}

		return sum;

}

size_t CountIslands(char *islands)
{
    char accessed[ROWS] = {0};
    size_t r = 0;
    size_t c = 0;
    size_t counter = 0;

    for (r = 0; r < ROWS; ++r)
    {
        for (c = 0; c < (sizeof(char) * BITS_IN_BYTE); ++c)
        {
            if (CheckIsland(islands, accessed, r, c))
						{
            	++counter;
						}
        }
    }

    return counter;
}

int main()
{
    char islands[ROWS] = {
        75, 54, 145, 70, 50
     };
     /*
    {   0, 1, 0, 0, 1, 0, 1, 1
        0, 0, 1, 1, 0, 1, 1, 0
        1, 0, 0, 1, 0, 0, 0, 1
        0, 1, 0, 0, 0, 1, 1, 0
        0, 0, 1, 1, 0, 0, 1, 0
    }
     */

    printf("amount of islands -> %lu\n", CountIslands(islands));

		return 0;
}
