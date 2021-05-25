#ifndef RD70_THREADPOOL
#define RD70_THREADPOOL

#include <vector>
#include <pthread.h>

#include "waitable_queue.hpp"
#include "task.hpp"
#include "shared_ptr.hpp"

class ThreadPool
{
public:
    explicit ThreadPool(size_t threads_number_);
    ~ThreadPool();

    void Pause();
    void Resume();

    SharedPtr<Task> GetTask();
    void AddTask(SharedPtr<Task> task_);

private:
    std::vector<pthread_t> m_container;
    WaitableQueue< SharedPtr<Task> > m_queue;
    bool run;
    size_t m_num_threads;
    pthread_mutex_t m_pauseMutex;

    static void *Run(void *unused);  

    class PauseTask:public Task
    {
    public:
        PauseTask(pthread_mutex_t *pause_mutex_) 
            : Task(-50), m_mutex(pause_mutex_) {}

        void Execute()
        {
            pthread_mutex_lock(static_cast<pthread_mutex_t *>(m_mutex));
            pthread_mutex_unlock(static_cast<pthread_mutex_t *>(m_mutex));

        }
        
    private:
        pthread_mutex_t *m_mutex;
    };
};

// bool operator>(const SharedPtr<Task> first_, const SharedPtr<Task> other_);
bool operator<(const SharedPtr<Task> first_, const SharedPtr<Task> other_);
#endif //RD70_THREADPOOL