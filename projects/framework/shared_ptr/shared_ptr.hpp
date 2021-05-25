#ifndef OL70_SHARED_PTR
#define OL70_SHARED_PTR


#include <cstddef>
#include <iostream>

template <class T>
class SharedPtr
{
public:
  // explicit SharedPtr();
  explicit SharedPtr(T *ptr=NULL);  // TODO: make new 
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

// #ifndef RD70_SHARED_PTR
// #define RD70_SHARED_PTR

// #include <cstddef>  // size_t
// #include <cassert>  // assert
// #include <stdio.h>

// #include "atomic.hpp"
// // #include "ilrd_util.hpp" //  nullptr



// template <typename T>
// class SharedPtr
// {
// public:
// 	explicit SharedPtr(T *ptr = 0);
// 	~SharedPtr() ;
// 	SharedPtr(const SharedPtr& other_); //point to the same location, inc counter reference

// 	SharedPtr& operator=(const SharedPtr& other_);

// 	template<typename O> // O* must be implicitly convertable to T*
// 	SharedPtr(const SharedPtr<O>& other_);

// 	T& operator*() const;
// 	T* operator->() const;

// private:
// 	T *m_ptr;
// 	Atomic<size_t> *m_counter;

// 	//Implementation functions
// 	void DeleteIfIMP();

// 	template <typename o>
// 	friend class SharedPtr<T>;
// };


// template <typename T> // delete use spaces
// void SharedPtr<T>::DeleteIfIMP()
// {
// 	assert(m_counter);
	
// 	if (m_counter->DecAndCheck(0))
// 	{
// 		delete m_counter;
// 		m_counter = 0;
// 		delete m_ptr;
// 		m_ptr = 0;
// 	}
// }

// template <typename T>
// SharedPtr<T>::SharedPtr(T *ptr)
// 	:m_ptr(ptr)
// {
// 	m_counter = new(std::nothrow) Atomic<size_t>(1);

// 	if (!m_counter)
// 	{
// 		delete m_ptr;
// 		m_ptr = 0;

// 		throw std::bad_alloc();
// 	}
// }

// template <typename T>
// SharedPtr<T>::~SharedPtr() 
// {
// 	DeleteIfIMP();
// }

// template <typename T>
// SharedPtr<T>::SharedPtr(const SharedPtr& other_)
// 	:m_ptr(other_.m_ptr), m_counter(other_.m_counter)
// {
// 	m_counter->Inc();
// }

// template <typename T>
// SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other_)
// {
// 	other_.m_counter->Inc();

// 	DeleteIfIMP();

// 	m_ptr = other_.m_ptr;
// 	m_counter = other_.m_counter;

// 	return (*this);
// }

// template <typename T>
// template<typename O>
// SharedPtr<T>::SharedPtr(const SharedPtr<O>& other_)
// 	:m_ptr(other_.m_ptr), m_counter(other_.m_counter)
// 	// O* must be implicitly convertable to T*
// {
// 	m_counter->Inc();
// }

// template <typename T>
// T& SharedPtr<T>::operator*() const
// {
// 	return (*m_ptr);
// }

// template <typename T>
// T* SharedPtr<T>::operator->() const
// {
// 	return (m_ptr);
// }



// #endif //RD70_SHARED_PTR
