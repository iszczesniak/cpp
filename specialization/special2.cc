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
void foo(C1 (*c1)())
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void goo()
{
}

int main()
{
  // Templates A, B and C are the candidates.  The template function
  // called: void foo(int (*)());
  foo(goo);
}
