#include <string>

using namespace std;

int
foo(const string &)
{
}

int main()
{
  int x = 1;
  // The reference binds to rvalue.
  const int &l1 = x;
  // The reference binds to lvalue.
  const int &l2 = 1;
  
  string s;
  // The function parameter reference binds to lvalue.
  foo(s);
  // The function parameter reference binds to rvalue, which is the
  // temporary created with the constructor taking a "const char *".
  foo("Hello!");
}
