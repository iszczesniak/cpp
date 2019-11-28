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
      std::unique_ptr<A> p(new A());
      foo();
    }
  catch (bool)
    {
    }
  
  return 0;
}
