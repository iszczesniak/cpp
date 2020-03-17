#include <iostream>

template <int N>
void
print()
{
  std::cout << N << std::endl;
}

int
main()
{
  print<100>();
}
