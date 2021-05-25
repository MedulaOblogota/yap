#include <stdio.h>

#define ROWS (5)
#define BITS_IN_BYTE (8)

int IsValidMove(char *accessed, int c, int r)
{
    int first_condition = ((c < (sizeof(char) * BITS_IN_BYTE)) && (c >= 0) && (r < ROWS) && (r >= 0));
    int second_condition = ((accessed[r] & (0x01 << c)) != (0x01 << c));

    return (first_condition && second_condition);
}

int CheckIsland(char *islands, char *accessed, int row_ind, int col_ind)
{
    int row[] = 		{0, 0, 	1, -1, 1, -1, 	-1, 1};
    int column[] = 	{1, -1, 0, 	0, 1, -1, 	1, -1};
		size_t k = 0;
		int ret = 0;
    /* 	char accessed[ROWS] = {0};*/
		int is_one = ((islands[row_ind] & (0x01 << col_ind)) == (0x01 << col_ind));
		int is_accessed = accessed[row_ind] & (0x01 << col_ind);
		queue_t *queue = QueueCreate();
    /*size_t i = 0;
    size_t j = 0;
*/
		if ((is_accessed) || !(is_one))
		{
			return 0;
		}

		QueueEnqueue(queue, &row_ind);
		QueueEnqueue(queue, &col_ind);
		accessed[row_ind] = (accessed[row_ind] | (0x01 << col_ind));

		printf("%d\n", accessed[row_ind]);

		while (!QueueIsEmpty(queue))
		{
			int curr_row = *(int *)QueuePeek(queue);
			QueueDequeue(queue);

			int curr_col = *(int *)QueuePeek(queue);
			QueueDequeue(queue);

			int next_row;
			int next_column;

	    for (k = 0; k < 8; ++k)
	    {
	        if (IsValidMove(accessed, curr_col + column[k], curr_row + row[k]))
	        {
							char row_val = islands[curr_row + row[k]];
							char col_val = curr_col + column[k];

							next_row = curr_row + row[k];
							next_column = curr_col + column[k];

							if (col_val < 0) printf("SHIT!\n");

							accessed[next_row] = accessed[next_column] | (0x01 << (next_column));

	            if ((row_val  & (0x01 << col_val)) == (0x01 << col_val))
	            {
									QueueEnqueue(queue, &next_row);
									QueueEnqueue(queue, &next_column);
									ret = 1;
	            }
	        }
					/*
					else
					{
						printf("invalid\n" );
					}*/
	    }
		}
		return ret;
/*
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < (sizeof(char) * BITS_IN_BYTE); ++j)
        {
            accessed[i] = (accessed[i] | (0x01 << j));

            for (k = 0; k < 8; ++k)
            {
                if IsValidMove(islands, accessed, j + row[k], i + column[k])
                {
                    if ((islands[i + column[k]] )<< (j + row[k]))
                    {
                        accessed[i + column[k]] ) =<< (0x01 + row[k]);
                    }
                }
            }
        }
    }*/


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
