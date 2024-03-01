#include "fibonacci.hpp"

#include <cassert>
#include <iostream>

int
main()
{
  assert((fibonacci<int, 0>() == 0));
  assert((fibonacci<int, 1>() == 1));
  assert((fibonacci<int, 2>() == 1));
  assert((fibonacci<int, 19>() == 4181));

  std::cout << fibonacci<unsigned long long, 19>() << std::endl;
}
