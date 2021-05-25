#include <iostream>
#include <string>

typedef std::basic_string<int> Str;

template<class T>
class CharTraits
{
  static const T TERM;
};

template<>
class CharTraits<char>
{
  static const char TERM = 0;
};

std::ostream& operator<<(std::ostream& os_, const Str& str)
{
  return os_ << "hello" << std::endl;
}

int main()
{

    Str myStr;
    // char c = 0;
    // char CharTraits::TERM(c);

    myStr = 124;

    std::cout << myStr << std::endl;
}
