#include <map>                          //map
#include <cassert>                      //assert
#include <iostream>                     //cout
#include <stdlib.h>                     //exit

#ifndef RD70_FACTORY
#define RD70_FACTORY

//HANDLE must be copyable
//KEY must be copyable and comparable
//DATA must be copyable
//CREATOR must be callable with DATA as argument
template <typename HANDLE, typename KEY, typename DATA, typename CREATOR = HANDLE (*)(DATA)>
class Factory
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
  if (m_map.find(key) == m_map.end())
  {
    std::cout << "wrong key! server going DOWN!" << std::endl;
    exit(-1);
  }

  return(m_map[key](data));
}

#endif //RD70_FACTORY
