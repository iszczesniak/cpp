#include <iostream>

using namespace std;

int
main()
{
  int x = 1;

  // Would not compile, because x is not captured, and the parameter
  // list is empty.
  // []{x = 10;}();

  // Capture every variable by value.
  [=]() mutable {x = 10;}();
  cout << "x = " << x << endl;

  // Capture every variable by reference.
  [&](){x = 10;}();
  cout << "x = " << x << endl;
}
