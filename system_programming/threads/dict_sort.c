#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>

#include "sorting.h"

#define AVERAGE_SIZE_OF_WORD (15)
#define NUM_OF_TIMES (10)
#define NUM_OF_CONSUMERS (10)
#define NUM_OF_LETTERS (26)
#define NUM_OF_TIMES_TO_RANDOMIZE (10)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

struct thread_pack_s
{
	size_t chunk;
	size_t index;
};

typedef struct thread_pack_s thread_pack_t;

char **CreateDictBuffer();
int MultiplyCopies(size_t line_counter);
void PrintToFile(size_t line_counter);
void PrintToFile2(size_t line_counter);
void PrintToFile3(size_t line_counter);

int randomize_words(const void *first, const void *second);
void MessUpString(size_t line_counter);

void *MergePart(void *value);
int sort_words(void *val1, void *val2);

char **pointer_to_words = NULL;

int main()
{
	size_t i = 0;
	size_t j = 0;
	size_t line_counter = 0;

	pthread_t consumers[NUM_OF_CONSUMERS];
	thread_pack_t thread_pack[NUM_OF_CONSUMERS];

	pointer_to_words = CreateDictBuffer(&line_counter);

	if (pointer_to_words == NULL)
	{
		return 1;
	}

	if (MultiplyCopies(line_counter) != 0)
	{
		return 1;
	}

	/*printf("length of %d copies is %lu\n", NUM_OF_TIMES, strlen(pointer_to_words));*/

	MessUpString(line_counter);
	PrintToFile(line_counter);

	thread_pack[0].chunk = line_counter * NUM_OF_TIMES;
	thread_pack[0].index = 0;

/*	MergePart(&thread_pack[0]);*/
	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		thread_pack[i].chunk = line_counter * NUM_OF_TIMES / NUM_OF_CONSUMERS;
		thread_pack[i].index = i;

		pthread_create(&consumers[i], NULL, &MergePart, &thread_pack[i]);
	}
	PrintToFile2(line_counter);

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		pthread_join(consumers[i], NULL);

	}

	thread_pack[0].chunk = line_counter * NUM_OF_TIMES;
	thread_pack[0].index = 0;
	MergePart(&thread_pack[0]);

	PrintToFile3(line_counter);


	return 0;
}

char **CreateDictBuffer(size_t *line_counter)
{
	char *filename = "./words";
	FILE *file = fopen(filename, "r");
	char c = 0;
	size_t counter = 0;
	char buffer[50] = {'\0'};

	if (NULL == file)
	{
		return(NULL);
	}

	fseek(file, 0, SEEK_SET);

	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			++(*line_counter);
		}
	}

	pointer_to_words = malloc((*line_counter) * sizeof(char **));


	/*for (i = 0; i < NUM_OF_TIMES; ++i)
	{*/
		fseek(file, 0, SEEK_SET);
		while (fgets(buffer, sizeof(buffer), file) != NULL)
		{
			/*buffer[strlen(buffer) - 1] = '\0';
			strcat(pointer_to_words, buffer);*/
			*(pointer_to_words + counter) = malloc(strlen(buffer) * sizeof(char *) + 1);
			strcat(*(pointer_to_words + counter), buffer);
			++counter;
		}

	/*}*/

	fclose(file);

	return (pointer_to_words);
}

int MultiplyCopies(size_t line_counter)
{
	size_t i = 0;
	/*size_t length = strlen(pointer_to_words);*/
	pointer_to_words = realloc(pointer_to_words, NUM_OF_TIMES * line_counter * sizeof(char **));

	if (NULL == pointer_to_words)
	{
		return 1;
	}

	for (i = 1; i < NUM_OF_TIMES; ++i)
	{
		memcpy((pointer_to_words + i * line_counter), pointer_to_words, line_counter * sizeof(char **));
	}
	/*pointer_to_words[length * NUM_OF_TIMES] = '\0';*/

	return 0;
}

void PrintToFile(size_t line_counter)
{
	size_t i = 0;
	FILE *file = fopen("temp", "w+");

	for (i = 0; i < (line_counter * NUM_OF_TIMES); ++i)
	{
		fputs(*(pointer_to_words + i), file);
	}

	fclose(file);
}

void PrintToFile2(size_t line_counter)
{
	size_t i = 0;
	FILE *file = fopen("temp2", "w+");

	for (i = 0; i < (line_counter * NUM_OF_TIMES); ++i)
	{
		fputs(*(pointer_to_words + i), file);
	}

	fclose(file);
}

void PrintToFile3(size_t line_counter)
{
	size_t i = 0;
	FILE *file = fopen("temp3", "w+");

	for (i = 0; i < (line_counter * NUM_OF_TIMES); ++i)
	{
		fputs(*(pointer_to_words + i), file);
	}

	fclose(file);
}
int randomize_words(const void *first, const void *second)
{
	int random = rand() % 2;

	return (random == 1 ? 1 : -1);
}

void MessUpString(size_t line_counter)
{
	size_t i = 0;

	for (i = 0; i < NUM_OF_TIMES_TO_RANDOMIZE; ++i)
	{
		qsort(pointer_to_words, NUM_OF_TIMES * line_counter, sizeof(char *), randomize_words);
	}
}

void *MergePart(void *value)
{
	size_t chunk = ((thread_pack_t *)value)->chunk;
	size_t index = ((thread_pack_t *)value)->index;

	size_t i = 0;

	printf("beginning index = %lu\nchunk = %lu\n", index * chunk, chunk);

	MergeSort(pointer_to_words + index * chunk, chunk, sizeof(char **), sort_words);

	return NULL;
}

int sort_words(void *val1, void *val2)
{
	/*char *str1 = *(char **)val1;
	char *str2 = *(char **)val2;
*/
	if (val1 == NULL)
	{
		return 1;
	}
	if (val2 == NULL)
	{
		return -1;
	}

	return(strcasecmp(*(char **)val1, *(char **)val2));
}
