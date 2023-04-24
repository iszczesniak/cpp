#include <iostream>

void g(int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void g(const int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void g(int &&)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T>
void f(T &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  g(t);
}

template <typename T>
void f(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  g(t);
}

int main()
{
  std::cout << "int &: ----------" << std::endl;
  int x = 1;
  f(x);
  g(x);

  std::cout << "const int &: ----" << std::endl;
  const int y = 2;
  f(y);
  g(y);

  std::cout << "int &&: ---------" << std::endl;
  f(1);
  g(1);
}
