/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	Sent
Title:		WS2_STRING Functions File
*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>	/* size_t */
#include <ctype.h>	/* tolow */
#include <assert.h>
#include "ws2_string.h"

/**************************************************************************/

/* returns size of String */
size_t StrLen(const char *str) 
{
	size_t size = 0;
	
	assert(NULL != str);
	
	while ('\0' != *(str))
	{
		++size;
		++str;
	}
	return(size);
}

/**************************************************************************/

/* copies n chars from src to dest string */
char *StrNCpy(char *dest, const char *src, size_t n) 
{
	char *base = dest;
	size_t i = 0;
	
	assert(NULL != src);
	assert (NULL != dest);
	
	for (i = 0; (i < n) && ('\0' != *src); i++)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	for ( ; i < n; i++) 
	{
		*dest = '\0';
		++dest;
	}
	
	if (i == 0) 
	{
		*(base) = '\0';
	}
		
	return base;
}

/**************************************************************************/

/* copies source string to dest */
char *StrCpy(char *dest, const char *source)
{	
	char *base = dest;
	
	assert(NULL != dest);
	assert(NULL != source);
	
	while (*source)
	{
		*(dest) = *(source);
		++dest;
		++source;
	}
	
	*(dest + 1) = '\0';
	
	return base;
}

/**************************************************************************/


