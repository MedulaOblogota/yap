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
		scanf (" %[^\n]*c", com);

		system(com);

		wait(NULL);
	}
	
	return (0);
}
