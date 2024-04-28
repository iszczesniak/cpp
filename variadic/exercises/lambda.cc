#include <utility>
#include <iostream>

using namespace std;

void g()
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void g(int)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void g(int, int)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  auto c = [](auto &&...p)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    g(forward<decltype(p)>(p)...);
    // For no arguments, expanded to:
    // g(); 
    // For one argument, expanded to:
    // g(forward<decltype(a1)>(a1));
    // For two arguments, expanded to:
    // g(forward<decltype(a1)>(a1), forward<decltype(a2)>(a2));
  };

  c();
  c(1);
  c(1, 2);
}
