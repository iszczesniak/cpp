#include <memory>
#include <utility>

using namespace std;

make_unique<int>
foo()
{
  return make_unique<int>();
}

int
main()
{
  shared_ptr<int> sp(foo());
}
