#include <iostream>

#include "threads.hpp"

class F
{
public:
  explicit F() {};
  ~F() {};

  int operator()();

};

int F::operator()()
{
  std::cout << "Hello man! "<< std::endl;

  return 1;
}

// int main()
// {
//   F f;
//   Thread<F> thread(f);
//
//   thread.Detach();
//
//   for (int i = 0; i < 20; ++i)
//   {
//     std::cout << i << std::endl;
//     // std::cout << thread.GetId() << std::endl;
//   }
//
//   return 0;
// }
