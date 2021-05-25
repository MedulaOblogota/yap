#include "pause_task.hpp"

PauseTask::PauseTask()
    : Task(-20)
{}

void *PauseTask::Execute(void *val, int p)
{
    (void)val;
    (void)p;
    // int i = 0;
    pthread_mutex_lock(&m_mutex);

    // for (i = 0; i < p; ++i)
    // {
    //     threadpool->AddTask()
    // }
    // pthread_cond_wait(&m_cond, &m_mutex);
    // pthread_mutex_unlock(&m_mutex);
    return NULL;
}