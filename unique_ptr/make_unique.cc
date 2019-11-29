#include <memory>

struct A
{
};

auto
factory()
{
  return std::make_unique<A>();
}

int
main()
{
  auto p = factory();
}
