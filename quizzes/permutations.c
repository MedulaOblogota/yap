void PrintPermutations(char *str)
{
	Recursive(str, str + 1);
}

void Recursive(char *first, size_t size)
{
	if (size > 0)
	{
		printf("%c", *first);
		Recursive(first + 1, size - 1);
	}
	else
	{
		printf("\n");
	}

	Recursive(first, second + 1);
	printf("%c", *second);
	Recursive(first + 1, second);
	Recursive(first + 1, second + 1);
}
