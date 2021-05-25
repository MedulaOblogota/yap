#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <semaphore.h>

#include "dlist.h"
#include "fsq.h"

#define SIZE_OF_ARRAY (100000)
#define SIZE_OF_MAX_THREADS (32000)
#define PRODUCER_CONSUMER_ARR_SIZE (1)
#define N (100)
#define NUM_OF_THREADS (10)
#define FSQ_SIZE (100000)
#define NUM_OF_THREADS_FSQ (4)
#define NUM_OF_CONSUMERS (10)
#define RANGE (100)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL  "\033[33m"
#define CYN "\x1B[36m"
#define BOLD   "\033[1m\033[30m"

int producer_consumer[PRODUCER_CONSUMER_ARR_SIZE] = {0};

dlist_t *dlist;
fsq_t *fsq;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_production = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_consumption = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_last_question = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

sem_t semaphore_produce;
sem_t semaphore_consume;

sem_t counter;

int is_reading = 0;
int is_writing = 1;

int getvalue = 0;

int is_done = 0;
int flag = 0;
pthread_cond_t cond;

void *ProduceWithFlag(void *value)
{
	while (*(int *)value <= N)
	{
		while (__sync_lock_test_and_set(&is_reading, 1));

		++(*(int *)value);
		printf(GRN"produced %d\n"RESET, *(int *)value);

		__sync_lock_release(&is_writing);
	}

	return(producer_consumer);
}

void *ConsumeWithFlag(void *value)
{
	while (*(int *)value <= N)
	{
		while (__sync_lock_test_and_set(&is_writing, 1));

		printf(RED"consumed %d\n"RESET, *(int *)value);

		__sync_lock_release(&is_reading);
	}

	return(producer_consumer);
}

void *ProduceWithMutex(void *value)
{
	size_t i = 0;

	for (i = *(size_t *)value; i < *(size_t *)value + N/NUM_OF_THREADS; ++i)
	{
		pthread_mutex_lock (&mutex);
		DListPushFront(dlist, (void *)i);
		printf(GRN"produced %d\n"RESET, (int)i);
		pthread_mutex_unlock(&mutex);
	}


	*(int *)value = i;

	return(producer_consumer);
}

