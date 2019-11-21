#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  // The implementation of the move constructor would be incorrect if
  // the std::move function was not used, because then would copy, not
  // move.
  B(B &&b): A(std::move(b)), m_s(std::move(b.m_s))
  {
  }
};
