#include <iostream>

class X
{
public:
  X() { std::cout << "X Ctor" << std::endl; }
  virtual ~X() {std::cout << "X Dtor" << std::endl;}

protected:
  int m_a;
};

class Y: public X
{
public:
  Y() { std:: cout<< "Y Ctor" << std::endl; }
  virtual ~Y() {std::cout << "Y Dtor" << std::endl;}

private:
  int m_b;
};

void Foo(X x)
{
  std::cout << "in Foo" << std::endl;
}

int main()
{
  X* xp = new Y[5];
  Y y1;

  Foo(y1);

  delete[] xp;

  return 0;
}
