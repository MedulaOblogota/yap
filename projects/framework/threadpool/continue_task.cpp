#include "continue_task.hpp"

ContinueTask::ContinueTask()
    : Task(-2)
{}

void *ContinueTask::Execute(void *val, int p)
{
    // (void)val;
    // int i = 0;
    pthread_mutex_lock(&m_mutex);

    pthread_mutex_unlock(&m_mutex);

    // for (i = 0; i < p; ++i)
    // {
    //     threadpool->AddTask()
    // }
    // pthread_cond_wait(&m_cond, &m_mutex);
    // pthread_mutex_unlock(&m_mutex);
    return NULL;
}