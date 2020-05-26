#include <concepts>
#include <string>

using namespace std;

void
inc(integral &t)
{
  ++t;
}

int
main()
{
  int x = 1;
  inc(x);

  std::string y("Hello World!");
  //  inc(y);
}
