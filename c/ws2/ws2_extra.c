/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	Sent
Title:		WS2_EXTRA Functions File
*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ws2_extra.h"


/**************************************************************************/

/* checks if String str is palindrome */
int IsPalindrome(const char *str)
{
	int length = strlen(str);
	char c1, c2;
	char *beg = (char *)str;
	char *end = beg + length - 1;
	int palindrome = 1;
	int size = 0;
	
	assert(NULL != str);
	
	while (size < length)
	{
		c1 = *beg;
		c2 = *end;
		++beg;
		--end;
		++size;
		if ((c1 != c2) && (size < length))
		{
			palindrome = 0;
		}
	}
	return palindrome;
}

/* Function that assists SevenBoom function */
/* swaps between 2 ints by referance */
void swap(int *x, int *y)
{
	int temp = *x;
		*x = *y;
		*y = temp;
}

/* Function that assists SevenBoom function */
/*checks if int num has 7 in one of it's digits */
int HasSevenAsDigit(int num) 
{
	while (num != 0)
	{
		if (((num % 10) == 7) || ((num % 10) == -7))
		{
			return(1);
		}
		num = num / 10;
	}
	return (0);
}

/* receives two ints first & seconds and prints all numbers in between */
/* with the rule of printing BOOM instead of numbers that divide by 7  */
/* or have 7 in one of their digits */
void SevenBoom(int first, int second) 
{
	int i=first;
	if (first > second) 
	{
		swap(&first, &second);
	}
	printf("SEVEN BOOM FOR %d to %d:\n\n", first, second);
	for (i = first; i <= second; i++)
	{
		if (i % 7 == 0) 
		{
			printf("BOOM\n");
		} 
		else if (HasSevenAsDigit(i)) 
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n", i);
		}
	}
}

/* swaps between two pointers to int */
void SwapPointer(int **first, int **second)
{
	int *temp = *first;
	*first = *second;
	*second = temp;
}

/* adds two large numbers represented as Strings and returns the result as String */
char *Addition(char *num1, char* num2)
{
	int length1 = strlen(num1);
	int length2 = strlen(num2);
	char *num1_index = num1 + length1 - 1;
	char *num2_index = num2 + length2 - 1;
	char *result;
	int dig1 = 0;
	int dig2 = 0;
	int res = 0;
	int rem = 0;
	char char_res;
	
	assert( NULL != num1);
	assert( NULL != num2);
	
	if (length1 > length2)
	{
		result = malloc(strlen(num1) + 2);
		result += length1;	
		*(result + 1) = '\0';
	}
	else
	{
		result = malloc(strlen(num2) + 2);
		result += length2;
		*(result + 1) = '\0';
	}
	
	while (*num1_index || *num2_index)
	{
		if (*num1_index)
		{
			if (isdigit(*num1_index))
				dig1 = *num1_index - '0';
			else dig1 = 0;
		}
		else
		{
			dig1 = 0;
		}
		
		if (*num2_index)
		{
			if (isdigit(*num2_index))
				dig2 = *num2_index - '0';
			else
				dig2 = 0;
		}
		else
		{
			dig2 = 0;
		}
		
		if (rem == 0)
			res = dig1 + dig2;
		else 
			res = dig1 + dig2 + 1;
			
		if (res > 9)
		{
			res = res - 10;
			rem = 1;
		} 
		else
		{
			rem = 0;
		}
		
		char_res = res + '0';
		*result = char_res;
		if (num1_index >= num1)
			--num1_index;
		if (num2_index >= num2)
			--num2_index;
		/*if (num1_index >=num1 || num2_index >= num2)*/
			--result;
	}
	if (rem == 1)
	{
		*(result) = '1';
	} 
	else 
	{
		++result;
	}
	return result;
	
}

char *MoveLeft(char *str, int size)	/*should return first char after space */
{
	char *temp = str + size;
	char *base = str;
	while (*temp)
	{
	/*	if (*temp = '\t')
			*temp = ' ';*/
		*str = *temp;
		++str;
		++temp;
	}
	*str = '\0';
	return (base);
}

/* removes spaces and tabs from beginning of String as well as changes to single space between words in String */
void RmSpaces(char *str)
{
	char *span = " \t";
	int size = strspn(str, span);
	if (size > 0)
	{
		str = MoveLeft(str, size);
	}
	
	while (*str)
	{
		size = strspn(str, span);
		if (size > 0)
		{
			if (*str == '\t')
				*str = ' ';
			MoveLeft(str, size - 1);
			if (*(str) == '\t')
				*(str) = ' ';
		}
		++str;
	}
	
	--str;
	
	if (strspn(str, span) > 0)
		*str = '\0';
}


