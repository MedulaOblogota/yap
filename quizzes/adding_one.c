#include <stdio.h>

unsigned int AddOneRecursive(unsigned int num)
{
	if (num & 0x01 == 0x01)
	{
		num = (num & ~0x01);
		num = AddOneRecursive(num >> 1);
		return (num << 1);
	}
	else
	{
		num = (num | 0x01);
		return (num);
	}
}

unsigned int AddOneIterative(unsigned int num)
{
	unsigned int mask = 0x01;

	while ((mask & num) == mask)
	{
		num = num & ~mask;
		mask = mask << 1;
	}

	return (num | mask);
}

int main()
{
	unsigned int num = 6;
	printf("add one to %d is %d\n", num, AddOneRecursive(num));
	printf("add one to %d is %d\n", num, AddOneIterative(num));
}
