// Compile with g++ -fconcepts test.cc

#include <iostream>
#include <type_traits>

// template<typename T>
// T max(T a, T b)
// {
//   // static_assert(std::is_integral<T>::value);
//   static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value);
//   return b < a ? a : b;
// }

template<typename T> requires std::is_integral<T>::value
T max(T a, T b)
{
  return b < a ? a : b;
}

// template<typename T>
// concept bool LessThanComparable = requires(T x, T y)
// {
//   { x < y } -> bool;
//   // a + b;
// };

// template<typename T> requires LessThanComparable<T>
// T max(T a, T b)
// {
//   return b < a ? a : b;
// }

// auto
// max(LessThanComparable a, LessThanComparable b)
// {
//   return b < a ? a : b;
// }

struct A
{
};

namespace std
{
  template <>
  struct is_integral<A>
  {
    static const bool value = true;
  };
}

struct B
{
};

int
main()
{
  max(1, 2);
  max(1., 2.);
  max(A(), A());
  max(B(), B());
}
