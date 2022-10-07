#include <iostream>

using namespace std;

const int test1 = 1;

int main()
{
  // Is the i1 global variable in the read-only memory?
  // *const_cast<int *>(&test1) = 10;
  // const_cast<int &>(test1) = 10;

  // Is this local variable in the read-only memory?
  const volatile int test2 = 2;
  *const_cast<int *>(&test2) = 20;
  cout << test2 << endl;
  const_cast<int &>(test2) = 200;
  cout << test2 << endl;

  // Is this local static variable in the read-only memory?
  static const int test3 = 3;
  // *const_cast<int *>(&test3) = 30;
  // const_cast<int &>(test3) = 30;

  // "Hello!" is a string literal in the read-only memory.
  // *static_cast<char *>("Hello!") = 'Y';

  // A string literal is of type "const char *", and that's why we had
  // to static-cast it to "char *".  This would not compile:
  // *"Hello!" = 'Y';
}
