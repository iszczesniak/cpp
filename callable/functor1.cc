#include <iostream>

struct functor_type
{
  void operator()() const
  {
  }
};

int
main()
{
  functor_type f;
  f();
}
