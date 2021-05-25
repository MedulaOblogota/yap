#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rotation(char *str1, char *str2)
{
	int i = 0;
	int length_str1 = strlen(str1);
	int length_str2 = strlen(str2);
	
	if (length_str1 != length_str2)
		return 0;

	for (i = 0; i < length_str1; ++i)
	{
		if (0 == strncmp(str1, str2 + i, length_str1 - i))
		{
			if (0 == strncmp(str1 + length_str1 - i, str2, i))
				return (1);
		}
	}
	
	return (0);
}

int main()
{
	char str1[] = "1223242";
	char str2[] = "2232421";
	printf("%d\n", rotation(str1, str2));
}
