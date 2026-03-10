#include <type_traits>

// A non-deduced context, like in forward?  std::forward uses this
// trick to force us to explicitly provide the template argument.
template <typename T>
void foo(typename std::remove_reference<T>::type &t)
{
}

int main()
{
  int x;
  // Doesn't compile.
  // foo(x);

  // Compiles, because we explicitly provide the template argument.
  foo<int>(x);
}
