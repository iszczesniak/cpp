#include <iostream>

template <typename T>
void print(const T &t)
{
  std::cout << t << '\n';
}

template <int N, typename T>
void print(const T &t)
{
  print(t);
  print<N - 1>(t);
}


// Explicit (full) specialization of a function template.
template <>
void print<0, int>(const int &)
{
}

int
main()
{
  print("Hello!");
  print<10>(1);
}
