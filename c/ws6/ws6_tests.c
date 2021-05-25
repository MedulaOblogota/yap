/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomi Daniel
Title:		WS6_BITS Functions File
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ws6.h"

void TestPow2();
void TestIsPowOf2Loop();
void TestIsPowOf2();
void TestAdd1();
void TestThreeBitsOn();
void TestByteMirrorLoop();
void TestByteMirror();
void TestIs2And6();
void TestIs2Or6();
void TestSwap3And5();
void TestDivisableBy16();
void TestSwap();
void TestCountBitsLoop();
void TestCountBits();
void TestFloatToBits();

int main() 
{
	TestPow2();
	TestIsPowOf2Loop();
	TestIsPowOf2();
	TestAdd1();
	TestThreeBitsOn();
	TestByteMirrorLoop();
	TestByteMirror();
	TestIs2And6();
	TestIs2Or6();
	TestSwap3And5();
	TestDivisableBy16();
	TestSwap();
	TestCountBitsLoop();
	TestCountBits();
	TestFloatToBits();
	return (0);
}

void TestPow2()
{
	unsigned int x = 128;
	int y = -3;
	
	printf("Pow2 -> ");
	
	if (Pow2(x,y) != 16)
	{
		printf("failed test with %d and %d", x, y);
	}
		
	x = 6;
	y = 4;
	if (Pow2(x,y) != 96)
	{
		printf("failed test with %d and %d", x, y);
	}
	
	x = 0;
	y = 0;
	if (Pow2(x,y) != 0)
		{
		printf("failed test with %d and %d", x, y);
	}
	
	x = 1;
	y = 1;
	if (Pow2(x,y) != 2)
	{
		printf("failed test with %d and %d", x, y);
	}
	
	printf("\n");
}

void TestIsPowOf2Loop()
{
	unsigned int num = 8;
	
	printf("IsPowOf2Loop -> ");
	
	if (IsPowOf2Loop(num) != 1)
		printf("fail for %d\n", num);
		
	num = 0;
	if (IsPowOf2Loop(num) == 1)
	{
		printf("fail for %d\n", num);
	}
		
	num = 1;
	if (IsPowOf2Loop(num) != 1)
	{
		printf("fail for %d\n", num);
	}
	
	num = 256;
	if (IsPowOf2Loop(num) != 1)
	{
		printf("fail for %d\n", num);
	}
		
	printf("\n");
}

void TestIsPowOf2()
{
	unsigned int num = 8;
	
	printf("IsPowOf2 -> ");
	
	if (IsPowOf2(num) != 1)
	{
		printf("fail for %d\n", num);
	}
		
	num = 0;
	if (IsPowOf2(num) == 1)
	{
		printf("fail for %d\n", num);
	}
		
	num = 1;
	if (IsPowOf2(num) != 1)
	{
		printf("fail for %d\n", num);
	}
	
	num = 256;
	if (IsPowOf2(num) != 1)
	{
		printf("fail for %d\n", num);
	}
		
	printf("\n");
}
void TestAdd1()
{
	unsigned int num = 0;
	
	printf("Add1 -> ");
	
	if ((num + 1) != (Add1(num)))
	{
		printf("failed for %d", num);
	}
	
	num = 6;
	if ((num + 1) != (Add1(num)))
	{
		printf("failed for %d", num);
	}
	
	num = 1262;
	if ((num + 1) != (Add1(num)))
	{
		printf("failed for %d", num);
	}
		
	num = 5632;
	if ((num + 1) != (Add1(num)))
	{
		printf("failed for %d", num);
	}
	
	num = 9;
	if ((num + 1) != (Add1(num)))
	{
		printf("failed for %d", num);
	}
	
	printf("\n");
}

void TestThreeBitsOn()
{
	unsigned int arr[] = { 105, 88, 27, 104, 3, 105, 38, 58, 81 };
	
	printf("ThreeBitsOn -> Should print values 88, 104, 38, 81:\n");
	
	ThreeBitsOn(arr, 9);
	
	printf("\n");
}

void TestByteMirrorLoop()
{
	unsigned int num = 89;
	
	printf("ByteMirrorLoop -> ");

	if (154 != ByteMirrorLoop(num))
	{
		printf("failed with %d\n", num);
	}
		
	num = 164;
	if (37 != ByteMirrorLoop(num))
	{
		printf("failed with %d\n", num);
	}
	
	num = 83;
	if (202 != ByteMirrorLoop(num))
	{
		printf("failed with %d\n", num);
	}

	num = 120;
	if (30 != ByteMirrorLoop(num))
	{
		printf("failed with %d\n", num);
	}

	num = 143;
	if (241 != ByteMirrorLoop(num))
	{
		printf("failed with %d\n", num);
	}
	
	printf("\n");
}

void TestByteMirror()
{
	unsigned int num = 89;
	printf("ByteMirror -> ");

	if (154 != ByteMirror(num))
	{
		printf("failed with %d\n", num);
	}
		
	num = 164;
	if (37 != ByteMirror(num))
	{
		printf("failed with %d\n", num);
	}
	
	num = 83;
	if (202 != ByteMirror(num))
	{
		printf("failed with %d\n", num);
	}

	num = 120;
	if (30 != ByteMirror(num))
	{
		printf("failed with %d\n", num);
	}

	num = 143;
	if (241 != ByteMirror(num))
	{
		printf("failed with %d\n", num);
	}
	
	printf("\n");
}

