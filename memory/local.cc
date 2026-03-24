#include "A.hpp"
#include <iostream>

int main()
{
  A a("a, function scope");
  A b("b, function scope");

  // Block scope.
  {
    A a("a, block scope");
    A b("b, block scope");
  }
  
  std::cout << "Bye!" << std::endl;
}
