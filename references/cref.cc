#include <string>

using namespace std;

// The function parameter is a const reference.
int
foo(const string &)
{
}

int
main()
{
  int x = 1;
  // The reference binds to an lvalue.
  const int &l1 = x;
  // The reference binds to an rvalue.
  const int &l2 = 1;
  
  string s;
  // The function parameter reference binds to an lvalue.
  foo(s);
  // Since C++98, a const reference can bind to the data of an rvalue.
  // Here the function parameter reference binds to an rvalue, which
  // is the expression with a temporary of type string created with
  // the constructor taking a "const char *".
  foo("Hello!");
}
