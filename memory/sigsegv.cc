#include <iostream>

using namespace std;

int main()
{
  // "Hello!" is a string literal in the read-only memory.
  *((char *)"Hello!") = 'Y';
}
