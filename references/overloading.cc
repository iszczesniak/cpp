#include <iostream>

using namespace std;

// Uncomment, and analyze the difference in overload resolution.
//
// // Overload #1
// void
// foo(int &)
// {
//   cout << "int &" << endl;
// }

// Overload #2
void
foo(const int &)
{
  cout << "const int &" << endl;
}

// Uncomment, and analyze the difference in overload resolution.
//
// // Overload #3
// void
// foo(int &&)
// {
//   cout << "int &&" << endl;
// }

int
main()
{
  int x = 1;
  int &rx = x;
  foo(x); // Overload #1 if available, overload #2 otherwise.
  foo(rx); // Overload #1 if available, overload #2 otherwise.

  const int y = 2;
  const int &ry = y;
  foo(y); // Always overload #2, an error otherwise.
  foo(ry); // Always overload #2, an error otherwise.

  int &&rz = 3;
  foo(3); // Overload #3 if available, overload #2 otherwise.
  foo(rz); // Overload #1 if available, overload #2 otherwise.
}
