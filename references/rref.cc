#include <iostream>

int main()
{
  // Error: an rvalue reference must be initialized.
  // int &&a;

  int i;

  // Erorr: an rvalue reference cannot bind to an lvalue.
  // int &&z = i;

  int &l = i;
  // Error: l is an lvalue, and an rvalue reference can't bind to it.
  // int &&r = l;

  // OK: an rvalue reference can bind to an rvalue.
  int &&x = 1;

  // Error: x is an lvalue, and an rvalue reference can't bind to it.
  // x is an lvalue, because it has a name, even though it's of the
  // rvalue reference type.

  // int &&z = x;
}
