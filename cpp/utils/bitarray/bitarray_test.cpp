#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "bitarray.hpp"

int main()
{
  BitArray<11> bit_array(true);
  BitArray<11> ba;

  printf("%d\n", (bit_array == ba));
  for (size_t i = 0; i < 11; ++i)
    std::cout << "ba[i] is " << ba.Get(i) << std::endl;

  std::cout << std::endl;

  ba.Set(true, 0);
  ba.Get(1);
  // ba[1] = ba[0];
  ba[2] = true;
  ba[3] = true;
  ba[4] = true;
  ba[5] = true;
  ba[6] = true;
  ba[7] = true;
  ba[8] = true;
  ba[9] = true;
  ba[10] = true;

  for (size_t i = 0; i < 11; ++i)
    std::cout << "ba[i] is " << ba.Get(i) << std::endl;

  std::cout << std::endl;

    for (size_t i = 0; i < 11; ++i)
      std::cout << "bitarray[i] is " << bit_array.Get(i) << std::endl;

  printf("%d\n", (bit_array == ba));

  ba.Toggle(10);

  for (size_t i = 0; i < 11; ++i)
  {
    std::cout << "ba[" << i << "] = " << ba[i] << std::endl;
  }

  std::cout << ba.Count() << std::endl;


  // std::cout << ba[2] << std::endl;
  // std::cout << ba[2] << std::endl;
  // std::cout << (bit_array != ba) << std::endl;
}
