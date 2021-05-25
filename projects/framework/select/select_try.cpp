// Server program
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAXLINE (1024)
#define MAX_VALUE_OF_TCP (20)

static int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

struct sockaddr_in FillServerInfo(int port);
void *CreateTCPServer(void * connfd);

int main(int argc, char *argv[])
{
    int listenfd, connfd, udpfd, nready, maxfdp1, sd;
    char buffer[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    char* message = "pong";
    void sig_chld(int);
		struct timeval timeout;
		pthread_t thread[MAX_VALUE_OF_TCP];
		int i = 0;

    int client_socket[30] = { 0 };

		int port = atoi(argv[1]);

    for (size_t i = 0; i < 30; ++i)
    {
      if (client_socket[i] != 0) printf ("bad zero!!!\n");
    }
    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

		servaddr = FillServerInfo(port);

    // binding server addr structure to listenfd
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    /* create UDP socket */
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    // binding server addr structure to udp sockfd
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // get maxfd
		maxfdp1 = max(listenfd, udpfd);

    while (1)
		{
				FD_ZERO(&rset);

        // set listenfd and udpfd in readset
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

				timeout.tv_sec = 5;
				timeout.tv_usec = 0;

				// printf("before select. nready = %d\n", nready);
        // select the ready descriptor

        // while (1);

        for (size_t i = 0; i < 30; ++i)
        {
          if (client_socket[i] > 0)
          {
            FD_SET(client_socket[i], &rset);
          }

          if (client_socket[i] > maxfdp1)
          {
            maxfdp1 = client_socket[i];
          }
        }

        nready = select(maxfdp1 + 1, &rset, 0, NULL, NULL);
				// printf("after select. nready = %d\n", nready);

        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(listenfd, &rset))
				{
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
						while (1)
						{
							pthread_create(&thread[i++ % MAX_VALUE_OF_TCP], NULL, CreateTCPServer, (void *)&connfd);
						}
						// CreateTCPServer(connfd);
						// while (1)
						// {
	          //   bzero(buffer, MAXLINE);
	          //   printf("Message From TCP client: ");
	          //   read(connfd, buffer, sizeof(buffer));
	          //   puts(buffer);
	          //   write(connfd, (const char*)message, 8);
						// }
					close(connfd);
        }

        // if udp socket is readable receive the message.
        if (FD_ISSET(udpfd, &rset))
				{
            len = sizeof(cliaddr);
            bzero(buffer, sizeof(buffer));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
                         (struct sockaddr*)&cliaddr, &len);
            puts(buffer);
            sendto(udpfd, (const char*)message, sizeof(buffer), 0,
                   (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        }
    }
		close(connfd);
}

struct sockaddr_in FillServerInfo(int port)
{
		struct sockaddr_in servaddr;

		bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

		return servaddr;
}

void *CreateTCPServer(void *connfd_v)
{
	char buffer[10];
	char* message = "pong";

	int connfd = *(int *)connfd_v;

	while (1)
	{
		bzero(buffer, MAXLINE);
		// printf("Message From TCP client: ");
		read(connfd, buffer, sizeof(buffer));
		puts(buffer);
		write(connfd, (const char*)message, 8);
		sleep(2);
	}
}
