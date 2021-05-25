/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Eliav Tubul
Version:	Sent
Title:		WS1 Bit Array Test File
*******************************************************************/
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"

#include <stdio.h> /* printf */
#include <limits.h> /* ULONG_MAX macro */
#include "../include/bitarray.h"

/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/

void TestBitsArrIsBitOn();
void TestBitsArrIsBitOff();
void TestBitsArrSetBitOn();
void TestBitsArrSetBitOff();
void TestBitsArrSetBit();
void TestBitsArrFlip();
void TestBitsArrCountOn();
void TestBitsArrCountOff();
void TestBitsArrRotateLeft();
void TestBitsArrRotateRight();
void TestBitsArrMirror();
void TestBitsArrLUTMirror();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main()
{
	TestBitsArrIsBitOn();
	TestBitsArrIsBitOff();
	TestBitsArrSetBitOn();
	TestBitsArrSetBitOff();
	TestBitsArrSetBit();
	TestBitsArrFlip();
	TestBitsArrCountOn();
	TestBitsArrCountOff();
	TestBitsArrRotateLeft();
	TestBitsArrRotateRight();
	TestBitsArrMirror(); 
	TestBitsArrLUTMirror();
	
	return (0);
}

/********************************************************************/
/*	 																*/
/*					Wrapper Functions								*/
/* 																	*/
/********************************************************************/

void WrapperBitsArrIsBitOn(unsigned long bit_array, int index, int correct_result)
{
	if (BitsArrIsBitOn(bit_array, index) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d\n" RESET, bit_array, index);
	}
}

void WrapperBitsArrIsBitOff(unsigned long bit_array, int index, int correct_result)
{
	if (BitsArrIsBitOff(bit_array, index) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d\n" RESET, bit_array, index);
	}
}

void WrapperBitsArrSetBitOn(unsigned long bit_array, int index, unsigned long correct_result)
{
	if (BitsArrSetBitOn(bit_array, index) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d\n" RESET, bit_array, index);
	} 
}

void WrapperBitsArrSetBitOff(unsigned long bit_array, int index, unsigned long correct_result)
{
	if (BitsArrSetBitOff(bit_array, index) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d\n" RESET, bit_array, index);
	} 
}

void WrapperBitsArrSetBit(unsigned long bit_array, int index, int decision, unsigned long correct_result)
{
	if (BitsArrSetBit(bit_array, index, decision) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d for decision %d\n" RESET, bit_array, index, decision);
	} 
}	

void WrapperBitsArrSetBitFlip(unsigned long bit_array, int index, unsigned long correct_result)
{
	if (BitsArrFlip(bit_array, index) != correct_result)
	{
		printf(RED "FAILED with %lu and index %d\n" RESET, bit_array, index);
	} 
}

void WrapBitArrCountOn(unsigned long bit_array, size_t correct_result)
{
	if (BitsArrCountOn(bit_array) != correct_result)
		{
			printf(RED "FAILED with %lu\n" RESET, bit_array);
		} 
}
	
void WrapBitArrCountOff(unsigned long bit_array, size_t correct_result)
{
	if (BitsArrCountOff(bit_array) != correct_result)
		{
			printf(RED "FAILED with %lu\n" RESET, bit_array);
		} 
}

void WrapBitsArrRotateLeft(unsigned long bit_array, size_t shift, unsigned long correct_result)
{
	if (BitsArrRotateLeft(bit_array, shift) != correct_result)
	{
		printf(RED "FAILED with %lu and shift of %lu\n" RESET, bit_array, shift);
	}
}

void WrapBitsArrRotateRight(unsigned long bit_array, size_t shift, unsigned long correct_result)
{
	if (BitsArrRotateRight(bit_array, shift) != correct_result)
	{
		printf(RED "FAILED with %lu and shift of %lu\n" RESET, bit_array, shift);
	}
}

void WrapBitsArrMirror(unsigned long bit_array, unsigned long correct_result)
{
	if (BitsArrMirror(bit_array) != correct_result)
	{
		printf(RED "FAILED with %lu\n" RESET, bit_array);
	}
}

void WrapBitsArrLUTMirror(unsigned long bit_array, unsigned long correct_result)
{
	if (BitsArrLUTMirror(bit_array) != correct_result)
	{
		printf(RED "FAILED with %lu\n" RESET, bit_array);
	}
}

void WrapBitArrLUTCountOn(unsigned long bit_array, size_t correct_result)
{
	if (BitsArrLUTCountOn(bit_array) != correct_result)
		{
			printf(RED "FAILED with %lu\n" RESET, bit_array);
		} 
}

/********************************************************************/
/*	 																*/
/*				Test Function Implementations						*/
/* 																	*/
/********************************************************************/

