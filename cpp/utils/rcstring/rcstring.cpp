#include <cstring>    //strlen
#include <cstdlib>    //size_t
#include <iostream>   //ostream
#include <cassert>    //assert

#include "rcstring.hpp"

namespace ilrd
{

char *RcString::CopyStringIMP(const char* other_)
{
  assert(other_);

  size_t length = sizeof(size_t) + strlen(other_) + 1;
  char *ret = static_cast<char *>(::operator new(length));

  memcpy(ret + sizeof(size_t), other_, length - sizeof(size_t));

  return ret + sizeof(size_t);
}

// char *RcString::CopyRcStringIMP(const char* other_)
// {
//   assert(other_);
//
//   size_t length = sizeof(size_t) + strlen(other_) + 1;
//   char *ret = static_cast<char *>(::operator new(length));
//
//   memcpy(ret, other_, length);
//
//   return ret + sizeof(size_t);
// }

void RcString::DecCounterIMP()
{
  // assert(*reinterpret_cast<size_t *>(m_str - sizeof(size_t)) > 0);
  //
  size_t counter = *reinterpret_cast<size_t *>(m_str - sizeof(size_t));

  __sync_lock_test_and_set((size_t *)(m_str - sizeof(size_t)), counter - 1);
}

void RcString::IncCounterIMP() const
{
  size_t counter = *reinterpret_cast<size_t *>(m_str - sizeof(size_t));
  __sync_lock_test_and_set((size_t *)(m_str - sizeof(size_t)), counter + 1);
  // ++*reinterpret_cast<size_t *>(m_str - sizeof(size_t));
}

size_t RcString::GetCounterIMP()
{
  return *reinterpret_cast<size_t *>(m_str - sizeof(size_t));
}

void RcString::InitCounterIMP()
{
  __sync_lock_test_and_set((size_t *)(m_str - sizeof(size_t)), 1);
  // *reinterpret_cast<size_t *>(m_str - sizeof(size_t)) = 1;
}


RcString::RcString(const char* str)
  : m_str(CopyStringIMP(str))
{
  *reinterpret_cast<size_t *>(m_str - sizeof(size_t)) = (1);
}

RcString::RcString(const RcString& other_)
  : m_str(other_.m_str)
{
  IncCounterIMP();
}

RcString::~RcString()
{
  DecCounterIMP();

  if (0 == GetCounterIMP())
  {
    ::operator delete(m_str - sizeof(size_t));
  }

  m_str = NULL;
}

RcString& RcString::operator=(const RcString& other_)
{
  other_.IncCounterIMP();
  DecCounterIMP();

  if (0 == GetCounterIMP())
  {
    ::operator delete(m_str - sizeof(size_t));
  }

  m_str = other_.m_str;

  return *(this);
}

std::size_t RcString::Length() const
{
  return strlen(m_str);
}

const char *RcString::Cstr() const
{
  return (m_str);
}

std::ostream& operator<<(std::ostream& os_, const RcString& string_)
{
  return os_ << string_.Cstr();
}

bool RcString::IsShared()
{
  return (GetCounterIMP() > 1);
}

char& RcString::operator[](size_t index)
{
  if (!IsShared())
  {
    return m_str[index];
  }

  DecCounterIMP();
  m_str = CopyStringIMP(m_str);
  InitCounterIMP();

  return m_str[index];
}

char RcString::operator[](size_t index) const
{
  return (m_str)[index];
}

} //namespace ilrd
