#include <iostream>

using namespace std;

template <typename T>
void foo(T)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void foo(T *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int x = 1;
  // Only the first overload can be used.  The template function
  // called is: void foo(int).
  foo(x);
  // Both overloads ("void foo(T) with T = int *" and "void foo(T *)
  // with T = int") can be instantiated, so that the resulting
  // template function "void foo(T *)" can be called.  The compiler
  // chooses the second template to produce the template function to
  // finally call it.
  foo(&x);
}
