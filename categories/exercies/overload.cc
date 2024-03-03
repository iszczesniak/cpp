#include <iostream>
#include <utility>

struct A
{
  A &operator++() &
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }

  A &&operator++() &&
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::move(*this);
  }
};

// A &operator++(A &a)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
//   return a;
// }

// A &&operator++(A &&a)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
//   return std::move(a);
// }

int
main()
{
  ++++A{};
  A a;
  ++++a;
}
