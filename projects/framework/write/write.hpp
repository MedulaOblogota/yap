#ifndef RD70_WRITE
#define RD70_WRITE

#include <fstream>
#include "logger.hpp"
// #include "singleton.hpp"

#include "command.hpp"
#include "dsbuffer.hpp"
#include "iofile.hpp"
#include "udp_manager.hpp"

class Writer:public IOFile
{
public:
    explicit Writer(char *buffer_, std::size_t offset, struct sockaddr_in client_addr, int socket_fd);
    virtual ~Writer();
    bool operator()();

private:
    // const char *m_buffer;
    std::ofstream m_file;
		// std::size_t m_offset;
		// DsBuffer m_ds_buffer;

    static Logger *write_logger;

};

// extern "C"
// {
// SharedPtr<Command> Create(char *buf, size_t offset, struct sockaddr_in client_addr, int socket_fd);
// char GetKey(char *buf);
// }

extern "C"
{
SharedPtr<Command> Create(serv_arg_t *arg);
char GetKey();
}

#endif //RD70_WRITE
