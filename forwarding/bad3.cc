#include <iostream>

void g(int &)
{
  std::cout << "int &\n";
}

void g(const int &)
{
  std::cout << "const int &\n";
}

template <typename T>
void f(T &t)
{
  g(t);
}

template <typename T>
void f(const T &t)
{
  g(t);
}

int main()
{
  int x = 1;
  f(x);
  f(1);
}
