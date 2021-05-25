/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomi Daniel
Version:	Sent
Title:		WS6_BITS Functions File
*******************************************************************/
#define INT_BITS 31
#define CHAR_BITS 7

#include <stdio.h>	/* printf */
#include <stdlib.h>
#include "ws6.h"

/* LUT for returning the mirror value of a Byte */
static const unsigned char MirrorArr[] = {0, 128, 64, 192, 32, 160, 96, 224, 16,
 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152,
 88, 216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84,
 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220,
 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50,
 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186,
 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118,
 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254,
 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137,
 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69,
 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205,
 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67, 195, 35,
 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171,
 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103,
 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239,
 31, 159, 95, 223, 63, 191, 127, 255};


/*******************************************************************
							FUNCTIONS
*******************************************************************/

/* returns x*(2^y) without arithmetic operations */
/*long Pow2(unsigned int multiplier, int exponent)
{
	long result = multiplier;

	if (exponent >=0)
	{
			result = ( result << exponent);
	}
	else
	{
		exponent = ~exponent + 1;
		result = ( result >> exponent);
	}

	return (result);
}*/

long Pow2(unsigned int multiplier, int exponent)
{
	if (exponent >= 0)
	{
		return (multiplier << exponent);
	}
	else
	{
		exponent = -exponent;
		return (multiplier >> exponent);
	}
}

/* Returns 1 if num is Power of Two, 0 otherwise. Uses Loop */
int IsPowOf2Loop(unsigned int num)
{
	unsigned int mask = 1;
	int i = 0;

	for (i = INT_BITS; i > 0; --i)
	{
		if (mask == num)
		{
			return (1);
		}
		mask <<= 1;
	}

	return (0);
}

/* Returns 1 if num is Power of Two, 0 otherwise */
/*int IsPowOf2(unsigned int num)
{
	unsigned int mask = 1;

	if (num == 0)
	{
		return (0);
	}
	else if (num == 1)
	{
		return (1);
	}

	--num;

	return (mask & num);
}*/

/* Returns 1 if num is Power of Two, 0 otherwise */
int IsPowOf2(unsigned int num)
{
	if (num == 0)
	{
		return 0;
	}

	return ((num & (num - 1)) == 0);
}

/* Adds 1 to num without arithmetic operations */
/*unsigned int Add1(unsigned int num)
{
	int i = 0;
	int count = 0;
	unsigned int mask = 1;

	for (i = 0; i < INT_BITS; ++i)
	{
		mask = 1 << i;

		if ((mask & num) == 0)
		{
			count = i;
			break;
		}
	}

	mask = ~0;
	mask = mask >> (INT_BITS - count);

	return (mask ^ num);
}*/

/* Adds 1 to num without arithmetic operations */
unsigned int Add1(unsigned int num)
{
	unsigned int mask = 0x01;

	while ((mask & num) == mask)
	{
		num = num ^ mask;
		mask <<= 1;
	}

	return (num | mask);
}

/* receives array of unsigned ints and prints only those with 3 bits */
void ThreeBitsOn(unsigned int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;

	unsigned int mask;

	int counter = 0;

	for (i = 0; i < size; ++i)
	{
		counter = 0;

		for (j = 0; j < INT_BITS; ++j)
		{
			mask = 1 << j;

			if ((mask & arr[i]) != 0)
			{
				counter = Add1(counter);
			}
		}

		if (counter == 3)
		{
			printf("%d, ", arr[i]);
		}
	}
}

/* returns a mirrored bit unsigned char in relation to src */
/*unsigned char ByteMirrorLoop(unsigned char src)
{
	unsigned char dest = 0;
	int i = 0;

	for (i = 0; i < 8; ++i)
	{
		dest = dest << 1;
		dest += (src & 0x01);
		src = src >> 1;
	}

	return (dest);
}*/

/* returns a mirrored bit unsigned char in relation to src */
unsigned char ByteMirrorLoop(unsigned char src)
{
	unsigned char dest = 0;
	int i = 0;

	for (i = 0 ; i < 8; ++i)
	{
		dest <<= 1;
		dest = dest | (src & 0x01);
		src >>= 1;
	}

	return dest;
}

/* returns a mirrored bit unsigned char in relation to src using LUT */
unsigned char ByteMirror(unsigned char src)
{
	return (MirrorArr[src]);
}

/* returns 1 if bits indexed 2 and 6 are set, 0 otherwise */
int Is2And6(unsigned char num)
{
	unsigned char two = 1 << 2;
	unsigned char six = 1 << 6;

	return ((num & two) && (num & six));
}

/* returns 1 if bits indexed 2 or 6 are set, 0 otherwise */
int Is2Or6(unsigned char num)
{
	unsigned char two = 1 << 2;
	unsigned char six = 1 << 6;

	return ((num & two) || (num & six));
}

/* swaps bits 3 & 5 in num */
/*unsigned char Swap3And5(unsigned char num)
{
	unsigned char eraser = (1 << 3) | (1 << 5);
	unsigned char new_digits = 0;

	new_digits = ((num & 0x08) << 2) | ((num & 0x20) >> 2);
	eraser = ~eraser;

	return ((eraser & num) | new_digits);

}
*/
/* swaps bits 3 & 5 in num */
unsigned char Swap3And5(unsigned char num)
{
	unsigned char three = 0x01 << 3;
	unsigned char five = 0x01 << 5;

	three = (num & three) << 2;
	five = (num & five) >> 2;

	num = num & ~(0x01 << 3);
	num = num & ~(0x01 << 5);

	num = num | three | five;

	return num;
}

/* returns lowest number that is divisable by 16 in relation to num */
unsigned int DivisableBy16(unsigned int num)
{
	return ((num >> 4) << 4);
}

/* swaps two unsigned ints without using a temp var */
void Swap(unsigned int *a, unsigned int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/* counts amount of set bits present in num */
size_t CountBitsLoop(int num)
{
	int i = 0;
	size_t counter = 0;
	int mask = 1;

	for (i = INT_BITS; i >= 0; --i)
	{
		mask = 1 << i;

		if (((mask & num) >> i) == 1)
		{
			++counter;
		}
	}

	return (counter);
}

size_t CountBits(int num)
{
	const int m1 = 0x55555555; /*binary: 0101... */
	const int m2 = 0x33333333; /*binary: 00110011.. */
	const int m3 = 0x0F0F0F0F; /*binary:  4 zeros,  4 ones ... */
	const int m4 = 0x00ff00ff; /*binary:  8 zeros,  8 ones ... */
	const int m5 = 0x0000ffff; /*binary: 16 zeros, 16 ones ... */

	num = (num & m1) + ((num >> 1) & m1);
	num = (num & m2) + ((num >> 2) & m2);
	num = (num & m3) + ((num >> 4) & m3);
	num = (num & m4) + ((num >> 8) & m4);
	num = (num & m5) + ((num >> 16) & m5);

	return (num);
}
/* prints bits of float datatype */
void FloatToBits(float num)
{
	int i = 0;
	int *ip = (int *)(&num);
	int mask =1;

	for (i = INT_BITS; i >= 0; --i)
	{
		mask = 1 << i;
		printf("%d", (((*ip) & mask) >> i));

		if ((i % 8) == 0)
		{
			printf(" ");
		}
	}
}
