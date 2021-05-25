// 31.12 : 10:10am -> compile:
//       g++ -L/home/student/roy-yablonka/projects/framework -Wall -o server ./framework/main/server_main.cpp ./framework/factorysync/factory_sync.cpp ./framework/command/addseverity.cpp ./framework/command/command.cpp ./framework/command/exit.cpp ./framework/command/reduceseverity.cpp ./framework/reactor/reactor.cpp ./framework/fdlistener/fdlistener.cpp ./framework/logger/logger.cpp  ./framework/udp_manager/udp_manager.cpp ./framework/udp_input_analyzer/udp_input_analyzer.cpp ./framework/inotify/inotify.cpp ./framework/dir_monitor/dir_monitor.cpp ./framework/dir_monitor/loader.cpp -I ./include/ -lpthread -ldl
// 31.12 : 10:10am -> libsos:
//      1. g++ -c -Wall -fpic ./rw/write.cpp ./logger/logger.cpp -I ../include/
//      2. g++ -shared -o libwrite.so *.o      

#include "reactor.hpp"
#include "dir_monitor.hpp"
#include "singleton.hpp"
#include "server.hpp"

Logger *m_logger = Singleton<Logger>::GetInstance();

int main(int argc, char *argv[])
{
    (void)argc;
    serv_arg_t udp_arg;

    std::ofstream *logfile = new std::ofstream("log2.log", std::ofstream::out);

    SharedPtr<std::ostream> logfile_sp(logfile);

    m_logger->SetOutput(logfile_sp);
    m_logger->SetOutputSeverity(Logger::DEBUG);

    udp_arg.port = atoi(argv[1]);
    UDPServerSetFD(&udp_arg);

    Reactor *reactor = Singleton<Reactor>::GetInstance();
    Singleton<Reactor>::GetInstance()->AddFD(std::make_pair(STDIN, FDListener::READ), ReactorWrapFuncCheckSTDIN);
    DirMonitor dm(*reactor, dm.PluginLoader);

    reactor->AddFD(std::make_pair(udp_arg.fd, FDListener::READ), ReactorWrapFuncUDPTest);

    reactor->Start();

    if (-1 == close(udp_arg.fd))
    {
        perror("udp_arg close");
    }

    return 0;
}