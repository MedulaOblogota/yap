#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str1[] = "hello";
	char *str2 = strtok(str1, "mello");
	char str3[] = "";
	printf("strcmp for 'hello' and NULL = %d", strcmp(str3, str1));
	printf("first token is = %s\n", str2);
	str2 = strtok(NULL, "mello");
	printf("second token is = %s\n", str2);
	str2 = strtok(NULL, "mello");
	printf("third token is = %s\n", str2);
	str2 = strtok(NULL, "mello");
	printf("fourth token is = %s\n", str2);
	
	return(1);
}
