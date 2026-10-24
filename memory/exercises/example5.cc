#include "hack.hpp"

struct X
{
  A m_a;

  X(A a = {})
  {
    new (&a) A("main");
    new (&m_a) A(a);
  }
};

int main()
{
  X();
}
