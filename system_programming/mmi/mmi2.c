#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "scheduler.h"
#include "mmi.h"

#define WATCH_DOG_EXECUTABLE_NAME ("./watch_dog")

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

int mmi_counter = 0;

/*******************************************************************************
				STATIC FUNCTIONS DECLARATIONS
*******************************************************************************/

void *keep_user_pcs_alive(void *thread_struct);

int IsWatchDogAlive();

void CreateWatchDog(size_t argc, char **argv, thread_struct_t thread_struct);

/*******************************************************************************
					FUNCTION IMPLEMANTATIONS
*******************************************************************************/

void * MMI(size_t intervals, size_t attempts, size_t argc, char **argv)
{
	pthread_t mmi_thread;

	thread_struct_t thread_struct;

	pid_t watch_dog_pid;

	thread_struct.intervals = intervals;
	thread_struct.attempts = attempts;
	thread_struct.argc = argc;
	thread_struct.argv = argv;
	thread_struct.user_proccess_pid = getpid();


	printf("MMI: user_proccess_pid (what im signaling to and supposed to wake up and is pid)=%d\n", thread_struct.user_proccess_pid);
	printf("MMI: mmi_pid is (getpid) %d\n", getpid());

	if (!IsWatchDogAlive())
	{
		setenv("RUNNER", "user", 1);
		watch_dog_pid = fork();
		if (watch_dog_pid < 0) /* error creating watch_dog pcs */
		{
			printf("error");
			exit(-1);
		}

		if (0 == watch_dog_pid) /* is child */
		{
			printf("MMI: im child and i will be watchdog\n");
			CreateWatchDog(argc, argv, thread_struct);
			/*execvp(argv[0], argv);*/
		}
		else  /* is father */
		{
			printf("MMI: father running as well...\n");
			thread_struct.watch_dog_pid = watch_dog_pid;
			printf("MMI: watchdog pid = %d\n", thread_struct.watch_dog_pid);
			pthread_create (&mmi_thread, NULL, &keep_user_pcs_alive, &thread_struct);
			pthread_join(mmi_thread, NULL);
			/* TODO should i write here something? */
		}
	}
	/*

	*/
}

/*******************************************************************************
				STATIC FUNCTIONS IMPLEMANTATIONS
*******************************************************************************/

int send_signal(void *value) /* Scheduler operating function for MMI */
{
	thread_struct_t thread_struct = *((thread_struct_t *)value);
	int tries = thread_struct.attempts;
	pid_t watch_dog_pid;

	++mmi_counter;
/*
	printf("MMI (send_signal): watch_dog_pid = %d\n", thread_struct.watch_dog_pid);
	printf("MMI (send_signal): counter = %d\n", mmi_counter);
*/
	printf("as MMI (pid=%d) I am sending signal to WD (pid=%d)\n", getpid(), thread_struct.watch_dog_pid);
	kill(thread_struct.watch_dog_pid, SIGUSR1);

	if (mmi_counter >= tries)
	{
		setenv("RUNNER", "user", 0);
		kill(thread_struct.watch_dog_pid, SIGKILL);
		watch_dog_pid = fork();

		if (watch_dog_pid == 0)
		{
			thread_struct.user_proccess_pid = getpid();
			CreateWatchDog(thread_struct.argc, thread_struct.argv, thread_struct);
		}
		else
		{
			thread_struct.watch_dog_pid = watch_dog_pid;
		}
	}

	return 1;
}

void wd_sig_handler(int sig, siginfo_t *siginfo, void *data)
{
	mmi_counter = 0;
	printf("MMI: entered mmi sig_handler\n");
}

void *keep_user_pcs_alive(void *value)
{
	struct sigaction wd;
	sched_t *scheduler = SchedCreate();
	thread_struct_t thread_struct = *((thread_struct_t *)value);

	wd.sa_flags = SA_SIGINFO;
	sigemptyset(&wd.sa_mask);
	wd.sa_sigaction = &wd_sig_handler;

	sigaction(SIGUSR1, &wd, NULL);

	printf("MMI: in keep_user_pcs_alive. watch_dog_pid=%d\n", thread_struct.watch_dog_pid);

	SchedAddTask(scheduler, send_signal, &(thread_struct), thread_struct.intervals);

	SchedRun(scheduler);

/*
	while (1)
	{

	}
*/
	return NULL;
}

int IsWatchDogAlive()
{
	char *env = getenv("RUNNER");
	if (env == NULL)
	{
		return 0;
	}
	else if (strcmp(env, "watch_dog") == 0)
	{
		return 1;
	}

	return 0;
	/*return (NULL != getenv("RUNNER"));*/
}

void CreateWatchDog(size_t argc, char **argv, thread_struct_t thread_struct)
{
	/*char *command[argc + 4] = {NULL};*/
	char **command = calloc(argc + 5, sizeof(char *));	/* argv[0] = watch_dog executable name*/
														/* argv[1 -> argc + 1] = argv */
														/* argv[argc + 2] = intervals */
														/* argv[argc + 3] = attempts */
	int i = 0;
	char intervals[5] = {'\0'};
	char attempts[5] = {'\0'};
	char user_proccess_pid[10] = {'\0'};

	command[0] = malloc(10 * sizeof(char));		/* TODO release malloc! */
	/*command[0] = "watch_dog";*/
	/*printf("MMI: command[0] = %s\n", command[0]);*/
	strcpy(command[0], WATCH_DOG_EXECUTABLE_NAME);
	sprintf(intervals, "%lu", thread_struct.intervals);
	/*itoa(thread_struct.intervals, intervals, 10);*/
	sprintf(attempts, "%lu", thread_struct.attempts);
	sprintf(user_proccess_pid, "%d", getppid());

	command[1] = intervals;
	command[2] = attempts;
	command[3] = user_proccess_pid;
/*
	printf("MMI: command[0] = %s\n", command[0]);
*/
	for (i = 3; i < argc + 3; ++i)
	{
		command[i + 1] = argv[i - 3];
	}

	/*itoa(thread_struct.attempts, attempts, 10);
	itoa(thread_struct.user_proccess_pid, user_proccess_pid, 10);*/


	/*
	for (i = 0; i < argc + 4; ++i)
	{
		printf("MMI: command[%d]=%s\n", i, command[i]);
	}
*/
	printf("MMI: before execvp with command[0]=%s as argument\n", command[0]);
	execvp(command[0], command);
	perror(command[0]);
}

/* COMPILE LINE:
gcc mmi.c ../../ds/scheduler.c ../../ds/UID.c ../../ds/PriorityQueue.c ../../ds/tasks.c ../../ds/sorted_list.c ../../ds/dlist.c -I ../../ds/include/ -lpthread
*/
