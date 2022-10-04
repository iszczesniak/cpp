#include <iostream>

int main()
{
  int x = 1;
  int *p = &x;
  // A reference to a pointer to an integer.
  int * & r2p = p;
  // A reference to a const pointer to an integer.
  int * const & r2cp = p;
  *r2p = 2;
  // We cannot modify the const pointer through the reference.
  // r2p = &x;
  // But we can modify the pointer.
  p = &x;
  std::cout << x << '\n';

  int &r = x;
  // A pointer to a reference does not exist.
  // int & * p2r = r;
}
