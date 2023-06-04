#include <iostream>
#include <string>

template <typename Arg1, typename ...Args>
void
print(const Arg1 &arg1, const Args &...args)
{
  std::cout << arg1;

  if constexpr(sizeof...(args))
    print(args...);
}

int
main()
{
  print("Hello", ' ', std::string("World x "), 100, '\n');
}
