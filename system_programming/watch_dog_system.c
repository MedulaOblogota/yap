#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	system("./program");
	while (1)
	{
		if (wait(NULL) < 0)
		{
			printf("ENTERED WHILE\n");
			system("./program");
		}
	}

	return (0);
}
