#include <iostream>
#include <string>

struct A
{
  A() = default;
  A(int) {}
};

template <typename ...Args>
struct B: Args...
{
  B(const Args &...args): Args(args)...
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  B<>();
  B<A>(1);
  B<A, std::string>({}, "Hello!");
}
