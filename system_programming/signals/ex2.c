#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void parent_sig_handler(int sig, siginfo_t *siginfo, void *data)
{
	write(0, "Ping", 4);
	sleep(1);
	kill(siginfo->si_pid, SIGUSR1);
}

int main(int argc, char *argv[])
{
	pid_t child_pid = 0;
	char *command[2];

	struct sigaction sa_parent;
	/*struct sigaction sa_child;*/

	if (argc == 1)
	{
		printf("input file name!\n");
		return 1;
	}

	command[0] = argv[1];
	command[1] = NULL;

	sa_parent.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_parent.sa_mask);
	sa_parent.sa_sigaction = &parent_sig_handler;

	/*sa_child.sa_handler = &child_sig_handler;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;*/

	child_pid = fork();

	if (child_pid > 0)	/* you are father */
	{
		printf("parent. my pid is %d. child_pid is %d\n", getpid(), child_pid);
		sigaction(SIGUSR2, &sa_parent, NULL);
		sleep(2);
		kill(child_pid, SIGUSR1);
	}
	else
	{
		printf("child\n");
		printf("command[0]=%s\n", command[0]);
		/* sigaction(SIGUSR1, &sa_child, NULL); */
		execvp(command[0], command);
	}

	while (1);
	return 0;
}
