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

  // New type: non-const lvalue reference + l_type (and the others).
  using ll_type = l_type &;
  static_assert(is_same_v<l_type &, int &>);
  using cll_type = cl_type &;
  static_assert(is_same_v<cll_type, const int &>);
  using rl_type = r_type &;
  static_assert(is_same_v<rl_type, int &>);
  using crl_type = cr_type &;
  static_assert(is_same_v<crl_type, const int &>);

  // Implement for all possible compilations as above.
}
