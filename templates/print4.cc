#include <iostream>

template <typename T>
void print(const T &t)
{
  std::cout << t << '\n';
}

template <int N, typename T>
void print(const T &t)
{
  if constexpr (N)
    {
      print(t);
      print<N - 1>(t);
    }
}

int
main()
{
  print("Hello!");
  print<10>(1);
}
