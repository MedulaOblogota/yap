#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tasks.h"
#include "scheduler.h"
#include "PriorityQueue.h"
#include "UID.h"

struct task_s {
    UID_t uid;
    time_t next_run;
    action_func_t func;
    size_t interval;
    void *param;
};


/*******************************************************************************
* Allocate memory for task.
*******************************************************************************/
task_t *TaskCreate(size_t interval, action_func_t func, void *param)
{
    task_t *task = malloc(sizeof(task_t));

    if (NULL == task)
    {
        return (NULL);
    }

    task->uid = UIDCreate();
    task->next_run = time(NULL) + interval;
    task->func = func;
    task->interval = interval;
    task->param = param;

    return(task);
}

/*******************************************************************************
* Realeses the memory allocated to the task.
*******************************************************************************/
void TaskDestroy(task_t *task)
{
    assert (NULL != task);

    free(task); task = NULL;
}

/*******************************************************************************
 * Execute a given task.
 ******************************************************************************/
task_run_t TaskRun(task_t *task)
{
    assert (task);

    TaskUpdateTimeToRun(task);
    return (task->func(task->param));

}

/*******************************************************************************
* Execute a compersion between the priority of two given tasks.
*******************************************************************************/
int TaskIsBefore(const task_t *task1, const task_t *task2, void *param)
{
    (void)param;
    return (task1->next_run > task2->next_run);
}

/*******************************************************************************
* Update time to run of a task.
*******************************************************************************/
void TaskUpdateTimeToRun(task_t *task)
{
    task->next_run = task->next_run + task->interval;
}

/*******************************************************************************
* task - a pointer to task (Not NULL).
*******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task)
{
    return(task->next_run);
}

/*******************************************************************************
* task - a pointer to task (Not NULL).
*******************************************************************************/
UID_t TaskGetUID(const task_t *task)
{
    return (task->uid);
}

/*******************************************************************************
* checks if the given uid is match to the give task.
*******************************************************************************/
int TaskIsMatch(const task_t *task, UID_t uid)
{
    return (UIDIsSame(uid, task->uid));
}
