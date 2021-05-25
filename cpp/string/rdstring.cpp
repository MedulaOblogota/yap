#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "rdstring.hpp"

namespace ilrd
{
// void RdString::DestroyIMP()
// {
//   delete[] m_str;   m_str = NULL;
// }

char *RdString::CopyIMP(const char* other_)
{
  assert(other_);
  size_t length = strlen(other_) + 1;
  char *ret = new char[length];

  memcpy(ret, other_, length);

  return ret;
}

RdString::RdString(const char* str)
  : m_str(CopyIMP(str))
{}

RdString::RdString(const RdString& other_)
  : m_str(CopyIMP(other_.m_str))
{}

// RdString::RdString(const RdString& other_)
//   : m_str(CopyIMP(other_.m_str))
// {
//
// }

RdString::~RdString()
{
  delete[] m_str;   m_str = NULL;
}

RdString& RdString::operator=(const RdString& other_)
{
  //Handles self-assignment
  char *temp = CopyIMP(other_.m_str);
  delete[] m_str;
  m_str = temp;

  return *this;
}

size_t RdString::Length() const
{
  return strlen(m_str);
}

const char *RdString::Cstr() const
{
  return m_str;
}

std::ostream& operator<<(std::ostream& os_, const RdString& string_)
{
  return os_ << string_.Cstr();
}
}
