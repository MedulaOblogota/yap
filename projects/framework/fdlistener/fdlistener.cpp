#include <sys/time.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include <utility>
#include <unistd.h>
#include <stdio.h>

#include "fdlistener.hpp"


std::vector<std::pair<int, FDListener::FDType> > FDListener::Wait(const std::vector<std::pair<int, FDType> > &vec)
{
    std::map<FDType, fd_set> fdmap;
    int max = 0;

    FD_ZERO(&fdmap[READ]);
    FD_ZERO(&fdmap[WRITE]);
    FD_ZERO(&fdmap[EXCEPT]);

    for (std::vector<std::pair<int, FDType> >::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        FD_SET((*it).first, &fdmap[(*it).second]);
        max = (max < (*it).first) ? (*it).first : max;
    }

    if (select(max + 1, &fdmap[READ], &fdmap[WRITE], &fdmap[EXCEPT], NULL) == -1)
    {
        perror("select");
    }

    std::vector<std::pair<int, FDType> > ret;

    for (std::vector<std::pair<int, FDType> >::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (FD_ISSET((*it).first, &fdmap[(*it).second]))
        {
            ret.push_back(*it);
        }
    }

    return (ret);
}
