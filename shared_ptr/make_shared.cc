#include <memory>

using namespace std;

int
main()
{
  // We have to type int twice.
  shared_ptr<int> sp(new int);
  // Bug: constructor and destructor mismatch: int[] vs int
  shared_ptr<int[]> sp2(new int);
  // Bug: constructor and destructor mismatch: int vs int[]
  shared_ptr<int> sp3(new int[5]);
}
