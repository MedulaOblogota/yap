#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LETTERS (26)

char IsLetter(char c)
{
		return (((c >= 'a') && (c <= 'z'))*'a' + ((c >= 'A') && (c <= 'Z'))*('A' - 9)) ;
}

int HasDupChar(char *first, char *sec)
{
		int *character_lut = calloc(LETTERS * 2, sizeof(int));
		char *runner = first;
		size_t i = 0;

		while (*runner)
		{
			char lessen_from = IsLetter(*runner);
			if (lessen_from)
			{
				++character_lut[tolower(*runner) - lessen_from];
			}
			++runner;
		}

		runner = sec;

		while (*runner)
		{
			char lessen_from = IsLetter(*runner);
			if (lessen_from)
			{
				if (character_lut[tolower(*runner) - lessen_from] == 0)
				{
					return 0;
				}

				--character_lut[tolower(*runner) - lessen_from];
			}
			++runner;
		}

		for (i = 0; i < LETTERS; ++i)
		{
			if (character_lut[i] != 0)
			{
				return 0;
			}
		}

		return 1;
}

// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int l, int r)
{
   int i;
   if (l == r)
     printf("%s\n", a);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); //backtrack
       }
   }
}

/* Driver program to test above functions */


int main()
{
		char name[] = "hello My Man";
		char other[] = "naMMy olleh";
		char per[] = "abc";

		printf("should be 1 -> %d\n", HasDupChar(name, other));

		permute(per, 0, 2);

		return 0;
}
