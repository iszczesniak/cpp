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

// A &operator++(A &)
// {
//   cout << __PRETTY_FUNCTION__ << std::endl;
//   return *this;
// }

// A &&operator++(A &&)
// {
//   cout << __PRETTY_FUNCTION__ << std::endl;
//   return std::move(*this);
// }

int
main()
{
  ++++A{};
  A a;
  ++++a;
}