void *ConsumeWithMutex(void *value)
{
	size_t data = 0;
	size_t i = 0;

	for (i = *(size_t *)value; i < *(size_t *)value + N/NUM_OF_THREADS; ++i)
	{
		pthread_mutex_lock (&mutex);
		if (DListIsEmpty(dlist))
		{
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		data = (size_t)DListPopBack(dlist);
		printf(RED"consumed %lu\n"RESET, data);
		pthread_mutex_unlock(&mutex);
	}

	return(producer_consumer);
}

void *ProduceWithMutexSemaphore(void *value)
{
	size_t i = 0;


	/*printf("\n\nbefore for loop in produce function:\n*(size_t *)value=%lu\n*(size_t *)value + N/NUM_OF_THREADS=%lu\n\n", *(size_t *)value, *(size_t *)value + N/NUM_OF_THREADS);*/
	for (i = 0; i < N/NUM_OF_THREADS; ++i)
	{
		/*printf("in Produce, before mutex\n");*/

		pthread_mutex_lock (&mutex);

		/*printf("in Produce, after mutex and before push of %lu\n", i);*/

		DListPushFront(dlist, *(size_t **)value);
		printf(GRN"produced %lu\n"RESET, *(size_t *)value);
		*(size_t *)value = *(size_t *)value + 1;

		/*printf("in Produce, after push of %lu\n", i);*/

		/*sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_post (&semaphore);
/*		sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_unlock(&mutex);

/*		printf("in Produce, after mutex unlock\n");*/
	}


	/* *(int *)value = (int)(i - 1);*/
/*	printf(BOLD"value is %d\n"RESET, *(int *)value);*/

	return(value);
}

void *ConsumeWithMutexSemaphore(void *value)
{
	size_t data = 0;
	size_t i = 0;

/*	printf("\n\nbefore for loop in consume function:\n*(size_t *)value=%lu\n*(size_t *)value + N/NUM_OF_THREADS=%lu\n\n", *(size_t *)value, *(size_t *)value + N/NUM_OF_THREADS);*/
	for (i = 0; i < N/NUM_OF_THREADS; ++i)
	{
		/*sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_wait (&semaphore);

/*		sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_lock (&mutex);
/*
		printf("in Consume, after locking mutex\n");
*/
		data = (size_t)DListPopBack(dlist);
/*
		printf("in Consume, after accepting %lu\n", data);*/
		printf(RED"consumed %lu\n"RESET, data);
		/*printf("in Consume, before mutex after accepting %lu\n", data);
*/
		pthread_mutex_unlock(&mutex);

/*		printf("in Consume, after unlocking mutex\n");*/
	}

	return(value);
}

void *ProduceWithFSQOneMutexTwoSemaphore(void *value)
{
	size_t i = 0;
	/*size_t data = 0;*/

	/*printf("in Produce before loop. FSQ_SIZE/NUM_OF_THREADS_FSQ=%lu\n", FSQ_SIZE/NUM_OF_THREADS_FSQ);*/
	for (i = 0; i < FSQ_SIZE/NUM_OF_THREADS_FSQ; ++i)
	{
		/*printf("in Produce, before mutex\n");*/
		sem_wait(&semaphore_produce);
		pthread_mutex_lock (&mutex);

		/*printf("in Produce, after mutex and before push of %d\n", *(int *)value);
*/
		FSQEnqueue(fsq, (int)(*(size_t *)value));
		printf(GRN"produced %d\n"RESET, (int)(*(size_t *)value));
/*		printf("in Produce, after push of %d\n", *(int *)value);*/
		*(int *)value = *(int *)value + 1;


		/*sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_post (&semaphore_consume);
/*		sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_unlock(&mutex);

		/*printf("in Produce, after mutex unlock\n");*/
	}


	/* *(int *)value = (int)(i - 1);*/
/*	printf(BOLD"value is %d\n"RESET, *(int *)value);*/

	return(value);
}

void *ConsumeWithFSQOneMutexTwoSemaphore(void *value)
{
	int data = 0;
	size_t i = 0;

	/*printf("in Consume before loop\n");*/
/*	printf("\n\nbefore for loop in consume function:\n*(size_t *)value=%lu\n*(size_t *)value + N/NUM_OF_THREADS=%lu\n\n", *(size_t *)value, *(size_t *)value + N/NUM_OF_THREADS);*/
	for (i = 0; i < FSQ_SIZE/NUM_OF_THREADS_FSQ; ++i)
	{
		/*sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_wait (&semaphore_consume);

/*		sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_lock (&mutex);

	/*	printf("in Consume, after locking mutex\n");

		printf("FSQIsEmpty=%d\n", FSQIsEmpty(fsq));*/

		data = FSQDequeue(fsq);

		/*printf("in Consume, after accepting %d\n", data);*/
		printf(RED"consumed %d\n"RESET, data);
		/*printf("in Consume, before mutex after accepting %d\n", data);
*/

		sem_post(&semaphore_produce);
		pthread_mutex_unlock(&mutex);
/*
		printf("in Consume, after unlocking mutex\n");*/
	}

	return(value);
}

void *ProduceWithFSQTwoMutexTwoSemaphore(void *value)
{
	size_t i = 0;
	/*size_t data = 0;*/

	/*printf("in Produce before loop. FSQ_SIZE/NUM_OF_THREADS_FSQ=%lu\n", FSQ_SIZE/NUM_OF_THREADS_FSQ);*/
	for (i = 0; i < FSQ_SIZE/NUM_OF_THREADS_FSQ; ++i)
	{
		/*printf("in Produce, before mutex\n");*/
		sem_wait(&semaphore_produce);
		pthread_mutex_lock (&mutex_production);

		/*printf("in Produce, after mutex and before push of %d\n", *(int *)value);
*/
		FSQEnqueue(fsq, (int)(*(size_t *)value));
		printf(GRN"produced %d\n"RESET, (int)(*(size_t *)value));
/*		printf("in Produce, after push of %d\n", *(int *)value);*/
		*(int *)value = *(int *)value + 1;


		/*sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_post (&semaphore_consume);
/*		sem_getvalue(&semaphore, &getvalue);

		printf(CYN"IN Produce, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_unlock(&mutex_production);

		/*printf("in Produce, after mutex unlock\n");*/
	}


	/* *(int *)value = (int)(i - 1);*/
/*	printf(BOLD"value is %d\n"RESET, *(int *)value);*/

	return(value);
}

void *ConsumeWithFSQTwoMutexTwoSemaphore(void *value)
{
	int data = 0;
	size_t i = 0;

	/*printf("in Consume before loop\n");*/
/*	printf("\n\nbefore for loop in consume function:\n*(size_t *)value=%lu\n*(size_t *)value + N/NUM_OF_THREADS=%lu\n\n", *(size_t *)value, *(size_t *)value + N/NUM_OF_THREADS);*/
	for (i = 0; i < FSQ_SIZE/NUM_OF_THREADS_FSQ; ++i)
	{
		/*sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, before SEMAPHORE which is %d\n"RESET, getvalue);
*/
		sem_wait (&semaphore_consume);

/*		sem_getvalue(&semaphore, &getvalue);
		printf(YEL"IN Consume, after SEMAPHORE which is %d\n"RESET, getvalue);
*/
		pthread_mutex_lock (&mutex_consumption);

	/*	printf("in Consume, after locking mutex\n");

		printf("FSQIsEmpty=%d\n", FSQIsEmpty(fsq));*/

		data = FSQDequeue(fsq);

		/*printf("in Consume, after accepting %d\n", data);*/
		printf(RED"consumed %d\n"RESET, data);
		/*printf("in Consume, before mutex after accepting %d\n", data);
*/

		sem_post(&semaphore_produce);
		pthread_mutex_unlock(&mutex_consumption);
/*
		printf("in Consume, after unlocking mutex\n");*/
	}

	return(value);
}

/*
void *ProduceForLastQuestion(void *value)
{
	int data = 0;
	size_t i = 0;

	for (i = 0; i < N/NUM_OF_CONSUMERS; ++i)
	{
		printf(YEL"PRODUCE: before sem_wait\n"RESET);
		sem_wait(&semaphore_last_question);
		printf(YEL"after sem_wait and before mutex lock\n"RESET);
		pthread_mutex_lock (&mutex_last_question);

		is_done = 0;
		printf(YEL"after changing is_done value to 0\n"RESET);
		pthread_cond_broadcast(&cond);
		printf(YEL"after cond__broadcast\n"RESET);
		pthread_mutex_unlock(&mutex_last_question);
		printf(YEL"after mutex unlock\n"RESET);

		printf(RED"produced %d\n"RESET, *(int *)value);
		*(int *)value = *(int *)value + 1;
		printf(YEL"after incrementing value\n"RESET);


	}
	return(value);
}
*/
void *ProduceForLastQuestion(void *value)
{
	size_t i = 0;

	for (i = 0; i < RANGE; ++i)
	{
		sem_wait(&counter);
		pthread_mutex_lock(&mutex_last_question);

		*(int *)value = *(int *)value + 1;
		printf(RED"produced %d\n"RESET, *(int *)value);

		flag = (flag == 0);

		pthread_cond_broadcast(&cond);

		pthread_mutex_unlock(&mutex_last_question);
	}
	return NULL;
}

void *ConsumeForLastQuestion(void *value)
{
	size_t i = 0;
	int local_flag = 0;

	for (i = 0; i < RANGE; ++i)
	{
		pthread_mutex_lock(&mutex_last_question);

		local_flag = flag;
		++*(size_t *)value;

		while (local_flag == flag)
		{
			if (*(size_t *)value == NUM_OF_CONSUMERS)
			{
				*(size_t *)value = 0;
				sem_post(&counter);
			}

			pthread_cond_wait(&cond, &mutex_last_question);
		}

		printf(GRN"consumed %d\n"RESET, *producer_consumer);

		pthread_mutex_unlock(&mutex_last_question);
	}

	return NULL;
}

/*
void *ConsumeForLastQuestion(void *value)
{
	printf(CYN"CONSUME: before locking mutex\n"RESET);
	pthread_mutex_lock(&mutex_last_question);
	printf(CYN"before if on is_done that includes cond_wait\n"RESET);
	if (!is_done)
	{
		pthread_cond_wait(&cond, &mutex_last_question);
	}

	printf(GRN"consumed %d\n"RESET, *(int *)value);

	printf(CYN"before sem_post\n"RESET);
	sem_post(&semaphore_last_question);
	printf(CYN"CONSUME: before unlocking mutex\n"RESET);
	pthread_mutex_unlock(&mutex_last_question);
	printf(CYN"CONSUME: after unlocking mutex\n"RESET);

	return(NULL);
}
*/
/*******************************************************************************
			MAIN METHODS IMPLEMENTATIONS
*******************************************************************************/

void OneProducerOneConsumerFlag()
{
	pthread_t producer;
	pthread_t consumer;

	*producer_consumer = 0;


	pthread_create (&producer, NULL, &ProduceWithFlag, producer_consumer);
	pthread_create (&consumer, NULL, &ConsumeWithFlag, producer_consumer);
	pthread_join (producer, NULL);
	pthread_join(consumer, NULL);


}

void MultiProducerMultiConsumerMutex()
{

	pthread_t producer;
	pthread_t consumer;

	/*pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;*/

	int i = 0;
	dlist = DListCreate();
	*producer_consumer = 1;


	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		printf(BOLD YEL"beginning of loop %d\n"RESET, i + 1);
		/*pthread_mutex_lock (&mutex);*/
		pthread_create (&producer, NULL, &ProduceWithMutex, producer_consumer);
		/*pthread_mutex_unlock (&mutex);*/

		/*pthread_mutex_lock (&mutex);*/
		pthread_create (&consumer, NULL, &ConsumeWithMutex, producer_consumer);
		/*pthread_mutex_unlock (&mutex);*/

		pthread_join (producer, NULL);
		pthread_join(consumer, NULL);
	}

}

