#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "scheduler.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

typedef struct package_s
{
    char *arg;
    size_t time_of_task;
} package_t;

typedef struct file_package_s
{
    char *filename;
    char *input_string;
} file_package_t;

sched_t *sched;

/************************ START OF TASKS FOR SCHEDULER*************************/
int CreateFile(void *arg)
{
    FILE *file = NULL;
    file_package_t file_package = *(file_package_t *)arg;

    file = fopen(file_package.filename, "a");

    if (NULL == file)
    {
        printf("waddup man - failed to create file %s!\n", file_package.filename);
        return (0);
    }
    fseek(file, 0, SEEK_END);

    fclose(file);

    return(0);
}

int WriteToFile(void *arg)
{
    file_package_t file_package = *(file_package_t *)arg;
    FILE *file = fopen(file_package.filename, "a");

/*    file = fopen(file_package.filename, "a");*/

    if (NULL == file)
    {
        printf("failed to find file %s!\n", file_package.filename);
        return (0);
    }

    /*fseek(file, 0, SEEK_END);*/
    fwrite(file_package.input_string, 1, strlen(file_package.input_string), file);

    fclose(file);

    return (0);
}

int DeleteFile(void *arg)
{
    file_package_t file_package = *(file_package_t *)arg;
    int status = remove(file_package.filename);

    if (status == 0)
    {
        printf("failed to remove file %s as doesnt exist\n", file_package.filename);
    }

    return (status);
}

int PrintString(void *str)
{
    printf("%s\n", (char *)str);
    return(0);
}

int Stop(void *sched)
{
    SchedStop((sched_t *)sched);

    return (0);
}

int SleepSizetTime(void *time_to_sleep)
{
    sleep(*(size_t *)time_to_sleep);

    return (0);
}

int AddItemToSched(void *arg)
{
    package_t pack = *(package_t *)arg;
    SchedAddTask(sched, PrintString, pack.arg, pack.time_of_task);
    return (0);
}

int CreateNewSched(void *arg)
{
    sched_t *sched2 = SchedCreate();
    (void)arg;
    if (NULL == sched2)
    {
        printf(GRN"Great SUCCESS with not being able to create 2 scheds!\n"RESET);
    }

    return (0);

}

int SumToNum(void *num)
{
    static int sum = 0;

    ++sum;

    if (sum == *(int *)num)
    {
        printf(GRN "reached %d!\n" RESET, *(int *)num);
        return (0);
    }
    else
    {
        return (1);
    }
}

/************************** END OF TASKS FOR SCHEDULER*************************/

void TestSchedCreateAndRemove();
void TestAddTaskRunRemoveStop();
void TestSchedClear();

int main()
{
    sched = SchedCreate();
    TestSchedCreateAndRemove();
    TestAddTaskRunRemoveStop();
    TestSchedClear();





    return (0);
}

static void WrapperCompareSizet(char *func_name, size_t value, size_t expected_value)
{
    if (value == expected_value)
    {
        printf(GRN "SUCCESS with %s!\n" RESET, func_name);
    }
    else
    {
        printf(RED "FAILURE with %s!\n" RESET, func_name);
    }
}

void TestSchedCreateAndRemove()
{


        WrapperCompareSizet("SchedCreate + SchedIsEmpty", SchedIsEmpty(sched), 1);
        WrapperCompareSizet("SchedCreate + SchedSize", SchedSize(sched), 0);

}

void TestAddTaskRunRemoveStop()
{
    UID_t uid;
    size_t num = 3;
    int intnum = 2;
    package_t pack = {"fourth", 15};
    file_package_t file_package = {"try.txt", "Hello "};



    SchedAddTask(sched, PrintString, "third", 2);
    SchedAddTask(sched, PrintString, "first", 0);
    SchedAddTask(sched, PrintString, "second", 1);
    SchedAddTask(sched, PrintString, "second", 1);

    SchedAddTask(sched, CreateFile, (void *)&file_package, 5);
    file_package.input_string = "my ";
    SchedAddTask(sched, WriteToFile, (void *)&file_package, 6);
    file_package.input_string = "friend!";
    SchedAddTask(sched, WriteToFile, (void *)&file_package, 8);
    SchedAddTask(sched, DeleteFile, (void *)&file_package, 4);

    SchedAddTask(sched, Stop, (void *)sched, 4);
    SchedRun(sched);
/*    printf("schedsize = %lu\n", SchedSize(sched));*/
    WrapperCompareSizet("Stop Function", SchedSize(sched), 4);


    /*SchedAddTask(sched, CreateFile, (void *)&file_package, 4);
    SchedAddTask(sched, WriteToFile, (void *)&file_package, 6);
    SchedAddTask(sched, WriteToFile, (void *)&file_package, 8);
    SchedAddTask(sched, DeleteFile, (void *)&file_package, 9);*/

    SchedAddTask(sched, Stop, (void *)sched, 10);
    SchedRun(sched);

    SchedAddTask(sched, CreateNewSched, (void *)&num, 11);
    uid = SchedAddTask(sched, PrintString, "shouldnt print!", 13);
    SchedAddTask(sched, AddItemToSched, (void *)&pack, pack.time_of_task);
    SchedAddTask(sched, SleepSizetTime, (void*)&num, 14);
    SchedAddTask(sched, SumToNum, (void *)&intnum, 15);

    SchedRemoveTask(sched, uid);

    SchedRun(sched);


}

void TestSchedClear()
{


    SchedAddTask(sched, PrintString, "third", 2);
    SchedAddTask(sched, PrintString, "first", 0);
    SchedAddTask(sched, PrintString, "second", 1);
    SchedAddTask(sched, PrintString, "second", 1);

    SchedClear(sched);

    WrapperCompareSizet("SchedClear", SchedIsEmpty(sched), 1);
    WrapperCompareSizet("SchedClear", SchedSize(sched), 0);

    SchedDestroy(sched);
}
