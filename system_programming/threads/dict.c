#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>

#define AVERAGE_SIZE_OF_WORD (15)
#define NUM_OF_TIMES (1000)
#define NUM_OF_CONSUMERS (40)
#define NUM_OF_LETTERS (26)

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

struct thread_pack_s
{
	size_t *lut_index;
	size_t index;
};

typedef struct thread_pack_s thread_pack_t;


char *CreateDictBuffer();
int MultiplyCopies();
void *CountLetters(void *value);

char *pointer_to_words = NULL;

int main()
{
	size_t i = 0;
	size_t j = 0;
	pthread_t consumers[NUM_OF_CONSUMERS];
	size_t ttl_char_lut[NUM_OF_LETTERS] = {0};

	size_t character_lut[NUM_OF_CONSUMERS][NUM_OF_LETTERS] = {{0, 0}};

	thread_pack_t thread_pack[NUM_OF_CONSUMERS];

	size_t counter_ttl = 0;

	clock_t beginning = clock();

	pointer_to_words = CreateDictBuffer();

	if (pointer_to_words == NULL)
	{
		return 1;
	}

	printf("length of one copy is %lu\n", strlen(pointer_to_words));

	if (MultiplyCopies() != 0)
	{
		return 1;
	}

	printf("length of %d copies is %lu\n", NUM_OF_TIMES, strlen(pointer_to_words));

	beginning = clock();

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{

		/*printf("loop %d\n", i);*/
		thread_pack[i].lut_index = character_lut[i];
		thread_pack[i].index = i;
		pthread_create(&consumers[i], NULL, &CountLetters, &thread_pack[i]);
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		pthread_join(consumers[i], NULL);
	}

	printf(RED"time difference for using %d consumers is %f\n"RESET, NUM_OF_CONSUMERS, (double)(clock() - beginning)/CLOCKS_PER_SEC);

	for (i = 0; i < NUM_OF_LETTERS; ++i)
	{
		for (j = 0; j < NUM_OF_CONSUMERS; ++j)
		{
			ttl_char_lut[i] += character_lut[j][i];
		}
	}

	for (i = 0; i < NUM_OF_LETTERS; ++i)
	{
		printf("%c: %lu\n", 'a' + (int)i, ttl_char_lut[i]);
		counter_ttl += ttl_char_lut[i];
	}

	printf("total amount = %lu\n", counter_ttl);


	free(pointer_to_words);
	return 0;
}

char *CreateDictBuffer()
{
	char *filename = "./words";
	FILE *file = fopen(filename, "r");
	char c = 0;
	size_t line_counter = 0;
	char buffer[50] = {'\0'};
	char *pointer_to_words = NULL;

	if (NULL == file)
	{
		return(NULL);
	}

	fseek(file, 0, SEEK_SET);

	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			++line_counter;
		}
	}

	pointer_to_words = malloc((line_counter) * AVERAGE_SIZE_OF_WORD * sizeof(char));


	/*for (i = 0; i < NUM_OF_TIMES; ++i)
	{*/
		fseek(file, 0, SEEK_SET);
		while (fgets(buffer, sizeof(buffer), file) != NULL)
		{
			buffer[strlen(buffer) - 1] = '\0';
			strcat(pointer_to_words, buffer);
		}

	/*}*/

	fclose(file);

	return (pointer_to_words);
}

int MultiplyCopies()
{
	size_t i = 0;
	size_t length = strlen(pointer_to_words);
	pointer_to_words = realloc(pointer_to_words, NUM_OF_TIMES * length + 1);

	if (NULL == pointer_to_words)
	{
		return 1;
	}

	for (i = 0; i < NUM_OF_TIMES; ++i)
	{
		memcpy(pointer_to_words + i * length, pointer_to_words, length);
	}
	pointer_to_words[length * NUM_OF_TIMES] = '\0';

	return 0;
}

void *CountLetters(void *value)
{
	size_t length = strlen(pointer_to_words);
	size_t chunk = length / NUM_OF_CONSUMERS;
	size_t ind = ((thread_pack_t *)value)->index;
	size_t *lut = ((thread_pack_t *)value)->lut_index;
	size_t beginning = chunk * ind;
	size_t end = beginning + chunk - 1;
	size_t i = 0;

	/*printf("\n\nind=%lu\n", ind);
	printf("length of pointer_to_words at CountLetters is %lu\n", length);*/
	printf("beginning=%lu\nend=%lu\n\n", beginning, end);

	for (i = beginning; i <= end; ++i)
	{
		char c = *(pointer_to_words + i);
		if (isalpha(c))
		{
			/*printf("c-'a'=%d\n", tolower(c) - 'a');*/
			++(*(lut + (tolower(c) - 'a')));
		}
		/*printf("%c", c);*/
	}

	return NULL;
}
