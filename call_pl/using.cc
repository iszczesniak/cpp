#include <functional>

class A;

int
main()
{
  using param_type = A();
  A a(param_type);
}
