#include <cassert>
#include <concepts>
#include <iostream>
#include <optional>
#include <vector>

template <typename T>
concept has_empty_member = requires (const T &t)
  {
    {t.empty()} -> std::same_as<bool>;
  };

bool empty(const has_empty_member auto &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return t.empty();
}

struct A
{
  // Non-const doesn't qualify.
  bool empty();
};

int main()
{
  // empty(1);

  std::vector<int> v;
  assert(empty(v));

  A a;
  // empty(a);

  std::optional<int> o;
  // empty(o);
}
