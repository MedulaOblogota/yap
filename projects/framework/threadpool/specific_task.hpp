#ifndef RD70_SPEC_TASK
#define RD70_SPEC_TASK

#include "task.hpp"
class SpecificTask:public Task
{
public:
    SpecificTask(int priority_);
    ~SpecificTask() {};
    void Execute();

private:
    int m_i;

    // Task& operator>(const Task& other_);
};

#endif //RD70_SPEC_TASK