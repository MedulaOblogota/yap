#include <cstdlib>
#include <cstring>
#include <iostream>

class String;

std::ostream& operator<<(std::ostream& os_, const String& str_);

class String
{
public:
  String(char *str_="");  //may throw bad_alloc
  String(const String& str_);
  ~String();

  char *ToCStr() const;

private:
  char *m_str;
  char *copyIMP(const char *str_);
  String& operator=(const String& str_);
};

char *String::copyIMP(const char *str_)
{
  size_t length = strlen(str_) + 1;
  char *temp = new char[length];
  memmove(temp, str_, length);

  std::cout << "entered copyIMP" << std::endl;

  return temp;
}

String::String(char *str_)
  : m_str(copyIMP(str_))
{
  std::cout << "entered ctor" << std::endl;
}

String::String(const String& str_)
  : m_str(copyIMP(str_.m_str))
{
  std::cout << "entered cctor" << std::endl;
}

String::~String()
{
  delete[] m_str;
  std::cout << "entered dtor" << std::endl;
}

char * String::ToCStr() const
{
  std::cout << "entered toCStr" << std::endl;
  return m_str;
}

// String& String::operator=(const String& str_)
// {
//   delete[] m_str;
//
//   m_str = copyIMP(str_.m_str);
//
//   return (*this);
// }

std::ostream& operator<<(std::ostream& os_, const String& str_)
{
  std::cout << "entered <<" << std::endl;
  return os_ << str_.ToCStr();
}


int main()
{
  String str = "Hello";

  std::cout << str << std::endl;;

  // String str2 = "Hi";

  // str = str2;

  std::cout << str << std::endl;
}
