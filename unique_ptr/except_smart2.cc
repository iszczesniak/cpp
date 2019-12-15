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
foo(int, std::unique_ptr<A> p)
{
}

int
index()
{
  throw true;
  return 0;
}

int
main(void)
{
  try
    {
      foo(index(), std::make_unique<A>());
    }
  catch (bool)
    {
    }
  
  return 0;
}
