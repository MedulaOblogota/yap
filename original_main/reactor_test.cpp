//COMPILE WITH UDP_PORT, TCP_PORT, BROADCASR_PORT

#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "reactor.hpp"

#define STDIN (0)
#define NUM_OF_SOCKETS (4)
#define UNUSED(x) (void)(x)


int CheckSTDIN();

void TCPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort, size_t address_size);
int TCPServerBindSocket(struct sockaddr_in *address, socklen_t addr_len);
int TCPServerListenAndAccept(int serv_fd, struct sockaddr_in *address, socklen_t addr_len);
int TCPServerReadAndPongClient(int client_fd);
int TCPServerPongClient(int client_fd);

void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
int UDPServerPongClient(int socket_fd);

void BoardcastServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int BoardcastServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
int BoardcastServerPongClient(int socket_fd);

typedef struct serv_arg
{
    struct sockaddr_in address;
    uint16_t port;
    int fd;
} serv_arg_t;

void UDPServerSetFD(serv_arg_t *args);
void TCPServerSetFD(serv_arg_t *args);
void BoardcastServerSetFD(serv_arg_t *args);
void SelectLoop(serv_arg_t *udp_arg, serv_arg_t *boardcast_arg, serv_arg_t *tcp_arg);
int PongClient(int client_fd);

Reactor reactor;

int main(int argc, char const *argv[])
{
    serv_arg_t tcp_arg;
    serv_arg_t udp_arg;
    serv_arg_t boardcast_arg;

    assert(argc > 3);

    udp_arg.port = atoi(argv[1]);
    UDPServerSetFD(&udp_arg);

    tcp_arg.port = atoi(argv[2]);
    TCPServerSetFD(&tcp_arg);

    boardcast_arg.port = atoi(argv[3]);
    BoardcastServerSetFD(&boardcast_arg);

    SelectLoop(&udp_arg, &boardcast_arg, &tcp_arg);

    if (-1 == close(udp_arg.fd))
    {
        perror("udp_arg close");
    }

    if (-1 == close(tcp_arg.fd))
    {
        perror("tcp_arg close");
    }

    if (-1 == close(boardcast_arg.fd))
    {
        perror("boardcast_arg close");
    }

    return (0);
}

int StdInFunc(int val)
{
    std::string buff;
    const std::string EXIT = "exit";

    std::cin >> buff;

    if (buff != EXIT)
    {
        std::cout << buff << " : PONG" << std::endl;
    }

    reactor.Stop();
    return 1;
}



void SelectLoop(serv_arg_t *udp_arg, serv_arg_t *boardcast_arg, serv_arg_t *tcp_arg)
{
    int new_socket = 0;
    socklen_t size = sizeof(tcp_arg->address);
    struct sockaddr_in *address = &(tcp_arg->address);

    std::cout << "udp fd = " << udp_arg->fd << std::endl;
    std::cout << "tcp fd = " << tcp_arg->fd << std::endl;

    reactor.AddFD(std::make_pair(STDIN, FDListener::READ), StdInFunc);
    reactor.AddFD(std::make_pair(udp_arg->fd, FDListener::READ), UDPServerPongClient);
    reactor.AddFD(std::make_pair(boardcast_arg->fd, FDListener::READ), BoardcastServerPongClient);
    reactor.AddFD(std::make_pair(tcp_arg->fd, FDListener::READ), TCPServerPongClient);
    
    // std::cout << "entered select-loop" << std::endl;    
    
    if (listen(tcp_arg->fd, 6) < 0)
    {
        perror("listen");
    }

    // // std::cout << "tcp listening" << std::endl;    

    if ((new_socket = accept(tcp_arg->fd, (struct sockaddr *)address, &size)) < 0)
    {
        perror("accept");
    }

    // // std::cout << "tcp accepting" << std::endl;    

    reactor.AddFD(std::make_pair(new_socket, FDListener::READ), PongClient);
    // std::cout << "after adding tcp" << std::endl;    
    reactor.Start();
}

int TCPServerPongClient(int client_fd)
{
    int new_socket = 0;
    sockaddr_in address;
    socklen_t size = sizeof(address);

    if ((new_socket = accept(client_fd, (struct sockaddr *)&address, &size)) < 0)
    {
        perror("accept");
    }

    // // std::cout << "tcp accepting" << std::endl;    

    reactor.AddFD(std::make_pair(new_socket, FDListener::READ), PongClient);

    return 1;
}

int CheckSTDIN()
{
    std::string buff;
    const std::string EXIT = "exit";

    std::cin >> buff;

    if (buff != EXIT)
    {
        std::cout << buff << " : PONG" << std::endl;

        return (0);
    }

    reactor.Stop();

    return (1);
}

void CheckIfError(int err_num, const char *str)
{
    if (0 > err_num)
    {
        perror(str);

        exit(-1);
    }
}

void TCPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort, size_t address_size)
{
    memset(address, 0, address_size);
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(hostshort);
}

int TCPServerBindSocket(struct sockaddr_in *address, socklen_t addr_len)
{
    int opt = 1;
    int serv_fd = 0;

    CheckIfError(serv_fd = socket(AF_INET, SOCK_STREAM, 0), "socket");

    CheckIfError(setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                            &opt, sizeof(opt)),
                 "setsockopt");

    CheckIfError(bind(serv_fd, (struct sockaddr *)address, addr_len), "bind");

    return (serv_fd);
}

