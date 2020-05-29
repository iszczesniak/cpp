#include <string>

using namespace std;

template <typename T> requires requires (T t) {++t;}
void
inc(T &t)
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
