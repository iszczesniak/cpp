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

int
main()
{
  auto c = [](auto &&... args)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    g(forward<decltype(args)>(args)...);
  };

  c();
  c(1);
}
