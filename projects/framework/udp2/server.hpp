// compile: g++ -L/home/student/roy-yablonka/projects/framework -Wall -o server ./framework/main/reactor_test_main_server.cpp ./framework/factorysync/factory_sync.cpp ./framework/command/addseverity.cpp ./framework/command/command.cpp ./framework/command/exit.cpp ./framework/command/reduceseverity.cpp ./framework/reactor/reactor.cpp ./framework/fdlistener/fdlistener.cpp ./framework/rw/write.cpp ./framework/rw/read.cpp ./framework/logger/logger.cpp ./framework/rw/dsbuffer.cpp -I ./include/ -lpthread ./framework/write.so ./framework/read.so -ldl

//for libsos:
//  1. g++ -c -Wall -fpic ./rw/write.cpp ./logger/logger.cpp -I ../include/
//  2. g++ -shared -o libwrite.so *.o

#ifndef RD70_SERVER
#define RD70_SERVER

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
// #include "write.hpp"
// #include "read.hpp"
#include "command.hpp"
#include "logger.hpp"
#include "factory_sync.hpp"
#include "udp_manager.hpp"
#include "udp_input_analyzer.hpp"
#include "dir_monitor.hpp"
#include "loader.hpp"

#define STDIN (0)
#define NUM_OF_SOCKETS (4)
#define UNUSED(x) (void)(x)
#define MAXLINE (4200)

int CheckSTDIN();
void CheckIfError(int err_num, const char *str);
void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort);
int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len);
void ReactorWrapFuncUDPTest(int client_fd);
void UDPServerSetFD(serv_arg_t *args);
void ReactorWrapFuncCheckSTDIN(int unused);

// Logger *logger = Singleton<Logger>::GetInstance();

// void ReactorWrapFuncCheckSTDIN(int unused)
// {
//     UNUSED(unused);

//     if (CheckSTDIN())
//     {
//         Singleton<Reactor>::GetInstance()->Stop();
//     }
// }

// int CheckSTDIN()
// {
//     AcceptInput();

//     return (1);
// }

// void CheckIfError(int err_num, const char *str)
// {
//     if (0 > err_num)
//     {
//         perror(str);

//         exit(-1);
//     }
// }

// void UDPServerSetSockAddrIn(struct sockaddr_in *address, uint16_t hostshort)
// {
//     memset(address, 0, sizeof(struct sockaddr_in));

//     address->sin_family = AF_INET; /*Internet Protocol v4 addresses*/
//     address->sin_addr.s_addr = htonl(INADDR_ANY);
//     address->sin_port = htons(hostshort);
// }

// int UDPServerSocketAndBind(struct sockaddr_in *serv_addr, socklen_t len)
// {
//     int socket_fd = 0;
//     int opt = 1;

//     if (0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)))
//     {
//         perror("socket");
//         exit(-1);
//     }

//     if (0 > setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                        &opt, sizeof(opt)))
//     {
//         perror("setsockopt");
//         exit(-1);
//     }

//     if (bind(socket_fd, (const struct sockaddr *)serv_addr, len))
//     {
//         perror("bind");
//         if (-1 == close(socket_fd))
//         {
//             perror("close");
//         }
//         exit(-1);
//     }

//     return (socket_fd);
// }

// void ReactorWrapFuncUDPTest(int socket_fd)
// {
//     std::cout << std::endl << std::endl<< "in UDP after reactor.add!" << std::endl << std::endl;

//     logger->Log(Logger::DEBUG, "got here man!");

//     char buffer[MAXLINE];
//     Factory<SharedPtr<Command>, char, serv_arg_t*> *command_factory = Singleton<Factory<SharedPtr<Command>, char, serv_arg_t*> >::GetInstance();
//     serv_arg_t udp_arg;
//     static int run = 1;

//     std::cout << "run number " << run <<std::endl;
//     ++run;

    
//     udp_arg = UdpManager(socket_fd, buffer).Receive();
//     std::cout << "reached here2" << std::endl;

//     UDPInputAnalyzer udp_input_analyzer(*command_factory);

//     std::cout << "reached here4" << std::endl;
//     udp_input_analyzer.Respond(*buffer, udp_arg);
//     std::cout << "reached here5" << std::endl;
// }

// void UDPServerSetFD(serv_arg_t *args)
// {
//     UDPServerSetSockAddrIn(&args->address, args->port);

//     logger->Log(Logger::DEBUG, "port num is ");

//     std::cout << "port num is " << args->port << std::endl;

//     args->fd = UDPServerSocketAndBind(&args->address, sizeof(struct sockaddr_in));
// }

#endif //RD70_SERVER