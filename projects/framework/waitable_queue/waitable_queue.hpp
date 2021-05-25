#ifndef RD70_WAITABLEQUEUE
#define RD70_WAITABLEQUEUE

#include <queue>          // std::queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <iostream>
#include <pthread.h>
#include <semaphore.h>


//T must have > operator
template <typename T>
class WaitableQueue
{
public:
    explicit WaitableQueue();
    ~WaitableQueue();

    void Push(T);
    T Pop();
    // T Front();
    // T Back();
    size_t Size();
    bool IsEmpty();

    // bool Comparison(const T& other_);

private:
    std::priority_queue<T> m_queue;
    pthread_mutex_t m_mutex;
    sem_t m_semaphore;
};

template <typename T>
WaitableQueue<T>::WaitableQueue()
    : m_queue()
{
    pthread_mutex_init(&m_mutex, NULL);
    sem_init(&m_semaphore, 0, 0);
    // m_mutex = PTHREAD_MUTEX_INITIALIZER;
}

template <typename T>
WaitableQueue<T>::~WaitableQueue()
{
    pthread_mutex_destroy(&m_mutex);
    sem_destroy(&m_semaphore);
}

template <typename T>
void WaitableQueue<T>::Push(T t)
{
    pthread_mutex_lock(&m_mutex);

    m_queue.push(t);

    pthread_mutex_unlock(&m_mutex);
    sem_post(&m_semaphore);
}

template <typename T>
T WaitableQueue<T>::Pop()
{
    sem_wait(&m_semaphore);
    pthread_mutex_lock(&m_mutex);
    
    T value(m_queue.top());
    m_queue.pop();

    pthread_mutex_unlock(&m_mutex);

    return value;
}

// template <typename T>
// T WaitableQueue<T>::Front()
// {
//     T value;
//     pthread_mutex_lock(&m_mutex);
//     value = m_queue.front();
//     pthread_mutex_unlock(&m_mutex);
//     return value;
// }

// template <typename T>
// T WaitableQueue<T>::Back()
// {
//     T value;
//     pthread_mutex_lock(&m_mutex);
//     value = m_queue.back();
//     pthread_mutex_unlock(&m_mutex);
//     return value;
// }

template <typename T>
size_t WaitableQueue<T>::Size()
{
    return m_queue.size();
}

template <typename T>
bool WaitableQueue<T>::IsEmpty()
{
    return (m_queue.empty());
}
#endif //RD70_WAITABLEQUEUE