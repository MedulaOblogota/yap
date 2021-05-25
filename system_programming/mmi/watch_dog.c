#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "scheduler.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

#define USER_PROCESS_EXECUTABLE_NAME ("./a.out")

/*******************************************************************************
				GLOBAL VARIABLE AND TYPEDEF DECLARATIONS
*******************************************************************************/

typedef struct thread_struct_s thread_struct_t;

struct thread_struct_s
{
	size_t intervals;
	size_t attempts;
	size_t argc;
	char **argv;
};

int wd_counter = 0;
pid_t up_pid;
int dnr_flag_on = 0;

/*******************************************************************************
				STATIC FUNCTIONS DECLARATIONS
*******************************************************************************/

int send_signal_to_mmi(void *value);

void thread_handler(int sig, siginfo_t *siginfo, void *data);

void CreateUP(size_t argc, char **argv, thread_struct_t thread_struct);

void *watch_dog(void *value);

int close_sched(void *value);

void close_sched_on_mmi(int sig, siginfo_t *siginfo, void *data);


/*******************************************************************************
					FUNCTION IMPLEMANTATIONS
*******************************************************************************/

int main(int argc, char *argv[])
{
	pthread_t wd_thread;

	thread_struct_t thread_struct;

	struct sigaction dnr;

	dnr.sa_flags = SA_SIGINFO;
	sigemptyset(&dnr.sa_mask);
	dnr.sa_sigaction = &close_sched_on_mmi;

	sigaction(SIGUSR2, &dnr, NULL);

	up_pid = getppid();

	thread_struct.intervals = atoi(argv[0]);
	thread_struct.attempts = atoi(argv[1]);
	thread_struct.argv = argv;
	thread_struct.argc = argc;

	watch_dog(&thread_struct);
}

void *watch_dog(void *value)
{
	struct sigaction up;
	sched_t *scheduler = SchedCreate();
	thread_struct_t thread_struct = *((thread_struct_t *)value);
	sem_t *wd_sem = sem_open("/wd_sem", O_CREAT,
                       S_IRWXU, 0);
	sem_t *mmi_sem = sem_open("/mmi_sem", O_CREAT,
                       S_IRWXU, 0);

	up.sa_flags = SA_SIGINFO;
	sigemptyset(&up.sa_mask);
	up.sa_sigaction = &thread_handler;

	sigaction(SIGUSR1, &up, NULL);

	SchedAddTask(scheduler, send_signal_to_mmi, &(thread_struct), thread_struct.intervals);
	SchedAddTask(scheduler, close_sched, (void *)scheduler, 1);

	sem_post(mmi_sem);
	sem_wait(wd_sem);

	SchedRun(scheduler);

	sem_close(mmi_sem);
	sem_close(wd_sem);

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

	++wd_counter;

 	printf(RED"as WD (pid=%d) I am sending signal to MMI (pid=%d)\n"RESET, getpid(), up_pid);

	kill(up_pid, SIGUSR1);

	if (wd_counter == tries)
	{
		unsetenv("RUNNER");
		setenv("RUNNER", "watch_dog", 1);
		wd_counter = 0;

		kill(up_pid, SIGKILL);

		user_proccess_pid = fork();

		if (user_proccess_pid == 0)
		{
			CreateUP(thread_struct.argc, thread_struct.argv, thread_struct);
		}
		else
		{
			up_pid = user_proccess_pid;
		}
	}

	return 1;
}

void thread_handler(int sig, siginfo_t *siginfo, void *data)
{
	wd_counter = 0;
}

void CreateUP(size_t argc, char **argv, thread_struct_t thread_struct)
{
	int i = 0;

	setenv("RUNNER", "watch_dog", 1);
	execvp(argv[argc - 1], argv);
	perror("execvp");
}

int close_sched(void *value)
{
	sched_t *scheduler = (sched_t *)value;

	if (dnr_flag_on)
	{
		printf(RED"WD: entered close_sched condirtion (flag is on! which is good)\n"RESET);
		unsetenv("RUNNER");
		SchedStop(scheduler);
		SchedDestroy(scheduler);
	}

	return 1;
}

void close_sched_on_mmi(int sig, siginfo_t *siginfo, void *data)
{
	dnr_flag_on = 1;
}
