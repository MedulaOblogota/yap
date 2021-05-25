// compile: g++ -L/home/student/roy-yablonka/projects/framework -Wall -o server ./framework/main/reactor_test_main_server.cpp ./framework/factorysync/factory_sync.cpp ./framework/command/addseverity.cpp ./framework/command/command.cpp ./framework/command/exit.cpp ./framework/command/reduceseverity.cpp ./framework/reactor/reactor.cpp ./framework/fdlistener/fdlistener.cpp ./framework/rw/write.cpp ./framework/rw/read.cpp ./framework/logger/logger.cpp ./framework/rw/dsbuffer.cpp -I ./include/ -lpthread ./framework/write.so ./framework/read.so -ldl

//for libsos:
//  1. g++ -c -Wall -fpic ./rw/write.cpp ./logger/logger.cpp -I ../include/
//  2. g++ -shared -o libwrite.so *.o

#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fstream>

#include "fdlistener.hpp"
#include "reactor.hpp"
#include "singleton.hpp"
#include "shared_ptr.hpp"
#include "write.hpp"
#include "read.hpp"
#include "command.hpp"
#include "logger.hpp"
#include "factory_sync.hpp"
#include "udp_manager.hpp"
#include "udp_input_analyzer.hpp"

#define STDIN (0)
#define NUM_OF_SOCKETS (4)
#define UNUSED(x) (void)(x)
#define MAXLINE (4200)

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
void ReactorWrapFuncUDPTest(int client_fd);
void UDPServerAcceptTest(int socket_fd, SharedPtr<Writer> writer, SharedPtr<Reader> reader);

void BoardcastServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int BoardcastServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
void BoardcastServerPongClient(int socket_fd);

// typedef struct serv_arg
// {
//     struct sockaddr_in address;
//     uint16_t port;
//     int fd;
//     char *buffer;
// } serv_arg_t;

void UDPServerSetFD(serv_arg_t *args);
void TCPServerSetFD(serv_arg_t *args);
void BoardcastServerSetFD(serv_arg_t *args);

void SetReactor(serv_arg_t *udp_arg, serv_arg_t *boardcast_arg, serv_arg_t *tcp_arg);
void ReactorWrapFuncTCPNewConnection(int fd);
void ReactorWrapFuncTCPPong(int fd);
void ReactorWrapFuncBroadcastPong(int fd);
void ReactorWrapFuncUDPPong(int fd);
void ReactorWrapFuncCheckSTDIN(int unused);

SharedPtr<Command> ReadFunc(serv_arg_t *);
SharedPtr<Command> WriteFunc(serv_arg_t *);

Logger *logger = Singleton<Logger>::GetInstance();

int main(int argc, char const *argv[])
{
    serv_arg_t udp_arg;
    serv_arg_t tcp_arg;
    serv_arg_t boardcast_arg;

    std::ofstream *logfile = new std::ofstream("log2.log", std::ofstream::out);

    SharedPtr<std::ostream> logfile_sp(logfile);

    logger->SetOutput(logfile_sp);
    logger->SetOutputSeverity(Logger::DEBUG);

    assert(argc > 3);

    udp_arg.port = atoi(argv[1]);
    UDPServerSetFD(&udp_arg);

    tcp_arg.port = atoi(argv[2]);
    TCPServerSetFD(&tcp_arg);

    boardcast_arg.port = atoi(argv[3]);
    BoardcastServerSetFD(&boardcast_arg);

    logger->Log(Logger::INFO, "This is the shit!");

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
    // Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(udp_arg->fd, FDListener::READ), ReactorWrapFuncUDPPong);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(udp_arg->fd, FDListener::READ), ReactorWrapFuncUDPTest);
    // Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(udp_arg->fd, FDListener::READ), UDPServerAcceptTest);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(boardcast_arg->fd, FDListener::READ), ReactorWrapFuncBroadcastPong);
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(tcp_arg->fd, FDListener::READ), ReactorWrapFuncTCPNewConnection);
}


