#include "task.hpp"

Task::Task(int priority_)
    : m_priority(priority_)
{
    // pthread_cond_init (&m_cond, NULL);  //maybe should not be NULL?
    // pthread_mutex_init(&m_mutex, NULL);
}

bool Task::operator>(const Task& other_)
{
    return (m_priority > other_.m_priority);
}

bool Task::operator<(const Task& other_)
{
    return (m_priority < other_.m_priority);
}

int Task::GetPriority()
{
    return m_priority;
}