#include <iostream>

#include "question1.hpp"


int main()
{
  int arr[12];

  std::cout << Max<int>(3,5) << " "
            << Max<int>(4, 12) << " ";
  // std::cout << Max<int *>(arr, arr+8) << std::endl;
  // std::cout << Max<float>(2.1, 6.2) << " ";
  // std::cout << Max('a', 'b') << std::endl;

  return 0;

}
