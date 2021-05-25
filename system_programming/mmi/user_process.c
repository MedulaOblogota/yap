#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>

#include "mmi.h"

#define MAX_SIZE (100)

int main(int argc, char *argv[])
{
	void *thread = MMI(2, 5, argc, argv);
	size_t i = 0;

	printf("UP: user_proccess_pid = %d\n", getpid());
	printf("UP: before infinite loop\n");

	printf("hello\n");
	for (i = 0; i < MAX_SIZE; ++i)
	{
		printf("%lu, ", i);
		/*sleep(1);*/
	}
	printf("\n");
	while (1);
	printf("UP: after infinite loop\n");
/*
	 DNR(thread);

	 thread = MMI(2, 5, argc, argv);
	 printf("hello2\n");
	 while(1);

	 for (i = 0; i < MAX_SIZE; ++i)
 	{
 		printf("%lu, ", i + MAX_SIZE);

 	}

	DNR(thread);*/
}
