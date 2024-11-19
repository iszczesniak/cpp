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
  print(5, "10", std::string("15"));
  std::cout << std::endl;
}
