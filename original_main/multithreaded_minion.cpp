/* compile with "gcc minion.cpp ping_pong_network.cpp -g -I ./" */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <dlfcn.h>

#include "ping_pong_socket.h"
#include "read.hpp"
#include "write.hpp"
#include "command.hpp"
// #include "udp.hpp"

#include "logger.hpp"
#include "singleton.hpp"
#include "shared_ptr.hpp"
#include "multithreaded_minion.hpp"

#include "factory_sync.hpp"

#define PORT 8080
#define MAXLINE (4200)

// void ExitFunc()
// {
//     Singleton<Logger>::Delete();
//     exit(0);
// }

void CreateStdInput(int port_num)
{
    std::string input;
    pthread_t thread;

    pthread_create(&thread, NULL, CreateUDPServer, &port_num);

    AcceptInput();

    printf("exited\n");
    // pthread_join(thread, NULL);
}

void *CreateUDPServer(void *port_num_v)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int num_of_arg = 0;
    void *handle = dlopen("/home/student/roy-yablonka/projects/bin/lib/rw_cmd.so", RTLD_LAZY);


    Logger *logger = Singleton<Logger>::GetInstance();
    std::ofstream *logfile = new std::ofstream("log.log", std::ofstream::out);

    SharedPtr<std::ostream> logfile_sp(logfile);

    logger->SetOutput(logfile_sp);
    logger->SetOutputSeverity(Logger::DEBUG);

    if (NULL == handle)
    {
        logger->Log(Logger::ERROR, "failed to open reader-writer");
        exit(EXIT_FAILURE);
    }

    num_of_arg = *(int *)port_num_v;

    logger->Log(Logger::INFO, "port number allocated");
    /* Creating socket file descriptor */
    if ((sockfd = CreateSocket()) < 0)
    {
        logger->Log(Logger::ERROR, "Error with creating Socket for Server");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr = FillServerInfo(num_of_arg);

    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        logger->Log(Logger::ERROR, "Error with binding Server to socket");
        exit(EXIT_FAILURE);
    }

    int num = 6;

    while (1)
    {
        char buffer[MAXLINE];
        int n;
        socklen_t len = sizeof(struct sockaddr);

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     (socklen_t *)&len);

        buffer[n] = '\0';

        if (*buffer == 1)
        {
            typedef SharedPtr<Writer> (*cmd_func_t)(char *, size_t);
            cmd_func_t func = reinterpret_cast<cmd_func_t>(dlsym(handle, "CreateWriter"));
            if (NULL == func)
            {
                logger->Log(Logger::ERROR, "Error with opening Writer functions");
                exit(EXIT_FAILURE);
            }

            SharedPtr<Writer> writer = (*func)(buffer, 17);

            // Writer writer(buffer, 17);

            buffer[9] = (*writer)();
            (buffer[9] == 1) ? (logger->Log(Logger::INFO, "Received (with status = 1) write request from client")) : (logger->Log(Logger::INFO, "Received (with status = 0) write request from client"));

            sendto(sockfd, (const char *)buffer, 10,
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                   len);

            logger->Log(Logger::INFO, "Sent package to Client");
        }
        else
        {
            typedef SharedPtr<Reader> (*cmd_func_t)(char *, size_t);
            cmd_func_t func = reinterpret_cast<cmd_func_t>(dlsym(handle, "CreateReader"));
            if (NULL == func)
            {
                logger->Log(Logger::ERROR, "Error with opening Reader functions");
                exit(EXIT_FAILURE);
            }

            SharedPtr<Reader> reader = (*func)(buffer, 10);

            buffer[9] = (*reader)();

            (buffer[9] == 1) ? (logger->Log(Logger::INFO, "Received (with status = 1) read request from client")) : (logger->Log(Logger::INFO, "Received (with status = 0) read request from client"));

            sendto(sockfd, (const char *)buffer, 4106,
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                   len);

            logger->Log(Logger::INFO, "Sent package to Client");
        }

        // --num;
    }

    printf("\n\n\nENDING\n\n\n");
    logger->Log(Logger::DEBUG, "ending server");
    // logger->~Logger();
    // Singleton<Logger>::Delete();
    // logfile->close();

    return NULL;
}