#ifndef RD70_DIR_MONITOR
#define RD70_DIR_MONITOR

#include <string>
#include <boost/function.hpp>

#include "reactor.hpp"
#include "inotify.hpp"

class DirMonitor
{
public:
    explicit DirMonitor(Reactor &reactor, boost::function<void(int)>);
    static void PluginLoader(int);
    
private:
    Reactor &m_reactor;
    static Inotify m_inotify;
};

#endif //RD70_DIR_MONITOR