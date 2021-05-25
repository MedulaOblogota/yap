#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "sllist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestQueueCreate();
void TestQueueEnqueue();
void TestQueueDequeue();
void TestQueueSize();
void TestQueuePeek();
void TestQueueIsEmpty();
void TestQueueAppend();

int main()
{
    TestQueueCreate();
    TestQueueEnqueue();
    TestQueueDequeue();
    TestQueueSize();
    TestQueuePeek();
    TestQueueIsEmpty();
    TestQueueAppend();

    return (0);
}

static void InsertToQueue(queue_t *queue, size_t size)
{
    size_t i = 0;
    for (i = 1; i <= size; ++i)
    {
        QueueEnqueue(queue, (void *)i);
    }
}

void TestQueueCreate()
{
    queue_t *queue = QueueCreate();

    if (NULL != queue)
    {
        printf(GRN "SUCCESS with QueueCreate!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with QueueCreate!!!\n" RESET);
    }

    QueueDestroy(queue);
}

void WrapperQueueEnqueue(queue_t *queue, size_t num)
{
        if (QueueEnqueue(queue, (void *)num) == 0)
        {
            printf(RED "something BAAAAD happened with QueueEnqueue\n" RESET);
            return;
        }

        if ((size_t)QueuePeek(queue) == 5)
        {
            printf(GRN "SUCCESS with QueueEnqueue!\n" RESET);
        }
        else
        {
            printf(RED "FAILURE with QueueEnqueue!!!\n" RESET);
        }
}

void TestQueueEnqueue()
{
    queue_t *queue = QueueCreate();
    size_t num = 5;

    WrapperQueueEnqueue(queue, num);

    num = 7;
    WrapperQueueEnqueue(queue, num);

    QueueDestroy(queue);
}

void TestQueueDequeue()
{
    queue_t *queue = QueueCreate();
    size_t i = 0;
    /*CreateQueueOfNStrings(queue);*/
    char *str[] = { "hello buddy, how are you my friend?!",
                    "I am doing great! How are you buddy??",
                    "Hey! I ain't your buddy pal!",
                    "You go to hell and you die!"
                };

    QueueEnqueue(queue, str[0]);
    QueueEnqueue(queue, str[1]);
    QueueEnqueue(queue, str[2]);
    QueueEnqueue(queue, str[3]);
    printf("queue size is now %lu\n", QueueSize(queue));
    for (i = 1; i < 4; ++i)
    {
        QueueDequeue(queue);
        /*printf("QueuePeek(queue)=%s\n", (char *)QueuePeek(queue));*/
        if (memcmp(QueuePeek(queue), str[i], sizeof(size_t)) == 0)
        {
            printf(GRN "SUCCESS with QueueDequeue!\n" RESET);
        }
        else
        {
            printf(RED "FAILURE with QueueDequeue!!!\n" RESET);
        }
    }

    printf("queue size is now %lu\n", QueueSize(queue));
    QueueDequeue(queue);
    printf("queue size is now %lu\n", QueueSize(queue));
    QueueDequeue(queue);
    printf("queue size is now %lu\n", QueueSize(queue));
    QueueDequeue(queue);

    QueueDestroy(queue);
}

static void WrapperQueueSize(queue_t *queue, size_t expected_size)
{
    if (QueueSize(queue) != expected_size)
    {
        printf(RED "FAILURE with QueueSize!!!\n" RESET);
    }
    else
    {
        printf(GRN "SUCCESS with QueueSize!\n" RESET);
    }
}

void TestQueueSize()
{
    queue_t *empty_queue = QueueCreate();
    queue_t *one_element_queue = QueueCreate();
    queue_t *regular_queue = QueueCreate();

    InsertToQueue(one_element_queue, 1);
    InsertToQueue(regular_queue, 6);

    WrapperQueueSize(empty_queue, 0);
    WrapperQueueSize(one_element_queue, 1);
    WrapperQueueSize(regular_queue, 6);

    QueueDestroy(empty_queue);
    QueueDestroy(one_element_queue);
    QueueDestroy(regular_queue);
}

void TestQueuePeek()
{
    queue_t *empty_queue = QueueCreate();

    if (QueuePeek(empty_queue) == NULL)
    {
        printf(GRN "SUCCESS with QueuePeek!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with QueuePeek!!!\n" RESET);
    }

    QueueDestroy(empty_queue);

}

