#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void child_sig_handler(int sig, siginfo_t *siginfo, void *data)
{
	write(0, "Ping", 4);
	sleep(1);
	kill(siginfo->si_pid, SIGUSR2);
}

int main(int argc, char *argv[])
{
	pid_t child_pid = 0;

	struct sigaction sa_child;
	/*struct sigaction sa_child;*/

	sa_child.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_sigaction = &child_sig_handler;

	printf("my pid is %d. run my pid as attachment\n", getpid());

	sigaction(SIGUSR1, &sa_child, NULL);

	while (1);

	return 0;
}
