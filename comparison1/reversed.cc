#include <cassert>

struct A
{
  bool operator == (const A &) const = default;
};

struct B: A
{
  // using A::operator ==;

  // bool operator == (const B &b) const
  // {
  //   return static_cast<const A &>(*this) == static_cast<const A &>(b);
  // }
};

int main()
{
  assert(B() == B());
}
