#include <memory>
#include <utility>

using namespace std;

unique_ptr<int>
factory()
{
  return make_unique<int>();
}

int
main()
{
  shared_ptr<int> sp(factory());
}
