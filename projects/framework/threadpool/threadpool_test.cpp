#include <unistd.h>

#include "threadpool.hpp"
#include "specific_task.hpp"
#include "shared_ptr.hpp"

int main()
{
    ThreadPool threadpool(10);
    SharedPtr<SpecificTask> task_third = SharedPtr<SpecificTask>(new SpecificTask(1));
    SharedPtr<SpecificTask> task_second = SharedPtr<SpecificTask>(new SpecificTask(5));
    SharedPtr<SpecificTask> task_first = SharedPtr<SpecificTask>(new SpecificTask(10));
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);
    // threadpool.AddTask(task);

    // for (size_t i = 0; i < 5; ++i)
    // {
    //     threadpool.AddTask(task_second);
    // }

    // for (size_t i = 0; i < 5; ++i)
    // {
    //     threadpool.AddTask(task_first);
    // }

    // // threadpool.Pause();


    // for (size_t i = 0; i < 5; ++i)
    // {
    //     threadpool.AddTask(task_third);
    // }

    // threadpool.Pause();
    for (size_t i = 0; i < 10; ++i)
    {
        threadpool.AddTask(SharedPtr<SpecificTask>(new SpecificTask(i)));
    }
    // threadpool.Resume();
    // threadpool.Resume();
    // sleep(2);
}