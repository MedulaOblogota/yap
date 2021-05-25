#ifndef RD70_COMMAND
#define RD70_COMMAND


#include "dsbuffer.hpp"

class Command
{
public:
    // explicit Command() {};
    virtual ~Command() {};
    virtual bool operator()() = 0;

    // virtual SharedPtr<Command> CreateWriter();
};

#endif //RD70_COMMAND
