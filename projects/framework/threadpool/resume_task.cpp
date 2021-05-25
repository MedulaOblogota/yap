#include "resume_task.hpp"

ResumeTask::ResumeTask()
    : Task(-1)
{}

void *ResumeTask::Execute(void *val, int p)
{
    (void)val;
    (void)p;
    // pthread_mutex_lock(&m_mutex);
    // pthread_cond_broadcast(&m_cond);
    pthread_mutex_unlock(&m_mutex);

    return NULL;
}