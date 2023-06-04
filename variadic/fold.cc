#include <iostream>
#include <string>

template <typename ...Args>
void
print(const Args &...args)
{
  (std::cout << ... << args);
}

int
main()
{
  print("Hello", ' ', std::string("World x "), 100, '\n');
}
