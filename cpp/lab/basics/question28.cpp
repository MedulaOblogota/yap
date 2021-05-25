#include <cstdio>

int main()
{
	const int i=3;
	int * ip=(int *)&i;

	*ip = 5;

	printf("addresses: &i = %p, ip = %p\n", &i, ip);
	printf("%d  %d\n", i, *ip);

	return 0;
}
