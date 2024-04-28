#include <iostream>
#include <string>

template <typename P1, typename ...P>
void
print(const P1 &p1, const P &...p)
{
  std::cout << p1;

  if constexpr(sizeof...(p))
    print(p...);
}

int
main()
{
  print("Hello", ' ', std::string("World x "), 100, '\n');
}
