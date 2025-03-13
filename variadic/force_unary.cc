#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

template <typename... P>
void
read(P &&... p)
{
  (... >> p);
}

template <typename... P>
void
write(P &&... p)
{
  (... << p);
}

int
main()
{
  write(cout, "Hello", ' ', std::string("World"), " x ", 100, "!\n");

  istringstream in("Hi! 100 0");

  string txt;
  bool b;

  // We don't care about the 100, so we read it into a temporary.
  read(in, txt, int(), b);
  write(cout, txt, ' ', 200, ' ', b, '\n');
}
