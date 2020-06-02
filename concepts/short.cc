#include <iostream>
#include <string>

using namespace std;

template <typename T>
concept incr = requires (T t) {++t;};

template <incr T>
void
inc(T &t)
{
  ++t;
}

int
main()
{
  int x = 1;
  inc(x);

  string s;
  // inc(s);
}
