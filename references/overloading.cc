#include <iostream>

using namespace std;

void
foo(int &)
{
  cout << "int &" << endl;
}

void
foo(const int &)
{
  cout << "const int &" << endl;
}

// Odkomentować i sprawdzić, kiedy ta funkcja została wybrana.
//
// void
// foo(int &&)
// {
//  cout << "int &&" << endl;
// }

int
main()
{
  int x = 1;
  int &rx = x;
  foo(x);
  foo(rx);

  const int y = 2;
  const int &ry = y;
  foo(y);
  foo(ry);

  int &&rz = 3;
  foo(3);
  foo(rz);
}
