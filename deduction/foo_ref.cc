#include <iostream>

void
hello()
{
  std::cout << "Hello World!\n";
}

template <typename F>
void
foo(F &f)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  f();
}

void
goo(void (&f)())
{
  f();
}

int
main()
{
  foo(hello);
  goo(hello);
}
