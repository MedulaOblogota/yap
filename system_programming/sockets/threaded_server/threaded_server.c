/*********************************************************************************
 *	name: 				Roy Yablonka
 *	lab: 				RD70
 *	date:				30/11/2019
 * ******************************************************************************/

#include <stdio.h>		/*printf*/
#include <stdlib.h>		/* exit */
#include <string.h>		/* strlen */
#include <arpa/inet.h>	/* inet_addr */
#include <unistd.h>		/* read, write */
#include <pthread.h>	/* pthread_t */

#include "threaded_server.h"

#define MAX 80
#define SA struct sockaddr
#define MAX_VALUE (10)
#define MAXLINE 1024

/*********************************************************************************
 *                      STATIC FUNCTION DECLARATIONS
 * ******************************************************************************/

static struct sockaddr_in FillServerInfoBroadcast(int num_of_arg);

static struct sockaddr_in FillServerInfoWithoutIP(int num_of_arg);

static int CreateUDPSocket();

static int CreateTCPSocket();

static void FuncTCP(int sockfd);

static void *ThreadFunc(void *value);


/*********************************************************************************
 *                      STATIC FUNCTION DEFINITIONS
 * ******************************************************************************/

static struct sockaddr_in FillServerInfoBroadcast(int num_of_arg)
{
    struct sockaddr_in servaddr;

	bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    servaddr.sin_port = htons(num_of_arg);

    return servaddr;
}

struct sockaddr_in FillServerInfoWithoutIP(int num_of_arg)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(num_of_arg);

    return servaddr;
}

int CreateUDPSocket()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   if (sockfd < 0)
   {
       perror("socket creation failed");
       return -1;
   }

   return sockfd;
}

static int CreateTCPSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("socket creation failed...\n");
        return -1;
    }
    else
    {
        printf("Socket successfully created..\n");
        return sockfd;
    }
}

static void FuncTCP(int sockfd)
{
    char buff[MAX];

    while (1)
    {
        if (read(sockfd, buff, sizeof(buff)) < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("SERVER: %s\n", buff);
        bzero(buff, MAX);

        strcpy(buff, "pong");

        if (write(sockfd, buff, sizeof(buff)) < 0)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        sleep(1);
    }
}

void *ThreadFunc(void *value)
{
/* Function for chatting between client and server */
    FuncTCP(*(int *)value);
}

/*********************************************************************************
 *                      SOURCE FUNCTION DEFINITIONS
 * ******************************************************************************/

void CreateStdInput(int udp_port_num, int tcp_port_num, int broadcast_port_num)
{
	pthread_t thread[3];
	int selection = 2;
	int udp_port_num1, tcp_port_num1, broadcast_port_num1;

	pthread_create(&thread[0], NULL, CreateUDPServer, &udp_port_num);
	pthread_create(&thread[1], NULL, CreateTCPServer, &tcp_port_num);
	pthread_create(&thread[2], NULL, CreateBroadcastServer, &broadcast_port_num);
/*
	while ((selection >= 1) && (selection <= 3))
	{
			printf("select 1 for UDP, 2 for TCP & 3 for Broadcast\n");
			scanf("%d", &selection);
			switch (selection)
			{
				case 1:
					printf("select port number for udp connection: ");
					scanf("%d", &udp_port_num1);
					pthread_create(&thread[0], NULL, CreateUDPServer, &udp_port_num1);
					break;

				case 2:
					printf("select port number for tcp connection: ");
					scanf("%d", &tcp_port_num1);
					pthread_create(&thread[1], NULL, CreateTCPServer, &tcp_port_num1);
					break;

				case 3:
					printf("select port number for broadcast connection: ");
					scanf("%d", &broadcast_port_num1);
					pthread_create(&thread[2], NULL, CreateBroadcastServer, &broadcast_port_num1);
					break;

				default:
					break;
			}

	}
*/
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
}

void *CreateUDPServer(void *port_num_v)
{
	int sockfd;
	char buffer[MAXLINE];
	char *pong = "Pong";
	struct sockaddr_in servaddr, cliaddr;

	int port_num = *(int *)port_num_v;

	printf("port_num = %d\n", port_num);

	/* Creating socket file descriptor */
	if ( (sockfd = CreateUDPSocket()) < 0 )
	{
			exit(EXIT_FAILURE);
	}

	printf("SERVER: sockfd: %d\n", sockfd);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	/* Filling server information */
	servaddr = FillServerInfoWithoutIP(port_num);

	/* Bind the socket with the server address */
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
					sizeof(servaddr)) < 0 )
	{
			perror("bind failed");
			exit(EXIT_FAILURE);
	}

	while (1)
	{
			int len, n;
			n = recvfrom(sockfd, (char *)buffer, MAXLINE,
									MSG_WAITALL, ( struct sockaddr *) &cliaddr,
									(socklen_t *)&len);

			/*printf("SERVER: received ping\n" );*/
			buffer[n] = '\0';
			printf("%s\n", buffer);
			/*printf("strlen(pong) = %lu\n", strlen(pong));*/
			sendto(sockfd, (const char *)pong, strlen(pong),
					MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
							len);
			/*printf("SERVER: sent pong\n" );*/
			sleep(1);
	}
}

