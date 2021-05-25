
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>	/* size_t */
#include <ctype.h>	/* tolow */
#include <assert.h>
#include "ws2_string.h"

/* compares first string to second and returnsthe ASCII difference of first char-difference if exists as int */
int StrCmp(const char *first, const char *second) 
{
	int sum = 0;
	
	/*assert(NULL != first);
	assert(NULL != second);*/
	
	while ((*first) && (*second)) 
	{
	if (*first != *second)			
		{
			break;
		}
		++first;
		++second;
	}
	
	/*ELiav: Same sum as above. why? It will work also without this row.*/
	sum = *first - *second;
	
	return (sum);
}

/**************************************************************************/

/* compares s1 string to s2 (case insensitive) and returns the ASCII difference of first char-difference if exists as int */
int StrCaseCmp(const char *s1, const char *s2) 
{
	int sum = 0;
										/*Eliav: You should activate the assrt.*/
	/*assert(NULL != s1);
	assert(NULL != s2);*/
	
	while (*s1 && *s2) 
	{
		if (tolower(*s1) != tolower(*s2))
		{
			break;
		}
		++s1;
		++s2;
	}
	/*ELiav: Same sum as above. why? It will work also without this row.*/
	sum = tolower(*s1) - tolower(*s2);
	
	return (sum);
}

/**************************************************************************/

/* returns pointer to first occurance of char c in String str */
char *StrChr(const char *str, int c) 
{	

	assert(NULL != str); 
	
	if ('\0' == c) 
	{
		return NULL;	
	}
		
	while ('\0' != *(str)) 
	{
		if (*(str) == c) 
		{
			return ((char *)(str));
		}
		++str;
	}
	
	return NULL;
}

/**************************************************************************/


