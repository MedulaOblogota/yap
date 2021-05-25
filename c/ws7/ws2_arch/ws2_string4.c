
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>	/* size_t */
#include <ctype.h>	/* tolow */
#include <assert.h>
#include "ws2_string.h"

/* locates substring needle in haystack String */
/*TRY 2
*/
char *StrStr(const char *haystack, const char *needle)
{	
	char *haystack_runner = NULL;
	char *needle_runner = NULL;
	char *needle_location_in_haystack = NULL;
	int needle_length = 0;
	int stay = 1;
	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	haystack_runner = (char *)haystack;
	needle_runner = (char *)needle;
	needle_length = StrLen(needle);
	
	if (*needle == '\0')
		return (haystack_runner);
		
	while (stay && ('\0' != *haystack_runner))
	{
		needle_location_in_haystack = StrChr(haystack_runner, *needle);
		if (NULL != needle_location_in_haystack)
		{
			haystack_runner = needle_location_in_haystack;
			needle_runner = (char *)needle;
			
			while (('\0' != haystack_runner) && ('\0' != needle_runner))
			{
				if (*haystack_runner != *needle_runner)
				{
					break;
				}
				++haystack_runner;
				++needle_runner;
			}
			
			if ((haystack_runner - needle_location_in_haystack) == needle_length)
			{
				return (needle_location_in_haystack);
			} 
		}
		else
		{
			stay = 0;
		}
	}
	return NULL;	
}

/**************************************************************************/

/* returns length of substring in str1 built out of chars in String str2 */
size_t StrSpn( const char *str1, const char *str2 )
{
	size_t size = 0;
	char c1 = 'a'; 
	char c2 = 'a';
	char *base = (char *)str2;
	int exists = 0;
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	while (*str1) 
	{
		c1 = *str1;
		str2 = base;
		exists = 0;
		while (*str2)
		{
			c2 = *str2;
			if (c1 == c2)
			{
				++size;
				exists = 1;
				break;
			}
			++str2;
		}
		if (exists == 1)
			++str1;
		else
			break;
	}
	return (size);
}

/**************************************************************************/
/*Eliav: 
- Never-ending loop. check it out. I tried "one-two-three" as str and "-" as delim.
*/
char *StrTok(char *str, const char *delim)
{
	static char *ptr = NULL;
	char *check_delim = (char *)delim;
	char *token = str;
	if (str == NULL)
	{
		if (ptr != NULL) 
		{
			str = ptr;
			token = str;
		} 
		else 
			return (NULL);
	}
	
	while (*str)
	{
		check_delim = (char *)delim;
		while (*check_delim)
		{
			if (*check_delim == *str)
			{
				ptr = str + 1;
				++str;
				*(str - 1) = '\0';
				if (0 == StrCmp(token, ""))
					return NULL;
				else
					return (token);
			}
			++check_delim;
		}
		++str;
	}
	if (ptr == token)
		ptr = token + StrLen(token);
	if (str != token)
		return (token);
	return NULL;
} 

