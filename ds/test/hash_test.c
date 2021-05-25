#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "dlist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

size_t hash_func(const void *data_key)
{
	char *data = (char *)data_key;
	size_t i = 0;
	size_t sum = 0;

	for (i = 0; i < strlen(data); ++i)
	{
		sum += data[i];
	}
	return sum % 100;
}

int comp_func(const void *data1, const void *data2)
{
	return (!strcmp((char *)data1, (char *)data2));
}

int action_func(void *data, void *param)
{
	if (strcmp((char *)data, "zombie's") == 0)
	{
		printf(GRN"MAN!!!! GREAT F'ING JOB!!\n"RESET);
		return 0;
	}
	return 1;
}

void FreeMalloc(char **pointer_to_words, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		free(pointer_to_words[i]);
	}

	free(pointer_to_words);
}

int main(int argc, char *argv[], char **envp)
{
	hash_t *hash = HashCreate(100, hash_func, comp_func);
	int i = 0;
	char *filename = "./words";
	FILE *file = fopen(filename, "r");
	char buffer[20];
	char **pointer_to_words = NULL;
	char c = 0;
	size_t line_counter = 0;

	size_t counter = 0;

	char *word = "isolates";

	printf("argc = %d\n", argc);

	if (file == NULL)
	{
		printf("baaad\n");
	}
	fseek(file, 0, SEEK_SET);

	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			++line_counter;
		}
	}

	if (HashIsEmpty(hash) != 1)
	{
		printf(RED"FAILURE WITH HashIsEmpty!!!\n"RESET );
	}
	else
	{
		printf(GRN"SUCCESS with HashIsEmpty\n"RESET);
	}

	pointer_to_words = malloc((line_counter + 500) * sizeof(char *));


	counter = 0;

	fseek(file, 0, SEEK_SET);

	while (fscanf(file, "%s", buffer) != EOF)
	/*for (i = 0; i < line_counter; ++i)*/
	{
	/*	fscanf(file, "%s", buffer);*/
		/*printf("buffer=%s\n", buffer);*/

		pointer_to_words[counter] = malloc(strlen(buffer) + 1);
		memcpy(pointer_to_words[counter], buffer, (strlen(buffer) + 1));
		/*printf("strlen() is %lu\n", strlen(buffer));*/

		if (HashInsert(hash, pointer_to_words[counter]) == 0)
		{
			printf("damn!\n");
			break;
		};
		++counter;
	}

	/*FreeMalloc(pointer_to_words, line_counter + 500);*/

	/*printf("%lu\n", counter);
	printf("hash size is %lu\n", HashSize(hash));
	printf("HashFind for A is %s\n", (char *)HashFind(hash, word));*/

	if (HashSize(hash) != counter)
	{
		printf(RED"FAILURE WITH HashSize!!!\n"RESET );
	}
	else
	{
		printf(GRN"SUCCESS with HashSize\n"RESET);
	}

	if (HashFind(hash, "kjhgflksahg") == NULL)
	{
		printf(GRN"great success with finding item that doesn't exist!\n"RESET);
	}
	else
	{
		printf(RED"FAILURE with finding item that doesn't exist!!!\n"RESET);
	}

	if (strcmp((char *)HashRemove(hash, "A"), "A") == 0)
	{
		printf(GRN"great success with removing item that exists!\n"RESET);
	}
	else
	{
		printf(RED"great failure with removing item that exists!\n"RESET);
	}

	if (HashRemove(hash, "dsagfsagag") == NULL)
	{
		printf(GRN"great success with removing item that doesnt exist!\n"RESET);
	}
	else
	{
		printf(RED"great failure with removing item that doesnt exist!\n"RESET);
	}

	HashForEach(hash, action_func, NULL);

	HashDestroy(hash);
	FreeMalloc(pointer_to_words, counter);
	fclose(file);

	return (0);
}
