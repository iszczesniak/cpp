#include <iostream>

// A table of characters initialized with a string literal.
char t[] = "Hello!";

int main()
{
  t[0] = 'Y';
  std::cout << t << std::endl;
}
