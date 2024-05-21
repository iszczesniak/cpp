#include <iostream>
#include <utility>

using namespace std;

void
test(const string &s1, const string &s2)
{
  if (s1 != s2)
    cout << "Expected: " << s1 << ", got: " << s2 << endl;
}

void
g(int &, const string &s)
{
  cout << __PRETTY_FUNCTION__ << endl;
  test(s, "int &");
}

void
g(const int &, const string &s)
{
  cout << __PRETTY_FUNCTION__ << endl;
  test(s, "const int &");
}

void
g(int &&, const string &s)
{
  cout << __PRETTY_FUNCTION__ << endl;
  test(s, "int &&");
}

template<typename T>
void
f(T &&t, const string &s)
{
  cout << __PRETTY_FUNCTION__ << endl;
  // g(t, s);
  g(forward<T>(t), s);
}

int main()
{
  // Test "int &"
  int x;
  g(x, "int &");
  f(x, "int &");

  // Test "const int &"
  const int &y = 1;
  g(y, "const int &");
  f(y, "const int &");

  // Test "int &&"
  g(1, "int &&");
  f(1, "int &&");

  // We pass an rvalue of double type, but expect the "int &&"
  // overload of g to be called.  Inside function f, when passing
  // parameter t to function g, type conversion from double to int
  // takes place, creating a temporary.  That conversion is allowed
  // and required there, just like in C.
  g(1.0, "int &&");
  f(1.0, "int &&");
}
