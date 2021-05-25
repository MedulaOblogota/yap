#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#include "dlist.h"

#define SIZE_OF_ARRAY (100000)
#define SIZE_OF_MAX_THREADS (32000)
#define PRODUCER_CONSUMER_ARR_SIZE (1)
#define N (100000)
#define NUM_OF_THREADS (100)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL  "\033[33m"
#define BOLD   "\033[1m\033[30m"

int arr[SIZE_OF_ARRAY] = {0};
int arr2[SIZE_OF_MAX_THREADS] = {0};
int producer_consumer[PRODUCER_CONSUMER_ARR_SIZE] = {0};
dlist_t *dlist;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int is_reading = 0;
int is_writing = 1;

void *InsertToArray(void *value)
{
	*(int *)(arr + *(int *)value) = *(int *)value + 1;

	return((arr));
}

void *InsertToSmallerArray(void *value)
{
	int i = 0;
	int counter = 0;

	for (i = 1; i <= *(int *)value; ++i)
	{
		if ((*(int *)value % i) == 0)
		{
			counter += i;
		}
	}
	*(int *)(arr2 + *(int *)value) = counter;

	return((arr2));
}

void *InsertToSmallerArrayMinAndMax(void *min_and_max)
{
	int min = *(int *)min_and_max;
	int max = *(int *)((int *)min_and_max + 1);
	int i = min;
	int counter = 0;

	printf("\nin function: min=%d\nmax=%d\n", min, max);
	for (i = min; i < max; ++i)
	{
		int j = 0;
		for (j = 1; j <= i; ++j)
		{
			if (i % j == 0)
			{
				counter += j;
			}
		}
		*(int *)(arr2 + i) = counter;
		counter = 0;
	}

	return((arr2));
}

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
	/*	++(*(int *)value);*/
	}


	*(int *)value = i;
	/*while (*(int *)value <= N)
	{
		while (__sync_lock_test_and_set(&is_reading, 1));


		__sync_lock_release(&is_writing);
	}
*/
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


/*	while (*(int *)value <= N)
	{
		while (__sync_lock_test_and_set(&is_writing, 1));


		__sync_lock_release(&is_reading);
	}*/

	return(producer_consumer);
}

void problem1()
{
	pthread_t thread;
	int i = 0;

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		pthread_create (&thread, NULL, &InsertToArray, &i);
	}

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		printf("%d, ", arr[i]);
	}


	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		if (arr[i] != (i+1))
		{
			printf("FAIL!!! (at %d)\n", i+1);
			break;
		}
	}
}

void problem2()
{
	pthread_t thread;
	int i = 0;

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		pthread_create (&thread, NULL, &InsertToArray, &i);
	}

	sleep(10);

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		printf("%d, ", arr[i]);
	}


	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		if (arr[i] != (i+1))
		{
			printf("FAIL!!! (at %d)\n", i+1);
			break;
		}
	}
}

void problem3()
{
	pthread_t thread;
	pthread_attr_t attribute;
	int i = 0;

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		pthread_attr_init(&attribute);
		pthread_attr_setdetachstate(&attribute,PTHREAD_CREATE_DETACHED);
		pthread_create (&thread, &attribute, &InsertToArray, &i);
		/*pthread_cancel(thread);*/
	}

	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		printf("%d, ", arr[i]);
	}


	for (i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		if (arr[i] != (i+1))
		{
			printf("FAIL!!! (at %d)\n", i+1);
			break;
		}
	}
}

void problem4()
{
	pthread_t thread;
	int i = 0;
	size_t sum = 0;

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		pthread_create (&thread, NULL, &InsertToSmallerArray, &i);
		/*pthread_cancel(thread);*/
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		/*printf("%d, ", arr2[i]);*/
		sum += arr2[i];
	}

	printf("sum=%lu\n", sum);

}

void problem5()
{
	int i = 0;
	size_t sum = 0;

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		InsertToSmallerArray(&i);
		/*pthread_cancel(thread);*/
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		/*printf("%d, ", arr2[i]);*/
		sum += arr2[i];
	}

	printf("sum=%lu\n", sum);

}

void problem6()
{
	pthread_t thread;
	int i = 0;
	int min_and_max[2] = {0};
	size_t sum = 0;

	for (i = 0; i < 10; ++i)
	{
		min_and_max[0] = i * 3200;
		min_and_max[1] = i * 3200 + 3200;

		pthread_create (&thread, NULL, &InsertToSmallerArrayMinAndMax, &min_and_max[0]);
		pthread_join (thread, NULL);
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		printf("%d, ", arr2[i]);
	}


	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		if (arr2[i] != (i+1))
		{
			printf("FAIL!!! (at %d)\n", i+1);
			break;
		}
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		/*printf("%d, ", arr2[i]);*/
		sum += arr2[i];
	}

	printf("sum=%lu\n", sum);
}

void problem7()
{
	int th_id;
	int i = 0;
	size_t sum = 0;

	#pragma omp parallel private(th_id)
	{
		int min_and_max[2] = {0};
		th_id = omp_get_thread_num();

		min_and_max[0] = th_id * 3200;
		min_and_max[1] = th_id * 3200 + 3200;

		printf("\n%d. min = %d. max = %d\n", th_id, min_and_max[0], min_and_max[1]);

		InsertToSmallerArrayMinAndMax(&min_and_max[0]);
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		printf("%d, ", arr2[i]);
	}


	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		if (arr2[i] != (i+1))
		{
			printf(RED"FAIL!!! (at %d)\n"RESET, i+1);
			break;
		}
	}

	for (i = 0; i < SIZE_OF_MAX_THREADS; ++i)
	{
		/*printf("%d, ", arr2[i]);*/
		sum += arr2[i];
	}

	printf("sum=%lu\n", sum);
}

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

int main(int argc, char *argv[])
{
	int option = 0;

	if (argc == 1)
	{
		printf(RED"no value entered!\n"RESET);
		return (1);
	}

	option = atoi(argv[1]);

	switch (option)
	{
		case 1:			/* 100000 items without detachment or join */
			problem1();
			break;
		case 2:			/* 100000 items without detachment but with sleep */
			problem2();
			break;
		case 3:			/* 100000 items with detachment */
			problem3();
			break;
		case 4:			/* 32000 items, summing up each item's dividers, no detachment */
			problem4();
			break;
		case 5:			/* 32000 items, single thread */
			problem5();
			break;
		case 6:			/* 32000 items, 10 threads */
			problem6();
			break;
		case 7:			/* using openmp & pragma */
			problem7();
			break;
		case 8:			/* 1 producer, 1 consumer while using a flag. doesn't work well enough */
			OneProducerOneConsumerFlag();
			break;
		case 9:			/* 1 producer, 1 consumer while using Mutex. should work */
			MultiProducerMultiConsumerMutex();
			break;
		default:
			printf("no reasonable option inserted!!!\n");
			break;
	}

	return (0);

}
