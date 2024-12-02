#include <concepts>

int &foo()
{
  static int i = 1;

  return i;
}

int main()
{
  auto c = [](){return foo();};

  // The return type is deduced as `int`, and that suggests `auto`.
  static_assert(std::is_same_v<decltype(c()), int>);
}
