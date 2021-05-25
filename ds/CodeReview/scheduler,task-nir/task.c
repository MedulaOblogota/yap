#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "Tasks.h"
#include "UID.h"

struct task_s
{
    UID_t UID;
    time_t next_run;
    action_func_t action_func;
    size_t interval;
    void *param;
};


task_t *TaskCreate(size_t interval, action_func_t func, void *param)
{
    task_t *new_task = malloc(sizeof(task_t));
    if (NULL == new_task)
    {
        return (NULL);
    }

    new_task->interval = interval;
    new_task->action_func = func;
    new_task->UID = UIDCreate();
    new_task->next_run = time(NULL) + interval;
    new_task->param = param;

    return (new_task);
}

void TaskDestroy(task_t *task)
{
    free(task);

    return;
}

/*******************************************************************************
 * Execute a given task.
 *
 * task - pointer to task (not NULL).
 *
 * Return - TRUE if task has bee executed succefully, FALSE otherwise.
 ******************************************************************************/
task_run_t TaskRun(task_t *task)
{
    assert(NULL != task);
    assert(NULL != task->action_func);
    assert(NULL != task->param);

    if (TaskGetTimeToRun(task) > time(NULL))
    {
        sleep(TaskGetTimeToRun(task) - time(NULL));
    }

    TaskUpdateTimeToRun(task);

    return (task->action_func(task->param));
}

/*******************************************************************************
* Execute a compersion between the priority of two given tasks.
*
* task1, task2 - pointers to tasks (not NULL).
*
* Return value: TRUE(1) if task1 is before task 2. 0 otherwise.
*******************************************************************************/
int TaskIsBefore(const task_t *task1, const task_t *task2, void *param)
{
    return (TaskGetTimeToRun(task1) < TaskGetTimeToRun(task2));
}

/*******************************************************************************
* Update time to run of a task.
*
* task - pointer to task (not NULL).
*******************************************************************************/
void TaskUpdateTimeToRun(task_t *task)
{
    assert(NULL != task);

    task->next_run = time(NULL) + task->interval;

    return;
}

/*******************************************************************************
* task - a pointer to task (Not NULL).
*
* Return value: time to run of a task.
*******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task)
{
    assert(NULL != task);

    return (task->next_run);
}

UID_t TaskGetUID(const task_t *task)
{
    assert(NULL != task);

    return (task->UID);
}

int TaskIsMatch(const task_t *task, UID_t uid)
{
    return (UIDIsSame(uid, task->UID));
}