int CheckSTDIN()
{
    AcceptInput();

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

typedef SharedPtr<Writer> (*cmd_func_t_writer)(char *, size_t, struct sockaddr_in, int);
typedef SharedPtr<Reader> (*cmd_func_t_reader)(char *, size_t, struct sockaddr_in, int);

void ReactorWrapFuncUDPTest(int socket_fd)
{
    char buffer[MAXLINE];
    struct sockaddr_in client_addr;
    int n;
    socklen_t len = sizeof(struct sockaddr);
    Factory<SharedPtr<Command>, char, serv_arg_t*, SharedPtr<Command>(*)(serv_arg_t*)> command_factory;
    serv_arg_t udp_arg;

    // LAB COMP
    void *handle_read = dlopen("/home/student/roy-yablonka/projects/framework/libread.so", RTLD_LAZY);
    void *handle_write = dlopen("/home/student/roy-yablonka/projects/framework/libwrite.so", RTLD_LAZY);

    // //HOME COMP
    // void *handle_read = dlopen("/home/roy/git/roy-yablonka/projects/framework/libread.so", RTLD_LAZY);
    // void *handle_write = dlopen("/home/roy/git/roy-yablonka/projects/framework/libwrite.so", RTLD_LAZY);

    if (handle_read == NULL || handle_write == NULL) 
    {
        printf("bad handle\n"); 
        perror("handle");
    }
    else printf("success with handles\n");

    cmd_func_t_writer func_writer = reinterpret_cast<cmd_func_t_writer>(dlsym(handle_write, "CreateWriter"));
    cmd_func_t_reader func_reader = reinterpret_cast<cmd_func_t_reader>(dlsym(handle_read, "CreateReader"));

    if ((NULL == func_writer) || (NULL == func_reader))
    {
        exit(EXIT_FAILURE);
    }

    // memset(&client_addr, 0, sizeof(client_addr));

    udp_arg = UdpManager(socket_fd, buffer).Receive();

    // n = recvfrom(socket_fd, (char *)buffer, MAXLINE,
    //                 MSG_WAITALL, (struct sockaddr *)&client_addr,
    //                 (socklen_t *)&len);

    // buffer[n] = '\0';

    // udp_arg.address = client_addr;
    // udp_arg.buffer = buffer;
    // udp_arg.fd = socket_fd;
    // udp_arg.port = 8080;

    command_factory.add(0, ReadFunc);
    command_factory.add(1, WriteFunc);

    // (*command_factory.create(*buffer, &udp_arg))();

    UDPInputAnalyzer udp_input_analyzer(command_factory);
    udp_input_analyzer.Respond(*buffer, udp_arg);


    // if (*buffer == 1)
    // {
    //     SharedPtr<Command> writer = (*func_writer)(buffer, 17);

    //     buffer[9] = (*writer)();
    //     (buffer[9] == 1) ? (logger->Log(Logger::INFO, "Received (with status = 1) write request from client")) : (logger->Log(Logger::INFO, "Received (with status = 0) write request from client"));

    //     sendto(socket_fd, (const char *)buffer, 10,
    //             MSG_CONFIRM, (const struct sockaddr *)&client_addr,
    //             len);

    //     logger->Log(Logger::INFO, "Sent package to Client");
    //     // std::cout << "end of write mode" << std::endl;
    // }
    // else
    // {
    //     SharedPtr<Command> reader = (*func_reader)(buffer, 10);
    //     buffer[9] = (*reader)();

    //     (buffer[9] == 1) ? (logger->Log(Logger::INFO, "Received (with status = 1) read request from client")) : (logger->Log(Logger::INFO, "Received (with status = 0) read request from client"));

    //     sendto(socket_fd, (const char *)buffer, 4106,
    //             MSG_CONFIRM, (const struct sockaddr *)&client_addr,
    //             len);

    //     logger->Log(Logger::INFO, "Sent package to Client");
    // }

    dlclose(handle_read);
    dlclose(handle_write);
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

SharedPtr<Command> ReadFunc(serv_arg_t *arg)
{
    return SharedPtr<Command>(new Reader(arg->buffer, 10, arg->address, arg->fd));
}

SharedPtr<Command> WriteFunc(serv_arg_t *arg)
{
    return SharedPtr<Command>(new Writer(arg->buffer, 17, arg->address, arg->fd));
}
