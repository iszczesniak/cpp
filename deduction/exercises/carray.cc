#include <iostream>

template<typename T, unsigned N, unsigned I = 0>
void print(T (&t)[N])
{
  if constexpr (I != N)
    {
      std::cout << t[I] << std::endl;
      print<T, N, I + 1>(t);
    }
}

int
main()
{
  int t[] = {1, 2, 3};
  print(t);
}
