#include <pthread.h>  //mutex
#include <iostream>		//cout

#include "scoped_lock.hpp"
#include "threads.hpp"

pthread_mutex_t producer_mutex;// = PTHREAD_MUTEX_INITIALIZER;
int num = 0;

void lock(pthread_mutex_t& val)
{
	pthread_mutex_lock(&val);
}

// void sem_lock()

void unlock(pthread_mutex_t& val)
{
	pthread_mutex_unlock(&val);
}

void *Producer(void *);
void *Consumer(void *);

int main()
{
	pthread_t producer;
	pthread_t consumer;

	pthread_create(&producer, NULL, &Producer, NULL);
	pthread_create(&consumer, NULL, &Consumer, NULL);
	// ScopedLock<pthread_mutex_t, &lock, &unlock> scoped_lock(producer_mutex);
	// ScopedLock<pthread_mutex_t, &lock, &unlock> scoped_lock(consumer_mutex);
	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	// Producer();
	// Consumer();

	return 0;
}

void *Producer(void *val)
{
	for (int i = 0; i < 20; ++i)
	{
		{
			ScopedLock<pthread_mutex_t, &lock, &unlock> scoped_lock(producer_mutex);

			++num;
			std::cout << "PRODUCED " << num << std::endl;
		}
	}
}

void * Consumer(void *val)
{
	for (int i = 0; i < 20; ++i)
	{
		{
			ScopedLock<pthread_mutex_t, &lock, &unlock> scoped_lock(producer_mutex);

			std::cout << "consumed " << num << std::endl;
		}
	}
}
