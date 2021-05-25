/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Or Ben-Lulu
Title:		WS5_LIB Main File
*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws5_lib.h"

struct element
{
	const char *string;
	int (*check)(const char *, const char *);
	working (*implement_func)(const char *, const char *);
};

static const struct element log_array[] = {
							{"-remove", Check, RemoveImplement },
							{"-count", Check, CountImplement},
							{"-exit", Check, ExitImplement},
							{"<", PrependCheck, PrependImplement},
							{"MUST BE LAST", AlwaysTrueCheck, AlwaysTrueImplement}
							}; 
												
int main(int argc, char *argv[]) 
{
	char str[101];
	int stay = 1;
	int i = 0;
	char *filename = argv[1];
	working result;

	if (argc < 2)
	{
		printf("You did not input a file name!\n");
		stay = 0;
	}
	
	while (stay == 1)
	{
		printf("Enter String [up to 100 chars]: \n");
		scanf(" %[^\n]s", str);

		for (i = 0; i < 5; ++i)
		{
			if (log_array[i].check(str, log_array[i].string))
			{
		  		result = log_array[i].implement_func(filename, str);
		  		
		  		if (i == 0)
		  		{	
		  			if (result == yes)
		  				printf("%s removed succesfully\n", filename);
		  			else
		  				printf("%s was not removed succesfully. It may not exist!\n", filename);
		  		} 
		  		else if (i == 1)
		  		{		  			
		  			if (result == yes)
		  				printf("counting-line added succesfully to %s \n", 	filename);
		  			else
		  				printf("%s doesnt exist!\n", filename);
		  		} 
		  		else if (i == 2)
		  		{		
		  			stay = 0;
		  		}	
		  		else if ((i == 3) || (i == 4))
		  		{
		  			if (result == no)
		  				printf("Error, %s may not exist!\n", filename);
		  		}	
		  		break;
		  	}
		}
	}
	return (0);
}
