#include <utility>

struct A
{
  A() = default;
  A(const A &) = default;
  A(A &&) = delete;
};

// Struct B has the move constructor that is defaulted.  The compilers
// should report an error, because that constructor is ill-formed: it
// cannot call the move constructor of the base class.  However, GCC
// implicitly undeclares that constructor.  Clang does the same, but
// reports a warning.  Since the move constructor is undeclared, the
// copy constructor is called.  I don't know why GCC and clang do it.

struct B: A
{
  B() = default;
  B(const B &) = default;
  B(B &&) = default;
};

int main()
{
  B x;
  B y(std::move(x));
}
