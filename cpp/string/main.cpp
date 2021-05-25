#include <iostream>
#include <cstdlib>

#include "rdstring.hpp"

using namespace ilrd;

int main()
{
  RdString str1("hello");
  RdString str2(str1);
  RdString str3;

  std::cout << "str1 -> " << str1 << std::endl;
  std::cout << "str2 -> " << str2 << std::endl;
  std::cout << "str3 -> " << str3 << std::endl;

  str2 = "wassup";

  std::cout << "str1 -> " << str1 << std::endl;
  std::cout << "str2 -> " << str2 << std::endl;
  std::cout << "str3 -> " << str3 << std::endl;

  std::cout << "str2 length is " << str2.Length() << std::endl;

  std::cout << "str2 as Cstr print -> " << str2.Cstr() << std::endl; 
}
