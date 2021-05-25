// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>

#include "ping_pong_socket.h"
// #include "read.hpp"
// #include "write.hpp"

#include "logger.hpp"
#include "singleton.hpp"
// #include "shared_ptr.hpp"
// #include "udp.hpp"
#include "multithreaded_minion.hpp"

void LoggerExit()
{
    //Logger *delete_logger = Singleton<Logger>::GetInstance();
    // delete_logger->~Logger();
    Singleton<Logger>::Delete();
    // printf("at exit!");
}


int main(int argc, char *argv[])
{
    atexit(LoggerExit);
    int port_num;
    // Logger *logger = Singleton<Logger>::GetInstance();
    // logger->Log(Logger::ERROR, "ani main gever rezah 1");

    if (!IsEnoughArgc(argc, 2))
    {
        exit(EXIT_FAILURE);
    }

    port_num = atoi(argv[1]);

    // logger->Log(Logger::ERROR, "ani main gever rezah 2");
    CreateStdInput(port_num);
    // logger->Log(Logger::ERROR, "ani main gever rezah 3");

    return 0;
}
