#include <iostream>

using namespace std;

// Template A
template <typename A1>
void foo(A1 a1)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

// Template B
template <typename B1>
void foo(B1 *b1)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

// Template C
template <typename C1>
void foo(void (*c1)(C1))
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void goo1(int)
{
}

void goo2()
{
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

  // Call #3:
  foo(goo1);

  // This one compiles too!
  foo(goo2);
}
