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
foo(int, A *p)
{
  delete p;
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
      foo(index(), new A());
    }
  catch (bool)
    {
    }
  
  return 0;
}
