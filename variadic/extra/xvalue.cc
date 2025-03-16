#include <iostream>

struct A
{
  A()
  {
    std::cout << "ctor\n";
  }
};

int main()
{
  A a;
  A &&r = std::move(a);
}
