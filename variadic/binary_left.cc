#include <iostream>
#include <string>

template <typename... P>
void
print(const P &... p)
{
  (std::cout << ... << p);
}

int
main()
{
  print("Hello", ' ', std::string("World"), " x ", 100, '\n');
}
