#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	pid_t child_pid = fork();
	(void)argc;

	if (child_pid > 0) /* you are father */
	{
		while (1)
		{
			if (wait(NULL) < 0)
			{
				printf("ENTERED WHILE\n");
				child_pid = fork();
				if (child_pid == 0)
				{
					execvp (argv[1], &(*(argv + 1)));
				}
			}
		}
	}
	else if (child_pid == 0)/* you are child */
	{
			execvp (argv[1], &(*(argv + 1)));
	}

	return (0);
}
