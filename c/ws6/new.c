/* returns x*(2^y) without arithmetic operations */
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
	size_t i = 0;
	unsigned int mask = 0x01;

	for (i = 0; i < 31; ++i)
	{
		if (mask == num)
		{
			return 1;
		}

		mask <<= 1;
	}

	return (0);
}

/* Returns 1 if num is Power of Two, 0 otherwise */
int IsPowOf2(unsigned int num)
{
	return ((num & (num - 1)) == 0)
}

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

/* returns a mirrored bit unsigned char in relation to src */
unsigned char ByteMirrorLoop(unsigned char src)
{
	unsigned char dest = 0;
	while (src > 0)
	{
		dest <<= 1;
		dest = dest | (src & 0x01);
		src >>= 1;
	}

	return dest;
}
