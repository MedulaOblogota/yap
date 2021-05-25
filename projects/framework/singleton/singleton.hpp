#ifndef RD70_SINGLETON
#define RD70_SINGLETON

#include <pthread.h>


template <class T>
class Singleton
{
public:
    static T* GetInstance();
    static void Delete();
    
private:
    explicit Singleton() {};

    static T* m_instance;
};

template <class T>
T* Singleton<T>::m_instance = 0;

template <class T>
T* Singleton<T>::GetInstance()
{
    pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&m_mutex);
    if (0 == m_instance)
    {
        m_instance = new T;
    }
    pthread_mutex_unlock(&m_mutex);

    return m_instance;
}

template <class T>
void Singleton<T>::Delete()
{
        delete m_instance;      m_instance = 0;   
}

#endif //RD70_SINGLETON