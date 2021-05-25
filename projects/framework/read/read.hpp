#ifndef RD70_READ
#define RD70_READ

#include <fstream>
#include "command.hpp"
#include "logger.hpp"
#include "dsbuffer.hpp"
#include "iofile.hpp"
#include "udp_manager.hpp"

// #include "singleton.hpp"

class Reader:public IOFile
{
public:
    explicit Reader(char *buffer_, std::size_t offset, struct sockaddr_in client_addr, int socket_fd);
    virtual ~Reader();
    bool operator()();

private:
    std::ifstream m_file;

    static Logger *read_logger;

};

// Logger* Reader::logger = Singleton<Logger>::GetInstance();

// extern "C"
// {
// SharedPtr<Command> Create(char *buf, size_t offset, struct sockaddr_in client_addr, int socket_fd);
// char GetKey();
// }

extern "C"
{
SharedPtr<Command> Create(serv_arg_t *);
char GetKey();
}

#endif //RD70_READ
