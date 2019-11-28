#include <cassert>
#include <iostream>
#include <memory>
#include <deque>

struct A
{
  A()
  {
    std::cout << "ctor\n";
  }

  ~A()
  {
    std::cout << "dtor\n";
  }
};

int
main(void)
{
  try
    {
      A *p = new A();
    }
  catch ()
    {
    }
  
  return 0;
}
