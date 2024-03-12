#include <iostream>
#include <tuple>

template<typename T, std::size_t I = 0>
void print(const T &t)
{
  if constexpr (I < std::tuple_size<T>{})
    {
      std::cout << std::get<I>(t) << std::endl;
      print<T, I + 1>(t);
    }
}

int
main()
{
  std::tuple t{1, .1, "txt"};

  print(t);
}
