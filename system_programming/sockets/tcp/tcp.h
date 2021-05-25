#ifndef RD70_TCP
#define RD70_TCP

int IsEnoughArgc(int argc, int max_args);

int CreateSocket();

struct sockaddr_in FillServerInfo(int num_of_arg, char *str);

struct sockaddr_in FillServerInfoWithoutIP(int num_of_arg);

#endif /* RD70_TCP */