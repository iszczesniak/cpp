#include <utility>

class A {};

int main()
{
  A a;
  // How come an lvalue is not converted to an rvalue with the
  // standard conversion?  This rule does not apply to reference
  // initialization.
  A &&r1 = static_cast<A &&>(a);
  A &&r2 = std::move(a);
}
