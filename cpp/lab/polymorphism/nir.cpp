#include <iostream>

class Base
{
public:
  void show() { std::cout << "in base" << std::endl; }
};

class Derived: public Base
{
public:
  void show() { std::cout << "in derived" << std::endl; }
};

int main()
{
  Base *bp = new Derived();
  bp->show();
  return 0;

}
