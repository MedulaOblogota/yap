#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "UID.h"
#include "Tasks.h"
#include "Scheduler.h"
#include "PriorityQueue.h"

int has_sched = 0;

struct sched_s
{
    pqueue_t *pqueue;
    task_t *curr_task;
    int has_been_stoped;

};

static int SchedCmp(const void *task1, const void *task2, const void *param)
{
    return((-1)*TaskIsBefore(task1, task2, NULL));
}

static int SchedTaskMatch(const void *task, const void *uid_ptr)
{
    return(TaskIsMatch(task, *(UID_t *)uid_ptr));
}

sched_t *SchedCreate()
{
    sched_t *new_sched = NULL;

    if (has_sched)
    {
        return (NULL);
    }

    new_sched = malloc(sizeof(sched_t));
    if (NULL == new_sched)
    {
        return (NULL);
    }

    new_sched->pqueue = PQCreate(SchedCmp, NULL);
    if (NULL == new_sched->pqueue)
    {
        SchedDestroy(new_sched);
        return (NULL);
    }

    new_sched->has_been_stoped = 0;

    has_sched = 1;

    return (new_sched);
}

void SchedDestroy(sched_t *sched)
{
    assert(NULL != sched);

    SchedClear(sched);
    PQDestroy(sched->pqueue);
    free(sched);
    has_sched = 0;

    return;
}

void SchedClear(sched_t *sched)
{
    assert(NULL != sched);

    while (!SchedIsEmpty(sched))
    {
        TaskDestroy(PQDequeue(sched->pqueue));
    }

    return;
}

int SchedIsEmpty(sched_t *sched)
{
    assert(NULL != sched);

    return(PQIsEmpty(sched->pqueue));
}

size_t SchedSize(sched_t *sched)
{
    assert(NULL != sched);

    return(PQSize(sched->pqueue));
}

UID_t SchedAddTask(sched_t *sched, op_func_t func, void *param, size_t interval)
{
    task_t *new_task = TaskCreate(interval, (action_func_t)func, param);
    if (NULL == new_task)
    {
        return (BAD_UID);
    }

    assert(NULL != sched);

    if (!PQEnqueue(sched->pqueue, new_task))
    {
        TaskDestroy(new_task);
        return (BAD_UID);
    }

    return (TaskGetUID(new_task));
}

void SchedRemoveTask(sched_t *sched, UID_t uid)
{
    UID_t *uid_ptr = &uid;
    task_t *task_to_remove = NULL;

    assert(NULL != sched);

    task_to_remove = PQErase(sched->pqueue, SchedTaskMatch, uid_ptr);

    TaskDestroy(task_to_remove);

    return;
}

sched_run_t SchedRun(sched_t *sched)
{
    task_run_t task_status = STOP;
    sched_run_t run_status = SUCCESS;

    assert(NULL != sched);

    while (!SchedIsEmpty(sched))
    {
        sched->curr_task = PQDequeue(sched->pqueue);

        task_status = TaskRun(sched->curr_task);

        if (sched->has_been_stoped)
        {
            run_status = STOPPED;
            TaskDestroy(sched->curr_task);
            sched->has_been_stoped = 0;
            break;
        }

        if (REPEAT == task_status)
        {
            if (0 == PQEnqueue(sched->pqueue, sched->curr_task))
            {
                run_status = ERROR;
                break;
            }
        }

        else if (STOP == task_status)
        {
            TaskDestroy(sched->curr_task);
        }

    }

    return (run_status);
}


void SchedStop(sched_t *sched)
{
    assert(NULL != sched);

    ((sched_t *)sched)->has_been_stoped = 1;

    return;
}