void TestBitsArrIsBitOn()
{
	unsigned long bit_array = 53216763125326265; 
	
	int index = 12;
	int correct_result = 0;
	
	printf("BitsArrIsBitOn->\n");
	
	WrapperBitsArrIsBitOn(bit_array, index, correct_result);
	
	bit_array = 0;
	index = 0;
	correct_result = 0;
	WrapperBitsArrIsBitOn(bit_array, index, correct_result);
	
	bit_array = 0;
	index = 63;
	correct_result = 0;
	WrapperBitsArrIsBitOn(bit_array, index, correct_result);
	
	bit_array = 626247437634124;
	index = 63;
	correct_result = 0;
	WrapperBitsArrIsBitOn(bit_array, index, correct_result);
	
	bit_array = ULONG_MAX;
	index = 63;
	correct_result = 1;
	WrapperBitsArrIsBitOn(bit_array, index, correct_result);

	printf("\n");
}

void TestBitsArrIsBitOff()
{
	unsigned long bit_array = 53216763125326265; 
	
	int index = 12;
	int correct_result = 1;
	
	printf("BitsArrIsBitOff->\n");
	
	WrapperBitsArrIsBitOff(bit_array, index, correct_result);
	
	bit_array = 0;
	index = 0;
	correct_result = 1;
	WrapperBitsArrIsBitOff(bit_array, index, correct_result);
	
	bit_array = 0;
	index = 63;
	correct_result = 1;
	WrapperBitsArrIsBitOff(bit_array, index, correct_result);
	
	bit_array = 626247437634124;
	index = 63;
	correct_result = 1;
	WrapperBitsArrIsBitOff(bit_array, index, correct_result);
	
	bit_array = ULONG_MAX;
	index = 63;
	correct_result = 0;
	WrapperBitsArrIsBitOff(bit_array, index, correct_result);
	
	printf("\n");
}
void TestBitsArrSetBitOn()
{
	unsigned long bit_array = 53216763125326265;
	
	int index = 12;
	unsigned long result = 53216763125330361;
	
	printf("BitsArrSetBitOn->\n");
		
	/* turning on closed bit */
	WrapperBitsArrSetBitOn(bit_array, index, result);
	
	index = 13;
	result = 53216763125326265;
	/* turning on open bit */
	WrapperBitsArrSetBitOn(bit_array, index, result);
	
	bit_array = 0;
	index = 0;
	result = 1;
	WrapperBitsArrSetBitOn(bit_array, index, result);
	
	bit_array = 1;
	index = 63;
	result = 9223372036854775809;
	WrapperBitsArrSetBitOn(bit_array, index, result);

	printf("\n");
}
void TestBitsArrSetBitOff()
{
	unsigned long bit_array = 53216763125326265;
	
	int index = 12;
	unsigned long result = 53216763125326265;
	
	printf("BitsArrSetBitOff->\n");
		
	/* turning off closed bit */
	WrapperBitsArrSetBitOff(bit_array, index, result);
	
	index = 13;
	result = 53216763125318073;
	/* turning off open bit */
	WrapperBitsArrSetBitOff(bit_array, index, result);
	
	bit_array = 0;
	index = 0;
	result = 0;
	WrapperBitsArrSetBitOff(bit_array, index, result);
	
	bit_array = 9223372036854775808;
	index = 63;
	result = 0;
	WrapperBitsArrSetBitOff(bit_array, index, result);

	printf("\n");
}

void TestBitsArrSetBit()
{
	unsigned long bit_array = 53216763125326265;
	int index = 12;
	int decision = 1;
	unsigned long value = 53216763125330361;
	printf("BitsArrSetBit->\n");		
	
	WrapperBitsArrSetBit(bit_array, index, decision, value);	
	
	index = 12;
	decision = 0;
	value = 53216763125326265;
	WrapperBitsArrSetBit(bit_array, index, decision, value);	
	
	index = 13;
	decision = 0;
	value = 53216763125318073;
	WrapperBitsArrSetBit(bit_array, index, decision, value);	

	index = 13;
	decision = 1;
	value = 53216763125326265;
	WrapperBitsArrSetBit(bit_array, index, decision, value);	

	bit_array = 0;
	index = 0;
	decision = 0;
	value = 0;
	WrapperBitsArrSetBit(bit_array, index, decision, value);			
	
	bit_array = 1;
	index = 63;
	decision = 1;
	value = 9223372036854775809;
	WrapperBitsArrSetBit(bit_array, index, decision, value);			

	printf("\n");
}
void TestBitsArrFlip()
{
	unsigned long bit_array = 53216763125326265;	
	int index = 0;
	unsigned long result = 53216763125326264;
	
	printf("BitsArrFlip->\n");	
	/* open to closed bit */
	WrapperBitsArrSetBitFlip(bit_array, index, result);

	index = 9;
	result = 53216763125326777;
	/* closed to open bit */
	WrapperBitsArrSetBitFlip(bit_array, index, result);
	
	bit_array = 7;
	index = 0;
	result = 6;
	WrapperBitsArrSetBitFlip(bit_array, index, result);
	
	bit_array = 9223372036854775808;
	index = 63;
	result = 0;
	WrapperBitsArrSetBitFlip(bit_array, index, result);
	
	printf("\n");
}

