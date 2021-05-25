#include <map>                          //map
#include <boost/core/noncopyable.hpp>   //boost::noncopyable
#include <boost/shared_ptr.hpp>         //boost::shared_ptr
#include <cassert>                      //assert
#include "shared_ptr.hpp"

// #include "glut_utils.h"

#ifndef RD70_FACTORY
#define RD70_FACTORY

//HANDLE must be copyable
//KEY must be copyable and comparable
//DATA must be copyable
//CREATOR must be callable with DATA as argument
template <typename HANDLE, typename KEY, typename DATA, typename CREATOR = HANDLE (*)(DATA)>
class Factory:private boost::noncopyable
{
public:
  // GENERATED CTOR & DTOR

  void add(KEY, CREATOR);   //undefined behavior if KEY exists          //add value to created function (CREATOR) by key
  HANDLE create(KEY, DATA); //undefined behavior if KEY is not found    //create function to handle something

private:
  std::map<KEY, CREATOR> m_map;
};

template <typename HANDLE, typename KEY, typename DATA, typename CREATOR>
void Factory<HANDLE, KEY, DATA, CREATOR>::add(KEY key, CREATOR creator)
{
  assert(m_map.find(key) == m_map.end());

  m_map.insert(std::pair<KEY, CREATOR>(key, creator));
}

template <typename HANDLE, typename KEY, typename DATA, typename CREATOR>
HANDLE Factory<HANDLE, KEY, DATA, CREATOR>::create(KEY key, DATA data)
{
  assert(m_map.find(key) != m_map.end());

  return(m_map[key](data));
}

#endif //RD70_FACTORY
