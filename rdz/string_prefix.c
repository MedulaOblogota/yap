#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IndexExists(int *letters, int *instances, int index, int required)
{
  int temp = letters[index];
  int i = 0;

  for (i = 0; i < instances[index] - 1; ++i)
  {
    temp = temp / 10;
  }

  if (instances[index] > 1)
  {
    --instances[index];
  }
  return ((temp % 10) == required);
}

void CopyInstances(int *orig, int *curr)
{
  int i = 0;

  for (i = 0; i < 26; ++i)
  {
    curr[i] = orig[i];
  }
}

char *LongestCommonPrefix(char **str, int size)
{
  int *letters = calloc(26, sizeof(int));
  int *letters_instances = calloc(26, sizeof(int));
  int i = 0;
  int j = 0;
  int counter = 0;
  int max_counter = 0;
  char *prefix = NULL;

  for (i = 0; i < strlen(str[0]); ++i)
  {
    int index = str[0][i] - 'a';
    ++letters_instances[index];
    letters[index] = letters[index]*10 + (i+1);
  }

  for (i = 0; i < size; ++i)
  {
    counter = 0;
    int *current_instances = calloc(26, sizeof(int));
    CopyInstances(letters_instances, current_instances);
    for (j = 0; j < strlen(str[i]); ++j)
    {
      int index = str[i][j] - 'a';

      if (!IndexExists(letters, current_instances, index, j + 1))
      {
        break;
      }
      ++counter;
    }
    if  ((counter <= max_counter) || (i == 0))
    {
      max_counter = counter;
    }
    free(current_instances);
  }

  prefix = malloc(sizeof(char) * max_counter);

  for (i = 0; i < max_counter; ++i)
  {
    prefix[i] = str[0][i];
  }
  prefix[max_counter] = '\0';

  free(letters);
  free(letters_instances);

  return prefix;
}

int main()
{
  char *str[] = {"goof", "goowy", "god"};

  printf("%s\n", LongestCommonPrefix(str, 3));

}
