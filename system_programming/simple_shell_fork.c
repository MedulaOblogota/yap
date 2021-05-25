#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	char *command[2];
	pid_t child_pid;
	char com[20];
	/*char dest[25];*/

	command[0] = malloc(100);
	command[1] = NULL;

	/*strcpy(command[0], "./watch_dog ");*/

	/*command[0] = "./watch_dog ";*/

	while (1)
	{
		child_pid = fork();

		if (child_pid == 0)
		{
			scanf (" %[^\n]*c", command[0]);

			/*strcat(command[0], com);*/

			printf("command[0]=%s\n", command[0]);

			execvp(command[0], command);

			/*strcpy(command[0], "./watch_dog ");*/
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
