#include <iostream>

#include "magic_number.hpp"

int main()
{
  double num = 3;
  double *p_num = &num;

  p_num = NULL;

  std::cout << &p_num << std::endl;
}
