#include <stdio.h>

int main()
{
	int i = 8;
	unsigned int &ip = i;

	ip = 9;

	printf("%d\n", i);
	printf("ip=%d\n", ip);
	printf("&ip=%p\n", &ip);
	printf("&i=%p\n", &i);
	printf("sizeof(ip)=%d\n", sizeof(ip));
}
