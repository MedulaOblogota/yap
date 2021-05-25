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

#include "udp.hpp"
#include "shared_ptr.hpp"
#include "factory.hpp"
#include "udp_input_analyzer.hpp"
#include "udp_manager.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "reactor.hpp"

#define STDIN (0)
#define UNUSED(x) (void)(x)
#define MAXLINE (4200)


void ReactorWrapFuncUDPTest(int socket_fd)
{
    char buffer[MAXLINE];
    Factory<SharedPtr<Command>, char, serv_arg_t*> *command_factory = Singleton<Factory<SharedPtr<Command>, char, serv_arg_t*> >::GetInstance();
    serv_arg_t udp_arg;

    udp_arg = UdpManager(socket_fd, buffer).Receive();

    UDPInputAnalyzer udp_input_analyzer(*command_factory);

    udp_input_analyzer.Respond(*buffer, udp_arg);
}

void UDPServerSetFD(serv_arg_t *args)
{
    UDPServerSetSockAddrIn(&args->address, args->port);

    logger->Log(Logger::DEBUG, "port num is ");

    std::cout << "port num is " << args->port << std::endl;

    args->fd = UDPServerSocketAndBind(&args->address, sizeof(struct sockaddr_in));
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

void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort)
{
    memset(address, 0, sizeof(struct sockaddr_in));

    address->sin_family = AF_INET; /*Internet Protocol v4 addresses*/
    address->sin_addr.s_addr = htonl(INADDR_ANY);
    address->sin_port = htons(hostshort);
}

int CheckSTDIN()
{
    AcceptInput();

    return (1);
}

void ReactorWrapFuncCheckSTDIN(int unused)
{
    UNUSED(unused);

    if (CheckSTDIN())
    {
        Singleton<Reactor>::GetInstance()->Stop();
    }
}