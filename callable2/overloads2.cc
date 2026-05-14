#include <functional>

// A template function -----------------------------------------------
template <typename T>
void goo(T)
{
}

int
main()
{
  // Template function call ------------------------------------------
  goo(1);

  // std::invoke(goo);
  // std::invoke(goo, 1);

  // std::apply(goo, std::make_tuple());
  // std::apply(goo, std::forward_as_tuple(1));
}
