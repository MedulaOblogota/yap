#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void parent_sig_handler(int sig, siginfo_t *siginfo, void *data)
{
	write(0, "Pong", 4);
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
		printf("input pid!\n");
		return 1;
	}

	command[0] = argv[1];
	command[1] = NULL;

	sa_parent.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_parent.sa_mask);
	sa_parent.sa_sigaction = &parent_sig_handler;

	printf("my pid is %d. run me with pid as attachment after running other program\n", getpid());

	sigaction(SIGUSR2, &sa_parent, NULL);

	kill(atoi(command[0]), SIGUSR1);

	while (1)
	{
		pause();
	}

	return 0;
}
