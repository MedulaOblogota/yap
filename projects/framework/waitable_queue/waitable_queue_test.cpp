#include <iostream>
#include <cstdio>

#include "waitable_queue.hpp"

#define NUM_OF_THREADS (10)
#define RANGE (100)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL  "\033[33m"
#define CYN "\x1B[36m"
#define BOLD   "\033[1m\033[30m"

WaitableQueue<int> wq;
pthread_mutex_t mutex;
sem_t semaphore;
int producer_consumer[1] = {0};

void *ProduceForLastQuestion(void *value)
{
    ++(*(int *)value);
    wq.Push(*(int *)value);

    printf(GRN"produced %d\n"RESET, *(int *)value);
}

void *ConsumeForLastQuestion(void *value)
{
	
    int val = wq.Pop();
    // wq.Pop();
    
    printf(RED"consumed %d\n"RESET, val);
	return NULL;
}

int main()
{

	pthread_t producer;
	pthread_t consumer;

	int i = 0;

	*producer_consumer = 0;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		
		pthread_create (&producer, NULL, &ProduceForLastQuestion, producer_consumer);
		
		pthread_create (&consumer, NULL, &ConsumeForLastQuestion, producer_consumer);
		

		pthread_join (producer, NULL);
		pthread_join(consumer, NULL);
	}

}