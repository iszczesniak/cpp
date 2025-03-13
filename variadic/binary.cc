#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

template <typename... P>
void
read(P &... p)
{
  (cin >> ... >> p);
}

template <typename... P>
void
write(P &&... p)
{
  (cout << ... << p);
}

int
main()
{
  write("Hello", ' ', std::string("World"), " x ", 100, "!\n");

  string txt;
  int x;
  bool b;

  read(txt, x, b);
  write(txt, ' ', x, ' ', b, '\n');
}
