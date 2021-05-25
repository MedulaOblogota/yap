#include "socket.h"

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
   int sockfd =  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

   if (sockfd < 0)
   {
       perror("socket creation failed");
       return -1;
   }

   return sockfd;
}

struct sockaddr_in FillServerInfo(int num_of_arg, char *str)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family    = AF_INET; /* IPv4 */
    servaddr.sin_addr.s_addr = inet_addr(str); 
    servaddr.sin_port = htons(num_of_arg);

    return servaddr;
}
