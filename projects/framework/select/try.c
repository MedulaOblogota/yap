#include <stdio.h>
#include <sys/select.h>

int main()
{
	fd_set readfds;
	char buf[15];
	int fd = 2;

	struct timeval timeout;

	while (1)
	{
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		if (select(2, &readfds, NULL, NULL, &timeout) == 0)
		{
			printf("timeout!\n");
		}
		else
		{
			memset((void *)buf, 0, 15);

			if (read(fd, (void *)buf, 15) != -1)
			{
				printf("buffer = %s\n", buf);
			}
		}
	}

	return 0;

}
