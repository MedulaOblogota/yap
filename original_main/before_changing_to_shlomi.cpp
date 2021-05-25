#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "fdlistener.hpp"
#include "reactor.hpp"
#include "singleton.hpp"

#define STDIN (0)
#define NUM_OF_SOCKETS (4)
#define UNUSED(x) (void)(x)

// using namespace ilrd;

int CheckSTDIN();

void CheckIfError(int err_num, const char *str);
void TCPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort, size_t address_size);
int TCPServerBindSocket(struct sockaddr_in *address, socklen_t addr_len);
int TCPServerListenAndAccept(int serv_fd, struct sockaddr_in *address, socklen_t addr_len);
void TCPServerReadAndPongClient(int client_fd);

void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
void UDPServerPongClient(int socket_fd);

void BoardcastServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int BoardcastServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
void BoardcastServerPongClient(int socket_fd);

typedef struct serv_arg
{
    struct sockaddr_in address;
    uint16_t port;
    int fd;
} serv_arg_t;

void UDPServerSetFD(serv_arg_t *args);
void TCPServerSetFD(serv_arg_t *args);
void BoardcastServerSetFD(serv_arg_t *args);

void SetReactor(serv_arg_t *udp_arg, serv_arg_t *boardcast_arg, serv_arg_t *tcp_arg);
void ReactorWrapFuncTCPNewConnection(int fd);
void ReactorWrapFuncTCPPong(int fd);
void ReactorWrapFuncBroadcastPong(int fd);
void ReactorWrapFuncUDPPong(int fd);
void ReactorWrapFuncCheckSTDIN(int unused);

int main(int argc, char const *argv[])
{
    serv_arg_t udp_arg;
    serv_arg_t tcp_arg;
    serv_arg_t boardcast_arg;

    assert(argc > 3);

    udp_arg.port = atoi(argv[1]);
    UDPServerSetFD(&udp_arg);

    tcp_arg.port = atoi(argv[2]);
    TCPServerSetFD(&tcp_arg);

    boardcast_arg.port = atoi(argv[3]);
    BoardcastServerSetFD(&boardcast_arg);

    if (listen(tcp_arg.fd, 6) < 0)
    {
        perror("listen");
    }

    SetReactor(&udp_arg, &boardcast_arg, &tcp_arg);

    Singleton<Reactor>::GetInstance()->Start();

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

void ReactorWrapFuncCheckSTDIN(int unused)
{
    UNUSED(unused);

    if (CheckSTDIN())
    {
        Singleton<Reactor>::GetInstance()->Stop();
    }
}

void ReactorWrapFuncUDPPong(int fd)
{
    UDPServerPongClient(fd);
}

void ReactorWrapFuncBroadcastPong(int fd)
{
    BoardcastServerPongClient(fd);
}

void ReactorWrapFuncTCPPong(int fd)
{
    char buff[50] = {0};
    const char pong[] = "PONG!";
    int readRet = 0;

    CheckIfError(readRet = read(fd, buff, 50), "read");
    if (0 == readRet)
    {
        Singleton<Reactor>::GetInstance()->RemoveFd(std::make_pair(fd, FDListener::READ));
        return;
    }
    puts(buff);
    CheckIfError(send(fd, pong, sizeof(pong), 0), "send");
}

void ReactorWrapFuncTCPNewConnection(int fd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    socklen_t size = sizeof(address);

    if ((new_socket = accept(fd, (struct sockaddr *)&address, &size)) < 0)
    {
        perror("accept");
    }

    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(new_socket, FDListener::READ), ReactorWrapFuncTCPPong);
}

void SetReactor(serv_arg_t *udp_arg, serv_arg_t *boardcast_arg, serv_arg_t *tcp_arg)
{
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(STDIN, FDListener::READ), ReactorWrapFuncCheckSTDIN);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(udp_arg->fd, FDListener::READ), ReactorWrapFuncUDPPong);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(boardcast_arg->fd, FDListener::READ), ReactorWrapFuncBroadcastPong);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(tcp_arg->fd, FDListener::READ), ReactorWrapFuncTCPNewConnection);
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
                                    (socklen_t *)&addr_len),
                 "accept");

    printf("%d\n", client_fd);

    return (client_fd);
}

void TCPServerReadAndPongClient(int client_fd)
{
    char buff[50] = {0};
    const char pong[] = "PONG!";

    CheckIfError(read(client_fd, buff, 50), "read");
    puts(buff);
    CheckIfError(send(client_fd, pong, sizeof(pong), 0), "send");
}

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

void UDPServerPongClient(int socket_fd)
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

void BoardcastServerPongClient(int socket_fd)
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
