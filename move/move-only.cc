#include <utility>

// A move-only type.
struct A
{
  A() = default;
  A(A &&) = default;
  A & operator=(A &&) = default;
};

int
main()
{
  A a;
  // A b(a); // Error: we cannot copy.
  A b(std::move(a));
}
