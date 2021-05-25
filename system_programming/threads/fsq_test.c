#include <stdio.h>
#include "fsq.h"

int main()
{
	fsq_t *fsq = FSQCreate(3);
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;

	int result = FSQEnqueue(fsq, num1);
	if (result != 0)
	{
		printf("failed!\n");
	}

	result = FSQEnqueue(fsq, num2);
	if (result != 0)
	{
		printf("failed!\n");
	}

	result = FSQEnqueue(fsq, num3);
	if (result != 0)
	{
		printf("failed!\n");
	}

	result = FSQEnqueue(fsq, num1);
	if (result != 1)
	{
		printf("failed!\n");
	}

	printf("%d\n", FSQDequeue(fsq));
	printf("%d\n", FSQDequeue(fsq));
	printf("%d\n", FSQDequeue(fsq));
	printf("%d\n", FSQDequeue(fsq));

	/*
	if (result != 1)
	{
		printf("failed!\n");
	}

	result = FSQDequeue(fsq);
	if (result != 2)
	{
		printf("failed!\n");
	}

	result = FSQDequeue(fsq);
	if (result != 3)
	{
		printf("failed!\n");
	}*/

	if (FSQIsEmpty(fsq) == 0)
	{
		printf("failed!\n");
	}

	FSQDestroy(fsq);
	return 0;
}
