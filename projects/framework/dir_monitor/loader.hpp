#ifndef RD70_LOADER
#define RD70_LOADER

#include <string>

#include "factory.hpp"
#include "dir_monitor.hpp"
#include "shared_ptr.hpp"
#include "command.hpp"
#include "udp_manager.hpp"

class Loader
{
public:
    static void LoadFile(std::string filename);
private:
    static Factory<SharedPtr<Command>, char, serv_arg_t*>& m_command_factory;
};

// SharedPtr<Command> ReadFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(new IOFile(arg->buffer, 10, arg->address, arg->fd));
// }

// SharedPtr<Command> WriteFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(new IOFile(arg->buffer, 17, arg->address, arg->fd));
// }

#endif //RD70_LOADER