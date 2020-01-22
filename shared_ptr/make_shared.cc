#include <memory>

using namespace std;

int
main()
{
  // We have to type A twice.
  shared_ptr<int> sp(new int);
  // Bug: constructor and destructor mismatch.
  shared_ptr<int[]> sp2(new int);
  // Bug: constructor and destructor mismatch.
  shared_ptr<int> sp3(new int[5]);
}
