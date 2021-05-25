/* CLIENT SIDE */
/* INPUT PARAMS SHOULD BE <PORT> <IP> */
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

#include "tcp.h"

#define MAX 80 

#define SA struct sockaddr 

void func(int sockfd) 
{ 
    char ping[] = "PING!";

    printf("size of ping is %lu\n", sizeof(ping));

    while (1) 
    { 
        char buff[MAX] = {0}; 
        /*bzero(buff, sizeof(buff)); */
        /* strcpy(buff, "ping");*/

        /*printf("CLIENT: sending ping\n");*/

        if (write(sockfd, ping, sizeof(ping)) < 0)
        {
            perror("write");
            exit(EXIT_FAILURE);
        } 

        /* printf("CLIENT: reading pong\n");*/

        if (read(sockfd, buff, sizeof(buff)) < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        } 
        printf("CLIENT (should be pong): %s\n", buff);

        sleep(1);
    } 
} 
  
int main(int argc, char *argv[]) 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    int num_of_arg = 0;

    if (!IsEnoughArgc(argc, 3)) 
    {
       exit(EXIT_FAILURE); 
    }

    if ((sockfd = CreateSocket()) < 0) 
    { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Socket successfully created..\n"); 
    }

    num_of_arg = atoi(argv[1]);

    servaddr = FillServerInfo(num_of_arg, argv[2]);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("connected to the server..\n"); 
    }

    func(sockfd); 
  
    close(sockfd); 

    return 0;
} 