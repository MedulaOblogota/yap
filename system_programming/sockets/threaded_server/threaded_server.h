#ifndef RD70_THREADED_SERVER
#define RD70_THREADED_SERVER

void CreateStdInput(int udp_port_num, int tcp_port_num, int broadcast_port_num);

void *CreateUDPServer(void *port_num);

void *CreateTCPServer(void *port_num);

void *CreateBroadcastServer(void *port_num);

#endif /* RD70_THREADED_SERVER */
