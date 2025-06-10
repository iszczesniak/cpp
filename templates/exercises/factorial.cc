#include "factorial.hpp"

#include <iostream>

int main()
{
  std::cout << factorial<unsigned, 5>() << std::endl;
  std::cout << factorial<unsigned long, 10>() << std::endl;
  std::cout << factorial<unsigned long long, 15>() << std::endl;
}
