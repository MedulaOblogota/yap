#include <dlfcn.h>
#include <arpa/inet.h>
#include <string.h>

#include "udp_manager.hpp"
#include "shared_ptr.hpp"
#include "command.hpp"
#include "iofile.hpp"

#define MAXLINE (4200)
// typedef SharedPtr<IOFile> (*cmd_func_t_writer)(char *, size_t, struct sockaddr_in, int);
// typedef SharedPtr<IOFile> (*cmd_func_t_reader)(char *, size_t, struct sockaddr_in, int);

UdpManager::UdpManager(int socket_fd, char *buffer)
    : m_socket_fd(socket_fd), m_buffer(buffer)
{

}

serv_arg_t UdpManager::Receive()
{
    // char buffer[MAXLINE];
    struct sockaddr_in client_addr;
    int n;
    socklen_t len = sizeof(struct sockaddr);
    // Factory<SharedPtr<Command>, char, serv_arg_t*, SharedPtr<Command>(*)(serv_arg_t*)> command_factory;
    serv_arg_t udp_arg;

    // // LAB COMP
    // // void *handle_read = dlopen("/home/student/roy-yablonka/projects/framework/read.so", RTLD_LAZY);
    // // void *handle_write = dlopen("/home/student/roy-yablonka/projects/framework/write.so", RTLD_LAZY);

    // //HOME COMP
    // void *handle_read = dlopen("/home/roy/git/roy-yablonka/projects/framework/libread.so", RTLD_LAZY);
    // void *handle_write = dlopen("/home/roy/git/roy-yablonka/projects/framework/libwrite.so", RTLD_LAZY);

    // if (handle_read == NULL || handle_write == NULL) 
    // {
    //     printf("bad handle\n"); 
    //     perror("handle");
    // }
    // else printf("success with handles\n");

    // cmd_func_t_writer func_writer = reinterpret_cast<cmd_func_t_writer>(dlsym(handle_write, "Create"));
    // cmd_func_t_reader func_reader = reinterpret_cast<cmd_func_t_reader>(dlsym(handle_read, "Create"));

    // if ((NULL == func_writer) || (NULL == func_reader))
    // {
    //     exit(EXIT_FAILURE);
    // }
    // else 

    memset(&client_addr, 0, sizeof(client_addr));

    n = recvfrom(m_socket_fd, (char *)m_buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *)&client_addr,
                    (socklen_t *)&len);

    m_buffer[n] = '\0';

    udp_arg.address = client_addr;
    udp_arg.buffer = m_buffer;
    udp_arg.fd = m_socket_fd;
    udp_arg.port = 8080;

    return udp_arg;

    // command_factory.add(0, ReadFunc);
    // command_factory.add(1, WriteFunc);

    // (*command_factory.create(*buffer, &udp_arg))();
}

// SharedPtr<Command> ReadFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(Create(arg->buffer, 10, arg->address, arg->fd));
// }

// SharedPtr<Command> WriteFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(Create(arg->buffer, 17, arg->address, arg->fd));
// }