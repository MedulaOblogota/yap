#ifndef RD70_CONTINUE_TASK
#define RD70_CONTINUE_TASK

#include "task.hpp"
class ContinueTask:public Task
{
public:
    ContinueTask();
    ~ContinueTask() {};
    void *Execute(void *, int);
};

#endif//RD70_CONTINUE_TASK