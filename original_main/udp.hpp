#ifndef RD70_UDP
#define RD70_UDP

void ReactorWrapFuncUDPTest(int socket_fd);

void UDPServerSetFD(serv_arg_t *args);

int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);

void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);

int CheckSTDIN();

void ReactorWrapFuncCheckSTDIN(int unused);

#endif //RD70_UDP