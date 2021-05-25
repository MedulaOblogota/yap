#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "scheduler.h"

#define USER_PROCESS_EXECUTABLE_NAME ("./a.out")

/*******************************************************************************
				VARIABLE AND TYPEDEF DECLARATIONS
*******************************************************************************/

typedef struct thread_struct_s thread_struct_t;

struct thread_struct_s
{
	size_t intervals;
	size_t attempts;
	size_t argc;
	pid_t user_proccess_pid;
	pid_t watch_dog_pid;
	char **argv;
};

int counter = 0;
int waiting_for_creation = 0;

/*******************************************************************************
				STATIC FUNCTIONS DECLARATIONS
*******************************************************************************/

int send_signal_to_mmi(void *value);

void thread_handler(int sig, siginfo_t *siginfo, void *data);

void CreateUP(size_t argc, char **argv, thread_struct_t thread_struct);

void *watch_dog(void *value);


/*******************************************************************************
					FUNCTION IMPLEMANTATIONS
*******************************************************************************/

int main(int argc, char *argv[])
{
	pthread_t wd_thread;

	thread_struct_t thread_struct;

	pid_t mmi_pid;

	char *watch_dog_name = argv[0];
	/*int intervals = atoi(argv[argc + 2]);
	int attempts = atoi(argv[argc + 3]);*/

	thread_struct.intervals = atoi(argv[1]);
	thread_struct.attempts = atoi(argv[2]);
	thread_struct.user_proccess_pid = atoi(argv[3]);
	printf("WD (main): thread_struct.user_proccess_pid %d\n", thread_struct.user_proccess_pid);
	printf("WD: argc = %d\n", argc);
	printf("WD: i am watchdog. my pid is %d\nintervals=%lu. attempts=%lu\n", getpid(), thread_struct.intervals, thread_struct.attempts);
	printf("WD: as watchdog my ppid is %d\n", getppid());

	watch_dog(&thread_struct);

}

void *watch_dog(void *value)
{
	struct sigaction up;
	sched_t *scheduler = SchedCreate();
	thread_struct_t thread_struct = *((thread_struct_t *)value);

	up.sa_flags = SA_SIGINFO;
	sigemptyset(&up.sa_mask);
	up.sa_sigaction = &thread_handler;

	printf("WD: watch_dog_pid is %d\n", getpid());

	sigaction(SIGUSR1, &up, NULL);

	SchedAddTask(scheduler, send_signal_to_mmi, &(thread_struct), thread_struct.intervals);

	SchedRun(scheduler);

/*
	while (1)
	{

	}
*/
	return NULL;
}

/*******************************************************************************
				STATIC FUNCTIONS IMPLEMANTATIONS
*******************************************************************************/

int send_signal_to_mmi(void *value) /* Scheduler operating function */
{
	thread_struct_t thread_struct = *((thread_struct_t *)value);
	int tries = thread_struct.attempts;
	pid_t user_proccess_pid;

	++counter;
	/*printf("WD (send_signal_to_mmi): thread_struct.user_proccess_pid %d\n", thread_struct.user_proccess_pid);
	printf("WD (send_signal_to_mmi): counter = %d\n", counter);
*/
	printf("as WD (pid=%d) I am sending signal to MMI (pid=%d)\n", getpid(), thread_struct.user_proccess_pid);
	printf("WD: tries=%d. 	counter = %d\n", tries, counter);
	kill(thread_struct.user_proccess_pid, SIGUSR1);

	if (counter >= tries)
	{
		/* remove envp and set envp to something else */
		setenv("RUNNER", "watch_dog", 1);
		printf("WD: entered here\n");
		waiting_for_creation = 1;

		kill(thread_struct.user_proccess_pid, SIGKILL);

		user_proccess_pid = fork();

		if (user_proccess_pid == 0)
		{
			thread_struct.watch_dog_pid = getpid();
			printf("WD: ***i am child\n");
			CreateUP(thread_struct.argc, thread_struct.argv, thread_struct);
		}
		else
		{
			printf("WD: ***i am parent\n");
			thread_struct.user_proccess_pid = user_proccess_pid;
			while(waiting_for_creation);
			setenv("RUNNER", "user", 1);
		}


	}

	return 1;
}

void thread_handler(int sig, siginfo_t *siginfo, void *data)
{
	counter = 0;
	waiting_for_creation = 0;
	printf("WD: entered watchdog sig_handler\n");
}

void CreateUP(size_t argc, char **argv, thread_struct_t thread_struct)
{
	char **command = calloc(argc + 5, sizeof(char *));

	int i = 0;
	char intervals[5] = {'\0'};
	char attempts[5] = {'\0'};
	char watch_dog_pid[10] = {'\0'};

	command[0] = calloc(10, sizeof(char));


	strcpy(command[0], "./a.out");
	printf("WD: creating UP!\n");

	sprintf(intervals, "%lu", thread_struct.intervals);
	/*itoa(thread_struct.intervals, intervals, 10);*/
	sprintf(attempts, "%lu", thread_struct.attempts);
	sprintf(watch_dog_pid, "%d", getpid());

	command[1] = intervals;
	command[2] = attempts;
	command[3] = watch_dog_pid;

	for (i = 3; i < argc + 3; ++i)
	{
		command[i + 1] = argv[i - 3];
	}

	for (i = 0; i < argc + 4; ++i)
	{
		printf("WD: command[%d]=%s\n", i, command[i]);
	}

	execvp(command[0], command);
	perror("execvp");
}
