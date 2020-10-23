#include <iostream>

using namespace std;

int
main()
{
  int x = 1, y = 2;

  // Would not compile, because x is not captured.
  // []{x = 10;}();

  // Capture every variable by value.
  //  [=](){x = 10;}();
  cout << "x = " << x << endl;

  // Capture every variable by reference.
  [&](){x = 10;}();
  cout << "x = " << x << endl;
}
