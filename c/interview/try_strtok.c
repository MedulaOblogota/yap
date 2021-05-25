#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[] = "hello$my *man$";
	char delim[] = " *$";

	printf("%s\n", strtok(str, delim));
	printf("%s\n", strtok(NULL, delim));
	printf("%s\n", strtok(NULL, delim));
	printf("%s\n", strtok(NULL, delim));

	return 0;
}
