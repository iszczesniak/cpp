#include <iostream>

template <typename T>
void foo(T t1, T t2)
{
  std::cout << "Template with one parameter.\n";
}

template <typename T1, typename T2>
void foo(T1 t1, T2 t2)
{
  std::cout << "Template with two parameters.\n";
}

int main()
{
  foo(1, 1);
}
