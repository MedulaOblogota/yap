#ifndef RD70_REACTOR
#define RD70_REACTOR

#include <boost/core/noncopyable.hpp>
#include <iostream>
#include <map>
#include <boost/function.hpp>

#include "fdlistener.hpp"

class Reactor: private boost::noncopyable
{
public:
    //generated Ctor and Dtor sufficient

    void AddFD(std::pair<int, FDListener::FDType>, boost::function<void(int)>);
    void RemoveFd(std::pair<int, FDListener::FDType>);

    void Start();
    void Stop();

private:
    std::map<std::pair<int, FDListener::FDType>, boost::function<void(int)> > m_map;
    int m_run;
};

#endif //RD70_REACTOR