#include <memory>

using namespace std;

void
foo(unique_ptr<int> p)
{
}

unique_ptr<int>
factory()
{
  try
    {
      auto p = make_unique<int>();

      // Work on the new data.  An exception could be thrown here.
      throw true;

      return p;
    }
  catch(bool)
    {
    }

  return nullptr;
}

int
main()
{
  auto p = factory();
  foo(move(p));
}