void TestIs2And6()
{
	unsigned int num = 68;
	
	printf("Is2And6 -> ");
	
	if (Is2And6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 66;
	if (Is2And6(num) != 0)
	{
		printf("failed for %d\n", num);
	}
		
	num = 69;
	if (Is2And6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 84;
	if (Is2And6(num) != 1)
	{
		printf("failed for %d\n", num);
	}

	num = 1;
	if (Is2And6(num) != 0)
	{
		printf("failed for %d\n", num);
	}
		
	num = 0;
	if (Is2And6(num) != 0)
	{
		printf("failed for %d\n", num);
	}
		
	num = 6;
	if (Is2And6(num) != 0)
	{
		printf("failed for %d\n", num);
	}	

		
	printf("\n");
}

void TestIs2Or6() 
{
	unsigned int num = 20;
	
	printf("Is2Or6 -> ");

	if (Is2Or6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 68;
	if (Is2Or6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 0;
	if (Is2Or6(num) != 0)
	{
		printf("failed for %d\n", num);
	}
		
	num = 9;
	if (Is2Or6(num) != 0)
	{
		printf("failed for %d\n", num);
	}

	num = 80;
	if (Is2Or6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 12;
	if (Is2Or6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	num = 6;
	if (Is2Or6(num) != 1)
	{
		printf("failed for %d\n", num);
	}
		
	printf("\n");
}

void TestSwap3And5()
{
	unsigned int num = 77;
	
	printf("Swap3And5 -> ");
	
	if (Swap3And5(num) != 101)
	{
		printf("failed for %d\n", num);
	}
	
	num = 168;
	if (Swap3And5(num) != 168)
	{
		printf("failed for %d\n", num);
	}
	
	num = 49;
	if (Swap3And5(num) != 25)
	{
		printf("failed for %d\n", num);
	}
	
	num = 80;
	if (Swap3And5(num) != 80)
	{
		printf("failed for %d\n", num);
	}

	printf("\n");
}

void TestDivisableBy16()
{
	unsigned int num = 87;
	printf("DivisableBy16 -> ");

	if (DivisableBy16(num) != 80)
	{
		printf("failed for %d\n", num);
	}
	
	num = 4;
	if (DivisableBy16(num) != 0)
	{
		printf("failed for %d\n", num);
	}

	num = 16;
	if (DivisableBy16(num) != 16)
	{
		printf("failed for %d\n", num);
	}
		
	num = 1;
	if (DivisableBy16(num) != 0)
	{
		printf("failed for %d\n", num);
	}
	
	num = 451;
	if (DivisableBy16(num) != 448)
	{
		printf("failed for %d\n", num);
	}
	
	num = 4215;
	if (DivisableBy16(num) != 4208)
	{
		printf("failed for %d\n", num);
	}
	
	printf("\n");
}

void TestSwap()
{
	unsigned int first = 10; 
	unsigned int second = 8;
	
	unsigned int *p_first = &first; 
	unsigned int *p_second = &second; 
	
	printf("Swap -> ");
	
	Swap(p_first, p_second);
	
	if (p_first != &first || p_second != &second)
	{
		printf("failed\n");
	}
	
	printf("\n");
}

void TestCountBitsLoop()
{
	unsigned int num = 340;
	
	printf("CountBitsLoop -> ");

	if (CountBitsLoop(num) != 4)
	{
		printf("failed with %u\n", num);
	}
	
	num = 1008;
	if (CountBitsLoop(num) != 6)
	{
		printf("failed with %u\n", num);
	}
	
	num = 443;	
	if (CountBitsLoop(num) != 7)
	{
		printf("failed with %u\n", num);
	}
	
	num = 80;
	if (CountBitsLoop(num) != 2)
	{
		printf("failed with %u\n", num);
	}
	
	num = 1;	
	if (CountBitsLoop(num) != 1)
	{
		printf("failed with %u\n", num);
	}
		
		
	printf("\n");
}

void TestCountBits() 
{
	unsigned int num = 340;
	printf("CountBits -> ");

	if (CountBits(num) != 4)
	{
		printf("failed with %u\n", num);
	}
	
	num = 1008;
	if (CountBits(num) != 6)
	{
		printf("failed with %u\n", num);
	}
	
	num = 443;	
	if (CountBits(num) != 7)
	{
		printf("failed with %u\n", num);
	}
	
	num = 80;
	if (CountBits(num) != 2)
	{
		printf("failed with %u\n", num);
	}
	
	num = 1;	
	if (CountBits(num) != 1)
	{
		printf("failed with %u\n", num);
	}
		
		
	printf("\n");
}

void TestFloatToBits()
{
	int i = 0;
	
	printf("CountBits -> Should print Float Bit value of numbers 1 to 5:\n");
	for (i = 0; i <= 5; ++i)
	{
		printf("%d - ", i);
		FloatToBits(i);
		printf("\n");
	}
}

