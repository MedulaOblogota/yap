#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "tasks.h"
#include "scheduler.h"
#include "PriorityQueue.h"
#include "UID.h"

struct sched_s
{
    pqueue_t *pqueue;
    task_t *curr_task;
    unsigned int closed;
};

static int is_first = 1;


int IsBeforeSched(const void *data1, const void *data2, const void *compare)
{
    task_t *task1 = (task_t *)(void *)data1;
    task_t *task2 = (task_t *)(void *)data2;

    (void)compare;

    return ((-1) * TaskIsBefore(task2, task1, (void *)compare)); /*MAYBE MINUS IS DUMB, MAYBE ITS GENIUS */
}

int IsMatch(const void *data, const void *param)
{
    UID_t uid1 = *(UID_t *)data;
    UID_t uid2 = *(UID_t *)param;

    return(UIDIsSame(uid1, uid2));
}



/*******************************************************************************
* Allocate memory for scheduler.
*******************************************************************************/
sched_t *SchedCreate()
{
    sched_t *sched = NULL;

    if (is_first)
    {
        sched = malloc(sizeof(sched_t));

        if (NULL == sched)
        {
            return (NULL);
        }

        sched->pqueue = PQCreate(IsBeforeSched, NULL);

        sched->curr_task = NULL;

        sched->closed = 0;

        is_first = 0;
    }

    return(sched);

}

/*******************************************************************************
* Realeses the memory allocated to the scheduler.
*******************************************************************************/
void SchedDestroy(sched_t *sched)
{
    /*PQClear(sched->pqueue);
    TaskDestroy((task_t *)PQDestroy(sched->pqueue));*/
    is_first = 1;

    SchedClear(sched);

    PQDestroy(sched->pqueue);

/*    if (NULL != sched->curr_task)
    {
        TaskDestroy(sched->curr_task);  sched->curr_task = NULL;
    }*/

    free(sched);    sched = NULL;
}

/*******************************************************************************
 * Execute all the tasks in a given scheduler.
 ******************************************************************************/
sched_run_t SchedRun(sched_t *sched)
{
    time_t time_to_run = 0;

    sched->closed = 0;

    while (!SchedIsEmpty(sched))
    {
        sched->curr_task = PQDequeue(sched->pqueue);
        time_to_run = TaskGetTimeToRun(sched->curr_task);

    /*    printf("time is %lu\n", (long)(time_to_run - time(NULL)));*/
        if (time_to_run > time(NULL))
        {
            sleep(time_to_run - time(NULL));
        }

        if (REPEAT == TaskRun(sched->curr_task))
        {
            if (0 == PQEnqueue(sched->pqueue, (void *)(sched->curr_task)))
            {
                return (ERROR);
            }

            sched->curr_task = NULL;
        }
        else
        {
            TaskDestroy(sched->curr_task);  sched->curr_task = NULL;
        }

        if (sched->closed)
        {
            /*TaskDestroy(sched->curr_task);  sched->curr_task = NULL;*/
            return(STOPPED);
        }
    }

    /*sched->curr_task = NULL;*/

    return(SUCCESS);
}

/*******************************************************************************
* Execute a compersion between the priority of two given tasks.
*******************************************************************************/
size_t SchedSize(sched_t *sched)
{
    return (PQSize(sched->pqueue));
}

/*******************************************************************************
* Clears the scheduler, by emptying it from tasks.
*******************************************************************************/
void SchedClear(sched_t *sched)
{
    while (!SchedIsEmpty(sched))
    {
        TaskDestroy((task_t *)PQDequeue(sched->pqueue));
    }
}

/*******************************************************************************
* Returns TRUE(1) if the sched is empty, FALSE(0) otherwise.
*******************************************************************************/
int SchedIsEmpty(sched_t *sched)
{
    return (PQIsEmpty(sched->pqueue));
}

/*******************************************************************************
* Adds Task to Scheduler, returns UID of the task.
*******************************************************************************/
UID_t SchedAddTask(sched_t *sched, op_func_t func, void *param, size_t interval)
{

    task_t *task = TaskCreate(interval, (action_func_t)func, param);

    if (NULL == task)
    {
        return (BAD_UID);
    }

    PQEnqueue(sched->pqueue, (void *)task);

    return (TaskGetUID(task));
}

/*******************************************************************************
* Removes task from the scheduler.
*******************************************************************************/
void SchedRemoveTask(sched_t *sched, UID_t uid)
{
    task_t *task = PQErase(sched->pqueue, IsMatch, (void *)&uid);
    if (NULL != task)
    {
        TaskDestroy(task);
    }
}

/*******************************************************************************
* Causes the scheduler to stop.
*******************************************************************************/
void SchedStop(sched_t *sched)
{
    sched->closed = 1;
}
