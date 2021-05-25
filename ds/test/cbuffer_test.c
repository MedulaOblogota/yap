#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "cbuffer.h"

#define BUFFER_SIZE (5)
#define PARTIAL_SIZE (3)
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestCreateBuffer();

void TestWriteAndReadToBuffer();
void TestEmptyCapacityFreeSpace();

int main()
{
	TestCreateBuffer();
	TestWriteAndReadToBuffer();
	TestEmptyCapacityFreeSpace();
	
	return (0);
}

static void PrintBuffer(char *buffer)
{
	int i = 0;
	for (i = 0; i < BUFFER_SIZE; ++i)
	{
		printf("%c", buffer[i]);
	}
	printf("\n");
}

static void FillUpBuffer(c_buffer_t *buffer)
{
    int i = 0;
    char str[BUFFER_SIZE] = {0};
    for (i = 0; i < BUFFER_SIZE; ++i)
    {
        str[i] = 21 + (i + '!') % 21;
    }

    CBuffWrite(buffer, str, BUFFER_SIZE);
}

static void PartiallyFillUpBuffer(c_buffer_t *buffer)
{
    int i = 0;

    char str[PARTIAL_SIZE] = {0};
    for (i = 0; i < PARTIAL_SIZE; ++i)
    {
        str[i] = 21 + (i + '!') % 21;
    }

    CBuffWrite(buffer, str, PARTIAL_SIZE);
}

static void WrapperTestCreateBuffer(c_buffer_t *buffer)
{
    if (buffer != NULL)
    {
        printf(GRN "SUCCESS with CBuffCreate function\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with CBuffCreate function\n" RESET);
    }

}
void TestCreateBuffer()
{
    c_buffer_t *full_buffer = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *empty_buffer = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *buffer = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *zero_buffer = CBuffCreate(0);

    FillUpBuffer(full_buffer);
    PartiallyFillUpBuffer(buffer);

    WrapperTestCreateBuffer(full_buffer);
    WrapperTestCreateBuffer(empty_buffer);
    WrapperTestCreateBuffer(buffer);
    if (zero_buffer == NULL)
    {
        printf(GRN "SUCCESS with CBuffCreate function\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with CBuffCreate function\n" RESET);
    }

    CBuffDestroy(full_buffer);
    CBuffDestroy(empty_buffer);
    CBuffDestroy(buffer);
}

static void WrapperTestWriteToBuffer(c_buffer_t *buffer, char *str, size_t buffer_length, ssize_t correct_size)
{
    if (CBuffWrite(buffer, str, buffer_length) != correct_size)
    {
        printf(RED "FAILURE with CBuffRead function for %s\n" RESET, str);
    }
    else
    {
        printf(GRN "SUCCESS with CBuffRead function for %s\n" RESET, str);
    }
}

static void WrapperTestReadToBuffer(c_buffer_t *buffer, char *str, ssize_t buffer_length, ssize_t correct_size)
{
    if (CBuffRead(buffer, str, buffer_length) != correct_size)
    {
        printf(RED "FAILURE with CBuffRead function for %s\n" RESET, str);
    }
    else
    {
        printf(GRN "SUCCESS with CBuffRead function for %s\n" RESET, str);
    }
}

void WrapperCompareBuffers(char *dest, char *result, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		if (dest[i] != result[i])
		{
			printf(RED "FAILURE with comparing string %s\n" RESET, result);
		}
		else
		{
			printf(GRN "SUCCESS with comparing string %s\n" RESET, result);
		}
	}
}

