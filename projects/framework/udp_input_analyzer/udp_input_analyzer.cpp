#include "udp_input_analyzer.hpp"
#include "shared_ptr.hpp"

UDPInputAnalyzer::UDPInputAnalyzer(Factory<SharedPtr<Command>, char, serv_arg_t*, SharedPtr<Command>(*)(serv_arg_t*)>& command_factory)
    : m_command_factory(command_factory)
{
    // command_factory.add(0, ReadFunc);
    // command_factory.add(1, WriteFunc);
}

void UDPInputAnalyzer::Respond(char key, serv_arg_t& udp_arg)
{
    // command_factory.add(0, ReadFunc);
    // command_factory.add(1, WriteFunc);
    // std::cout << "before factory create" << std::endl;
    // std::cout << "key = " << (int)key << std::endl;
    // std::cout << std::endl << std::endl << "udp_arg:" << std::endl << udp_arg.port << std::endl << std::endl;
    (*m_command_factory.create(key, &udp_arg))();
    // std::cout << "after factory create" << std::endl;

}

// SharedPtr<Command> ReadFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(new Reader(arg->buffer, 10, arg->address, arg->fd));
// }

// SharedPtr<Command> WriteFunc(serv_arg_t *arg)
// {
//     return SharedPtr<Command>(new Writer(arg->buffer, 17, arg->address, arg->fd));
// }