void *CreateTCPServer(void *port_num_v)
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	pthread_t thread[20];
	int i = 0;
	int port_num = *(int *)port_num_v;

	printf("port number is %d\n", port_num);
	/* socket create and verification */
	if ( (sockfd = CreateTCPSocket()) < 0 )
	{
			exit(EXIT_FAILURE);
	}

	servaddr = FillServerInfoWithoutIP(port_num);

	/* Binding newly created socket to given IP and verification */
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
			printf("socket bind failed...\n");
			exit(0);
	}
	else
	{
			printf("Socket successfully binded..\n");
	}

	/* Now server is ready to listen and verification */
	if ((listen(sockfd, MAX_VALUE)) != 0)
	{
			printf("Listen failed...\n");
			exit(0);
	}
	else
	{
			printf("Server listening..\n");
	}

	len = sizeof(cli);

	while (1)
	{
			/* Accept the data packet from client and verification */
			connfd = accept(sockfd, (SA*)&cli, (socklen_t*)&len);

			if (connfd < 0)
			{
					printf("server acccept failed...\n");
					exit(0);
			}

			printf("server acccept the client...\n");
			pthread_create(&thread[i++ % MAX_VALUE], NULL, ThreadFunc, &connfd);
	}
	/* After chatting close the socket */
	close(sockfd);
}

void *CreateBroadcastServer(void *port_num_v)
{
	int sockfd;
	char buffer[MAXLINE];
	char *pong = "Pong";
	struct sockaddr_in servaddr, cliaddr;
	int broadcast = 1;

	int port_num = *(int *)port_num_v;


	/* Creating socket file descriptor */
	if ( (sockfd = CreateUDPSocket()) < 0 )
	{
			exit(EXIT_FAILURE);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof broadcast) == -1) 
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }


	printf("SERVER: sockfd: %d\n", sockfd);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	/* Filling server information */
	servaddr = FillServerInfoWithoutIP(port_num);

	/* Bind the socket with the server address */
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
					sizeof(servaddr)) < 0 )
	{
			perror("bind failed");
			exit(EXIT_FAILURE);
	}

	while (1)
	{
			int len, n;
			bzero(buffer, MAXLINE);

			printf("buffer is %s. ", buffer);

			n = recvfrom(sockfd, (char *)buffer, MAXLINE,
									MSG_WAITALL, ( struct sockaddr *) &cliaddr,
									(socklen_t *)&len);
			buffer[n] = '\0';
			printf("buffer is %s. ", buffer);
			
			printf("%s\n", buffer);
			sendto(sockfd, (const char *)pong, strlen(pong),
					MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
							len);

			printf("buffer now is %s\n", buffer);
			bzero(buffer, MAXLINE);
			printf("buffer now is %s\n", buffer);
			sleep(1);
	}
}
