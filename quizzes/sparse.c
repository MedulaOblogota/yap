#include <stdio.h>

int IsSparse(int num)
{
	int counter = 0;
	int mask = 0x01;
	int sparse = 0;

	while (num != 0)
	{
		if ((num & mask) == mask)
		{
			++counter;
		}
		else if (counter > 0)
		{
			--counter;
		}

		if (counter == 2)
		{
			sparse = 1;
			break;
		}

		num = num >> 1;
	}

	return (sparse);
}


int AddToNextSparse(int num)
{
	int sparse = 0;

	while (IsSparse(num))
	{
		++num;
		sparse = 1;
	}

	if (sparse)
	{
		printf("sparse!\n");
	}

	return (num);
}

int ChangeToNextSparse(int num)
{
	int counter = 0;
	int mask = 0x01;

	while (num >= mask)
	{
		if ((num & mask) == mask)
		{
			++counter;
		}
		else if (counter > 0)
		{
			-- counter;
		}

		if ((counter >=2) && ((num & (mask << 1)) != (mask  << 1)))
		{
			int i = 0;
			num = num | (mask << 1);

			for (i = 0; i < counter; ++i)
			{
				num = num & mask;
			}
		}

		mask = mask << 1;
	}

	return (num);
}

int main()
{
	int num = 221;
	printf("%d\n", AddToNextSparse(num));

	printf("%d\n", ChangeToNextSparse(num));

	return 0;
}
