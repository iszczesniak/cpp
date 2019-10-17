#include <iostream>

using namespace std;

int main()
{
  // "Hello!" is a string literal in the read-only memory.
  *static_cast<char *>("Hello!") = 'Y';

  // A string literal is of type "const char *", and that's why we had
  // to static-cast it to "char *".  This would not compile:
  // *"Hello!" = 'Y';
}
