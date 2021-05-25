#include <string.h>
#include <stdio.h>

char *StrTok(char *str, const char *delim)
{
		static char *temp_str = NULL;
		const char *runner = delim;
		char *instance = NULL;

		if (NULL == str)
		{
			if (NULL == temp_str)
			{
				return NULL;
			}
			else
			{
				str = temp_str;
				instance = str;
			}
		}

		instance = strchr(str, *runner);
		while (*runner)
		{
			char *temp_instance = NULL;
			++runner;
			temp_instance = strchr(str, *runner);

			if ((temp_instance < instance) || (NULL == instance))
			{
				instance = temp_instance;
			}
		}

		*instance = '\0';
		temp_str = instance + 1;

		return str;
}

size_t StrSpn( const char *str1, const char *str2 )
{
	char *str1_runner = str1;
	size_t counter = 0;

	while ((*str1_runner != '\0') && (strchr(str2, *str1_runner) != NULL))
	{
		++counter;
		++str1_runner;
	}

	return counter;
}

int main()
{
	char str[] = "hello$my *man$";
	char delim[] = " *$";

	printf("%s\n", StrTok(str, delim));
	printf("%s\n", StrTok(NULL, delim));
	printf("%s\n", StrTok(NULL, delim));
	printf("%s\n", StrTok(NULL, delim));

	char str1[] = "hello my man";
	char str2[] = "ln hoayem";

	printf("%lu\n", StrSpn(str1, str2));
	return 0;
}
