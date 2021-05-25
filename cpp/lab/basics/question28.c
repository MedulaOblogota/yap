#include <stdio.h>

int main()
{
	const int i=3;
	int * ip=(int *)&i;

	*ip = 5;

	printf("addresses: &i = %p, ip = %p", &i, ip);
	printf("values: i=%d  *ip=%d\n", i, *ip);


	return 0;
}
