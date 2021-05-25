/* Client side implementation of UDP client-server model */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "socket.h"

#define MAXLINE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[MAXLINE];
    char *ping = "ping";
    struct sockaddr_in     servaddr;
    int num_of_arg = 0;

    if (!IsEnoughArgc(argc, 3))
    {
       exit(EXIT_FAILURE);
    }

    num_of_arg = atoi(argv[1]);

    printf("num_of_arg = %d\n", num_of_arg);

    /* Creating socket file descriptor */
    if ( (sockfd = CreateSocket()) < 0 )
    {
        exit(EXIT_FAILURE);
    }

    printf("CLIENT: sockfd: %d\n", sockfd);

    memset(&servaddr, 0, sizeof(servaddr));

    /* Filling server information */
    servaddr = FillServerInfo(num_of_arg, argv[2]);

    while (1)
    {
        int n, len;

        sendto(sockfd, (const char *)ping, strlen(ping),
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                sizeof(servaddr));

			/*	printf("CLIENT: sent ping\n");*/

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    (socklen_t *)&len);

				/*printf("CLIENT: received pong\n");*/
        buffer[n] = '\0';
        printf("%s\n", buffer);
        sleep(1);
    }

    close(sockfd);
    return 0;
}
