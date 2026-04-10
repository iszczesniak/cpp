#include <iostream>

// Template A
template <typename A1>
void foo(A1 a1)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// Template B
template <typename B1>
void foo(B1 *b1)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int x = 1;

  // Call #1: only template A is a candidate.  The template function
  // called: void foo(int).
  foo(x);

  // Call #2: templates A and B are the candidates.  The template
  // function called: void foo(int *).
  foo(&x);
}
