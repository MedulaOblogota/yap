#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	while (1)
	{
		printf("hello. I am child pcs, my pid is %d\n", (int)getpid());
		printf("my parent pid is %d\n", (int)getppid());
		sleep(1);

	}
	return (0);
}