static void WrapperQueueIsEmpty(queue_t *queue, int expected_value)
{
    if (QueueIsEmpty(queue) == expected_value)
    {
        printf(GRN "SUCCESS with QueueIsEmpty!\n" RESET);
    }
    else
    {
        printf(RED "FAILURE with QueueIsEmpty!!!\n" RESET);
    }
}

void TestQueueIsEmpty()
{
    queue_t *empty_queue = QueueCreate();
    queue_t *one_element_queue = QueueCreate();
    queue_t *regular_queue = QueueCreate();

    InsertToQueue(one_element_queue, 1);
    InsertToQueue(regular_queue, 6);

    WrapperQueueIsEmpty(empty_queue, 1);
    WrapperQueueIsEmpty(one_element_queue, 0);
    WrapperQueueIsEmpty(regular_queue, 0);

    QueueDestroy(empty_queue);
    QueueDestroy(one_element_queue);
    QueueDestroy(regular_queue);
}

static void WrapperQueueAppend(queue_t *queue, size_t expected_size, size_t expected_peek)
{
    if (QueueSize(queue) == expected_size)
    {
        if ((size_t)QueuePeek(queue) == expected_peek)
        {
            printf(GRN "GREAT SUCCESS with QueueAppend & size + peek!\n" RESET);
        }
        else
            printf(RED "FAILURE with QueueAppend with peek!!\n" RESET);
    }
    else
    {
        if ((size_t)QueuePeek(queue) == expected_peek)
        {
            printf(GRN "SUCCESS with QueueAppend & peak but FAIL with size!\n" RESET);
        }
        else
            printf(RED "GREAT FAILURE with QueueAppend (peek & size)!!\n" RESET);
    }
}

void TestQueueAppend()
{
    queue_t *empty_queue = QueueCreate();
    queue_t *empty_queue2 = QueueCreate();
    queue_t *one_element_queue = QueueCreate();
    queue_t *regular_queue = QueueCreate();

    queue_t *appended_queue1 = NULL;
    queue_t *appended_queue2 = NULL;
    queue_t *appended_queue3 = NULL;
    queue_t *appended_queue4 = NULL;

    size_t num = 7;

    InsertToQueue(one_element_queue, 1);
    InsertToQueue(regular_queue, 6);

    appended_queue1 = QueueAppend(empty_queue, one_element_queue);
    WrapperQueueAppend(appended_queue1, 1, 1);

    QueueDestroy(empty_queue);
    QueueDestroy(one_element_queue);

    empty_queue = QueueCreate();
    one_element_queue = QueueCreate();
    InsertToQueue(one_element_queue, 1);

    appended_queue2 = QueueAppend(empty_queue, regular_queue);
    WrapperQueueAppend(appended_queue2, 6, 1);

    QueueDestroy(empty_queue);
    QueueDestroy(regular_queue);
    empty_queue = QueueCreate();
    regular_queue = QueueCreate();
    InsertToQueue(regular_queue, 6);

    appended_queue3 = QueueAppend(regular_queue, one_element_queue);
    WrapperQueueAppend(appended_queue3, 7, 1);

    QueueEnqueue(appended_queue3, (void *)num);
    QueueDequeue(appended_queue3);
    printf("queuepeek=%lu\n", QueuePeek(appended_queue3));

    QueueDestroy(empty_queue);
    QueueDestroy(regular_queue);
    empty_queue = QueueCreate();
    regular_queue= QueueCreate();
    InsertToQueue(regular_queue, 6);

    appended_queue4 = QueueAppend(regular_queue, empty_queue);
    WrapperQueueAppend(appended_queue4, 6, 1);

/*
    if (QueueSize(appended_queue4) == 0)
    {
        if (QueuePeek(appended_queue4) == NULL)
        {
            printf(GRN "GREAT SUCCESS with QueueAppend & size + peek!\n" RESET);
        }
        else
            printf(RED "FAILURE with QueueAppend with peek!!\n" RESET);
    }
    else
    {
        if (QueuePeek(appended_queue4) == NULL)
        {
            printf(GRN "SUCCESS with QueueAppend & peak but FAIL with size!\n" RESET);
        }
        else
            printf(RED "GREAT FAILURE with QueueAppend (peek & size)!!\n" RESET);
    }

*/

    QueueDestroy(empty_queue);
    QueueDestroy(empty_queue2);
    QueueDestroy(one_element_queue);
    QueueDestroy(regular_queue);

    /*QueueDestroy(appended_queue1);
    QueueDestroy(appended_queue2);
    QueueDestroy(appended_queue3);*/
}
