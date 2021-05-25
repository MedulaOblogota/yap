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
void child_sig_handler(int sig)
{
	write(0, "Pong\n", 5);
	sleep(1);
	kill(getppid(), SIGUSR2);
}

int main()
{
	pid_t child_pid = 0;

	struct sigaction sa_parent;
	struct sigaction sa_child;

	sa_parent.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_parent.sa_mask);
	sa_parent.sa_sigaction = &parent_sig_handler;

	sa_child.sa_handler = &child_sig_handler;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;

	child_pid = fork();

	if (child_pid > 0)
	{
		printf("parent\n");
		sigaction(SIGUSR2, &sa_parent, NULL);
		sleep(1);
		kill(child_pid, SIGUSR1);
	}
	else
	{
		printf("child\n");
		sigaction(SIGUSR1, &sa_child, NULL);
	}

	while (1);
}
