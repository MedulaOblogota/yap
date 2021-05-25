#ifndef RD70_PINGPONGSOCKET
#define RD70_PINGPONGSOCKET

#include <stdio.h> 
#include <stdlib.h> 
// #include <unistd.h> 
#include <string.h> 
// #include <sys/types.h> 
// #include <sys/socket.h> 
#include <arpa/inet.h> 
// #include <netinet/in.h> 

int IsEnoughArgc(int argc, int max_args);

int CreateSocket();

struct sockaddr_in FillServerInfo(int num_of_arg);

#endif /* RD70_PINGPONGSOCKET */