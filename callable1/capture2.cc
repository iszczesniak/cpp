#include <iostream>

int
main()
{
  int x = 1;

  // Would not compile, because x is not captured, and the parameter
  // list is empty.
  // []{x = 10;}();

  [](int &x){x = 10;}(x);
  std::cout << "x = " << x << std::endl;
}
