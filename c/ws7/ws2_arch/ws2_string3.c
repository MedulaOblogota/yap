
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>	/* size_t */
#include <ctype.h>	/* tolow */
#include <assert.h>
#include "ws2_string.h"

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
	
	*(base + length + n) = '\0';

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


