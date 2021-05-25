#include <boost/function.hpp>
#include <iostream>

#include "reactor.hpp"
#include "fdlistener.hpp"

void Reactor::AddFD(std::pair<int, FDListener::FDType> pair_, boost::function<void(int)> func)
{
    m_map.insert(std::pair<std::pair<int, FDListener::FDType>, boost::function<void(int)> >(pair_, func));
}

void Reactor::RemoveFd(std::pair<int, FDListener::FDType> pair_)
{
    m_map.erase(pair_);
}

void Reactor::Start()
{
    FDListener fdl;
    // m_map.insert()

    m_run = 1;

    while (m_run)
    {  
        std::vector<std::pair<int, FDListener::FDType> > vec;
        for (std::map<std::pair<int, FDListener::FDType>, boost::function<void(int)> >::iterator it = m_map.begin(); it != m_map.end(); ++it)
        {
            vec.push_back((*it).first);
        }

        std::vector<std::pair<int, FDListener::FDType> > setVec(fdl.Wait(vec));

        for (std::vector<std::pair<int, FDListener::FDType> >::iterator it = setVec.begin(); it != setVec.end(); ++it)
        {
            m_map[(*it)]((*it).first);
        }
    }
}

void Reactor::Stop()
{
    m_run = 0;
    exit(0);
}
