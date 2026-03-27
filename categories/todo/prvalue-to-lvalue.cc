#include "A.hpp"

const A &foo()
{
  return A("Hello");
}

int main()
{
  foo();
  static_cast<const A &>(A("World"));
}
