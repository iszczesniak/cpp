#include <iostream>

struct empty_callable
{
  void
  operator()()
  {
  }
};

struct it
{
  void
  operator()()
  {
    std::cout << "Done it.\n";
  }
};

template <typename C = empty_callable>
void
do_sth(C c = {})
{
  c();
}


int
main()
{
  // Do nothing.
  do_sth();
  // Do it.
  do_sth(it{});
}
