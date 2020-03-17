#include <iostream>

template <typename T>
void print(const T &t)
{
  std::cout << t << '\n';
}

template <int N, typename T>
void print(const T &t)
{
  for(int n = N; n--;)
    print(t);
}

int
main()
{
  print("Hello!");
  print<10>("World!");
}
