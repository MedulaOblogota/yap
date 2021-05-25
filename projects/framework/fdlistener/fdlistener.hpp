#ifndef RD70_FDLISTENER
#define RD70_FDLISTENER

#include <sys/time.h>
#include <vector>
#include <utility>

class FDListener
{
public:
    enum FDType {READ, WRITE, EXCEPT};

    //default ctor dtor cctor assignment op

    std::vector<std::pair<int, FDType> > Wait(const std::vector<std::pair<int, FDType> > &vec);
    //void SetTime(struct time_val time_);

private:
    //struct time_val m_time;
};


#endif //RD70_FDLISTENER