#include "A.hpp"
#include <iostream>

A * factory()
{
  return new A("factory");
}

int main()
{
  A *p = factory();
  delete p;

  std::cout << "Bye!" << std::endl;
}
