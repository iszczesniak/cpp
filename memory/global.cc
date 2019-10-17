#include <iostream>

using namespace std;

// This is not a string literal, but a table of characters initialized
// with a string literal.  It's global and initialized before entering
// the main function.
char t[7] = "Hello!";

int main()
{
  t[0] = 'Y';
  cout << t << endl;
}
