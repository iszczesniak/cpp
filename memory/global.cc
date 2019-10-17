#include <iostream>

using namespace std;

// This is not a string literal, but a table of characters initialized
// with a string literal.
char t[] = "Hello!";

int main()
{
  t[0] = 'Y';
  cout << t << endl;
}
