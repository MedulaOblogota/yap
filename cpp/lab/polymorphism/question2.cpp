#include <iostream>

template<typename T>
void Foo(T t)
{
  std::cout << t << " Generic foo" << std::endl;
  ++t;
}

template<>
void Foo<int>(int t)
{
  std::cout << t << " Specialized Foo (for int param)" << std::endl;
  --t;
}

void Foo(int t)
{
  std::cout << t << " main Foo (for int param)" << std::endl;
  --t;
}

int main()
{
  size_t num = 7;
  Foo(5);
  Foo(num);
  // Foo<int>(5);

  return 0;
}