void TestBitsArrCountOn()
{
	unsigned long bit_array = 53216763125326265;	
	int result = 28;
	
	printf("BitsArrCountOn->\n");				
	
	WrapBitArrCountOn(bit_array, result);
	
	bit_array = 0;
	result = 0;
	WrapBitArrCountOn(bit_array, result);
	
	bit_array = ULONG_MAX;
	result = 64;
	WrapBitArrCountOn(bit_array, result);

	printf("\n");
}
void TestBitsArrCountOff()
{
	
	unsigned long bit_array = 53216763125326265;	
	int result = 36;
	printf("BitsArrCountOff->\n");					
	
	WrapBitArrCountOff(bit_array, result);
	
	bit_array = 0;
	result = 64;
	WrapBitArrCountOff(bit_array, result);
	
	bit_array = ULONG_MAX;
	result = 0;
	WrapBitArrCountOff(bit_array, result);
	
	printf("\n");
}

void TestBitsArrRotateLeft()
{
	unsigned long bit_array = 53216763125326265;	
	size_t shift = 10;
	unsigned long result = 17600477292914992130;										
	printf("BitsArrRotateLeft->\n");					
	
	WrapBitsArrRotateLeft(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 64;
	result = 53216763125326265;
	WrapBitsArrRotateLeft(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 0;
	result = 53216763125326265;
	WrapBitsArrRotateLeft(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 100;
	result = 7126413765847877075;
	WrapBitsArrRotateLeft(bit_array, shift, result);
	
	bit_array = 0;
	shift = 70;
	result = 0;
	WrapBitsArrRotateLeft(bit_array, shift, result);
	
	printf("\n");
}
void TestBitsArrRotateRight()
{
	unsigned long bit_array = 53216763125326265;	
	size_t shift = 10;
	unsigned long result = 7944401712176794520;										
	printf("BitsArrRotateRight->\n");					
	
	WrapBitsArrRotateRight(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 64;
	result = 53216763125326265;
	WrapBitsArrRotateRight(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 0;
	result = 53216763125326265;
	WrapBitsArrRotateRight(bit_array, shift, result);
	
	bit_array = 53216763125326265;
	shift = 100;
	result = 15231989895775637765;
	WrapBitsArrRotateRight(bit_array, shift, result);
	
	bit_array = 0;
	shift = 70;
	result = 0;
	WrapBitsArrRotateRight(bit_array, shift, result);

	printf("\n");
}
void TestBitsArrMirror()
{
	unsigned long bit_array = 53216763125326265;	
	unsigned long value = 11350887921160338688;
	
	printf("BitsArrMirror->\n");	
	
	WrapBitsArrMirror(bit_array, value);
	
	bit_array = 0;
	value = 0;
	WrapBitsArrMirror(bit_array, value);
	
	bit_array = 1;
	value = 9223372036854775808;
	WrapBitsArrMirror(bit_array, value);
	
	bit_array = 9223372036854775809;
	value = 9223372036854775809;
	WrapBitsArrMirror(bit_array, value);
	
	printf("\n");
	
}

void TestBitsArrLUTMirror()
{
	unsigned long bit_array = 53216763125326265;	
	unsigned long value = 11350887921160338688;
	
	printf("BitsArrLUTMirror->\n");	
	
	WrapBitsArrLUTMirror(bit_array, value);
	
	bit_array = 0;
	value = 0;
	WrapBitsArrLUTMirror(bit_array, value);
	
	bit_array = 1;
	value = 9223372036854775808;
	WrapBitsArrLUTMirror(bit_array, value);
	
	bit_array = 9223372036854775809;
	value = 9223372036854775809;
	WrapBitsArrLUTMirror(bit_array, value);
	
	printf("\n");
}

void TestBitsArrLUTCountOn()
{
	unsigned long bit_array = 53216763125326265;	
	int result = 28;
	
	printf("BitsArrLUTCountOn->\n");					
	
	WrapBitArrLUTCountOn(bit_array, result);
	
	bit_array = 0;
	result = 0;
	WrapBitArrLUTCountOn(bit_array, result);
	
	bit_array = ULONG_MAX;
	result = 64;
	WrapBitArrLUTCountOn(bit_array, result);

	printf("\n");
}

/*00000000 10111101 00010000 01011101 00110110 00101110 01100001 10111001*/
