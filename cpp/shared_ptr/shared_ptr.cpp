#include "shared_ptr.hpp"

namespace ilrd
{
template <class T>
SharedPtr<T>::SharedPtr(T *ptr)
  : m_ptr(ptr), m_counter(new std::size_t(1))
{
  // *m_counter = 0;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other_)
  : m_ptr(other_.m_pntr), m_counter(++*other_.m_counter)
{}

template <class T>
SharedPtr<T>::~SharedPtr()
{
  --*m_counter;

  if (0 == *m_counter)
  {
    delete m_counter;
    delete[] m_ptr;
  }

  m_counter = NULL;
  m_ptr = NULL;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other_)
{
  --*(m_counter);

  if (0 == m_counter)
  {
    delete[] m_ptr;
    delete m_counter;
  }

  this.m_ptr = other_.m_ptr;
  this.m_counter = other_.m_counter;

  ++*m_counter;
}

template <class T>
T& SharedPtr<T>::operator*()const
{
  return *m_ptr;
}

template <class T>
T* SharedPtr<T>::operator->()const
{
  return m_ptr;
}

template <class T> template <class O>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<O>& other_)
{
  --*(m_counter);

  if (0 == m_counter)
  {
    delete[] m_ptr;
    delete m_counter;
  }

  this.m_ptr = other_.m_ptr;
  this.m_counter = other_.m_counter;

  ++*m_counter;
}

template <class T> template <class O>
SharedPtr<T>::SharedPtr(const SharedPtr<O>& other_)
  : m_ptr(other_.m_pntr), m_counter(++*other_.m_counter)
{}
}

int main()
{
  // SharedPtr<int> pnt2(pnt);
  int num = 3;
  ilrd::SharedPtr<int> pnt(&num);


}
