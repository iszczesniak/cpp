#include <array>
#include <memory>

using namespace std;

void
foo(unique_ptr<array<int, 5>> p)
{
  // Do sth with p.
  try
    {
      // An exception could be thrown here.
      throw true;
    }
  catch(bool)
    {
    }
}

int
main()
{
  foo(make_unique<array<int, 5>>());
}
