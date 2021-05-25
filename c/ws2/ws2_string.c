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

/* returns a duplication of src Sring */ 
char *StrDup(const char *src)
{
	/*Should be StrLen(src) + 1 in malloc. For the '\0' in the end of the string.*/
	char *dest = (char *)malloc(StrLen(src) + 1);	

	if (NULL != dest)
		dest = StrCpy(dest, src);
	
	*(dest + StrLen(src)) = '\0';
	
	return (dest);
}

/**************************************************************************/

/* concatonates src String to end of dest String 
returns pointer to new dest String */
char *StrCat(char *dest, const char *src)
{
	char *base = dest;
	int length = StrLen(dest);

	assert(NULL != dest);
	assert(NULL != src);

	while ('\0' != *(src))
	{

		*(dest + length) = *(src);
		++dest;
		++src;
		/* printf("dest is now %s\n", dest); */
	} 
	
	*(dest + length) = '\0';

	/*printf("final - dest is now %s\n", base);
	if (*(dest) != '\0')
		printf("not null\n");
	else
		printf("null\n"); */
	return (base);
}

/**************************************************************************/

/* concatonates first N chars of src String to dest String */
char *StrNCat(char *dest, const char *src, size_t n) 
{
	char *base = dest;
	int length = StrLen(dest);
	size_t size = 0;

	assert(NULL != dest);
	assert(NULL != src);
	
	/*Eliav: You should forward "size" and not "n".*/
	while (('\0' != *(src)) && (size < n))
	{

		*(dest + length) = *(src);
		++dest;
		++src;
		++size;
		/* printf("dest is now %s\n", dest); */
	} 
	
	*(base + length + size) = '\0';

	/*printf("final - dest is now %s\n", base);
	if (*(dest) != '\0')
		printf("not null\n");
	else
		printf("null\n"); */
	return (base);
}

/**************************************************************************/

/* locates substring needle in haystack String */
/*char *StrStr(const char *haystack, const char *needle)
{
	int i = 0;
	int j = 0;
	int index = 0;
	int needle_length = StrLen(needle);*/
	
	/*printf("needle length is %d", needle_length);*/
	
	/*
	int exists = 0;
	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	while ('\0' != *(haystack + i))
	{
		if (*(haystack + i) == *(needle))
		{
			exists = 1;
			index = i;
			j=0;
			for (j=0; j < (needle_length); j++ )
			{
				if (*(haystack + i) != *(needle + j)) 
				{
					exists = 0;
					break;
				}
				else
					i++;
			}
			if (exists == 1) 
			{ 
				return ((char *)(haystack + index));
			}
		} else
			i++;
	}
	return NULL;
} */

/**************************************************************************/

/* locates substring needle in haystack String */
/*Eliav:
- Does not pass this test: first = "Something"; second = "". Should return "Something". Returning "null".
*/
/*char *StrStr(const char *haystack, const char *needle)
{	
	char *first_haystack = (char *)haystack;
	char *first_needle = (char *)needle;
	int index = 0;
	int needle_length = StrLen(needle);

	int exists = 0;
	

	
	while ('\0' != *(haystack))
	{
		if (*(haystack) == *(needle))
		{
			exists = 1;
			index = haystack - first_haystack;
			while (*needle)
			{
				if (*(haystack) != *(needle)) 
				{
					if  ((needle - first_needle) == needle_length) 
					{
						break;
					}
					else
					{
						exists = 0;
						needle = first_needle;
						break;
					}
				}
				else
				{
					++haystack;
					++needle;
				}
			}
			if (exists == 1) 
			{ 
				return ((char *)(first_haystack + index));
			}
		} else
			++haystack;
	}
	if (*needle == '\0')
		return (first_haystack);
	else
		return (NULL);
} */

/**************************************************************************/

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

