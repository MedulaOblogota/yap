#include <cstdio>     //size_t
#include <iostream>   //cout

#include "shared_ptr.hpp"

int main()
{
  // SharedPtr<int> pnt2(pnt);
  int *num = new int(3);
  int *num2 = new int(7);

  SharedPtr<int> pnt(num);
  SharedPtr<int> pnt2(num2);
  SharedPtr<int> ccpnt(pnt);

  std::cout << "ccpnt = " << *ccpnt << std::endl;
  // SharedPtr<char> fpnt(pnt);

  // SharedPtr<int> iptr(num);
  // SharedPtr<const int> iptr2(iptr);

  std::cout << *pnt2 << std::endl;

  std::cout << "before pnt = pnt2, pnt = " << *pnt << ". pnt2=" << *pnt2 << std::endl;

  pnt2 = pnt;

  std::cout << "after pnt = pnt2, pnt = " << *pnt << ". pnt2=" << *pnt2 << std::endl;

}
