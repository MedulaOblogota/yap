#ifndef RD70_UDP
#define RD70_UDP

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int IsEnoughArgc(int argc, int max_args);

int CreateSocket();

struct sockaddr_in FillServerInfo(int num_of_arg, char *str);

#endif /* RD70_UDP */