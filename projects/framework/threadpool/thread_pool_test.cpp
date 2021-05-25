#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.hpp"
#include "shared_ptr.hpp"
#include "task.hpp"

//******************test use task********************************************/
class MyTask : public Task
{
public:
    MyTask(int priority, int a) :Task(priority), m_a(a) {};
    virtual ~MyTask() {}
    virtual void *Execute(void *, int) {std::cout << "task: " << m_a << std::endl;}

private:
    int m_a;
};

class MyTaskSleep : public Task
{
public:
    MyTaskSleep(int priority, int a) :Task(priority), m_a(a) {};
    virtual ~MyTaskSleep() {}
    virtual void *Execute(void *, int) {sleep(2); std::cout << "TASK SLEEP: " << m_a << std::endl;}

private:
    int m_a;
};
//***********************************************************************/

int main()
{
    ThreadPool t(5);
    t.Pause();
    
    for (int i = 0; i < 10; i++)
    {
        SharedPtr<Task> task(new MyTask(i, i));
        t.AddTask(task);
    }

    SharedPtr<Task> task_sleep(new MyTaskSleep(10, 10));
    t.AddTask(task_sleep);

    sleep(1);
    t.Resume();

    return 0;
}