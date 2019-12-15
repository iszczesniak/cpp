#include <iostream>

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
  A *p;

  try
    {
      p = new A();
      foo();
      delete p;
    }
  catch (bool)
    {
      // Have to delete.
      delete p;
    }
  
  return 0;
}
