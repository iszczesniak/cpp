#include <functional>

struct Y
{
  int f() const&;
  int g(this Y const&);
};

int main()
{
  Y y;

  auto pf = &Y::f;
  // pf(y);
  (y.*pf)();
  std::invoke(pf, y);

  auto pg = &Y::g;
  pg(y);
  (&Y::g)(y);
  // (y.*pg)();
  std::invoke(pg, y);
}
