#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

int IsEnoughArgc(int argc, int max_args)
{
   if (argc < max_args)
    {
        printf("no PORT inserted, please input it with execution!\n");
        perror("no input from user");

        return 0; 
    } 

    return 1;
}

int CreateSocket()
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

struct sockaddr_in FillServerInfo(int num_of_arg, char *str)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(str); 
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