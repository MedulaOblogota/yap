#include <iostream>

class Base
{
public:
  ~Base() {  }
  virtual void Print()=0;

};

class Derived:public Base
{
public:
  ~Derived() {  }
  void Print() { std::cout << "hi" << std::endl; };

private:
  char * m_char[10];
};

int main()
{
  Derived error;

  return 0;
}
