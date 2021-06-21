#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <semaphore.h>

#define BIG 1000000000UL
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t producer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consumer_lock = PTHREAD_MUTEX_INITIALIZER;

sem_t sem;

void* myturn(void *arg)
{
  int *iptr = (int *)arg;
  int *tptr = malloc(sizeof(int));

  *tptr = 5;
  for (int i = 0; i < 8; ++i)
  {
    sleep(1);
    printf("My Turn! v=%d\n", *iptr);
    ++(*iptr);
    ++(*tptr);
  }

  return tptr;
}

void yourturn()
{
  for (int i = 0; i < 3; ++i)
  {
    sleep(1);
    printf("Your Turn! %d\n", i);
  }
}

void *count_to_big(void *arg)
{
  for (uint32_t i = 0; i < BIG; ++i)
  {
    pthread_mutex_lock(&lock);
    ++counter;
    pthread_mutex_unlock(&lock);
  }

  return NULL;
}

void *Produce(void *arg)
{
  while (1)
  {
    sleep(1);
    pthread_mutex_lock(&producer_lock);
    ++counter;
    printf(GRN"produced %d\n"RESET, counter);
    sem_post(&sem);
    pthread_mutex_unlock(&consumer_lock);
  }
}

void *Consume(void *arg)
{
  while (1)
  {
  //  sleep(1);
    sem_wait(&sem);
    pthread_mutex_lock(&consumer_lock);
    printf(RED"consumed %d\n"RESET, counter);
    pthread_mutex_unlock(&producer_lock);
  }
}

int main()
{
  pthread_t producer[10];
  pthread_t consumer[10];

  sem_init(&sem, 0, 0);

  for (int i = 0; i < 10; ++i)
    pthread_create(&consumer[i], NULL, Consume, NULL);
  for (int i = 0; i < 10; ++i)
    pthread_create(&producer[i], NULL, Produce, NULL);
  // int v = 0;
  // int *var;
  //
  // pthread_create(&thread, NULL, myturn, &v);
  //
  // yourturn();
  //
  // pthread_join(thread, (void*)&var);
  //
  // printf("thread's done, v=%d. var=%d\n", v, *var);

  // pthread_create(&thread, NULL, count_to_big, NULL);
  // count_to_big(NULL);
  // pthread_join(thread, NULL);
  // printf("%d\n", counter);

  for (int i = 0; i < 10; ++i)
    pthread_join(producer[i], NULL);
  for (int i = 0; i < 10; ++i)
    pthread_join(consumer[i], NULL);
}
