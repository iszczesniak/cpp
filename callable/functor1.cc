#include <iostream>

struct functor_type
{
  void operator()() const
  {
    std::cout << "Hello World from a functor!\n";
  }
};

int
main()
{
  functor_type f;
  f();
}
