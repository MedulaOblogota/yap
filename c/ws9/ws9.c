/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shahar Saar
Version:	Sent
Title:		WS9 Functions File
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "ws9.h"

#define WORD_SIZE (8)
#define DECIMAL_BASE (10)
#define SUM_OF_LETTERS (26)

/* receives String with it's base and returns a decimal int */
int Atoi(char *str, int base)
{
	int num = 0;
	size_t i = 0;
	int dig = 0;
	char c = 0;
	size_t length = strlen(str);
	int negative = 0;
	
	assert(NULL != str);
	
	
	if ((base == 10) && (str[0] == '-'))
	{
		negative = 1;
	}
	
	for (i = 0; i < length; ++i)
	{
		c = *(str + i);
		if (c != '-')
		{
			if (!isalpha(c))
			{
				dig = *(str + i) - '0';
			}
			else
			{
				if ((c <= 'Z') && (c >= 'A'))
				{
					dig = c - 'A' + DECIMAL_BASE;
				}
				else if ((c <= 'z') && (c >= 'a'))
				{
					dig = c - 'a' + DECIMAL_BASE;
				}
			}
		
			num = num * base + dig;
		}
	}
	if (negative)
	{
		num = -num;
	}
	return (num);
}

/* receives an int in value and returns it's string version according to a 
	specific base. Will treat negative only in case int is decimal */
char *Itoa( int value, char *str, int base )
{
	static char num_to_value_lut[] = 
	{	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
		'U', 'V', 'W', 'X', 'Y', 'Z'};
	
	int modulus = 0;
	char *ptr = NULL;
	int negative = 0;
	
	assert(NULL != str);
	
	ptr = str + sizeof(str) - 1;
	*(ptr + 1) = '\0';
	if (value < 0)
	{
		value = -value;
		negative = 1;
	}
	
	while (value > 0)
	{
		modulus = value % base;
		value = value / base;
		*ptr = num_to_value_lut[modulus];
		--ptr;
	}
	
	if ((negative == 1) && (base == 10))
	{
		*ptr = '-';
		--ptr;
	}
	
	if (ptr == (str + sizeof(str) -1))
	{
		*ptr = '0';
		--ptr;
	}
	
	return (ptr + 1);
}

/* INNER FUNCTION FOR USE OF PrintLetters */
/* 	Checks which letters are in str and changes ASCII values in LUT array 
	'letters' to 1 for each existing letter */
static void CheckLettersConv(const char *str, size_t size, int letters[], int check)
{
	int dig = 0;
	size_t i = 0;
	char c = 0;
	
	for (i = 0; i < size; ++i)
	{
		c = *(str + i);
		
		if (isalpha(c))
		{
			dig = *(str + i) - 'a';
		}
		
		if ((letters[dig] == check) && (dig >= 0))
		{
			++letters[dig];
		}
		
		dig = -1;
	}
	
	return;
}

/* prints letters that exist in str1 & str2 but don't exist in str3. CASE insensitive */
char *PrintLettersIn2Not3(const char *str1, const char *str2, const char *str3, char *result)
{
	static int letters[SUM_OF_LETTERS] = {0};
	int i = 0;
	size_t size1 = 0;
	size_t size2 = 0;
	size_t size3 = 0;
	
	assert(NULL != str1);
	assert(NULL != str2);
	assert(NULL != str3);
	
	size1 = strlen(str1);
	size2 = strlen(str2);
	size3 = strlen(str3);
	
	CheckLettersConv(str1, size1, letters, 0);
	CheckLettersConv(str2, size2, letters, 1);
	CheckLettersConv(str3, size3, letters, 2);

	
	for (i = 0; i < SUM_OF_LETTERS; ++i)
	{
		if (letters[i] == 2)
		{
			printf("%c", i + 'a');
			*result = i + 'a';
			++result;
		}
	}
	
	printf("\n");
	
	return (result);
}

