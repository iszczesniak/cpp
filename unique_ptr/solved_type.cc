#include <memory>

using namespace std;

int
main()
{
  // Undefined behavior!
  unique_ptr<int> up1(new int[5]);
  unique_ptr<int[]> up2(new int);

  // The preferred way, because it's less error-prone.
  auto up3 = make_unique<int>();
  auto up4 = make_unique<int[]>(5);
}
