#include <iostream>

template <typename C>
void f(C &&c)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  c();
}

void g()
{
}

int
main()
{
  // Function g is an lvalue.
  f(g); // C = void (&)();
  // The closure is an rvalue.
  f([]{});
}
