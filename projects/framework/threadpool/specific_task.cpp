#include "specific_task.hpp"
#include "task.hpp"

#include <cstdio>
SpecificTask::SpecificTask(int priority_)
    : Task(priority_), m_i(priority_)
{}

void SpecificTask::Execute()
{
    // (void)val;
    // if (p == 1) printf("first\n");
    // if (p == 5) printf("second\n");
    // if (p == 10) printf("third\n");

    printf("hello %d\n", m_i);
}

// Task& SpecificTask::operator>(const Task& other_)
// {
//     return (m_priority > other_.m_priority);
// }

