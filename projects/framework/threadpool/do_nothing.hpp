#ifndef RD70_DO_NOTHING
#define RD70_DO_NOTHING

#include "task.hpp"
class DoNothing:public Task
{

public:
    DoNothing(int priority_);
    ~DoNothing() {};
    void Execute();

    // Task& operator>(const Task& other_);
};

#endif //RD70_DO_NOTHING