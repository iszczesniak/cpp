#include <string>

using namespace std;

template <typename T>
void
inc(T &t) requires requires {++t;}
{
  ++t;
}

struct A
{
  A &
  operator++()
  {
    return *this;
  }
};

int
main()
{
  int x = 1;
  inc(x);

  A a;
  inc(a);
  
  std::string y("Hello World!");
  // This would not compile, because std::string is not incrementable.
  // inc(y);
}
