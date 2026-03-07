#include <iostream>

using namespace std;

// A table of characters initialized with a string literal.
char t[] = "Hello!";

int main()
{
  t[0] = 'Y';
  cout << t << endl;
}
