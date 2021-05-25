#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include "broadcast.h"
  
#define PORT     8080 
#define MAXLINE 1024 
  
int main(int argc, char *argv[]) 
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *pong = "Pong"; 
    struct sockaddr_in servaddr, cliaddr; 
    int num_of_arg = 0;
    int broadcast = 1;
    
    if (!IsEnoughArgc(argc, 2)) 
    {
       exit(EXIT_FAILURE); 
    }

    num_of_arg = atoi(argv[1]);

    /* Creating socket file descriptor */
    if ( (sockfd = CreateSocket()) < 0 ) 
    { 
        exit(EXIT_FAILURE); 
    } 


    printf("SERVER: sockfd: %d\n", sockfd);
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    /* Filling server information */
    servaddr = FillServerInfo(num_of_arg, "127.0.0.1");
      
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
        buffer[n] = '\0'; 
        printf("%s\n", buffer); 
        sendto(sockfd, (const char *)pong, strlen(pong),  
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                len); 
        sleep(1);
    }
    return 0; 
} 