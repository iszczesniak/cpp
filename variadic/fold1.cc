#include <iostream>
#include <string>

template <typename T, typename ...P>
void
print(const T &t, const P &...p)
{
  std::cout << t;
  ((std::cout << ", " << p), ...);
}

int
main()
{
  print("Hello", std::string("World"), "x", 100);
  std::cout << std::endl;
}
