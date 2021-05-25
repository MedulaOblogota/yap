/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	
Title:		WS3_ARR Functions File
*******************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <string.h>	/* strlen */
#include <ctype.h> 	/* to_lower */
#include "ws3_arr.h"

/**************************************************************************/

/*	receives array of soldiers who stab the  adjacent soldier. Will returns 
	index of last soldier who survives. */  
size_t Soldiers(size_t length)
{
	size_t knife = 0;
	int index = 0;
	int counter = length;
	size_t i = 0;
	int *soldiers = malloc(sizeof(int) * length);
	if (NULL == soldiers)
	{
		
		return '\0';
		
	}
		
	for (i = 0; i < length; ++i)
	{
		soldiers[i] = 1;	
	}
	
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
	free (soldiers);
	soldiers = NULL;
	return (knife);
}

/**************************************************************************/

/*	returns size of envp variable */  
size_t SizeOfEnvp(char **envp)
{
	size_t size = 0;
	while ((*envp) != NULL)
	{
			++size;
			++(envp);
	}
	/*printf("size of envp = %d\n", size);*/
	return (size);
}

/**************************************************************************/

/* PRIVATE FUNCTION FOR USE OF BUILDSTRUCTURE FUNCTION */
/*	frees dynamic memory of envp variable in case a string malloc did not 
	succeed */  
void FreeEnvp(char **envp, size_t index)
{
	int i = index;
	for (i = index; i >= 0; --i)
	{
		free(*(envp + i));
		*(envp + i ) = NULL;
	}
	free(&(*envp));
	envp = NULL;
}

/*	receives Linux enviromental parameters and returns their duplicate */
char **CreateEnvStruct(char **envp)
{
	char **structure = NULL; 
	char *new_str= "";
	int str_len = 0;
	size_t i = 0; 
	int j = 0;
	size_t size = SizeOfEnvp(envp);
	structure = malloc(size * sizeof(char *) + 1);
	if (NULL == structure)
	{
		return NULL;
	}
	/*printf("entered BuildStrucutre Function\n");*/
	for (i = 0; i < size; i++)
	{
		str_len = strlen(*(envp+i));
		new_str = (char *)malloc(str_len + 1);
		if (NULL == new_str)
			FreeEnvp(envp, i-1);
		/*str_len = strlen(*(envp+i));*/
		for (j = 0; j < str_len; j++)
		{
		/*	printf("entered inner loop\n"); */
			*(new_str + j) = tolower(*(*(envp + i) + j));
		}
		*(new_str + j) = '\0';
		/*printf("new_str=%s\n", new_str);*/
		*(structure + i) = new_str;
	}
	*(structure + i) = NULL;
	return (structure);
} 

/**************************************************************************/

/* prints all datatypes in C and their size */
void PrintDataTypes()
{
	printf("name: SHORT INT. size: %lu.\n", sizeof(short int));
	printf("name: UNSIGNED SHORT INT. size: %lu.\n", sizeof(unsigned short int));
	printf("name: UNSIGNED INT. size: %lu.\n", sizeof(unsigned int));
	printf("name: INT. size: %lu.\n", sizeof(int));
	printf("name: LONG INT. size: %lu.\n", sizeof(long int));
	printf("name: UNSIGNED LONG INT. size: %lu.\n", sizeof(unsigned long int));
	printf("name: SIGNED CHAR. size: %lu.\n", sizeof(signed char));
	printf("name: UNSIGNED CHAR. size: %lu.\n", sizeof(unsigned char));
	printf("name: FLOAT. size: %lu.\n", sizeof(float));
	printf("name: DOUBLE. size: %lu.\n", sizeof(double));
	printf("name: LONG DOUBLE. size: %lu.\n", sizeof(long double));
}

