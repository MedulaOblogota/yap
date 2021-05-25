#ifndef RD70_ATOMIC
#define RD70_ATOMIC

#include <pthread.h>
#include <cstdio>

#include "scoped_lock.hpp"

template <typename VAR>
class Atomic
{
public:
    explicit Atomic(VAR init_ = 0);
    ~Atomic();

    VAR GetVar();
    void SetVar(VAR val_);
    void Inc();
    void Dec();
    bool DecAndCheck(VAR val_);

private:
    VAR m_var;
    pthread_mutex_t m_mutex;

    static void MutexLock(pthread_mutex_t &t);
    static void MutexUnlock(pthread_mutex_t &t);
    typedef ScopedLock<pthread_mutex_t, MutexLock, MutexUnlock> MutexScopedLock;
};

template <typename VAR>
Atomic<VAR>::Atomic(VAR init_)
    : m_var(init_)
{
    if (-1 == pthread_mutex_init(&m_mutex, NULL))
    {
        perror("pthread_mutex_init");
    }
}

template <typename VAR>
Atomic<VAR>::~Atomic()
{
    if (-1 == pthread_mutex_destroy(&m_mutex))
    {
        perror("pthread_mutex_destroy");
    }
}

template <typename VAR>
VAR Atomic<VAR>::GetVar()
{
    return (m_var);
}

template <typename VAR>
void Atomic<VAR>::SetVar(VAR val_)
{
    //MutexScopedLock lock(m_mutex);
    MutexLock(m_mutex);
    m_var = val_;
    MutexUnlock(m_mutex);
}

template <typename VAR>
void Atomic<VAR>::Inc()
{
    MutexLock(m_mutex);
    //MutexScopedLock lock(m_mutex);
    ++m_var;
    MutexUnlock(m_mutex);
}

template <typename VAR>
void Atomic<VAR>::Dec()
{
    MutexLock(m_mutex);
    //MutexScopedLock lock(m_mutex);
    --m_var;
    MutexUnlock(m_mutex);
}

template <typename VAR>
bool Atomic<VAR>::DecAndCheck(VAR val_)
{
    //MutexScopedLock lock(m_mutex);
    MutexLock(m_mutex);

    --m_var;
    bool ret = m_var == val_;
    MutexUnlock(m_mutex);

    return (ret);
}

//static
template <typename VAR>
void Atomic<VAR>::MutexLock(pthread_mutex_t &t)
{
    if (-1 == pthread_mutex_lock(&t))
    {
        perror("pthread_mutex_lock");
    }
}

//static
template <typename VAR>
void Atomic<VAR>::MutexUnlock(pthread_mutex_t &t)
{
    if (-1 == pthread_mutex_unlock(&t))
    {
        perror("pthread_mutex_unlock");
    }
}



#endif //RD70_ATOMIC