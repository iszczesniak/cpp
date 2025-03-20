#include <utility>

// A move-only type.  We do not have to explicitly delete the copy
// constructor, and the copy assignment operator, because they will be
// implicitly deleted, since the move constructor and the move
// assignment operator are explicitly defaulted.
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
  // A b(a); // Error: we cannot copy initialize.
  A b(std::move(a));
  // b = a; // Error: we cannot copy assign.
  b = std::move(a);
}
