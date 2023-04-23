#include <string>
#include <tuple>

std::tuple
foo()
{
  int a;
  std::string txt;
  return {a, 2.0, std::move(txt)};
}

int main()
{
  auto [a, f, s] = foo();
}
