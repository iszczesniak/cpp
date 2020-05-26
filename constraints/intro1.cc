#include <string>

template <typename T>
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

  std::string y("Hello World!");
  inc(y);
}
