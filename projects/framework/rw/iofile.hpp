#ifndef RD70_IOFILE
#define RD70_IOFILE

#include <netinet/in.h>

#include "command.hpp"
#include "dsbuffer.hpp"

class IOFile:public Command
{
public:
    explicit IOFile(char *buffer, size_t offset, struct sockaddr_in client_addr, int socket_fd)
        :  m_buffer(buffer), m_offset(offset), m_ds_buffer(buffer), m_client_addr(client_addr), m_socket_fd(socket_fd)
    {  }
    virtual ~IOFile() {};
    virtual bool operator()() = 0;

protected:
    char *m_buffer;
    std::size_t m_offset;
    DsBuffer m_ds_buffer;
    struct sockaddr_in m_client_addr;
    int m_socket_fd;
};

#endif //RD70_IOFILE