int TCPServerListenAndAccept(int serv_fd, struct sockaddr_in *address, socklen_t addr_len)
{
    int client_fd = 0;
    static int is_not_listen = 1;

    if (is_not_listen)
    {
        CheckIfError(listen(serv_fd, 1), "listen");
    }

    is_not_listen = 0;
    CheckIfError(client_fd = accept(serv_fd, (struct sockaddr *)&address,
                                    (socklen_t *)&addr_len), "accept");

    printf("%d\n", client_fd);

    return (client_fd);
}

int PongClient(int client_fd)
{
    char buff[50] = {0};
    const char pong[] = "PONG!";
    int check_read = 0;

    // std::cout << "SERVER: reading ping" << std::endl;

    check_read = read(client_fd, buff, 50);
    CheckIfError(check_read, "read");

    if (check_read == 0)
    {
        // getpeername(client_fd , (struct sockaddr*)&tcp_address , (socklen_t*)&addrlen);   
        printf("Host disconnected!\n");
        reactor.RemoveFd(std::make_pair(client_fd, FDListener::READ));
        // inet_ntoa(tcp_address.sin_addr) , ntohs(tcp_address.sin_port));   
                        
        //Close the socket and mark as 0 in list for reuse  
        return 0;  
    }

    printf("SERVER: %s\n", buff);

    // std::cout << "SERVER: sending pong" << std::endl;

    CheckIfError(send(client_fd, pong, sizeof(pong), 0), "send");

    sleep(1);

    return 1;
}

// int TCPServerReadAndPongClient(int client_fd)
// {
//     int new_socket = 0;
//     socklen_t size = sizeof(tcp_arg.address);
//     struct sockaddr_in *address = &tcp_arg.address;

//     if ((new_socket = accept(client_fd, (struct sockaddr *)address, &size)) < 0)
//     {
//         perror("accept");
//     }

//     reactor.AddFD(std::make_pair(new_socket, FDListener::READ), PongClient);
//     // reactor.RemoveFd(std::make_pair(client_fd, FDListener::READ));
// }

void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort)
{
    memset(address, 0, sizeof(struct sockaddr_in));

    address->sin_family = AF_INET; /*Internet Protocol v4 addresses*/
    address->sin_addr.s_addr = htonl(INADDR_ANY);
    address->sin_port = htons(hostshort);
}

int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len)
{
    int socket_fd = 0;
    int opt = 1;

    if (0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        exit(-1);
    }

    if (0 > setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                            &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(-1);
    }

    if (bind(socket_fd, (const struct sockaddr *)serv_addr, len))
    {
        perror("bind");
        if (-1 == close(socket_fd))
        {
            perror("close");
        }
        exit(-1);
    }

    return (socket_fd);
}

int UDPServerPongClient(int socket_fd)
{
    char buff[50];
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    const char pong[] = "PONG!";
    int n = 0;

    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    n = recvfrom(socket_fd, buff, 50, MSG_WAITALL,
                       (struct sockaddr *)&client_addr, &len);

    if (-1 == n)
    {
        perror("recvfrom");
    }

    buff[n] = '\0';

    puts(buff);
    sleep(1);

    if (-1 == sendto(socket_fd, pong, sizeof(pong), MSG_CONFIRM,
                     (struct sockaddr *)&client_addr, len))
    {
        perror("sendto");
        if (-1 == close(socket_fd))
        {
            perror("close");
        }
    }

    return 1;
}

void BoardcastServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort)
{
    memset(address, 0, sizeof(struct sockaddr_in));

    address->sin_family = AF_INET; /*Internet Protocol v4 addresses*/
    address->sin_addr.s_addr = INADDR_BROADCAST;
    address->sin_port = htons(hostshort);
}

int BoardcastServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len)
{
    int socket_fd = 0;
    int broadcast_opt = 1;
    int opt = 1;

    if (0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        exit(-1);
    }

    if (0 > setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(-1);
    }

    if (0 > setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST,
                       &broadcast_opt, sizeof(broadcast_opt)))
    {
        perror("setsockopt broadcast");
        exit(-1);
    }

    if (bind(socket_fd, (const struct sockaddr *)serv_addr, len))
    {
        perror("bind");
        if (-1 == close(socket_fd))
        {
            perror("close");
        }
        exit(-1);
    }

    return (socket_fd);
}

int BoardcastServerPongClient(int socket_fd)
{
    char buff[50];
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    const char pong[] = "PONG!";

    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    if (-1 == recvfrom(socket_fd, buff, 50, MSG_WAITALL,
                       (struct sockaddr *)&client_addr, &len))
    {
        perror("recvfrom");
    }

    puts(buff);
    sleep(1);

    if (-1 == sendto(socket_fd, pong, sizeof(pong), MSG_CONFIRM,
                     (struct sockaddr *)&client_addr, len))
    {
        perror("sendto");
        if (-1 == close(socket_fd))
        {
            perror("close");
        }
    }

    return 1;
}

void UDPServerSetFD(serv_arg_t *args)
{
    UDPServerSetSockAddrIn(&args->address, args->port);

    args->fd = UDPServerSocketAndBind(&args->address, sizeof(struct sockaddr_in));
}

void TCPServerSetFD(serv_arg_t *args)
{
    TCPServerSetSockAddrIn(&args->address, args->port, sizeof(args->address));

    args->fd = TCPServerBindSocket(&args->address, sizeof(args->address));
}

void BoardcastServerSetFD(serv_arg_t *args)
{
    BoardcastServerSetSockAddrIn(&args->address, args->port);

    args->fd = BoardcastServerSocketAndBind(&args->address, sizeof(struct sockaddr_in));
}
