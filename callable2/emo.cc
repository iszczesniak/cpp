#include <iostream>
#include <functional>

using namespace std;

struct Y
{
  void f() const&
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  void g(this Y const&)
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

int main()
{
  Y y;

  auto pf = &Y::f;
  // pf(y);
  (y.*pf)();
  invoke(pf, y);

  auto pg = &Y::g;
  pg(y);
  (&Y::g)(y);
  // (y.*pg)();
  invoke(pg, y);
}
