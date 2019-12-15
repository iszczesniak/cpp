#include <iostream>
#include <memory>

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

void
foo()
{
  throw true;
}

int
main(void)
{
  try
    {
      auto p = make_unique<A>();
      foo();
    }
  catch (bool)
    {
    }
  
  return 0;
}
