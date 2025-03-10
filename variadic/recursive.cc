#include <iostream>
#include <string>

template <typename P1, typename... P>
void
print(P1 p1, P... p)
{
  std::cout << p1;

  if constexpr(sizeof...(P))
    print(p...);
}

int
main()
{
  print("Hello", ' ', std::string("World"), " x ", 100, '\n');
}
