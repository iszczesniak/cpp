#include <iostream>
#include <iterator>

template <typename T>
void foo(T &t)
{
  for(std::size_t i = 0; i < std::size(t); ++i)
    std::cout << t[i] << std::endl;
}

int main()
{
  int t[] = {1, 2, 3};
  foo(t);
}
