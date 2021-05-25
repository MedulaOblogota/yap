#include <pthread.h>
#include <unistd.h>

#include "threadpool.hpp"
#include "shared_ptr.hpp"
#include "do_nothing.hpp"
#include "specific_task.hpp"
// #include "pause_task.hpp"
// #include "resume_task.hpp"
// #include "continue_task.hpp"

ThreadPool::ThreadPool(size_t threads_number_)
    : m_container(threads_number_), m_queue() , run(true), m_num_threads(threads_number_) 
{
    size_t i = 0;
    pthread_mutex_init(&m_pauseMutex, NULL);


    for (i = 0; i < threads_number_; ++i)
    {
        pthread_create(&m_container.at(i), NULL, ThreadPool::Run, this);
    }


}


ThreadPool::~ThreadPool()
{
    size_t i = 0;

    sleep(2);

    run = false;

    for (i = 0; i < m_num_threads; ++i)
    {
        m_queue.Push(SharedPtr<Task>(new DoNothing(0)));
    }

    std::cout << "container size is " << m_container.size() << std::endl;
    for (i = 0; i < m_container.size(); ++i)
    {
        pthread_join(m_container.at(i), NULL);
    }
}

void ThreadPool::AddTask(SharedPtr<Task> task_)
{
    m_queue.Push(task_);
}

SharedPtr<Task> ThreadPool::GetTask()
{
    SharedPtr<Task> task = m_queue.Pop();

    return task;
}

void *ThreadPool::Run(void *v_tp)
{
    ThreadPool *threadpool = static_cast<ThreadPool *>(v_tp);

    while (threadpool->run)
    {
 
        threadpool->GetTask()->Execute();


    }

    return NULL;
}

void ThreadPool::Pause()
{
    SharedPtr<PauseTask> pause_task = SharedPtr<PauseTask>(new PauseTask(&m_pauseMutex));

    pthread_mutex_lock(&m_pauseMutex);

    for (size_t i = 0; i < m_num_threads; ++i)
    {
        m_queue.Push(pause_task);
    }
}

void ThreadPool::Resume()
{
    pthread_mutex_unlock(&m_pauseMutex);
}


bool operator<(const SharedPtr<Task> first_, const SharedPtr<Task> other_)
{
    return (first_->GetPriority() > other_->GetPriority());
}