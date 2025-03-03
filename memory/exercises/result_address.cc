#include <utility>

std::pair<int, int>
foo()
{
  return {1, 2};
}

int main()
{
  auto p = foo();
}
