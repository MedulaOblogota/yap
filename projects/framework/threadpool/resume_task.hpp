#ifndef RD70_RESUME_TASK
#define RD70_RESUME_TASK

#include "task.hpp"
class ResumeTask:public Task
{
public:
    ResumeTask();
    ~ResumeTask() {};
    void *Execute(void *, int);
};

#endif//RD70_RESUME_TASK