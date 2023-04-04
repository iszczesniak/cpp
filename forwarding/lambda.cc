#include <utility>

using namespace std;

void
loo(const &)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void
roo()
{
}

int
main()
{
  auto c = [](auto &&f, auto &&t)
  {
    forward<decltype(f)>(f)(forward<decltype(t)>(t));
  };
}
