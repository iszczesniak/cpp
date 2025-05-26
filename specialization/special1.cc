#include <iostream>

using namespace std;

// Overload #1
template <typename T>
void foo(T)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

// Overload #2
template <typename T>
void foo(T *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int x = 1;
  // Call #1: only overload #1 is a candidate.  The template function
  // called is: void foo(int).
  foo(x);

  // Call #2: overloads #1 and #2 are the candidates.  The template
  // function called is: void foo(int *).
  foo(&x);
}
