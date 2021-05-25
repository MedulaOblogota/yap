/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Eliav Tubul
Version:	Sent
Title:		WS1 Bit Array Functions File
*******************************************************************/
#define BITS_IN_LONG (64)
#define BITS_IN_BYTE (8)

#include <stdio.h>
#include <limits.h>
#include "bitarray.h"

int BitsArrIsBitOn(unsigned long bit_array, size_t bit_index)
{
	unsigned long map = (unsigned long)1 << bit_index;

	return ((map & bit_array) == map);
}

int BitsArrIsBitOff(unsigned long bit_array, size_t bit_index)
{
	unsigned long map = (unsigned long)1 << bit_index;

	return ((map & bit_array) != map);
}

unsigned long BitsArrSetBitOn (unsigned long bit_array, size_t bit_index)
{
	unsigned long map = (unsigned long)1 << bit_index;

	return (bit_array | map);
}

unsigned long BitsArrSetBitOff (unsigned long bit_array, size_t bit_index)
{
	unsigned long map = (unsigned long)1 << bit_index;
	map = ~map;

	return (bit_array & map);
}

unsigned long BitsArrSetBit (unsigned long bit_array, size_t bit_index, int bit_value)
{
	unsigned long map = (unsigned long)1 << bit_index;
	map = ~map;
	bit_array = bit_array & map;

	return (((unsigned long)bit_value << bit_index) ^ bit_array);
}

unsigned long BitsArrFlip(unsigned long bit_array, size_t bit_index)
{
	unsigned long map = (unsigned long)1 << bit_index;

	return (bit_array ^ map);
}

size_t BitsArrCountOn(unsigned long bit_array)
{
	unsigned long map = (unsigned long)1;
	size_t count = 0;
	size_t i = 0;

	for (i = 0; BITS_IN_LONG > i; ++i)
	{
		if ( (bit_array & (map << i)) == (map << i) )
		{
			++count;
		}
	}

	return (count);
}

size_t BitsArrCountOff(unsigned long bit_array)
{
	unsigned long map = (unsigned long)1;
	size_t count = 0;
	size_t i = 0;

	for (i = 0; BITS_IN_LONG > i; ++i)
	{
		if ( (bit_array & (map << i)) == (map << i) )
		{
			++count;
		}
	}

	return (BITS_IN_LONG - count);
}

unsigned long BitsArrRotateLeft(unsigned long bit_array, size_t shift_amount)
{

	unsigned long large = ULONG_MAX;
	unsigned long left = 0;
	unsigned long right = 0;

	shift_amount = shift_amount % BITS_IN_LONG;

	left = (large << (BITS_IN_LONG - shift_amount)) & bit_array;
	right = (large >> (shift_amount)) & bit_array;

	return ((left >> (BITS_IN_LONG - shift_amount)) | (right << (shift_amount)));
}

unsigned long BitsArrRotateRight(unsigned long bit_array, size_t shift_amount)
{

	unsigned long large =  ULONG_MAX;
	unsigned long left = 0;
	unsigned long right = 0;

	shift_amount = shift_amount % BITS_IN_LONG;

	left = (large << (shift_amount)) & bit_array;
	right = (large >> (BITS_IN_LONG - shift_amount)) & bit_array;

	return ((left >> (shift_amount)) | (right << (BITS_IN_LONG - shift_amount)));
}

unsigned long BitsArrMirror(unsigned long bit_array)
{
	unsigned long mirror = 0;
	int i = 0;
	unsigned long mask = 0x01;

	for (i = 0; BITS_IN_LONG > i; ++i)
	{
		mirror = mirror << 1;
		mirror += bit_array & mask;
		bit_array = bit_array >> 1;
	}

	return (mirror);
}

static unsigned char ByteMirrorLoop(unsigned char src)
{
	unsigned char dest = 0;
	int i = 0;

	for (i = 0; BITS_IN_BYTE > i; ++i)
	{
		dest = dest << 1;
		dest += (src & 0x01);
		src = src >> 1;
	}

	return (dest);
}

static void *SetMirrorLUT(unsigned char *mirror_lut, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		*(mirror_lut + i) = ByteMirrorLoop(i);
	}
}

unsigned long BitsArrLUTMirror(unsigned long bit_array)
{
	size_t i = 0;
	unsigned long new = 0;

	unsigned long map = 0xFF;
	unsigned long byte = 0;

	unsigned char mirror_lut[256];

	SetMirrorLUT(mirror_lut, 256);

	for (i = 0; BITS_IN_BYTE > i; ++i)
	{
		new = new << BITS_IN_BYTE;
		byte = bit_array & map;
		new += mirror_lut[byte];
		bit_array = bit_array >> BITS_IN_BYTE;
	}

	return (new);
}

static unsigned char CountBitsLoop(unsigned char num)
{
	int i = 0;
	size_t counter = 0;
	int mask = 1;

	for (i = 7; 0 >= i; --i)
	{
		mask = 1 << i;

		if (((mask & num) >> i) == 1)
		{
			++counter;
		}
	}

	return (counter);
}

static void SetCountOnLUT(unsigned char *mirror_lut, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		*(mirror_lut + i) = CountBitsLoop(i);
	}

	return;
}

size_t BitsArrLUTCountOn(unsigned long bit_array)
{
	size_t i = 0;
	size_t new = 0;

	unsigned long map = 0xFF;
	unsigned long byte = 0;

	unsigned char count_on_lut[256];

	SetCountOnLUT(count_on_lut, 256);

	for (i = 0; BITS_IN_BYTE > i; ++i)
	{
		byte = bit_array & map;
		new += count_on_lut[byte];
		bit_array = bit_array >> BITS_IN_BYTE;
	}

	return (new);
}
