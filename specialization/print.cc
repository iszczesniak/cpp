#include <iostream>

template <typename T>
void print(const T &t)
{
  std::cout << t << '\n';
}

template <unsigned N, typename T>
void print(const T &t)
{
  print(t);
  print<N - 1>(t);
}

// Complete specialization of a function template.
template <>
void print<0>(const int &)
{
}

int
main()
{
  print("Hello!");
  print<10>(1);
}