void MultiProducerMultiConsumerMutexSemaphore()
{

	pthread_t producer;
	pthread_t consumer;

	int i = 0;
	dlist = DListCreate();
	*producer_consumer = 1;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		/*pthread_mutex_lock (&mutex);*/
	/*	printf(BOLD YEL"beginning of loop %d"RESET, i + 1);*/
		pthread_create (&producer, NULL, &ProduceWithMutexSemaphore, producer_consumer);
		/*printf(BOLD YEL"after produce producer_consumer=%d\n"RESET, *producer_consumer);*/
		/*pthread_mutex_unlock (&mutex);*/

		/*pthread_mutex_lock (&mutex);*/
		pthread_create (&consumer, NULL, &ConsumeWithMutexSemaphore, producer_consumer);
		/*printf(BOLD YEL"after consume producer_consumer=%d\n"RESET, *producer_consumer);*/
		/*pthread_mutex_unlock (&mutex);*/

		pthread_join (producer, NULL);
		pthread_join(consumer, NULL);
	}

}

void FSQOneMutexTwoSemaphore()
{
	pthread_t producer;
	pthread_t consumer;

	int i = 0;
	fsq = FSQCreate(FSQ_SIZE);

	*producer_consumer = 1;

	for (i = 0; i < NUM_OF_THREADS_FSQ; ++i)
	{
		/*pthread_mutex_lock (&mutex);*/
		/*printf(BOLD YEL"beginning of loop %d"RESET, i + 1);*/
		pthread_create (&producer, NULL, &ProduceWithFSQOneMutexTwoSemaphore, producer_consumer);
		/*printf(BOLD YEL"after produce producer_consumer=%d\n"RESET, *producer_consumer);*/

		pthread_create (&consumer, NULL, &ConsumeWithFSQOneMutexTwoSemaphore, producer_consumer);
		/*printf(BOLD YEL"after consume producer_consumer=%d\n"RESET, *producer_consumer);*/


		pthread_join (producer, NULL);
		pthread_join(consumer, NULL);
	}
}

