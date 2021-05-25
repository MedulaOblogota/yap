#include <stdio.h>
#include <string.h>

void TurnUpsideDown(char *str)
{
	size_t length = strlen(str);
	size_t i = 0;

	size_t end = length - 1;
	for (i = 0; i < length / 2; ++i)
	{
		char temp = str[i];
		str[i] = str[end];
		str[end] = temp;
		--end;
	}
}

int IsPolynom(char *str)
{
	size_t length = strlen(str);
	size_t i = 0;

	size_t end = length - 1;
	int ret = 1;

	for (i = 0; i < length / 2; ++i)
	{
		if (str[i] != str[end])
		{
			ret = 0;
		}
		--end;
	}

	return ret;
}

int main()
{
	char hello[] = "whassup buddy?";
	char poly[] ="modom";
	char notpoly[] = "momm";

	TurnUpsideDown(hello);

	printf("%s\n", hello);

	printf("poly -> %d\n", IsPolynom(poly));
	printf("notpoly -> %d\n", IsPolynom(notpoly));

	return 0;
}
