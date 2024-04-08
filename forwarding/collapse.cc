#include <iostream>
#include <type_traits>

using namespace std;

// A reference does not have a top-level qualifier.

int
main()
{
  using l_type = int &;
  using cl_type = const int &;
  using r_type = int &&;
  using cr_type = const int &&;

  // A non-const lvalue reference to all other reference types.
  // int & & -> int &
  static_assert(is_same_v<l_type &, int &>);
  // const int & & -> const int &
  static_assert(is_same_v<cl_type &, const int &>);
  // int && & -> int &
  static_assert(is_same_v<r_type &, int &>);
  // const int && & -> const int &
  static_assert(is_same_v<cr_type &, const int &>);

  // A const lvalue reference to all other reference types.
  // int & const & -> int &
  static_assert(is_same_v<l_type const &, int &>);
  // const int & const & -> const int &
  static_assert(is_same_v<cl_type const &, const int &>);
  // int && const & -> int &
  static_assert(is_same_v<r_type const &, int &>);
  // const int && const & -> const int &
  static_assert(is_same_v<cr_type const &, const int &>);

  // A non-const rvalue reference to all other reference types.
  // int & && -> int &
  static_assert(is_same_v<l_type &&, int &>);
  // const int & && -> const int &
  static_assert(is_same_v<cl_type &&, const int &>);
  // int && && -> int &&
  static_assert(is_same_v<r_type &&, int &&>);
  // const int && && -> const int &&
  static_assert(is_same_v<cr_type &&, const int &&>);

  // A const rvalue reference to all other reference types.
  // int & const && -> int &
  static_assert(is_same_v<l_type const &&, int &>);
  // const int & const && -> const int & 
  static_assert(is_same_v<cl_type const &&, const int &>);
  // int && const && -> int &&
  static_assert(is_same_v<r_type const &&, int &&>);
  // const int && const && -> const int &&
  static_assert(is_same_v<cr_type const &&, const int &&>);
}
