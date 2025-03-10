#include <iostream>
#include <string>

struct A
{
  A() = default;
  A(int) {}
};

template <typename... P>
struct B: P...
{
  B(const P &... p): P(p)...
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
