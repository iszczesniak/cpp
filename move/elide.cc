#include <utility>
#include <iostream>

struct A
{
  A() = default;

  // Constructors not elided, so cannot delete them.
  // A(const A &) = delete;
  // A(A &&) = delete;
};

struct B
{
  A m_a;

  // Parameter a has to be copied or moved to m_a.  We move.
  // Constructor elision (for copying or moving from a to m_a) cannot
  // take place, because parameter a was already created by the
  // caller, and the constructor can only copy or move.
  B(A a): m_a(std::move(a))
  {
  }
};

int
main()
{
  B(A{});
}
