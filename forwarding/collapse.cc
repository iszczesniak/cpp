#include <iostream>
#include <type_traits>

using namespace std;

int
main()
{
  using l_type = int &;
  using cl_type = const int &;
  using r_type = int &&;
  using cr_type = const int &&;

  // A reference to the all other reference types.
  static_assert(is_same_v<l_type &, int &>);
  static_assert(is_same_v<cl_type &, const int &>);
  static_assert(is_same_v<r_type &, int &>);
  static_assert(is_same_v<cr_type &, const int &>);

  // Implement for all possible compilations as above.
}
