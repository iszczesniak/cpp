#include <iostream>

void
foo(int *p)
{
  // Do sth with p.

  // Should I destroy p?  I guess.
  delete p;
}

int
main()
{
  int *p = new int(1);
}
