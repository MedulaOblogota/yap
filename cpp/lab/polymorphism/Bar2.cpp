#include <iostream>

#include "question1.hpp"

void Bar2()
{
  // int arr[12];

  std::cout << Max<int>(4,6) << " "
            << Max<double>(5.7, 19.9) << " ";
  // std::cout << Max<int *>(arr, arr+8) << std::endl;
  // std::cout << Max<float>(2.1, 6.2) << " ";
  // std::cout << Max('a', 'b') << std::endl;
}
