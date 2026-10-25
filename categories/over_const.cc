#include <iostream>

int main()
{
  struct A
  {
    void foo()
    {
      std::cout << __PRETTY_FUNCTION__ << '\n';
    }

    void foo() const
    {
      std::cout << __PRETTY_FUNCTION__ << '\n';
    }
  };

  A a;
  a.foo();
  std::as_const(a).foo();  
  const A c;
  c.foo();
}
