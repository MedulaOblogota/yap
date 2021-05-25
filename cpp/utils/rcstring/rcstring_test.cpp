#include "rcstring.hpp"

using namespace ilrd;

int main()
{
  RcString string1("hello");
  RcString string2(string1);

  std::cout << "string1=" << string1 << std::endl;
  std::cout << "string2=" << string2 << std::endl;

  RcString string3 = "wassup";

  char c = string3[2];

  string3 = string1;

  string1[1] = 'a';

  std::cout << "string1=" << string1 << std::endl;
  RcString string0 = "yo";

  string0[1] = 'a';
  std::cout << "string0=" << string0 << std::endl;

  std::cout << c << std::endl;

  std::cout << "string1 length = " << string1.Length() << std::endl;

}
