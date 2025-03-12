#include <iostream>
#include <string>

template <typename... P>
void
in(P &... p)
{
  (std::cin >> ... >> p);
}

template <typename... P>
void
out(const P &... p)
{
  (std::cout << ... << p);
}

int
main()
{
  out("Hello", ' ', std::string("World"), " x ", 100, '\n');

  std::string s;
  int x;
  bool b;

  in(s, x, b);
  out(s, x, b);
}
