#include <iostream>
#include <string>

template <typename T, typename... P>
auto add(const T &t, const P &... p)
{
  // Addition is associative, so it doesn't matter whether we use the
  // left or the right version of the unary fold expression.

  // The left version.
  return (t + ... + p);
  // The right version.
  // return (p + ... + t);
}

int
main()
{
  std::cout << add(1, 2) << std::endl;
  std::cout << add(1, 2.3) << std::endl;
  std::cout << add(std::string("Hello "), "World", '!') << std::endl;
}
