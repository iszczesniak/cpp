#include <iostream>
#include <string>

template <typename T>
void foo(T &t);

template <typename T>
void foo(const T &t);

// Specialization #1: the argument of the primary template deduced.
template <>
void foo(const int &)
{
  std::cout << "Specialization.\n";
}

int main()
{
  const int i = 1;
  foo(i);
}
