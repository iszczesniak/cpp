#include <string>

using namespace std;

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
  // This would not compile, because std::string is not incrementable.
  // inc(y);
}
