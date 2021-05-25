#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void child_sig_handler(int sig)
{
	write(0, "Pong\n", 5);
	sleep(1);
	kill(getppid(), SIGUSR2);
}

int main()
{
	struct sigaction sa_child;

	sa_child.sa_handler = &child_sig_handler;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;

	printf("i am child, my pid is %d\n", getpid());

	sigaction(SIGUSR1, &sa_child, NULL);

	while (1);

	return 0;
}