void TestWriteAndReadToBuffer()
{
    c_buffer_t *buffer1 = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *buffer2 = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *buffer3 = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *buffer4 = CBuffCreate(BUFFER_SIZE);

    char smaller[] = "ab";
    char exactly[] = "12345";
    char larger[] = "abcdefg";
    char very_large[] = "a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6";
    char two[2] = "ma";

    char dest[90];


/*  FIRST TEST -> see if Write & Read funcs return correct values*/
	printf("\n\n FIRST TEST: \n\n");
    WrapperTestWriteToBuffer(buffer1, smaller, strlen(smaller), 2);
    WrapperTestWriteToBuffer(buffer2, exactly, strlen(exactly), 5);
    WrapperTestWriteToBuffer(buffer3, larger, strlen(larger), 5);

	/*PrintBuffer(buffer3);*/
    WrapperTestWriteToBuffer(buffer4, very_large, sizeof(very_large), 5);

    WrapperTestReadToBuffer(buffer1, dest, 2, 2);
	WrapperCompareBuffers(dest, smaller, 2);

    WrapperTestReadToBuffer(buffer2, dest, 5, BUFFER_SIZE);
	WrapperCompareBuffers(dest, exactly, 5);

    WrapperTestReadToBuffer(buffer3, dest, 7, BUFFER_SIZE);
	WrapperCompareBuffers(dest, larger, 5);

    WrapperTestReadToBuffer(buffer4, dest, 52, BUFFER_SIZE);
	WrapperCompareBuffers(dest, very_large, 5);

/*  SECOND TEST -> fill several times beyond capacity and read several times */
	printf("\n\n SECOND TEST: \n\n");
    CBuffDestroy(buffer1);
    buffer1 = CBuffCreate(BUFFER_SIZE);
    WrapperTestWriteToBuffer(buffer1, two, 2, 2);
    WrapperTestWriteToBuffer(buffer1, two, 2, 2);
    WrapperTestWriteToBuffer(buffer1, two, 2, 1);
    WrapperTestWriteToBuffer(buffer1, two, 2, 0);
    WrapperTestReadToBuffer(buffer1, two, 2, 2);
    WrapperTestReadToBuffer(buffer1, two, 2, 2);
    WrapperTestReadToBuffer(buffer1, two, 2, 1);
    WrapperTestReadToBuffer(buffer1, two, 2, 0);

/*	THIRD TEST -> fill partly, remove less, fill partly, remove less - up until you fill entirely, then remove and then fill less (leaving it not full) */
	printf("\n\n THIRD TEST: \n\n");
	CBuffDestroy(buffer1);
    buffer1 = CBuffCreate(BUFFER_SIZE);
	WrapperTestWriteToBuffer(buffer1, two, 2, 2);
	WrapperTestWriteToBuffer(buffer1, two, 2, 2);
	WrapperTestReadToBuffer(buffer1, two, 1, 1);
	WrapperTestWriteToBuffer(buffer1, two, 1, 1);
	WrapperTestWriteToBuffer(buffer1, two, 2, 1);
	WrapperTestReadToBuffer(buffer1, two, 2, 2);
	WrapperTestWriteToBuffer(buffer1, two, 1, 1);
	WrapperTestWriteToBuffer(buffer1, two, 8, 1);
	WrapperTestReadToBuffer(buffer1, two, 4, 4);
	WrapperTestWriteToBuffer(buffer1, two, 3, 3);


    CBuffDestroy(buffer1);
    CBuffDestroy(buffer2);
    CBuffDestroy(buffer3);
    CBuffDestroy(buffer4);
}

static void TestEmptyBuffer(c_buffer_t *buffer, int check)
{
	if (CBuffIsEmpty(buffer) != check)
	{
		printf(RED "FAILURE with CBuffIsEmpty\n" RESET);
	}
	else
	{
		printf(GRN "SUCCESS with CBuffIsEmpty\n" RESET);
	}
}

static void TestCapacityBuffer(c_buffer_t *buffer, size_t check)
{
	if (CBuffCapacity(buffer) != check)
	{
		printf(RED "FAILURE with CBuffCapacity\n" RESET);
	}
	else
	{
		printf(GRN "SUCCESS with CBuffCapacity\n" RESET);
	}
}

static void TestFreeSpaceBuffer(c_buffer_t *buffer, size_t check)
{
	if (CBuffFreeSpace(buffer) != check)
	{
		printf(RED "FAILURE with CBuffFreeSpace\n" RESET);
	}
	else
	{
		printf(GRN "SUCCESS with CBuffFreeSpace\n" RESET);
	}
}

void TestEmptyCapacityFreeSpace()
{
	c_buffer_t *full_buffer = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *empty_buffer = CBuffCreate(BUFFER_SIZE);
    c_buffer_t *buffer = CBuffCreate(BUFFER_SIZE);

	FillUpBuffer(full_buffer);
    PartiallyFillUpBuffer(buffer);

	TestEmptyBuffer(empty_buffer, 1);
	TestEmptyBuffer(full_buffer, 0);
	TestEmptyBuffer(buffer, 0);

	TestCapacityBuffer(empty_buffer, BUFFER_SIZE);
	TestCapacityBuffer(full_buffer, BUFFER_SIZE);
	TestCapacityBuffer(buffer, BUFFER_SIZE);

	TestFreeSpaceBuffer(empty_buffer, BUFFER_SIZE);
	TestFreeSpaceBuffer(full_buffer, 0);
	TestFreeSpaceBuffer(buffer, BUFFER_SIZE - PARTIAL_SIZE);

}
