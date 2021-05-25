#ifndef RD70_THREADS
#define RD70_THREADS

#include <pthread.h>  //thread_t
#include <string>     //string


template<class F>
class Thread: private boost:uncopyable
{
public:
  explicit Thread(F f);
  ~Thread() {};
  // int GetId();
  void Join();
  void Detach();

  class ThreadError: public std::runtime_error
  {
  public:
    ThreadError(const std::string& s_="Thread Error!")
    : runtime_error(s_) {}
  };

private:
  pthread_t m_thread;

  // Thread(const Thread& thread);
  // Thread& operator=(const Thread& thread);

  static void* TFIMP(void *f);
};

template<class F>
Thread<F>::Thread(F f)
{
  pthread_attr_t attr;

  if (pthread_attr_init(&attr))
  {
    throw(ThreadError("Thread attribute initialization error "));
  }

  if (pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE))
  {
    throw(ThreadError("Thread detach state error "));
  }

  F *tempF = new F(f);

  if (pthread_create(&m_thread, &attr, &TFIMP, tempF))
  {
    delete tempF;
    throw (ThreadError("Thread Create Error exception:"));
  }

}

template<class F>
void* Thread<F>::TFIMP(void *f)
{
  F functor = *((F*)f);
  functor();

  delete (F*)f;

  return NULL;
}

// template<class F>
// int Thread<F>::GetId()
// {
//   return getpid();
// }

template<class F>
void Thread<F>::Join()
{
  pthread_attr_t attr;

  if (pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE))
  {
    throw (ThreadError("Thread Join Error exception: "));
  }

  if (pthread_join(m_thread, NULL))
  {
    throw (ThreadError("Thread Join Error exception: "));
  }
}

template<class F>
void Thread<F>::Detach()
{
  pthread_attr_t attr;

  if (pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED))
  {
    throw (ThreadError("Thread Detach Error exception: "));
  }

  if (pthread_detach(m_thread))
  {
    throw (ThreadError("Thread Detach Error exception: "));
  }
}

#endif //RD70_THREADS
