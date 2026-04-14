#include <iostream>

template <typename T>
void foo(T)
{
  std::cout << "surprise!\n";
}

template <>
void foo(const int &)
{
  std::cout << "specialization\n";
}

int main()
{
  const int x = 1;
  foo(x);
  foo<const int &>(x);
}
