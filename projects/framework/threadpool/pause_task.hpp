#ifndef RD70_PAUSE_TASK
#define RD70_PAUSE_TASK

#include "task.hpp"
class PauseTask:public Task
{
public:
    PauseTask();
    ~PauseTask() {};
    void *Execute(void *, int);
};

#endif//RD70_PAUSE_TASK