#ifndef RD70_TASK
#define RD70_TASK

#include <pthread.h>

class Task
{
public:
    Task(int priority_);
    virtual ~Task() {};
    virtual void Execute() = 0;

    virtual bool operator>(const Task& other_);
    virtual bool operator<(const Task& other_);
    int GetPriority();

protected:
    // pthread_cond_t m_cond;
    // pthread_mutex_t m_mutex;

private:
    int m_priority;

    void operator=(const Task& other_);
    Task(const Task& other_);
};

#endif //RD70_TASK