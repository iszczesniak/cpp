#include <iostream>

using namespace std;

// Overload A
template <typename A1>
void foo(A1 a1)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

// Overload B
template <typename B1>
void foo(B1 *b1)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int x = 1;
  // Call #1: only overload A is a candidate.  The template function
  // called: void foo(int).
  foo(x);

  // Call #2: overloads A and B are the candidates.  The template
  // function called: void foo(int *).
  foo(&x);
}
