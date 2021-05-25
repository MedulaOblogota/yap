#include <stdio.h>
#include <string.h>
#include "tasks.h"

task_run_t CreateFile(void *str)
{
    FILE *file = fopen("file.txt", "w+");
    fseek(file, 0, SEEK_SET);
    fwrite((char *)str, 1, strlen((char *)str), file);

    fclose(file);

    return(STOP);
}

task_run_t PrintString(void *str)
{
    printf("%s\n", (char *)str);
    return(STOP);
}

int main()
{
    task_t *task = TaskCreate(0, CreateFile, "wassup?\n");
    task_t *task2 = TaskCreate(0, PrintString, "HelloWorld\n");
    TaskRun(task);
    TaskRun(task2);

    TaskDestroy(task);
    TaskDestroy(task2);

    return (0);
}