void FSQTwoMutexTwoSemaphore()
{
	pthread_t producer;
	pthread_t consumer;

	int i = 0;
	fsq = FSQCreate(FSQ_SIZE);

	*producer_consumer = 1;

	for (i = 0; i < NUM_OF_THREADS_FSQ; ++i)
	{
		/*pthread_mutex_lock (&mutex);*/
		/*printf(BOLD YEL"beginning of loop %d"RESET, i + 1);*/
		pthread_create (&producer, NULL, &ProduceWithFSQTwoMutexTwoSemaphore, producer_consumer);
		/*printf(BOLD YEL"after produce producer_consumer=%d\n"RESET, *producer_consumer);*/

		pthread_create (&consumer, NULL, &ConsumeWithFSQTwoMutexTwoSemaphore, producer_consumer);
		/*printf(BOLD YEL"after consume producer_consumer=%d\n"RESET, *producer_consumer);*/


		pthread_join (producer, NULL);
		pthread_join(consumer, NULL);
	}
}

void OneProducerMultiConsumerLastQuestion()
{
	pthread_t producer;
	pthread_t consumer[NUM_OF_CONSUMERS];

	int i = 0;
	size_t curr_num_of_consumers = 0;

	*producer_consumer = 0;

	pthread_cond_init (&cond, NULL);
	sem_init(&counter, 0, 0);

	pthread_create (&producer, NULL, &ProduceForLastQuestion, producer_consumer);
	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		/*pthread_mutex_lock (&mutex);*/
		printf(BOLD YEL"beginning of loop %d\n"RESET, i + 1);
		/*printf(BOLD YEL"after produce producer_consumer=%d\n"RESET, *producer_consumer);*/

		pthread_create (&consumer[i], NULL, &ConsumeForLastQuestion, &curr_num_of_consumers);
		/*printf(BOLD YEL"after consume producer_consumer=%d\n"RESET, *producer_consumer);*/
	}

	pthread_join (producer, NULL);

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		pthread_join(consumer[i], NULL);
	}
}

