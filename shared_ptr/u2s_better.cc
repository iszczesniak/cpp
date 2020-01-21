#include <memory>
#include <utility>

using namespace std;

int
main()
{
  auto up = make_unique<int>();
  shared_ptr<int> sp(move(up));
}
