#include <iostream>

// A regular (non-template) function.
// void foo(int *)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
// }

// A primary template.
template <typename T>
void foo(T);

// A primary template.
// template <typename T>
// void foo(T *);

template <>
void foo<int *>(int *)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int *p;
  foo(p);
}
