#include <iostream>
#include <utility>

using namespace std;

struct A
{
  A() = default;
  A(const A &) = delete;
  A(const A &&) = delete;
};

void
loo(const A &)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void
roo(const A &&)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  auto c = [](auto &&f, auto &&t)
  {
    forward<decltype(f)>(f)(forward<decltype(t)>(t));
  };

  A a;
  c(loo, a);
  // c(roo, a);

  c(roo, A());
  c(loo, A());

  c([](int i){cout << i << '\n';}, 1);
}
