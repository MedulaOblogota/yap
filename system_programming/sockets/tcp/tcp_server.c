/* SERVER SIDE */
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "tcp.h"

#define MAX 80
#define SA struct sockaddr
#define MAX_VALUE (10)

/* Function designed for chat between client and server. */
void func(int sockfd)
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

        sleep(2);
    }
}

void *ThreadFunc(void *value)
{
/* Function for chatting between client and server */
    func(*(int *)value);
}

int main(int argc, char *argv[])
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    int num_of_arg;
    pthread_t thread[20];
    int i = 0;

     if (!IsEnoughArgc(argc, 2))
    {
       exit(EXIT_FAILURE);
    }

    num_of_arg = atoi(argv[1]);

    printf("num_of_arg = %d\n", num_of_arg);

    /* socket create and verification */
    if ( (sockfd = CreateSocket()) < 0 )
    {
        exit(EXIT_FAILURE);
    }

    servaddr = FillServerInfoWithoutIP(num_of_arg);

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

    return 0;
}
