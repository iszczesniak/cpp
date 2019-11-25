#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B() {}

  // The copy assignment operator ------------------------------------

  // The copy assignment operator has to copy the base object of class
  // A of object b, and the string of object b.
  B & operator=(const B &b)
  {
    A::operator=(b);
    m_s = b.m_s;
    return *this;
  }

  // Above is the default implementation which we can get with:
  // B &operator=(const B &) = default;

  // The move assignment operator ------------------------------------

  // The implementation of the move assignment operator has to use the
  // std::move function to move the base object of class A of object
  // b, and the string of object b, otherwise they would be copied.
  B & operator=(B &&b)
  {
    A::operator=(std::move(b));
    m_s = std::move(b.m_s);
    return *this;
  }

  // Above is the default implementation which we can get with:
  // B &operator=(B &&) = default;
};

int
main()
{
  B b1, b2;
  b1 = b2;
  b1 = std::move(b2);
  b1 = B();
}
