#include <memory>

using namespace std;

int
main()
{
  // We don't have to write the type twice.
  auto sp = make_shared<int>();
  // We can't mismatch the constructor and destructor.
  auto sp2 = make_shared<int[]>(5);
}
