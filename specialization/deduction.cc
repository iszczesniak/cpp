#include <iostream>

template <typename T>
void f(void (&)(const T &t))
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void g1(const int &)
{
}

void g2(int)
{
}

int
main()
{
  f(g1);
  // f(g2);
}
