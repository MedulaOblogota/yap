#ifndef RD70_UDP_INPUT_ANALYZER
#define RD70_UDP_INPUT_ANALYZER

#include "command.hpp"
#include "shared_ptr.hpp"
#include "factory.hpp"
#include "udp_manager.hpp"

class UDPInputAnalyzer
{
public:
    //generated Dtor sufficient
    explicit UDPInputAnalyzer(Factory<SharedPtr<Command>, char, serv_arg_t*, SharedPtr<Command>(*)(serv_arg_t*)>& command_factory);
    void Respond(char, serv_arg_t&);

private:
    Factory<SharedPtr<Command>, char, serv_arg_t*, SharedPtr<Command>(*)(serv_arg_t*)>& m_command_factory;
};

// SharedPtr<Command> ReadFunc(serv_arg_t *arg);
// SharedPtr<Command> WriteFunc(serv_arg_t *arg);

#endif //RD70_UDP_INPUT_ANALYZER