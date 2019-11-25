#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B() {}

  // The copy constructor ------------------------------------------

  // The implementation of the copy constructor has to copy the base
  // and member objects.
  B(const B &b): A(b), m_s(b.m_s)
  {
  }

  // Above is the default implementation which we can get with:
  // B(const B &) = default;

  // The move constructor ------------------------------------------

  // The implementation of the move constructor has to use the
  // std::move function to move the base object of class A of object
  // b, and the string of object b, otherwise they would be copied.
  B(B &&b): A(std::move(b)), m_s(std::move(b.m_s))
  {
  }

  // Above is the default implementation which we can get with:
  // B(B &&) = default;
};

int
main()
{
  B b1;
  B b2(b1);
  B b3(std::move(b1));
  B b4{B()};
}
