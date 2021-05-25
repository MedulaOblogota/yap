#ifndef RD70_UDP_MANAGER
#define RD70_UDP_MANAGER

#include <arpa/inet.h>
#include "shared_ptr.hpp"

typedef struct serv_arg
{
    struct sockaddr_in address;
    uint16_t port;
    int fd;
    char *buffer;
} serv_arg_t;

class UdpManager
{
public:
    explicit UdpManager(int socket_fd, char *buffer);
    serv_arg_t Receive();

private:
    int m_socket_fd;
    char *m_buffer;
};

// SharedPtr<Command> ReadFunc(serv_arg_t *arg);

// SharedPtr<Command> WriteFunc(serv_arg_t *arg);

#endif //RD70_UDP_MANAGER