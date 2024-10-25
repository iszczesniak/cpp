#include <vector>

int
main()
{
  std::vector<int> v1{3, 1, 2};

  // A compiler can deduce the integer type from the initializer list.
  std::vector v2{3, 1, 2};
}
