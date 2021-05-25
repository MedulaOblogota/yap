#include <string>
#include <boost/function.hpp>

#include "reactor.hpp"
#include "dir_monitor.hpp"
#include "loader.hpp"
#include "inotify.hpp"

// Inotify DirMonitor::m_inotify("/home/student/roy-yablonka/projects/bin/lib");
Inotify DirMonitor::m_inotify("/home/roy/roy-yablonka/projects/bin/lib");
DirMonitor::DirMonitor(Reactor &reactor, boost::function<void(int)> func)
    : m_reactor(reactor)//, m_inotify(path)
{
    // std::cout << "before watch directory" << std::endl;
    // m_inotify.WatchDirectory();
    // std::cout << "after watch directory" << std::endl;
    // std::cout << m_inotify.m_fd << std::endl;
    m_reactor.AddFD(std::make_pair(m_inotify.m_fd, FDListener::READ), func);
    // std::cout << "after watch directory" << std::endl;
}

void DirMonitor::PluginLoader(int inotifyfd)
{
	(void)inotifyfd;
    // std::cout << "before m_inotify.WatchDirectory()";
    m_inotify.WatchDirectory();
    // std::vector<std::string> filenames = m_inotify.GetFilenames();

    // std::cout << "in DirMonitor func" << std::endl;

    std::string filenames = m_inotify.WatchDirectory();

    // std::cout << "vector size is " << filenames.size() << std::endl;

    // for (size_t i = 0; i < filenames.size(); ++i)
    // {
        // std::cout << std::endl << std::endl << "LOADING FILE " << filenames << std::endl << std::endl;
        Loader::LoadFile(filenames);
        // filenames.erase(filenames.begin() + i);
    // }

}
