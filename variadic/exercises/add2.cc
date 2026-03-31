#include <iostream>
#include <string>

template <typename... Params>
auto add(const Params &... params)
{
  // Addition is associative, so it doesn't matter whether we use the
  // left or the right version of the unary fold expression.

  // The left version.
  return (... + params);
  // The right version.
  // return (params + ...);
}

int
main()
{
  std::cout << add(1, 2) << std::endl;
  std::cout << add(1, 2.3) << std::endl;
  std::cout << add(std::string("Hello "), "World", '!') << std::endl;
}