/* checks whether system is Little or Big Endian */
int IsLittleEndian()
{
	short int x = 0x0001;
	char *tmp = (char *)(&x);
	if (tmp[0] == 1)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

/* INNER FUNCTION FOR USE OF MEMSET */
/* creates 8 Byte long type of size_t made of char c */
size_t CreateChunkConv(int c)
{
	size_t chunk = 0;
	char *ptr_chunk = (char *)&chunk;
	int i = 0;
	
	for (i = 0; i < WORD_SIZE; ++i)
	{
		*(ptr_chunk + i) = (unsigned char)c;
	}
	
	return (chunk);
}

/* efficiently sets first n bytes of string to char in c 
*/
void *MemSet(void *str, int c, size_t n)
{
	size_t *str_runner = NULL;

	char *first_and_last_tails = NULL;
	size_t i = 0;
	size_t repetitions = 0;
	
	size_t chunk = CreateChunkConv(c);
	
	assert(NULL != str);
	
	str_runner = str;
	repetitions = (long)str_runner % 8;
	
	first_and_last_tails = (char *)(str_runner);
	
	if (n == 0)
	{
		return (str);
	}
	
	for (i = 0; i < repetitions; ++i)
	{
		*(first_and_last_tails) = (unsigned char)c;
		++first_and_last_tails;
		--n;
		--repetitions;
	}
	
	while ((repetitions > 0) && (n > 0))
	{
		*(first_and_last_tails) = (unsigned char)c;
		++first_and_last_tails;
		--n;
		--repetitions;
	}
	repetitions = n / 8;
	n = n - 8 * repetitions;
	
	str_runner = (size_t *)first_and_last_tails;
	for (i = 0; i < repetitions; ++i)
	{
		*str_runner = chunk;
		++str_runner;
	}
	
	first_and_last_tails = (char *)(str_runner);
	
	for (i = 0; i < n; ++i)
	{
		*(first_and_last_tails + i) = (unsigned char)c;
	}
	
	return (str);
}

/* INNER FUNCTION FOR INNER USE */
/* returns chunk in size_t made of chars in src */
static size_t CreateChunkFromStringConv(char *src)
{
	size_t chunk = 0;
	char *ptr_chunk = (char *)&chunk;
	int i = 0;
	
	for (i = 0; i < 8; ++i)
	{
		*(ptr_chunk + i) = *(src + i);
		/*printf("%c", *(ptr_chunk + i));*/
	}
	/*printf("chunk is: \n");*/
	for (i = 0; i < 8; ++i)
	{
	/*	printf("%c", *(ptr_chunk + i)); */
	}
	
	return (chunk);
}

/* Copies src value to dest n times */
void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t chunk = 0;
	size_t *src_runner = NULL;
	size_t *dest_runner = NULL;
	char *src_char = NULL;
	char *dest_char = NULL;
	
	size_t repetitions = 0;
	size_t i = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	repetitions = (long)src % WORD_SIZE;
	src_runner = (void *)src;
	dest_runner = dest;
	src_char = (char *)src;
	dest_char = (char *)dest;
	
	/*
	if ((((size_t)dest - (size_t)src) < n) ||	(((size_t)src - (size_t)dest) < n))
	{
		return (NULL);
	}*/
	
	for (i = 0; i < repetitions; ++i)
	{
		*(dest_char + i) = *(src_char + i);
	}
	
	repetitions = n / 8;
	n = n - 8*repetitions;
	
	for (i = 0; i < repetitions; ++i)
	{
		chunk = CreateChunkFromStringConv((char *)src_runner);
		*dest_runner = chunk;
		++src_runner;
		++dest_runner;
	}
	
	dest_char = (char *)dest_runner;
	src_char = (char *)src_runner;
	
	for (i = 0; i < n; ++i)
	{
		*(dest_char + i) = *(src_char + i);
	}
	
	return (dest);
}

/* INNER FUNCTION FOR USE OF MemMove */
/* helps copy src data to dest for n elements */ 
void *MemMoveBackwardsConv(void *dest, const void *src, size_t n)
{
	size_t *src_runner = NULL;
	size_t *dest_runner = NULL;
	char *src_char = NULL;
	char *dest_char = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	
	src_char = (char *)src + n - 1;
	dest_char = (char *)dest + n - 1;
	
	while (((size_t)dest % 8 != 0) && (n > 0))
	{
		*dest_char = *src_char;
		--dest_char;
		--src_char;
		--n;
	}
	
	src_runner = (size_t *)src_char;
	dest_runner = (size_t *)dest_char;
	
	while (n >= 8)
	{
	
	/*	chunk = CreateChunkFromString((char *)(src_runner - 1));
		*dest_runner = chunk;
		--src_runner;
		--dest_runner;
		nt = nt - 8;*/
		--dest_runner;
		--src_runner;
		
		*(dest_runner) = (size_t)*src_runner;
	/*	chunk = CreateChunkFromString((char *)(src_runner));
		
		printf("chunk is: \n");
		for (i = 0; i < 8; ++i)
		{
			printf("%c", *(ptr_chunk + i)); 
		}
		
		*dest_runner = chunk;
		printf("%s\n", (char *)dest_runner);*/
		n = n - 8;
	}
	
	src_char = (char *)src_runner;
	dest_char = (char *)dest_runner;
	while (n > 0)
	{
		*dest_char = *src_char;
		--dest_char;
		--src_char;
		--n;
	}
	
	return (dest);
	
}

/* copies src data to dest for n elements */ 
void *MemMove(void *dest, const void *src, size_t n)
{
	
	if (dest == (void *)src)
	{
		return (dest);
	}
	else if (dest > src)
	{
		MemMoveBackwardsConv(dest, src, n);
	}
	else
	{
		MemCpy(dest, src, n);
	}
	
	return (dest);
	
}











