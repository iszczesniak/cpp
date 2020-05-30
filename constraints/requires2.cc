#include <string>

using namespace std;

template <typename T>
void
inc(T &t) requires requires {++t;}
{
  ++t;
}

int
main()
{
  int x = 1;
  inc(x);
}
