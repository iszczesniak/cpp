#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B() {}

  // The copy constructor ------------------------------------------

  // The implementation of the copy constructor has to copy the base
  // and member objects of the source object.
  B(const B &source): A(source), m_s(source.m_s)
  {
  }

  // Above is the default implementation which we can get with:
  // B(const B &) = default;

  // The move constructor ------------------------------------------

  // The implementation of the move constructor has to use the
  // std::move function to move the base and member objects of the
  // source object, otherwise they would be copied.
  B(B &&source): A(std::move(source)), m_s(std::move(source.m_s))
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
