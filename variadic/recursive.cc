#include <iostream>
#include <string>

template <typename Arg1, typename ...Args>
void
print(Arg1 arg1, Args ...args)
{
  std::cout << arg1;

  if constexpr(sizeof...(Args))
    print(args...);
}

int
main()
{
  print("Hello", ' ', std::string("World"), " x ", 100, '\n');
}
