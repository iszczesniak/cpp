#include <memory>

using namespace std;

int
main()
{
  auto up = make_unique<int>();
  shared_ptr<int> sp(up.release());
}
