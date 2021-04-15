#include <utility>

// A move-only type.  We do not have to explicitely delete the copy
// constructor, and the copy assignment operator, because they will be
// implicitely deleted, since the move constructor and the move
// assignment operator are explicitely defaulted.
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