int main(int argc, char *argv[])
{
	int option = 0;

	if (argc == 1)
	{
		printf(BOLD RED"be reasonable!!!!\n"RESET);
		return (1);
	}

	option = atoi(argv[1]);
	sem_init (&semaphore, 0, 0);
	sem_init(&semaphore_consume, 0, 0);
	sem_init(&semaphore_produce, 0, FSQ_SIZE);

	switch (option)
	{
		case 1:			/* 1 producer, 1 consumer while using a flag. doesn't work well enough */
			OneProducerOneConsumerFlag();
			break;
		case 2:			/* multi producer, multi consumer while using Mutex with dlist. should work */
			MultiProducerMultiConsumerMutex();
			break;
		case 3:			/* multi producer, multi consumer while using Mutex & semaphore with dlist. should work */
			MultiProducerMultiConsumerMutexSemaphore();
			break;
		case 4:			/* multi producer, multi consumer while using FSQ with 1 mutex and 2 semaphores */
			FSQOneMutexTwoSemaphore();
			break;
		case 5:			/* multi producer, multi consumer while using FSQ with 2 mutex and 2 semaphores */
			FSQTwoMutexTwoSemaphore();
			break;
		case 6:			/* 1 producer, multi consumer while using single-item int. 1 semaphore, 1 CV and 1 mutex */
			OneProducerMultiConsumerLastQuestion();
			break;
		default:
			printf("no reasonable option inserted!!!\n");
			break;

	}

	return (0);

}


/*
IN CODE:
0. 	counter = 0
	is_done = 0
1. producer:
	*run RANGE value times doing:
		*lock mutex
		*while (counter != 0) {wait}
		*define counter = 0
		*is_done = 0
		*produce
		*broadcast
		*define is_done=1
		*unlock mutex

2. consumer:
	*run RANGE value times doing:
		*lock mutex
		*while (!is_done) wait
		*consume
		*increment counter
		*unlock mutex
		*/
