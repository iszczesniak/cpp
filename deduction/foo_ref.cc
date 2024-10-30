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

  // An expression of a pointer type is an rvalue, and so &hello is an
  // rvalue.  Since the hello function is of a non-const type (there
  // is no such thing as a const non-member function), the constness
  // cannot be deduced, and therefore the non-const reference
  // parameter "F &" cannot be initialized with an rvalue.  It would
  // compile if the foo parameter was a const reference.

  foo(*hello);
}
