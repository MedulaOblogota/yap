#ifndef OL70_SHARED_PTR
#define OL70_SHARED_PTR

namespace ilrd
{
#include <cstddef>

template <class T>
class SharedPtr
{
public:
  // explicit SharedPtr();
  explicit SharedPtr(T *ptr=NULL);  // TODO: make new noexcept
  SharedPtr(const SharedPtr& other_);

  ~SharedPtr();

  SharedPtr& operator=(const SharedPtr& other_);  //TODO: self-assignment

  template<class O>//O* must be implicitally convertible to T*
  SharedPtr(const SharedPtr<O>& other_);

  T& operator*()const;
  T* operator->()const;

private:
  template <class O> friend class SharedPtr;
  T *m_ptr;
  size_t *m_counter;
};

template <class T>
SharedPtr<T>::SharedPtr(T *ptr)
  : m_ptr(ptr)//, m_counter(new size_t(1))
{
  m_counter = new (std::nothrow) size_t(1);

  if (NULL == m_counter)
  {
    delete m_ptr;
    
    std::bad_alloc exception;
    throw exception;
  }
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other_)
  : m_ptr(other_.m_ptr), m_counter(&(++*other_.m_counter))
{}

template <class T>
SharedPtr<T>::~SharedPtr()
{
  --(*m_counter);

  if (0 == *(m_counter))
  {
    delete m_counter;
    delete m_ptr;
  }

  m_counter = NULL;
  m_ptr = NULL;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other_)
{
  ++*(other_.m_counter);
  --*m_counter;

  if (0 == *m_counter)
  {
    delete m_ptr;
    delete m_counter;
  }

  this->m_ptr = other_.m_ptr;
  this->m_counter = other_.m_counter;

  return *this;
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

// template <class T> template <class O>
// SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<O>& other_)
// {
//   --*(m_counter);
//
//   if (0 == *m_counter)
//   {
//     delete m_ptr;
//     delete m_counter;
//   }
//
//   this.m_ptr = other_.m_ptr;
//   this.m_counter = other_.m_counter;
//
//   ++*m_counter;
//
//   return *this;
// }

template <class T> template <class O>
SharedPtr<T>::SharedPtr(const SharedPtr<O>& other_)
  : m_ptr(other_.m_ptr), m_counter(&(++*other_.m_counter))
{}

#endif //OL70_SHARED_PTR
}
