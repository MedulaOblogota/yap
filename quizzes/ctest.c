#include <stdio.h>

#define BITS_IN_BYTE (8)

int FlipVal(int value)
{
	int negative = 0;
	int flipped_value = 0;
	if (value < 0)
	{
		negative = 1;
		value = -value;
	}

	while (value > 0)
	{
		flipped_value = (flipped_value * 10) + (value % 10);
		value = value / 10;
	}

	if (negative)
	{
		flipped_value = -flipped_value;
	}

	return (flipped_value);
}

unsigned char Mirror(unsigned char src)
{
	unsigned char dest = 0;
	int i = 0;

	for (i = 0; i < BITS_IN_BYTE; ++i)
	{
		dest = dest << 1;
		dest = dest | (src & 0x01);
		src = src >> 1;
	}

	return (dest);
}

int flip(int val, int n)
{
	return (val ^ (1 << n));
}

size_t CountOnesInByte(unsigned char byte)
{
	size_t counter = 0;
	while (byte > 0)
	{
		if ((byte & 0x01) == 0x01)
		{
			++counter;
		}
		byte = byte >> 1;
	}

	return (counter);
}

char RotateLeft(char byte, int nbits)
{
	unsigned char map = 0xff;
	unsigned char left = 0;
	unsigned char right = 0;

	printf("%d\n", map);
	nbits = nbits % BITS_IN_BYTE;

	left = (map << (BITS_IN_BYTE - nbits)) & byte;
	right = (map >> (nbits)) & byte;

	return ((left >> (BITS_IN_BYTE - nbits)) | (right << (nbits)));
}

void SwapPointersToInts(int **first, int **second)
{
	int *temp = *first;
	*first = *second;
	*second = temp;
}

long fibonacci(unsigned int n)
{
	long value1 = 1;
	long value2 = 1;
	long temp = value1;
	unsigned int counter = 1;

	while (counter < n )
	{
		value2 = value1;
		value1 = temp + value1;
		temp = value2;
		++counter;
	}

	return(value2);
}

void IntToString(int number, char *str)
{
	sprintf(str, "%d", number);
}

int MultiplyByEight(int num)
{
	return (num << 3);
}

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

/* compares first string to second and returnsthe ASCII difference of first char-difference if exists as int */
int StrCmp(const char *first, const char *second)
{
	int sum = 0;

	assert(NULL != first);
	assert(NULL != second);

	while ((*first) && (*second))
	{
		if (*first != *second)
		{
			break;
		}
		++first;
		++second;
	}

	sum = *first - *second;

	return (sum);
}

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
	}

	*(dest + length) = '\0';

	return (base);
}

int main()
{
	int first = 5;
	int second = 7;
	int *pfirst = &first;
	int *psecond = &second;
	char str[20];
	printf("FlippedVal(4215)=%d\n", FlipVal(4215));
	printf("Mirror(243)=%d\n", Mirror(243));
	printf("flip for 2525 with n=3 is %d\n", flip(2525, 0));
	printf("There are %d 1s in 2\n", CountOnesInByte(2));
	printf("25 shifted 3 left is %d", RotateLeft(25, 3));
	printf("BEFORE: *first=%x. *second=%x\n", (pfirst), psecond);
	SwapPointersToInts(&pfirst, &psecond);
	printf("AFTER: *first=%x. *second=%x\n", (pfirst), psecond);
	printf("fibonacci of item 16 is %lu\n", fibonacci(16));
	IntToString(56, str);
	printf("56 in string is %s\n", str);
	printf("3*8=%d\n", MultiplyByEight(3));

	return (0);
}
