#include <stdio.h>

char FlipBits(unsigned char c)
{
	size_t i = 0;
	unsigned char new_ch = 0;

	for (i = 0; i < 8; ++i)
	{
			new_ch = new_ch << 1;
			new_ch = new_ch | (c & 0x01);
			c = c >> 1;
	}

	return new_ch;
}

char SetBit(unsigned char c, int val, int index)
{
	unsigned char mask = 0x01 << index;

	c = c & ~mask;

	return (c | (val << index));
}

int main()
{
	unsigned char ch = 117;

	unsigned char bit = 103; // 01100111

	unsigned char cch = FlipBits(ch);

	printf("%d\n", cch);

	printf("bit with index %d equal to %d is %d\n", 2, 1, SetBit(bit, 0, 2));
}
